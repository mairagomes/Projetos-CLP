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
