expr --> term,rexpr.
rexpr --> [+],expr, {write('y=POP(); x=POP(); PUSH(x ADD y)'),nl}.
rexpr --> [-],expr, {write('y=POP(); x=POP(); PUSH(x SUB y)'),nl}.
rexpr --> [].
term--> factor,rterm.
rterm--> [*],term, {write('y=POP(); x=POP(); PUSH(x MUL y)'),nl}.
rterm--> [/],term, {write('y=POP(); x=POP(); PUSH(x DIV y)'),nl}.
rterm--> [].
factor --> [a],{write('PUSH('),write(a), write(')'), nl}.
factor --> [b],{write('PUSH('),write(b), write(')'), nl}.
factor --> [c],{write('PUSH('),write(c), write(')'), nl}.
factor --> [d],{write('PUSH('),write(d), write(')'), nl}.
factor --> [e],{write('PUSH('),write(e), write(')'), nl}.
factor --> ['('], expr, [')'].
