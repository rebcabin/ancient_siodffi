;;;
;;; The RealLoad DLL implements GetProcAlist, MainDispatch, 
;;; MainDispatchCDecls, and cstring->string, which one would 
;;; use to convert 'flonums' returned by C functions into 
;;; strings Siod can deal with.
;;;
(require 'siod.scm   )
(require 'syslibs.scm)
(require 'pp.scm     )

(define (test) (load 'testload.scm) (regress))

;;
;; Some old test code
;;
;(define plist (GetProcAlist "../Victim/Debug/Victim.dll"))
;(print plist)

;(define plist (GetProcAlist (sysdir "kernel32.dll")))
;(require "pp.scm")
;(pp plist)

;(define qlist (mapcar setDispatch plist))

;(print (TestVictim0))
;(print (TestVictim3 1 2 3))
;(print (TV4 "Hello, TV4"))
;(print (TV4 'foobar))

;;;
;;; LIVE REGRESSION TESTS
;;;

(define (long-string)
  (define a (cons-array 32 'long))
  (letrec ((iter (lambda (i)
                   (cond
                    ((= i 32) (array->string a))
                    (#t       (aset a i (+              (+ i 32)
                                                 (* 256 (+ i 32))
                                          (* 256 (* 256 (+ i 32)))
                                   (* 256 (* 256 (* 256 (+ i 32))))))
                              (iter (+ i 1)))))))
    (iter 0)))

(define (test-callback)
  (iter-thunk 
    (lambda ()
      (TVcallback 3 4 (lambda (x) (* x 2))))
    100)

  (iter-monofunc 
    (lambda (i)
      (TVBinaryCallback i (+ i 1) (lambda (x y) 
        (print "first argument: ")
        (print x)
        (print "second argument: ")
        (print y))))
    10)

  (TVQuaternaryCallback 1 2 3 4
    (lambda (x y z w)
      (print x) (print " ")
      (print y) (print " ")
      (print z) (print " ")
      (print w) (print " ")
      42))

  (TVcallback 3 4 (lambda (x) (* x 2)))
  )

(define (regress)
  (print (LoadLibrary "/usr/local/bin/victim.dll"))
  (print (define z (string->array "foobar" 32)))
  (print (define w (TV5cdecl z " bazrat")))
  (print (cstring->string w))
  (define x (malloc 32))
  (free x)

  (print w)
  (print (num->cptr w))
  (print (indirect (num->cptr w)))
  (print (indirect (address-of (num->cptr w))))

  (define s "packmyboxwithliquorjugs")
  (define l (+ 1 (length s)))
  (define c (string->cstring s))
  (define a (cbytes->array c l))
  (print    (array->string a))

  (print (long-string))

  (print "Callback test: expect 24 = hex 18")
  (print "[101 iterations, btw]")
  ; (DebugBreak)
  (print (test-callback))

  )

