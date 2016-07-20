;;; ================================================================ ;;;
;;; Test DCOM support in SIOD                                        ;;;
;;; ================================================================ ;;;

(require    "dcom.scm")              ; MUST HAVE infrastructure

(define (test) (load 'testdcom.scm)) ; shortcut for repetition

;;; ================================================================ ;;;
;;; Test the GUID data type and its conversions                      ;;;
;;; ================================================================ ;;;

(define t1-string "{11223344-1111-2222-3333-444455556666}")
(define g1 (string->guid t1-string))
(define t2-string (guid->string g1))
(define test1 (equal? t1-string t2-string))
(print test1)

(define g2 (new-guid))
(print g2)

(define x1 (string->guid (guid->string g2)))
(define x2 (string->guid (guid->string g2)))
(define test2 (equal? x1 x2))
(print test2)

;;; ================================================================ ;;;
;;; Create an in-proc test object and get some of its interfaces     ;;;
;;; ================================================================ ;;;

(define com-test-cls  (string->guid "{9E214850-E8CF-11D0-9506-444553540000}"))
(define iCT1iid       (string->guid "{9E21484F-E8CF-11D0-9506-444553540000}"))

(print "CoInitializing...")
(print (CoInitialize))

(print "creating ComTest1 IUnknown interface...")
(define CT1unk (CoCreateInstance com-test-cls iunknown-iid CLSCTX_ALL))
(print CT1unk)

(print "querying for IComTest1 interface...")
(define CT1interface (QueryInterface CT1unk iCT1iid))
(print CT1interface)

(print "querying for IDispatch interface...")
(define CT1idispatch (QueryInterface CT1unk idispatch-iid))
(print CT1idispatch)

;;; ================================================================ ;;;
;;; Analyze & dump the object's type library                         ;;;
;;; ================================================================ ;;;

(print "getting type info count...")
(define typeinfo-count (GetTypeinfoCount CT1idispatch))
(print typeinfo-count)

(print "getting ITypeInfo...")
(define CT1itypeinfo (GetTypeinfo CT1idispatch 0 0))
(print CT1itypeinfo)

(print "getting TYPEATTR...")
(define CT1typeattrs (GetTypeattr CT1itypeinfo))
(print CT1typeattrs)

(print "getting CFuncs...")
(define CT1cfuncs (GetTypeattrCfuncs CT1typeattrs))
(print "CT1cfuncs:")
(print CT1cfuncs)

(print "x bound to the list of functions -- print if desired")
(define x (listfuncs CT1idispatch))

;;;
;;; We don't know how to get any VARDESCs into the type library
;;;

(define CT1cvars (GetTypeattrCvars CT1typeattrs))
(print "CT1cvars:")
(print CT1cvars)

(print "y bound to the list of variables")
(define y (listvars CT1idispatch))

;;;
;;; Dump out all the memids and names
;;;

;;; First, set the print mode to hexadecimal for integers
(set! **hex-mode** t)

(define (get-memid func-alist)
  (cadr (assoc 'memid func-alist)))

(define memid-list (mapcar get-memid x))

(define (get-name func-alist)
  (cadr (assoc 'Name func-alist)))

(define name-list (mapcar get-name x))

(print memid-list)
(print name-list)

;;;
;;; Call some of the functions through IDispatch 
;;;

;; ------- ------- ------- ------- ------- ------- ------- ------- -------
;; Here's what's going on in the following function.  We're making a Lisp
;; Representation for a DISPPARAMS.  It's a list.  
;; 
;; The first element of the list is a pseudo-alist of arguments.  The 
;; pseudo-alist contains type-value pairs.  It's a pseudo-alist because 
;; the 'keys' can be repeated. The keys can be repeated because they're 
;; just names of types.  
;; 
;; The second element of the DISPPARAMS list is a list of DISPIDs of the 
;; named arguments.
;;
;; The third element of the DISPPARAMS list is a count of the number of 
;; elements in the arguments alist.  
;;
;; TODO: maybe we should change the implementation to compute this 
;; automatically.  
;;
;; The fourth element in the DISPPARAMS list
;; is a count of the number of elements in the NamedArgs list.
;; ------- ------- ------- ------- ------- ------- ------- ------- -------

(define (MakeVarPropInput type value);; Make a DISPPARAMs
  (list (list (list type value))        ; alist for rgvarg
        (list DISPID_PROPERTYPUT)       ; list for rgdispidNamedArgs
        1                               ; num for cArgs
        1                               ; num for cNamedArgs
        ))

(define the-shortFoo 
  (Invoke CT1idispatch 
          2                             ; dispidMember
          DISPATCH_PROPERTYPUT          ; wFlags
          (MakeVarPropInput 'short 13)  ; dispparams
          ))

;;;
;;; Print the results
;;;

(print "HResult and return value from PROPERTYPUT on CT1...")
(print errobj)
(print the-shortFoo)

(print "HResult and return value from PROPERTYGET on CT1...")
(define the-short (Invoke CT1idispatch 2 DISPATCH_PROPERTYGET ()))
(print errobj)
(print the-short)

;;
;; Here's another function that creates a dispparams
;;

;;; ================================================================ ;;;
;;; Vestigial dispparams support                                     ;;;
;;;   will eventually migrate to dcom.scm                            ;;;
;;; ================================================================ ;;;

(define (bstr-ref)   '(BSTR-REF   ()))
(define (short-ref)  '(short-ref  ()))
(define (long-ref)   '(long-ref   ()))
(define (float-ref)  '(float-ref  ()))
(define (double-ref) '(double-ref ()))

(define (dispparams-multi ref-maker n)
  (list (make-list n (ref-maker))
        ()
        n
        0
        ))

(define the-hello (Invoke CT1idispatch 
                          1 
                          DISPATCH_METHOD 
                          (dispparams-multi bstr-ref 1)
                          ))
(print the-hello) 

;;; ================================================================ ;;;
;;; Out-of-proc objects                                              ;;;
;;; ================================================================ ;;;

(print "Create an out-of-proc object...")

(print "creating ComTest2 IUnknown interface...")
(define CT2unk 
  (CoCreateInstance 
   (string->guid "{105BB1D2-EFDD-11D0-9506-D74222CE0464}") 
   iunknown-iid 
   CLSCTX_ALL))
(print CT2unk)

(print "querying for IComTest2 interface...")
(define CT2interface
  (QueryInterface
   CT2unk
   (string->guid "{105BB1D1-EFDD-11D0-9506-D74222CE0464}")))
(print CT2interface)

(print "querying for IDispatch interface...")
(define CT2idispatch (QueryInterface CT2unk idispatch-iid))
(print CT2idispatch)

(print "HResult and return value from METHOD call on CT2...")
(define the-hello2 (Invoke 
                    CT2idispatch 
                    1 
                    DISPATCH_METHOD 
                    (dispparams-multi bstr-ref 1)
                    ))
(print errobj)
(print the-hello2) 

(print "HResult and return value from another METHOD call on CT2...")
(define more-hellos (Invoke
                     CT2idispatch
                     2
                     DISPATCH_METHOD
                     (dispparams-multi bstr-ref 4)
                     ))
(print errobj)
(pp more-hellos)

(print "more from CT2...")
(define example-short (Invoke
                       CT2idispatch
                       3
                       DISPATCH_METHOD
                       (dispparams-multi short-ref 1)
                       ))
(print errobj)
(print example-short)

;;; ================================================================ ;;;
;;; Release interfaces via garbage collection                        ;;;
;;; ================================================================ ;;;

(set! CT1unk       nil)
(set! CT1itypeinfo nil)
(set! CT1interface nil)
(set! CT1idispatch nil)

(set! CT2unk       nil)
(set! CT2interface nil)
(set! CT2idispatch nil)

(gc)

;;;;
;;;; The following test is deprecated because Bug636 and Bug788
;;;; (old viper bugs) are long gone.
;;;; 
;;;; ;;;
;;;; ;;; Create the Bug636 object
;;;; ;;;
;;;; 
;;;; (define (CoCreateDispInstance clsid-string)
;;;;   (CoCreateInstance
;;;;    (string->guid clsid-string)
;;;;    idispatch-iid
;;;;    CLSCTX_ALL))
;;;; 
;;;; (define BugDisp
;;;;   (CoCreateDispInstance "{25DFAAB7-DA98-11D0-9BE5-0000F877307E}"))
;;;; 
;;;; (print BugDisp)
;;;; 
;;;; (print "Big, pretty list of functions from BugDisp")
;;;; (define x (listfuncs BugDisp))
;;;; '(pp x) 
;;;; 
;;;; (define hello-again (Invoke BugDisp 1 DISPATCH_METHOD
;;;;                (dispparams-multi bstr-ref 1)))
;;;; 
;;;; (pp hello-again)
;;;; 
;;;; (define secvars (Invoke BugDisp
;;;;                         3
;;;;                         DISPATCH_METHOD
;;;;                         (dispparams-multi bstr-ref 4)
;;;;                         ))
;;;; 
;;;; (print "ISecurityProperty strings from BugDisp")
;;;; (pp secvars)
;;;; 
;;;; (define YasDisp
;;;;   (CoCreateDispInstance "{74320703-E1BC-11D0-BCA4-0000F877307E}"))
;;;; 
;;;; '(define x (listfuncs YasDisp))
;;;; '(pp x)
;;;; 
;;;; (print "YAS' ISecProp strings")
;;;; (pp (Invoke YasDisp 1 DISPATCH_METHOD
;;;;        (dispparams-multi bstr-ref 4)))

