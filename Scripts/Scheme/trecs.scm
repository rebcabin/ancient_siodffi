(define (clone item)
  (if (pair? item)
      (begin
        (cons (clone (car item))
              (clone (cdr item))))
      item))
