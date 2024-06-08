partition([], _, [], []).
partition([H|T], Pivot, [H|L], G) :- H =< Pivot, partition(T, Pivot, L, G).
partition([H|T], Pivot, L, [H|G]) :- H > Pivot, partition(T, Pivot, L, G).

quick_sort([], []).
quick_sort([H|T], Sorted) :-
    partition(T, H, L, G),
    quick_sort(L, SortedL),
    quick_sort(G, SortedG),
    append(SortedL, [H|SortedG], Sorted).
