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
