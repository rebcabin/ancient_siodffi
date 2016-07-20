Nil (in, nConst) = 

(map
 (sequence
   (sink   (portRef in) (messageRef cn    ))
   (source (portRef pn) (messageRef nConst)))
 (assignmentList
  (assignment (messageRef cn) (portRef pc))
  (assignment (messageRef cn) (portRef pn))))

Cons (in, V, L) =

(map
 (sequence
   (sink   (portRef in) (messageRef cn     ))
   (source (portRef pn) (messageRef consOut)))
 (assignmentList
  (assignment (messageRef cn) (portRef pc))
  (assignment (messageRef cn) (portRef pn))
  (assignment (messageRef consOut) (portRef V))
  (assignment (messageRef consOut) (portRef L))))

ALyst (l0) =



CdrDown (L) = 
  

