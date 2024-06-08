% Função de Ackermann
ackermann(0, N, Resultado) :- Resultado is N + 1.
ackermann(M, 0, Resultado) :-
    M > 0,
    M1 is M - 1,
    ackermann(M1, 1, Resultado).
ackermann(M, N, Resultado) :-
    M > 0,
    N > 0,
    M1 is M - 1,
    N1 is N - 1,
    ackermann(M, N1, ResultadoTemp),
    ackermann(M1, ResultadoTemp, Resultado).

% Calcular todos os valores possíveis em menos de 1 minuto
calcular_ackermann :-
    statistics(runtime, [T0|_]),
    between(0, 3, M), % Mantenha M pequeno devido ao crescimento rápido
    between(0, 10, N), % Ajuste N conforme necessário
    statistics(runtime, [T1|_]),
    (T1 - T0) < 60000,
    ackermann(M, N, Resultado),
    format('Ackermann(~d, ~d) = ~d~n', [M, N, Resultado]),
    fail.
calcular_ackermann.
