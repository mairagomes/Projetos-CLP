insert(X, [], [X]).
insert(X, [Y|T], [X,Y|T]) :- X =< Y.
insert(X, [Y|T], [Y|NT]) :- X > Y, insert(X, T, NT).

insertion_sort([], []).
insertion_sort([H|T], Sorted) :-
    insertion_sort(T, ST),
    insert(H, ST, Sorted).
