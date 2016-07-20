(require "siod.scm")

;;; Mini-BNF: <non-terminal>, terminal, ( and ) literal, [optional-stuff]
;;; *, +, ? as in regular expressions.
;;;
;;; <sexml> ::= (elt <element-tag> [(attrs <attr-alist>)]
;;;                                [(behaviors <behavior-alist>)]
;;;                                [<nested-elements>]
;;;                                [<element-text>])
;;;
;;; <element-tag ::= ordinary scheme symbol
;;;
;;; <attr-alist> ::= (<attr-name> <attr-value>) *
;;;
;;; <attr-name> ::= ordinary scheme symbol
;;;
;;; <attr-value> ::= lisp object, which will be stringified if not a string
;;;
;;; behavior structure completely analogous to attr structure
;;;
;;; <element-text> ::= lisp-string-object
;;;
;;; <nested-elements> ::= <sexml> *
;;;

(define (pick-tagged-alist lyst tag)
  (cond
   ((null? lyst) '())
   ((atom  lyst)  '())
   ((atom (car lyst)) '())
   ((eq? (caar lyst) tag) (cdar lyst))
   (#t (pick-tagged-alist (cdr lyst) tag))))

(define (parse-attfood rest)
  (pick-tagged-alist rest 'attrs))

(define (parse-behfood rest)
  (pick-tagged-alist rest 'behaviors))

(define (parse-elements lyst)
  (cond
   ((null? lyst) '())
   ((atom  lyst)  '())
   ((atom (car lyst)) '())
   ((eq? (caar lyst) 'elt)
    (cons (car lyst)
          (parse-elements (cdr lyst))))
   (#t (parse-elements (cdr lyst)))))

(define (leftovers rest)
  (cond
   ((null? rest) '())
   ((atom  rest) '())
   ((atom (car rest)) (tostring (car rest)))
   (#t (leftovers (cdr rest)))))

(define (attr-string thing indentation nl?)
  (cond
   ((null? thing) "")
   ('else
    (let ((attr-name (car  thing))
          (attr-valu (cadr thing)))
      (string-append
       (if nl? (newline-string) " ")
       (if nl? (string indentation " ") "")
       (tostring attr-name)
       "=\""
       (tostring attr-valu)
       "\"")))))

(define (attrs-list lyst indentation nl?)
  (mapcar (lambda (thing) (attr-string thing indentation nl?))
          lyst))

(define (sexml sexpr indentation nlAttrs?)
  (cond
   ((null? sexpr) #t)
   ((atom  sexpr) '())
   (#t (let* ((elt      (cadr sexpr))
              (sind     (string indentation " "))
              (ind-incr 2)
              (ind2     (+ indentation ind-incr))
              (sind2    (string ind2 " "))
              (selt     (tostring elt))
              (attfood  (parse-attfood (cddr sexpr)))
              (attrs    (attrs-list attfood ind2 nlAttrs?))
              (atts     (apply string-append attrs))
              (behfood  (parse-behfood (cddr sexpr)))
              (nestfood (parse-elements (cddr sexpr)))
              (elt-text (leftovers (cddr sexpr)))
              (nl       (newline-string))
              (guts?    (or nestfood elt-text)))
         (string-append
          sind  "<" selt
          atts
          (if guts? (string-append ">" nl) "")
          (if elt-text (string-append sind2 elt-text nl) "")
          (if nestfood
              (apply
               string-append
               (mapcar
                (lambda (food) (sexml food ind2 nlAttrs?))
                nestfood))
              "")
          (if guts?
              (string-append sind "</" selt ">" nl)
              (string-append "/>" nl))
          )))))

;;; Here's what we want to produce
; <module name="ContextTestingModule">
;   <schedule name="ContextTest">
;     <header>
;       <portlist>
;         <port name="pA"/>   <port name="pB"/>   <port name="pC"/>
;         <port name="pD"/>   <port name="pE"/>
;       </portlist>
;       <msglist>
;         <msg name="mM" />   <msg name="mN" />   <msg name="mO" />
;         <msg name="mP1"/>   <msg name="mQ" />
;       </msglist>
;     </header>
;     <independent ctxt="Fred">  <!-- CONTEXT DEFINITION -->
;       <sequence ctxt="Ralph">  <!-- CONTEXT DEFINITION -->
;         <action port="pA" msg="mM"  type="passive"/>
;         <action port="pB" msg="mN"  type="active" />
;         <action port="pB" msg="mN"  type="active" />
;         <action port="pC" msg="mO"  type="passive"/>
;       </sequence>
;       <sequence>
;         <action port="pD" msg="mP1" type="passive"/>
;         <ctxt   name="Fred"/>  <!-- CONTEXT REFERENCE -->
;         <action port="pE" msg="mQ"  type="active" />
;       </sequence>
;     </independent>
;   </schedule>
; </module>

(define m1
  '(elt module (attrs (name ContextTestingModule))
        (elt schedule (attrs (name ContextTest))
             (elt header
                  (elt portlist
                       (elt port (attrs (name pA)))
                       (elt port (attrs (name pB)))
                       (elt port (attrs (name pC)))
                       (elt port (attrs (name pD)))
                       (elt port (attrs (name pE))))
                  (elt msglist
                       (elt msg  (attrs (name mM)))
                       (elt msg  (attrs (name mN)))
                       (elt msg  (attrs (name mO)))
                       (elt msg  (attrs (name mP1)))
                       (elt msg  (attrs (name mQ)))))
             (elt independent (attrs (ctxt Fred))
                  (elt sequence (attrs (ctxt Ralph))
                       (elt action (attrs (port pA) (msg mM) (type passive)))
                       (elt action (attrs (port pB) (msg mN) (type active )))
                       (elt action (attrs (port pB) (msg mN) (type active )))
                       (elt action (attrs (port pC) (msg mO) (type passive))))
                  (elt sequence
                       (elt action (attrs (port pD) (msg mP1) (type passive)))
                       (elt ctxt (attrs (name Fred)))
                       (elt action (attrs (port pE) (msg mQ) (type active))))))))

(define (test)
  (load "sexml.scm")
  '(define w0
    (write-string
     (sexml '(elt fooby (attrs (baz rat)
                                        (bar qux)
                                        (frob nitz))
                           (elt boofer)
                           "bazrat-element-text") 0 #t)))
  (define w1
    (write-string
     (sexml m1 0 #f)))
  'done)

(define (newline-string) "\n")

(define (indent line indentation)
  (string-append
   (string indentation)
   line
   (newline-string)))


