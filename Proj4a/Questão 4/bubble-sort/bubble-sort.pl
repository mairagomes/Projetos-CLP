% Gerar uma lista de N inteiros aleatórios
generate_list(N, List) :-
    length(List, N),
    maplist(random_between(0, 1000), List).

% Gerar várias listas de diferentes tamanhos
generate_multiple_lists([], []).
generate_multiple_lists([Size | Sizes], [List | Lists]) :-
    generate_list(Size, List),
    generate_multiple_lists(Sizes, Lists).

% Implementação do Bubble Sort
swap([X, Y | Rest], [Y, X | Rest]) :- X > Y.
swap([Z | Rest], [Z | Rest1]) :- swap(Rest, Rest1).

bubble_sort(List, Sorted) :- 
    swap(List, List1), !, 
    bubble_sort(List1, Sorted).
bubble_sort(Sorted, Sorted).

% Medir o tempo gasto para ordenar uma lista
time_sort(List, Time) :-
    statistics(walltime, [Start, _]),
    bubble_sort(List, _),
    statistics(walltime, [End, _]),
    Time is End - Start.

% Medir os tempos para várias listas
measure_times([], []).
measure_times([List | Lists], [Time | Times]) :-
    time_sort(List, Time),
    measure_times(Lists, Times).

% Procedimento principal para gerar listas, medir tempos e imprimir resultados
main :-
    Sizes = [10, 100, 1000, 2000, 5000],  % Ajuste os tamanhos conforme necessário
    generate_multiple_lists(Sizes, Lists),
    measure_times(Lists, Times),
    writeln('Tamanhos das listas: '), writeln(Sizes),
    writeln('Tempos de ordenação (ms): '), writeln(Times).
