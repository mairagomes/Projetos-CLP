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
