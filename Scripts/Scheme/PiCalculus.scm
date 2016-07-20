;;;
;;; The following is taken right off page 21 of Robin Milner's
;;; "Polyadic Pi Calculus--A Tutorial".  It's a direct transcription
;;; of his BNF in a recursive-descent parser.
;;;
;;; Here's the original BNF: 
;;;
;;; Normal processes:   N ::= a.A | 0 | M + N
;;;        Processes:   P ::= N | P "|" Q | !P | (nu x)P
;;;     Abstractions:   F ::= P | (lambda x)F | (nu x)F
;;;      Concretions:   C ::= P | [x]C | (nu x)C
;;;           Agents:   A ::= F | C
;;;           Action:   a ::= name
;;;           Vector:   x ::= vector of names with arity "|x|"
;;;
;;; Here's the translation:
;;;
;;; (normal-process N) ::= `(,dot action agent) | (zero) | `(,plus normal-process normal-process)

(require 'siod.scm)
(require 'fm.scm)

(define (assert bool msg)
  (if (not bool)
      (begin
        (mb msg "Pi Calculus syntax error")
        (error msg))))


(define (assert-length len lyst msg)
  (assert (= (length lyst) len) msg))


(define (zero)
  (print "In Zero (done).")
  'zero)


(define (plus N M)
  (prin1 "In plus: ")
  (prin1 N)
  (prin1 ", ")
  (print M)
  'plus)


(define (dot a A)
  (prin1 "In dot: ")
  (prin1 a)
  (prin1 ", ")
  (print A)
  'dot)


(define (action a)
  (prin1 "In action: ")
  (print a)
  a)


(define (process P)
  (prin1 "In process: ")
  (print P)
  P)


(define (abstraction F)
  (prin1 "In abstraction: ")
  (print F)
  (assert (list? F) "An abstraction must be either a process, a lambda construct, or a nu of an abstraction")

  (let ((function (car F))
        (args     (cdr F)))

    (cond

     ((= function 'process)
      (assert-length 1 args "A process takes a single argument")
      (process (car args))
      )

     ((list? function)
      (let ((inner-function (car function))
            (inner-func-arg (cdr function)))
        (assert (symbol? inner-func-arg)
                "a lambda or a nu must take a vector argument")
        (cond

         ((= inner-function 'lambda))

         ((= inner-function 'nu))

         (t "Unknown argument to abstraction"))))

     (t "Unknown argument to abstraction")))
  F)


(define (concretion C)
  (prin1 "In concretion: ")
  (print C)
  C)

  
(define (agent A)
  (prin1 "In agent: ")
  (print A)
  (assert (list? A) "An action must either be a concretion or an abstraction")
  (let ((function (car A))
        (arg      (cdr A)))
    (cond
     ((= function 'abstraction)
      (assert-length 1 arg "an abstraction must have a single argument")
      (abstraction (car arg)))
     ((= function 'concretion)
      (assert-length 1 arg "an concretion must have a single argument")
      (concretion (car arg)))
     (t (assert nil "Unknown argument to agent")))))
  


(define (normal-process N)
  (prin1 "In normal-process: ")
  (print N)
  (assert (list? N) "normal-process must be either a dot, zero, or plus")
  (let ((function (car N))
        (args     (cdr N)))
    (cond

     ((= function 'dot)
      (assert-length 2 args "dot requires an action and an Agent")
      (dot (action (car args))
           (agent  (cadr args))))

     ((= function 'zero)
      (assert-length 0 args "zero does not take arguments")
      (zero))

     ((= function 'plus)
      (assert-length 2 args "plus requires two Normal processes")
      (plus
       (normal-process (car args))
       (normal-process (cadr args))))

     (t (assert nil "Unknown argument to normal-process")))))


(define (test)
  (load "picalculus.scm")
  (normal-process '(plus (zero) (zero)))
  (normal-process '(dot zed (abstraction (process Agent99))))
  )
