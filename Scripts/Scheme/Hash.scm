(define (merge-hash-tables htDest htSrc)
  
  (define (merge-alist-elt elt)
    (let ((key (car elt))
          (val (cdr elt)))
      (hset htDest key val)))

  (define (merge-alist alist)
    (mapcar merge-alist-elt alist))

  (define (merge-array iWhich)
    (cond
      ( (>= iWhich (length htSrc)) htDest )
      ( t  (merge-alist (aref htSrc iWhich))
	       (merge-array (+ 1 iWhich)) )))

  (merge-array 0))

	
