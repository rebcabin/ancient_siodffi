;;;
;;; TestVtbl.scm -- this file is idempotent
;;;

(require 'realcom.scm)

(define (test) (load 'testvtbl.scm))

(CoInitialize 0)

(define sz-cls "{9E214850-E8CF-11D0-9506-444553540000}")
(define sz-iid "{9E21484F-E8CF-11D0-9506-444553540000}")

(define test-cls (sz2guid sz-cls))
(define test-iid (sz2guid sz-iid))

(define iptr (cptr))

(define hr (CoCreateInstance test-cls 0 CLSCTX_ALL test-iid iptr))

(print (FormatMessage hr))

(if (not (= 0 hr))
    (error "Bailing out of test" hr))

(print (AR  iptr)) ;; fun with ref counts
(print (Rls iptr))

;;;
;;; This COM object has the following vtable slots:
;;; 0, 1, 2 are for IUnknown
;;; 3, 4, 5, 6 are for IDispatch
;;;

(define test-obj-methodlist 
  '(SayHello 
    ShortProp
    LongProp
    VariantProp
    BstrProp
    ))

(vtable test-obj-methodlist 7)

(let* ((c  (cptr))
       (hr (SayHello iptr c)))
  (print hr)
  (print (Bstr2sz (cptr->num c)))
  (SysFreeString (cptr->num c)))

(define test-obj-methlist2 '(SayHello))

;;;
;;; Now, test calling the thing through its DISPIDs. 
;;;

(define (testDispIDs)
  (print "testing GetIDsOfNames")
  (print test-obj-methodlist)
  (print
   (gion iptr test-obj-methodlist))
  )

;;; BUGBUG: WIN2000 has a bug here!!!!

;;; (testDispIDs)

(define (testInvoke)
  (print "testing Invoke")

  (let ((c (LocalAlloc 64 4))
        (d (new-DISPARAMS))
        (v (new-VARIANT)))

    (VARIANT::set-vt       v (bit-or VT_BSTR VT_BYREF))
    (VARIANT::set-value    v  c)
    (DISPARAMS::set-rgvarg d  v)
    (DISPARAMS::set-cArgs  d  1)

    (let ((hr (Invoke iptr 1 iid-null nil DISPATCH_METHOD d nil nil nil)))
      (FormatMessage hr))

    (print (wz2sz (val c)))

    (SysFreeString (val c))
    (LocalFree c)
    (del-VARIANT   v)
    (del-DISPARAMS d)
    ))

(testInvoke)

;;;
;;; Ok, we're done.
;;;

(Rls iptr) ;; the final release
