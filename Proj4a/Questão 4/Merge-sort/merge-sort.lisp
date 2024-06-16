(defun merge-sort (list)
  (if (or (null list) (null (cdr list)))
      list
      (let* ((mid (/ (length list) 2))
             (left (subseq list 0 mid))
             (right (subseq list mid)))
        (merge (merge-sort left) (merge-sort right)))))

(defun merge (left right)
  (cond ((null left) right)
        ((null right) left)
        ((<= (car left) (car right))
         (cons (car left) (merge (cdr left) right)))
        (t
         (cons (car right) (merge left (cdr right))))))

(defun generate-random-list (n)
  "Gera uma lista de comprimento n com números aleatórios"
  (loop for i from 1 to n collect (random 10000)))

(defun time-sort (sort-fn list)
  "Mede o tempo que a função sort-fn leva para ordenar a lista"
  (let ((start-time (get-internal-real-time)))
    (funcall sort-fn list)
    (/ (- (get-internal-real-time) start-time) internal-time-units-per-second)))

(defun average-time (sort-fn list-size trials)
  "Calcula o tempo médio para ordenar listas de tamanho list-size usando sort-fn"
  (let ((total-time 0.0))
    (dotimes (i trials)
      (let ((list (generate-random-list list-size)))
        (setf total-time (+ total-time (time-sort sort-fn list)))))
    (/ total-time trials)))

(defun test-sort-times ()
  "Testa e imprime os tempos médios para diferentes tamanhos de listas"
  (let ((sizes '(10 100 1000 10000 100000))
        (trials 10))
    (dolist (size sizes)
      (format t "Tempo médio para ordenar listas de tamanho ~D: ~F segundos~%" 
              size (average-time #'merge-sort size trials)))))

(test-sort-times)
