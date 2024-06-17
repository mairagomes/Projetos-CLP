(defun raiz (a n)
  (cond
    ((< n 0) nil)
    ((zerop n) 1)
    (t (/ (+ (raiz a (- n 1)) (/ 3 (raiz a (- n 1)))) 2))))

(defun precisao (a precision)
  (let* ((result (raiz a 10)) ; Exemplo usando n = 10 para iteração
         (formatted-result (format nil "~,10F" result))) ; Formata para 10 casas decimais
    (format t "Resultado aproximado de raiz(~A) com 10 iterações: ~A~%" a formatted-result)
    (format t "Precisão desejada: ~A casas decimais~%" precision)
    (format t "Comparação com precisão: ~A~%" (string= (subseq formatted-result 0 (1+ precision))
                                                      (subseq (format nil "~,10F" (sqrt a)) 0 (1+ precision))))))

(precisao 2 6) ; Testando com a raiz quadrada de 2 e precisão desejada de 6 casas decimais
