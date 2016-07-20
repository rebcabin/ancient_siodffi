;;; (print "This is test.scm")

(define (ftest thunk expected-value)
  (equal? (thunk) expected-value))

