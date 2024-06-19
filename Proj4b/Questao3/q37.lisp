(defun fib (n)
 (cond
 ((< n 1) nil)
 ((< n 3) 1)
 (T (+ (fib (- n 1)) (fib (- n 2))))
 )
)

(defun prod (n)
 (cond
 ((< n 1) nil)
 ((< n 3) 1)
 (T (* (fib n)(prod (- n 1))))
 )
)

(defun tempo (n)
  (let ((start-time (get-internal-real-time)))
    (produto n)
    (/ (- (get-internal-real-time) start-time) internal-time-units-per-second)))

(defun encontrar-max-n (max-tempo)
  (loop for n from 1
        while (< (medir-tempo n) max-tempo)
        finally (return (1- n))))
