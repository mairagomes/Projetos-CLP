% Gera uma lista de comprimento N com números aleatórios entre 0 e Max
generate_random_list(0, _, []) :- !.
generate_random_list(N, Max, [H|T]) :-
    N > 0,
    random(0, Max, H),
    N1 is N - 1,
    generate_random_list(N1, Max, T).

% Partição para o Quick Sort
partition([], _, [], []).
partition([H|T], Pivot, [H|L], G) :- H =< Pivot, partition(T, Pivot, L, G).
partition([H|T], Pivot, L, [H|G]) :- H > Pivot, partition(T, Pivot, L, G).

% Implementação do Quick Sort
quick_sort([], []).
quick_sort([H|T], Sorted) :-
    partition(T, H, L, G),
    quick_sort(L, SortedL),
    quick_sort(G, SortedG),
    append(SortedL, [H|SortedG], Sorted).

% Medição do tempo de ordenação
measure_sort_time(List, Time) :-
    statistics(runtime, [Start|_]),
    quick_sort(List, _),
    statistics(runtime, [End|_]),
    Time is End - Start.

% Função principal para gerar listas, ordenar e medir o tempo
main :-
    % Definindo tamanhos das listas
    Lengths = [10, 100, 1000, 10000, 100000],
    MaxValue = 1000000,
    findall(List, (member(L, Lengths), generate_random_list(L, MaxValue, List)), Lists),
    
    % Medindo tempo de ordenação para cada lista
    findall(Time, (member(L, Lists), measure_sort_time(L, Time)), Times),
    
    % Exibindo resultados
    format('Tamanhos das listas: ~w~n', [Lengths]),
    format('Tempos de ordenação (ms): ~w~n', [Times]).

% Executa o programa
:- main.
