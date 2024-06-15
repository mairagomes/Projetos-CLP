(defun bubble-sort (list)
  (let ((swapped t))
    (loop while swapped do
      (setf swapped nil)
      (setf list
            (loop for x on list
                  unless (null (cdr x))
                  do (when (> (car x) (cadr x))
                       (rotatef (car x) (cadr x))
                       (setf swapped t))
                  collect (car x) into sorted
                  finally (return (nconc sorted (cdr x))))))
    list))

(defun generate-random-list (length)
  (loop repeat length collect (random 10000)))

(defun measure-time (function &rest args)
  (let ((start-time (get-internal-real-time)))
    (apply function args)
    (/ (- (get-internal-real-time) start-time) internal-time-units-per-second)))

(defun average (numbers)
  (/ (reduce #'+ numbers) (length numbers)))

(defun benchmark-sorting (lengths iterations)
  (loop for length in lengths
        collect
        (let ((times (loop repeat iterations
                           collect (measure-time #'bubble-sort (generate-random-list length)))))
          (cons length (average times)))))

(let ((lengths '(10 100 1000 5000 10000))
      (iterations 10))
  (benchmark-sorting lengths iterations))
