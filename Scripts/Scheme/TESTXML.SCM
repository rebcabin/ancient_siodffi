;;; testxml.scm
(define (test) (load 'testxml.scm))

(require 'xml.scm)
(xml-start "x:")
(xml-load "casSample1.xml")
(xml-parse)
(xml-end)