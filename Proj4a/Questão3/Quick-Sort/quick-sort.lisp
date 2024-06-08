(defun quicksort (list)
  (if (or (null list) (null (cdr list)))
      list
      (let* ((pivot (car list))
             (rest (cdr list))
             (smaller (remove-if-not (lambda (x) (<= x pivot)) rest))
             (larger (remove-if (lambda (x) (<= x pivot)) rest)))
        (nconc (quicksort smaller) (list pivot) (quicksort larger)))))
