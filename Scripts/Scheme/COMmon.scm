;;;
;;; Definitions common to "DCOM.scm" and "RealCOM.scm"
;;;

(define CLSCTX_INPROC_SERVER   1)
(define CLSCTX_INPROC_HANDLER  2)
(define CLSCTX_LOCAL_SERVER    4)
(define CLSCTX_REMOTE_SERVER  16)
(define CLSCTX_ALL (+ CLSCTX_INPROC_SERVER 
                      CLSCTX_INPROC_HANDLER 
                      CLSCTX_LOCAL_SERVER 
                      CLSCTX_REMOTE_SERVER))

