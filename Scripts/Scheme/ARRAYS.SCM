(define dim1 10)

(define (fill-array dim a)
  (letrec ((iter (lambda (i)
                   (if (= i dim) a
                     (begin
                      (aset a (- dim i 1) i)
                      (iter (+ i 1)))))))
          (print (iter 0))))

(prin1 "double array: ") (fill-array dim1 (cons-array dim1 'double))
(prin1 "long   array: ") (fill-array dim1 (cons-array dim1 'long))
(prin1 "byte   array: ") (fill-array dim1 (cons-array dim1 'byte))
(prin1 "lisp   array: ") (fill-array dim1 (cons-array dim1 'lisp))
(prin1 "string array: ") (fill-array dim1 (cons-array dim1 'string))

