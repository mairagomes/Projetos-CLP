% Predicado para gerar listas de números aleatórios
generate_list(0, []).
generate_list(N, [H|T]) :-
    N > 0,
    random(1, 10000, H),
    N1 is N - 1,
    generate_list(N1, T).

% Predicado para medir o tempo de execução
time_execution(Goal, Time) :-
    get_time(T1),
    call(Goal),
    get_time(T2),
    Time is T2 - T1.

% Predicado para ordenar uma lista com merge sort
split([], [], []).
split([X], [X], []).
split([X,Y|T], [X|T1], [Y|T2]) :- split(T, T1, T2).

merge([], L, L).
merge(L, [], L).
merge([X|T1], [Y|T2], [X|T]) :- X =< Y, merge(T1, [Y|T2], T).
merge([X|T1], [Y|T2], [Y|T]) :- X > Y, merge([X|T1], T2, T).

merge_sort([], []).
merge_sort([X], [X]).
merge_sort(List, Sorted) :-
    split(List, L1, L2),
    merge_sort(L1, Sorted1),
    merge_sort(L2, Sorted2),
    merge(Sorted1, Sorted2, Sorted).

% Predicado para testar o tempo médio de execução
test_sorting_time(Size, AverageTime) :-
    findall(Time,
        (between(1, 10, _),
        generate_list(Size, List),
        time_execution(merge_sort(List, _), Time)),
    Times),
    sumlist(Times, TotalTime),
    length(Times, Count),
    AverageTime is TotalTime / Count.

% Predicado principal para testar diferentes tamanhos de lista
test_all :-
    Sizes = [10, 100, 1000, 10000],
    maplist(test_sorting_time, Sizes, AverageTimes),
    maplist(format('~d elementos: ~2f segundos~n'), Sizes, AverageTimes).

% Executar o teste principal
:- test_all.
