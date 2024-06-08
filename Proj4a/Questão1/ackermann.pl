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
