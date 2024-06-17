(defun fatorial (n)
  (cond
    ((< n 0) nil)
    ((zerop n) 1)
    (t (* n (fatorial (- n 1))))))

(defun potencia (b e)
  (cond
    ((< e 0) nil)
    ((zerop e) 1)
    (t (* b (potencia b (- e 1))))))

(defun ex (x n)
  (cond
    ((< n 0) nil)
    ((zerop n) 1)
    (t (+ (/ (potencia x n) (fatorial n))
          (ex x (- n 1))))))

;; Exemplo de uso
(print (ex 1.0 10)) ; Aproximação de e^1.0 com n = 10
