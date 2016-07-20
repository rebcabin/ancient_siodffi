;;;
;;; super-dumb pretty print for SIOD only
;;;

(define (pp thing . fileout)

  (define (atom? x) (not (pair? x)))

  (define (list? x)
    (cond
     ((null? x)  t)
     ((atom? x) ())
     (t (list? (cdr x)))))

  (define (flat? lyst)
    (cond
     ((null? lyst) t)
     (t (and (atom? (car lyst)) (flat? (cdr lyst))))))

  (define blank (intern ""))
  (define space (intern " "))
  (define lpar  (intern "("))
  (define rpar  (intern ")"))

  (define (spaces n)
    (define (spaces-x i mac)
      (if (= i mac) 
          t 
          (begin 
            (prin1 space (car fileout)) 
            (spaces-x (+ 1 i) mac))))
    (spaces-x 0 n))

  (define (newline) (print blank (car fileout)))

  (define (pp-x indentation indent-first? thing-x)

    (define (prepare-line)
      (if indent-first? (begin (newline) (spaces indentation))))

    (cond
     ((list? thing-x)
      (if (flat? thing-x)
	  (begin
	    (prepare-line)
	    (prin1 thing-x (car fileout)))
	  (begin
	    (prepare-line)
	    (prin1 lpar (car fileout))
	    (pp-x (+ 1 indentation) nil (car thing-x))
	    (mapcar (lambda (x)
		      (pp-x (+ 1 indentation) t x))
		    (cdr thing-x))
	    (prin1 rpar (car fileout)))))
     (t (prepare-line)
	(prin1 thing-x (car fileout)))))

   (pp-x 0 t thing)
   (newline)

  ())
	  
