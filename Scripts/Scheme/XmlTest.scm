(define (test) (load 'xml.scm)) ; load "this files": shortcut for repetition

(require 'realcom.scm)
(require 'structs.scm)

(CoInitialize 0)

;;;----------------------------------------------------------------------------------------
;;; Preliminaries  (allocated things that must be released)
;;; 
(define cls-xmldoc    (sz2guid "{CFC399AF-D876-11d0-9C10-00C04FC99C8E}"))
(define iid-xmldoc    (sz2guid "{F52E2B61-18A1-11d1-B105-00805F49916B}"))
(define iid-xmlerror  (sz2guid "{948C5AD3-C58D-11d0-9C0B-00C04FC99C8E}"))

(define ixmlerr (cptr))
(define ixmldoc (cptr))
(define istream (cptr))
(define ipsi    (cptr)) ; IPersistStreamInit

(define hr           0) ; global hresult

;;;
;;; IXMLDocument (starts at 7, after IUnknown & IDispatch)
;;;
(vtable '(get_root             get_fileSize     get_fileModifiedDate
          get_fileUpdatedDate  get_URL          put_URL
          get_mimeType         get_readyState   get_charset
          put_charset          get_version      get_doctype
          get_dtdURL           createElement)
        7)

;;;
;;; IXMLError
;;;
(vtable '(GetErrorInfo) 3)  

;;;----------------------------------------------------------------------------------------
;;; Get interfaces on cls-xmldoc
;;;
(check-report (CoCreateInstance cls-xmldoc 0 CLSCTX_ALL iid-xmlerror ixmlerr)
              "CoCI of xml-error: " ixmlerr)
(check-report (QI ixmlerr iid-xmldoc ixmldoc)
              "QI for xml-doc: "  ixmldoc)
(check-report (QI ixmldoc iid-ipsi ipsi)
              "QI for IPersistStreamInit: "  ipsi)

;;;----------------------------------------------------------------------------------------
;;; URLmon
;;;
(define urlmon (LoadLibrary (sysdir "urlmon.dll")))

(define pUnkOuter           0)
'(define MyUrl               "x:../MusicML/Music1.xml")
(define MyUrl               "d:../casxml/cassample1.xml")
(define dwReserved          0)
(define IBindStatusCallback 0)

(check-report (URLOpenBlockingStreamA pUnkOuter MyUrl istream dwReserved IBindStatusCallback)
			  "IStream from URL: " istream)

;;;; ;;;----------------------------------------------------------------------------------------
;;;; ;;; Read from the IStream
;;;; ;;;
;;;; (define buf    (LocalAlloc #x40 1024))
;;;; (define actual (LocalAlloc #x40    4))
;;;; 
;;;; (define hr (Read istream buf 1024 actual))
;;;; (prin1 "Result of reading from URL: ")
;;;; (print (FormatMessage hr))
;;;; (prin1 "Actual bytes read: ")
;;;; (print (val actual))
;;;; (print "Buffer read from the URL:")
;;;; (print (cstring->string buf))
;;;; 
;;;; (LocalFree    buf)
;;;; (LocalFree actual)
;;;; 
;;;; ;;;
;;;; ;;; Rewind this sucker.
;;;; ;;;
;;;; ;;; Must pass in two zeros for the desired position, since the method takes a 
;;;; ;;; 64-bit LARGE_INTEGER.
;;;; ;;;
;;;; (check-report (Seek istream 0 0 STREAM_SEEK_SET 0) "Rewinding: " istream)

;;;----------------------------------------------------------------------------------------
;;; Check XML for syntax errors
;;;
;;; Don't barf off on FAILED hr -- this is the signal that we need to analyze
;;; syntax errors!
;;;
(set! hr (IPSI::Load ipsi (cptr->num istream)))

(if (not (= 0 hr))
    (begin
     (define CbXML_ERROR
       (struct
        '(_nLine _pchBuf _cchBuf _ich _pszFound _pszExpected _reserved1 _reserved2)
        'XML_ERROR))
     (define errorinfo (LocalAlloc #x40 CbXML_ERROR))
     (GetErrorInfo ixmlerr errorinfo)
     (prin1 "XML Error on line ") (print          (XML_ERROR::_nLine       errorinfo))
     (prin1 "           Found: ") (print (Bstr2sz (XML_ERROR::_pszFound    errorinfo)))
     (prin1 "       Expecting: ") (print (Bstr2sz (XML_ERROR::_pszExpected errorinfo)))
     (SysFreeString (XML_ERROR::_pszFound    errorinfo))
     (SysFreeString (XML_ERROR::_pszExpected errorinfo))
     (SysFreeString (XML_ERROR::_pchBuf      errorinfo))
     (LocalFree errorinfo)
     ))

;;;----------------------------------------------------------------------------------------
;;; THE END -- clean up
;;;

(Release ipsi   )
(Release ixmldoc)
(Release ixmlerr)
(Release istream)

(LocalFree cls-xmldoc  )
(LocalFree iid-xmlerror)
(LocalFree iid-xmldoc  )

'(CoUninitialize)  ;; blows idempotency -- not sure why