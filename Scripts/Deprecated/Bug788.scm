(require "coinit.scm")

(define (test) (load 'Bug788.scm))   ; shortcut for repetition

;;;
;;; Create the Bug636 object
;;;

(define BugDisp (CoCreateDispInstance "{25DFAAB7-DA98-11D0-9BE5-0000F877307E}"))
(print "Client creates BugDisp")
(print BugDisp)
(define pause read)
'(pause) ; ... for the debugger.
(Invoke-by-name BugDisp "SayHello" (dispparams-simple (BSTR-REF)))

(define secstrings (dispparams-multi BSTR-REF 4))

(print "ISecurityProperty strings from BugDisp")
(pp (Invoke-by-name BugDisp "GetMTXSidsFromThisPackage" secstrings))

(print "ISecurityProperty strings from BugDisp's in-proc helper package")
(pp (Invoke-by-name BugDisp "GetMTxSIDs" secstrings))

(print "Client creates YAS")
(define YasDisp (CoCreateDispInstance "{74320703-E1BC-11D0-BCA4-0000F877307E}"))

(print "YAS' in-proc helper ISecProp strings")
(pp (Invoke-by-name YasDisp "GetMTxIdStrings" secstrings))

(define punk 
  (QueryInterface 
    YasDisp 
    (string->guid "{74320702-E1BC-11D0-BCA4-0000F877307E}")))
(pp punk)

(define yas-params ;; same order as typelib, reverse order of C++ declaration
   (dispparams-simple 
     (IUnknown punk) 
     (BSTR-REF) 
     (BSTR-REF) 
     (BSTR-REF) 
     (BSTR-REF)))

(print "Pass YAS to Bug636, get back identity strings")
(pp (Invoke-by-name BugDisp "CallYAS" yas-params))

(print "Tell Bug636 to create and call a YAS2")
(pp (Invoke-by-name BugDisp "CreateAndCallYAS2" secstrings)) 

(print "Tell Bug636 to create, release, and call again a YAS2")
(pp (Invoke-by-name BugDisp "CreateReleaseAndCallYAS2" secstrings)) 

(print "Tell YAS to create, release, and call again a YAS2")
(pp (Invoke-by-name YasDisp "CreateReleaseAndCallYAS2" secstrings)) 
