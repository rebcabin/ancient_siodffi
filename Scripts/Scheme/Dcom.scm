(require 'peloader.scm)
(require 'siod.scm)
(require 'fm.scm)
(require 'structs.scm)

(define mmfuncs (LoadLibrary (sysdir "winmm.dll")))

;;; The following are actual calls into the system

(define numindevs  (midiInGetNumDevs ))
(define numoutdevs (midiOutGetNumDevs))

;;; typedef struct { 
;;;     WORD      wMid; 
;;;     WORD      wPid; 
;;;     MMVERSION vDriverVersion; 
;;;     CHAR      szPname[MAXPNAMELEN]; 
;;;     DWORD     dwSupport; 
;;; } MIDIINCAPS; 

(define MAXPNAMELEN 32)

(define MIDIINCAPS 
  (struct 'MIDINCAPS
          `((wMid . 2) (wPid . 2) vDriverVersion
            (szPname . ,MAXPNAMELEN) dwSupport)))

;;; typedef struct { 
;;;     WORD      wMid; 
;;;     WORD      wPid; 
;;;     MMVERSION vDriverVersion; 
;;;     CHAR      szPname[MAXPNAMELEN]; 
;;;     WORD      wTechnology; 
;;;     WORD      wVoices; 
;;;     WORD      wNotes; 
;;;     WORD      wChannelMask; 
;;;     DWORD     dwSupport; 
;;; } MIDIOUTCAPS; 
 
(define MDIDOUTCAPS
  (struct 'MIDIOUTCAPS
          `((wMid . 2) (wPid . 2) vDriverVersion
            (szPname . ,MAXPNAMELEN) (wTechnology . 2)
            (wVoices . 2) (wNotes . 2) (wChannelMask . 2)
            dwSupport)))

;;; The current, big goal is just to make 
;;; some noise out the speakers of the system, so we'll look at
;;; output devices, first. 

(define (getMidiOutCaps)
  (let* ((n       numoutdevs)
         (rgMOCs (new-rg-MIDIOUTCAPS n))
         (MOCsiz (sizeof-MIDIOUTCAPS)))
    (define (iter so-far)
      (if (= so-far n) rgMOCs
          (begin
            (let* ((inst-addr (+ rgMOCs (* so-far MOCsiz)))
                  (mmresult  (midiOutGetDevCapsA
                              so-far inst-addr MOCsiz)))
              (if (not (= mmresult 0))
                  (FormatMessage mmresult)
                  (begin
                    (dump-MIDIOUTCAPS inst-addr)
                    (prin1 "pausing... [press the enter key]")
                    (getchar))))
            (iter (+ so-far 1)))))
    (iter 0)))
     
(define rgMOCs (getMidiOutCaps))
                      
         
