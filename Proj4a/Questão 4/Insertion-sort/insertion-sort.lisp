;; Definição das funções de ordenação por inserção
(defun insertion-sort (list)
  (if (null list)
      '()
      (insert (car list) (insertion-sort (cdr list)))))

(defun insert (x sorted)
  (cond ((null sorted) (list x))
        ((< x (car sorted)) (cons x sorted))
        (t (cons (car sorted) (insert x (cdr sorted))))))

;; Função para gerar listas aleatórias
(defun generate-random-list (n)
  (loop repeat n collect (random n)))

;; Função para medir o tempo médio de ordenação
(defun measure-sorting-time (sorting-func list-length num-trials)
  (let ((total-time 0))
    (dotimes (_ num-trials)
      (let ((random-list (generate-random-list list-length)))
        (let* ((start-time (get-internal-real-time))
               (sorted-list (funcall sorting-func random-list))
               (end-time (get-internal-real-time)))
          (incf total-time (- end-time start-time)))))
    (/ total-time num-trials)))

;; Teste de desempenho para diferentes tamanhos de listas
(defun test-sorting-performance ()
  (let* ((sizes '(10 100 1000 10000 100000)) ;; Adicione mais tamanhos se necessário
         (num-trials 10) ;; Número de execuções para obter tempo médio
         (insertion-times (mapcar (lambda (size)
                                    (measure-sorting-time #'insertion-sort size num-trials))
                                  sizes)))
    (format t "Tamanhos das listas: ~A~%" sizes)
    (format t "Tempos médios para ordenação por inserção: ~A~%" insertion-times)))

;; Executar o teste de desempenho
(test-sorting-performance)
