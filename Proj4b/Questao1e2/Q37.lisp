(defun fibonacci (n)
 (cond
 ((< n 1) nil)
 ((< n 3) 1)
 (T (+ (fibonacci (- n 1)) (fibonacci (- n 2))))
 )
)
(defun produto (n)
 (cond
 ((< n 1) nil)
 ((< n 3) 1)
 (T (* (fibonacci n)(produto (- n 1))))
 )
)
