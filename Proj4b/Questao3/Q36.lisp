(defun serieG ()
  (loop for n from 1
        do (let ((start-time (get-internal-real-time)))
             (handler-case
                 (serieG n)
               (error (condition)
                 (format t "Erro ao calcular serieG(~d): ~a~%" n condition)))
             (let ((end-time (get-internal-real-time))
                   (elapsed-seconds (/ (- end-time start-time) internal-time-units-per-second)))
               (format t "n = ~d, Tempo decorrido: ~f segundos~%" n elapsed-seconds)
               (when (> elapsed-seconds 60)
                 (format t "Tempo excedeu 1 minuto para n = ~d. Interrompendo o teste.~%" n)
                 (return)))))
  (format t "Teste concluído. Todas as iterações foram executadas em menos de 1 minuto.~%"))
