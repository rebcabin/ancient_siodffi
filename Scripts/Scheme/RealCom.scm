;;;=================================================================;;;
;;;                                                                 ;;;
;;;             C O M   S U P P O R T   F O R   S I O D             ;;;
;;;                                                                 ;;;
;;;         But using the new, typeless 'realload' facility.        ;;;
;;;        Means lighter weight, less C code, but less safety.      ;;;
;;;                                                                 ;;;
;;;=================================================================;;;

;;;=================================================================;;;
;;; Prerequisites                                                   ;;;
;;;=================================================================;;;
(if (symbol-bound? '*dcom.scm-loaded*)
  (error "realcom.scm incompatible with dcom.scm", *dcom.scm-loaded*))

(require    'siod.scm) ; generic junque
(require 'structs.scm) ; uh, yeah.
(require 'syslibs.scm) ; Windows, Win32
(require      'pp.scm) ; pretty print
(require      'fm.scm) ; format message
(require 'Unicode.scm) ; sz2wz, etc.
(require  'COMmon.scm) ; common code with dcom.scm

;;; Set print mode to hexadecimal for integers
(define (toggle-hex-mode)
  (set! **hex-mode** (not **hex-mode**)))

(set! **hex-mode** t)

;;;=================================================================;;;
;;; Talk to me about COM calls...                                   ;;;
;;;=================================================================;;;
(define (check-report hr-local message interface)
  (set! hr hr-local)
  (if (not (= 0 hr-local))
      (begin 
        (prin1 "hr = ")
        (prin1 hr)
        (prin1 message)
        (prin1 "; ")
        (error (FormatMessage hr-local) interface))
      (begin
        (prin1 "Success: ")
        (print interface))))
  
;;;=================================================================;;;
;;; Basic COM infrastructure                                        ;;;
;;;=================================================================;;;

(define (wz2guid wz)
  (let* ((pv (LocalAlloc #x40 32))
         (c  (ChkHresult (CLSIDFromString wz pv))))
    (if (not (equal? "" c)) (print c))
    (LocalFree wz)
    pv))

(define (sz2guid sz)
  (wz2guid (sz2wz sz)))

(define iid-null      (sz2guid "{00000000-0000-0000-0000-000000000000}"))
(define guid-null      iid-null)

(define iid-iunknown  (sz2guid "{00000000-0000-0000-C000-000000000046}"))
(define iid-idispatch (sz2guid "{00020400-0000-0000-C000-000000000046}"))
(define iid-istream   (sz2guid "{0000000c-0000-0000-C000-000000000046}"))
(define iid-ipsi      (sz2guid "{7FD52380-4E07-101B-AE2D-08002B2EC713}")) ; IPersistStreamInit

;;;
;;; The following section implements raw calls through a VTable,
;;; including some definitions for our favorite interfaces 
;;; (definitions created as we need them, on-demand, on-the-fly,
;;; and lazily.  
;;;

(define (vtable slots offset . scope)

  (define (bind-slot sym offset)
    (set-symbol-value!
     sym
     (lambda (interface . y)
       (let* ((this (cptr->num interface)))
         (MainDispatch 
           (indirect (+ (indirect this) (* offset 4)))  ;; func pointer
           (append (list this) y))))))                  ;; args
  
  (define (bind-slots slots offset)
    (cond
     ( (null? slots) 'done )
     ( t (bind-slot 
           (if (null? scope)
               (car slots) 
               (symbolconc (car scope) ':: (car slots)))
           offset)
         (bind-slots (cdr slots) (+ 1 offset)) )))
  
  (bind-slots slots offset)
  )

;;;=================================================================;;;
;;; Well known interfaces                                           ;;;
;;;=================================================================;;;

;;;
;;; IUnknown
;;;
(vtable '(QI AR Rls) 0)

(define (Release interface)
  (if (not (= 0 (cptr->num interface)))
      (Rls interface)
      #f))

(define AddRef AR)
(define QueryInterface QI)
(define CoCI CoCreateInstance)
(define COCI CoCreateInstance)

;;;
;;; IDispatch (almost always right after IUnknown)
;;;
(vtable '(GetTypeInfoCount GetTypeInfo GetIDsOfNames Invoke)
        3)

;;;
;;; Here's the schem-ification of GetIDsOfNames (there's
;;; a regression test in "testvtbl.scm".
;;;

(define gion nil) ;; temporary for GetIDsOfNames
;;
;; We're going through this rigmarole because we wish to 
;; preserve the option of replacing the symbol 'GetIDsOfNames
;; with the following definition, and this is the way to do
;; it.
;;
(let ((gion2 GetIDsOfNames))
  (set! gion 
        (lambda (iptr symlist)
          (let* ((names   (map symbol->string symlist))
                 (cnames  (map sz2wz names))
                 (anames  (list->array cnames))
                 (rgnames (array->rgpv anames))
                 (len     (length cnames))
                 (rgdids  (malloc (* 4 len)))
                 (hr      (gion2 iptr iid-null rgnames len nil rgdids))
                 (adids   (carray->array len 'long rgdids))
                 )
            (if (not (= 0 hr))
                (print (FormatMessage hr)))
            (free rgnames)
            (free rgdids)
            (map LocalFree cnames)
            adids))))

;;;
;;; IStream (start at 3 'cause there's always IUnknown ahead)
;;;
(vtable '(Read    Write   Seek        SetSize       CopyTo 
          Commit  Revert  LockRegion  UnlockRegion  Stat    Clone)
        3)

(define STREAM_SEEK_SET 0)
(define STREAM_SEEK_CUR 1)
(define STREAM_SEEK_END 2)

;;;
;;; IPersistStreamInit
;;;
(vtable '(GetClassID IsDirty Load Save GetSizeMax InitNew)
        3
        'IPSI)

;;;
;;; VARIANT data type
;;;
(require 'enum.scm)
(require 'hash.scm)

(define VT-index (cons-array 32 'lisp))

(merge-hash-tables
    VT-index
    (enum '(
        
        VT_EMPTY            ; = 0,
        VT_NULL             ; = 1,
        VT_I2               ; = 2,
        VT_I4               ; = 3,
        VT_R4               ; = 4,
        VT_R8               ; = 5,
        VT_CY               ; = 6,
        VT_DATE             ; = 7,
        VT_BSTR             ; = 8,
        VT_DISPATCH         ; = 9,
        VT_ERROR            ; = 10,
        VT_BOOL             ; = 11,
        VT_VARIANT          ; = 12,
        VT_UNKNOWN          ; = 13,
        VT_DECIMAL          ; = 14,
        )

        0) ; starting value of series
    )

(merge-hash-tables
    VT-index
    (enum '(
        VT_I1               ; = 16,
        VT_UI1              ; = 17,
        VT_UI2              ; = 18,
        VT_UI4              ; = 19,
        ;;
        ;; Supposedly, VARIANT doesn't support 8-byte ints
        ;;
        VT_I8               ; = 20,
        VT_UI8              ; = 21,
        ;;
        ;; Back to life, here:
        ;;
        VT_INT              ; = 22,
        VT_UINT             ; = 23,
        ;;
        ;; Oops, VARIANT doesn't support these until all the
        ;; way to VT_ARRAY and VT_BYREF below.
        ;;
        VT_VOID             ; = 24,
        VT_HRESULT          ; = 25,
        VT_PTR              ; = 26,
        VT_SAFEARRAY        ; = 27,
        VT_CARRAY           ; = 28,
        VT_USERDEFINED      ; = 29,
        VT_LPSTR            ; = 30,
        VT_LPWSTR           ; = 31,
        )

        16) ; starting value
    )

(merge-hash-tables
    VT-index
    (enum '(
        VT_RECORD           ; = 36,
        )

        36) ; starting value
    )

(merge-hash-tables
    VT-index
    (enum '(
        VT_FILETIME         ; = 64,
        VT_BLOB             ; = 65,
        VT_STREAM           ; = 66,
        VT_STORAGE          ; = 67,
        VT_STREAMED_OBJECT  ; = 68,
        VT_STORED_OBJECT    ; = 69,
        VT_BLOB_OBJECT      ; = 70,
        VT_CF               ; = 71,
        VT_CLSID            ; = 72,
        )

        64) ; starting value
    )

;;
;; Some sporadic definitions
;;

(define VT_BSTR_BLOB        #x0fff) 
(define VT_VECTOR           #x1000) 
(define VT_ARRAY            #x2000) 
(define VT_BYREF            #x4000) 
(define VT_RESERVED         #x8000) 
(define VT_ILLEGAL          #xffff) 
(define VT_ILLEGALMASKED    #x0fff) 
(define VT_TYPEMASK         #x0fff) 

(hset VT-index VT_BSTR_BLOB     'VT_BSTR_BLOB    )
(hset VT-index VT_VECTOR        'VT_VECTOR       )
(hset VT-index VT_ARRAY         'VT_ARRAY        )
(hset VT-index VT_BYREF         'VT_BYREF        )
(hset VT-index VT_RESERVED      'VT_RESERVED     )
(hset VT-index VT_ILLEGAL       'VT_ILLEGAL      )
(hset VT-index VT_ILLEGALMASKED 'VT_ILLEGALMASKED)
(hset VT-index VT_TYPEMASK      'VT_TYPEMASK     )

;;; Ok, here's the stuff you need for invoke
;;;
;;;  HRESULT Invoke( 
;;;    DISPID  dispIdMember,          from GetIDsOfNames (gion)
;;;    REFIID  riid,                  must be IID_NULL
;;;    LCID  lcid,                    should be nil
;;;    WORD  wFlags,                  see below
;;;    DISPPARAMS FAR*  pDispParams,  see below
;;;    VARIANT FAR*  pVarResult,      see below
;;;    EXCEPINFO FAR*  pExcepInfo,    see below
;;;    unsigned int FAR*  puArgErr    see below
;;;  );

;;
;; Invoke!wFlags should be one of the following:
;;
(define DISPATCH_METHOD         1)
(define DISPATCH_PROPERTYGET    2)
(define DISPATCH_PROPERTYPUT    4)
(define DISPATCH_PROPERTYPUTREF 8)

;;; typedef struct  tagDISPPARAMS
;;; {
;;;     VARIANTARG __RPC_FAR * rgvarg;
;;;     DISPID     __RPC_FAR * rgdispidNamedArgs;
;;;     UINT                   cArgs;
;;;     UINT                   cNamedArgs;
;;; }
;;; DISPPARAMS;

(define DISPARAMS
  (struct 'DISPARAMS '(rgvarg rgdispidNamedArgs cArgs cNamedArgs)))

;; The following is not entirely faithful, since we are limited to structs
;; containing DWORD-only fields for the moment (UNDONE, BUGBUG)

(define VARIANT
  (struct 'VARIANT '(vt reserved value)))



