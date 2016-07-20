(require 'syslibs.scm)
(require "winbase.scm")
(require "fm.scm")

(define (longNameFromDOSName dosName)
  (let* ((data (new-WIN32_FIND_DATAA))
         (lname (if (ChkHandleReturn
                     (FindFirstFileA (string->cstring dosName) data))
                    (cstring->string
                     (WIN32_FIND_DATAA::getAddr-cFileName data))
                    "INVALID_HANDLE_VALUE")))
    (del-WIN32_FIND_DATAA data)
    lname))
    
    
  