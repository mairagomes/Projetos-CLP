(defun insertion-sort (list)
  (if (null list)
      '()
      (insert (car list) (insertion-sort (cdr list)))))

(defun insert (x sorted)
  (cond ((null sorted) (list x))
        ((< x (car sorted)) (cons x sorted))
        (t (cons (car sorted) (insert x (cdr sorted))))))
