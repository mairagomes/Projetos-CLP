% Predicado para gerar uma lista de tamanho N com números aleatórios
generate_list(N, List) :-
    length(List, N),
    maplist(random_between(1, 1000), List). % números aleatórios entre 1 e 1000

% Predicado para gerar listas para diferentes tamanhos até um máximo especificado
generate_lists(MaxSize, Lists) :-
    findall(List, (between(1, MaxSize, N), generate_list(N, List)), Lists).

% insertion sort implementation
insert(X, [], [X]).
insert(X, [Y|T], [X,Y|T]) :- X =< Y.
insert(X, [Y|T], [Y|NT]) :- X > Y, insert(X, T, NT).

insertion_sort([], []).
insertion_sort([H|T], Sorted) :-
    insertion_sort(T, ST),
    insert(H, ST, Sorted).

% Predicado para medir o tempo de execução médio do insertion_sort para uma lista
average_time_insertion_sort(List, AvgTime) :-
    statistics(runtime, _),
    insertion_sort(List, _Sorted),
    statistics(runtime, [_, Time]),
    length(List, Len),
    AvgTime is Time / Len.

% Predicado para medir o tempo de execução médio do sort embutido para uma lista
average_time_builtin_sort(List, AvgTime) :-
    statistics(runtime, _),
    sort(List, _Sorted),
    statistics(runtime, [_, Time]),
    length(List, Len),
    AvgTime is Time / Len.

% Predicado para medir o tempo médio de execução do insertion_sort para várias listas
average_times_insertion_sort(Lists, AvgTimes) :-
    maplist(average_time_insertion_sort, Lists, AvgTimes).

% Predicado para medir o tempo médio de execução do sort embutido para várias listas
average_times_builtin_sort(Lists, AvgTimes) :-
    maplist(average_time_builtin_sort, Lists, AvgTimes).

% Predicado para realizar a comparação de desempenho
compare_performance(MaxSize) :-
    generate_lists(MaxSize, Lists),
    average_times_insertion_sort(Lists, AvgTimesInsertion),
    average_times_builtin_sort(Lists, AvgTimesBuiltIn),
    write('Tamanho da lista, Insertion Sort (ms/elemento), Sort embutido (ms/elemento)'), nl,
    write_separator(80),
    print_results(Lists, AvgTimesInsertion, AvgTimesBuiltIn, 1).

% Predicado auxiliar para imprimir resultados formatados
print_results([], [], [], _).
print_results([List|RestLists], [TimeInsertion|RestInsertion], [TimeBuiltIn|RestBuiltIn], Index) :-
    length(List, Len),
    format('| ~|~`0t~d~2+ | ~|~`0t~2f~6+ | ~|~`0t~2f~6+ |~n', [Len, TimeInsertion, TimeBuiltIn]),
    NextIndex is Index + 1,
    print_results(RestLists, RestInsertion, RestBuiltIn, NextIndex).

% Predicado auxiliar para imprimir separador
write_separator(0) :- !, nl.
write_separator(N) :-
    N > 0,
    write('-'),
    N1 is N - 1,
    write_separator(N1).

% Exemplo de uso:
% ?- compare_performance(1000).

% Para visualizar os tempos médios obtidos, ajuste o limite de tamanho de lista conforme necessário.
