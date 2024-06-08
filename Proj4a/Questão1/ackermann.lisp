(defun ackermann (m n)
  (cond ((= m 0) (+ n 1))
        ((and (> m 0) (= n 0)) (ackermann (- m 1) 1))
        (t (ackermann (- m 1) (ackermann m (- n 1))))))

(defun calcular-ackermann ()
  (let ((start-time (get-internal-real-time)))
    (loop for m from 0 to 3 do ; Mantenha M pequeno devido ao crescimento rápido
          (loop for n from 0 to 10 do ; Ajuste N conforme necessário
                (let ((current-time (get-internal-real-time)))
                  (when (>= (/ (- current-time start-time) internal-time-units-per-second) 60)
                    (return (format t "Tempo limite atingido.~%"))))
                (let ((resultado (ackermann m n)))
                  (format t "Ackermann(~d, ~d) = ~d~%" m n resultado))))))
