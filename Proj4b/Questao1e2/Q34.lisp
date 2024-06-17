(defun seriePI (n)
 (cond
   ((< n 1) nil)
   ((eql n 1) 4)
   ((eql (mod n 2) 0) (- (seriePI (- n 1)) (/ 4 (- (* n 2) 1))))
   (t (+ (seriePI (- n 1)) (/ 4 (- (* n 2) 1))))
 ))

;; Exemplo de uso para encontrar o número n para 15 casas decimais
(defun encontrar-n (precisao)
  (do ((n 1 (+ n 1))
       (pi-approx (seriePI 1) (seriePI n))
       (pi-exato (* 4.0 (atan 1.0))))
      ((<= (abs (- pi-approx pi-exato)) precisao) n)))
