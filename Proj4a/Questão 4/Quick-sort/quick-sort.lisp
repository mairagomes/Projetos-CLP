(defun quicksort (list)
  (if (or (null list) (null (cdr list)))
      list
      (let* ((pivot (car list))
             (rest (cdr list))
             (smaller (remove-if-not (lambda (x) (<= x pivot)) rest))
             (larger (remove-if (lambda (x) (<= x pivot)) rest)))
        (nconc (quicksort smaller) (list pivot) (quicksort larger)))))

(defun generate-random-list (size)
  (loop for i from 1 to size collect (random size)))

(defun measure-sorting-time (size num-trials)
  (let ((total-time 0.0))
    (dotimes (i num-trials)
      (let ((list (generate-random-list size)))
        (let ((start-time (get-internal-real-time)))
          (quicksort list)
          (setq total-time (+ total-time
                              (/ (- (get-internal-real-time) start-time)
                                 internal-time-units-per-second))))))
    (/ total-time num-trials)))

(defun main ()
  (let ((sizes '(10 100 1000 10000 100000))
        (num-trials 10))
    (dolist (size sizes)
      (format t "Average sorting time for size ~A: ~A seconds~%"
              size (measure-sorting-time size num-trials)))))

(main)
