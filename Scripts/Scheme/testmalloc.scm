(require "peloader.scm")
(define crt (LoadLibraryCDecls (sysdir "msvcrt40.dll")))

(define buf    (malloc 1024))
(define actual (malloc    4))
(print  (memset actual 0    4))
(print  (memset buf    0 1024))

(define f (fopen "c:/MusicML/Music1.xml" "r"))
(define act2 (fread buf 1 1024 f))
(fclose f)

(print (cstring->string buf))

(free buf)
(free actual)
