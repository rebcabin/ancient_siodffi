(define (enum lyst start . scope)

  (define bind-enum set-symbol-value!)

  (define (scoped-sym sym)
    (if (null? scope)
	    sym
		(symbolconc (car scope) ':: sym)))

  (define (bind-enums syms val)
    (cond 
	  ( (null? syms) val )
	  ( t (bind-enum
	        (scoped-sym (car syms))
		    val)
		   (bind-enums (cdr syms) (+ 1 val)) )))
  ;;
  ;; (inverted index)
  ;;
  ;; reverse lookup: from number to symbol (returns
  ;; an object that you should feed to "href").
  ;;
  (define (VT-lookup syms slot)
    (let ((arr (cons-array (length syms) 'lisp)))
	  (define (vt-set syms slot2)
	    (cond
		  ( (null? syms) arr )
		  ( t (hset arr slot2 (scoped-sym (car syms)))
		      (vt-set (cdr syms) (+ 1 slot2)) )))
	  (vt-set syms slot)))

  (bind-enums lyst start)
  (VT-lookup  lyst start)
  )
