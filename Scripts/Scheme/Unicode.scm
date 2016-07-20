;;;
;;; Unicode.scm  --  25 May 98 (brianbec)
;;;
(require 'syslibs.scm)
(require      'fm.scm)

(define (sz2wz sz)
  (let* ((l  (length sz))
         (lw (* 2 l))
         (wz (LocalAlloc #x40 (+ 2 lw)))
         (ir (MultiByteToWideChar 0 0 sz l wz l))
         (c  (ChkSysCall ir l)))
    (if (not (equal? c "")) (print c))
    wz))

(define (wz2sz wz)
  (let* ((l   (lstrlenW wz))
         (sz  (LocalAlloc #x40 (+ 1 l)))
         (ir  (WideCharToMultiByte 0 0 wz l sz l 0 0))
         (c   (ChkSysCall ir l)))
    (if (not (equal? c "")) 
        (print c)
        (begin
          (let ((s (cstring->string sz)))
            (LocalFree sz)
            s)))))

;;;=================================================================;;;
;;; BSTRs                                                           ;;;
;;;=================================================================;;;

(define (sz2Bstr sz)
  (SysAllocString (sz2wz sz)))

(define Bstr2sz wz2sz)
  

