(require 'realcom.scm)
(require 'structs.scm)

(CoInitialize 0)

;;;----------------------------------------------------------------------------------------
;;; Global variables 
;;; 

(define cls-xmldoc ())
(define iid-xmldoc ())
(define iid-xmlerr ())

(define ixmlerr ()) ; IXMLError
(define ixmldoc ()) ; IXMLDocument
(define ipsi    ()) ; IPersistStreamInit
(define istream ()) ; IStream

;;;
;;; Nasty discovery: CLSID XMLDocument does not directly support IXMLElement 
;;; (QueryInterface returns HRESULT 'No such interface supported'
;;;

(define hr 0) ; global hresult

(define root-drive "x:"            )
(define root-dir   "../casxml/"    )
(define root-file  "cassample1.xml")

;;;----------------------------------------------------------------------------------------
;;; (xml-start optional-drive-letter optional-file-name)
;;; 

(define (xml-start . optional-args)
  (if (not (null? optional-args))
      (begin
       (set! root-drive (car optional-args))
       (if (not (null? (cdr optional-args)))
           (set! root-file (cadr optional-args)))))

  (set! cls-xmldoc (sz2guid "{CFC399AF-D876-11d0-9C10-00C04FC99C8E}"))
  (set! iid-xmldoc (sz2guid "{F52E2B61-18A1-11d1-B105-00805F49916B}"))
  (set! iid-xmlerr (sz2guid "{948C5AD3-C58D-11d0-9C0B-00C04FC99C8E}"))

  (set! ixmlerr (cptr))
  (set! ixmldoc (cptr))
  (set! ipsi    (cptr))
  (set! istream (cptr))

  ;;
  ;; IXMLDocument (starts at 7, after IUnknown & IDispatch)
  ;;
  (vtable '(get_root             get_fileSize     get_fileModifiedDate
            get_fileUpdatedDate  get_URL          put_URL
            get_mimeType         get_readyState   get_charset
            put_charset          get_version      get_doctype
            get_dtdURL           createElement)
          7
		  'IXMLDocument)  

  ;;
  ;; IXMLError
  ;;
  (vtable '(GetErrorInfo) 3)  

  ;;
  ;; Get ipsi and xmlerr interfaces on cls-xmldoc
  ;;
  (check-report (CoCreateInstance cls-xmldoc 0 CLSCTX_ALL iid-xmldoc ixmldoc)
                "CoCI of xmldoc: " ixmldoc)
  (check-report (QI ixmldoc iid-xmlerr ixmlerr) "QI for xmlerr: " ixmlerr)
  (check-report (QI ixmldoc iid-ipsi      ipsi) "QI for IPrsStrmInit: "  ipsi)

  ;;
  ;; URLmon
  ;;
  (LoadLibrary (sysdir "urlmon.dll"))

  (the-environment)
  )

;;;----------------------------------------------------------------------------------------
;;; (xml-load optional-file-name)
;;;
;;; Load & Check XML for syntax errors
;;;
(define (xml-load . file)
  (define pUnkOuter           0)
  (if (not (null? file)) 
      (set! root-file (car file))) ; bugger up the global var
  (define TheUrl              (string-append root-drive root-dir root-file))
  (define dwReserved          0)
  (define IBindStatusCallback 0)

  ;;
  ;; Get the IStream on the URL containing the XML
  ;;
  (check-report (URLOpenBlockingStreamA
                 pUnkOuter TheUrl istream dwReserved IBindStatusCallback)
                "IStream from URL: " TheUrl)

  ;;
  ;; Call the 'Load' method on the IPersistStreamInterface
  ;; of XMLDocument, passing in the IStream on the URL. This
  ;; magically checks the syntax of the file.
  ;;
  (set! hr (IPSI::Load ipsi (cptr->num istream)))

  ;;
  ;; Don't barf off on FAILED hr -- this is the signal that we need to 
  ;; analyze syntax errors!
  ;;
  (if (not (= 0 hr))
      (begin
       (define CbXML_ERROR
         (struct
          '(_nLine _pchBuf _cchBuf _ich 
		    _pszFound _pszExpected _reserved1 _reserved2)
          'XML_ERROR))
       (define errorinfo (LocalAlloc #x40 CbXML_ERROR))
       (GetErrorInfo ixmlerr errorinfo)
	   (toggle-hex-mode)
       (prin1 "XML Error on line ") (print          (XML_ERROR::_nLine       errorinfo))
	   (toggle-hex-mode)
       (prin1 "           Found: ") (print (Bstr2sz (XML_ERROR::_pszFound    errorinfo)))
       (prin1 "       Expecting: ") (print (Bstr2sz (XML_ERROR::_pszExpected errorinfo)))

       (prin1 "SysFreeString x 3: ")
	   (print (SysFreeString (XML_ERROR::_pszFound    errorinfo)))
       (print (SysFreeString (XML_ERROR::_pszExpected errorinfo)))
       (print (SysFreeString (XML_ERROR::_pchBuf      errorinfo)))
       (LocalFree errorinfo)
       ))
  )

;;;----------------------------------------------------------------------------------------
;;; (xml-parse)
;;;
;;; Must call xml-check, first
(define (xml-parse)
  ;;
  ;; Get the root of the XML tree, in the form of the 
  ;; IXMLElement interface.
  ;;
  (define ixmlelt (cptr)) ; IXMLElement

  (check-report (IXMLDocument::get_root ixmldoc ixmlelt)
	"Getting IXMLElement interface" ixmlelt)

  (print (FormatMessage hr))

  ;;
  ;; Best to define the XMLElement interface vtables, hmmm?
  ;;
  (vtable '(get_tagName  put_tagName  get_parent
            setAttribute getAttribute removeAttribute
            get_children get_type     get_text
			put_text     addChild     removeChild)
    7
	'IXMLElt)

  (vtable '(put_length   get_length   get__newEnum  item)
    7
	'IXMLEltCollection)

  (vtable '(Next Skip Reset Clone) 3 'IEnum)

  ;;
  ;; Now, do the deed
  ;;
  (let* ((pBsTag      (cptr))
		 (pVarVal     (LocalAlloc #x40 256))
		 (pText       (cptr))
        )

     (define (checkVariantType)
	 	 (if (not (= (indirect pVarVal) VT_BSTR))
	         (error "Expected a BSTR")))

	 (define (getAttr sz)
	   (let ((bsAttr (sz2Bstr sz)))
 	     (set! hr (IXMLElt::getAttribute ixmlelt bsAttr pVarVal))
	     (checkVariantType)
	     (prin1 sz)
		 (let ((szAttr (Bstr2sz (indirect (+ pVarVal 8)))))
	       (print szAttr)
 	       (SysFreeString bsAttr)
		   szAttr)))

	 (set! hr (IXMLElt::get_tagName ixmlelt pBsTag))
     (prin1 "Tag Name: ")
     (print (Bstr2sz (cptr->num pBsTag)))
     ;;
	 ;; UNDONE TODO: these SysFreeStrings returns 0x20, "in-use
	 ;; by another process" or some such...
	 ;;
 	 (prin1 "SysFreeString: ")
	 (print (SysFreeString (cptr->num pBsTag)))

	 (getAttr "action")
	 (getAttr "permissionClass")
	 (getAttr "targetModule")
	 (getAttr "targetComponent")
	 (getAttr "targetClass")

	 (define ixmleltCollection (cptr))
	 (define pnChildren (LocalAlloc #x40 4))
	 (set! hr (IXMLElt::get_children ixmlelt ixmleltCollection))
	 (IXMLEltCollection::get_length ixmleltCollection pnChildren)
	 (prin1 "Number of children: ")
	 (print (indirect pnChildren))

	 (define (getChild i ienum)
	   (define nActual (LocalAlloc #x40 128))
	   (define ithElt  (LocalAlloc #x40 128))
	   (IEnum::Next ienum 1 ithElt nActual)
	   (print (indirect nActual))
	   (print (indirect ithElt))
	   (LocalFree ithElt)
	   (LocalFree nActual)
	   )

	 (define (getChild2 i ienum)
	   )

	 (define (getChildren i ienum)
	   (cond 
	     ( (= i (indirect pnChildren)) 'done )
		 ( t (getChild i ienum)
		     (getChildren (+ 1 i) ienum) )))

     (define ienumchildren (cptr))
	 (define ichild (cptr))
	 (set! hr (IXMLEltCollection::get__newEnum
	           ixmleltCollection ienumchildren))
	 (print (FormatMessage hr))
	 ;; Assume that each enum member is an IXMLElt
	 (set! hr (IEnum::Reset ienumchildren))
	 (getChildren 0 ienumchildren)
	 (print (Release ienumchildren))

  
     (set! hr (IXMLElt::get_text ixmlelt pText))
	 (prin1 "Text: ")
	 (print (Bstr2sz (cptr->num pText)))
	 (prin1 "SysFreeString: ")
	 (print (SysFreeString (cptr->num pText)))

	 (Release ixmlelt)
	 (Release ixmleltCollection)
	 
	 (prin1 "LocalFree: ")
	 (print (LocalFree pVarVal))
	 (print (LocalFree pnChildren))
     )
  )

;;;----------------------------------------------------------------------------------------
;;; (xml-end)
;;;

(define (xml-end)
  (Release ipsi   )
  (Release ixmldoc)
  (Release ixmlerr)
  (Release istream)

  (LocalFree cls-xmldoc)
  (LocalFree iid-xmlerr)
  (LocalFree iid-xmldoc)
  )

