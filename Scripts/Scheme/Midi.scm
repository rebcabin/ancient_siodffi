(require 'peloader.scm)
(require 'mmsystem.scm)
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
 
(define MIDIOUTCAPS
  (struct 'MIDIOUTCAPS
          `((wMid . 2) (wPid . 2) vDriverVersion
            (szPname . ,MAXPNAMELEN) (wTechnology . 2)
            (wVoices . 2) (wNotes . 2) (wChannelMask . 2)
            dwSupport)))

;;; The current, big goal is just to make 
;;; some noise out the speakers of the system, so we'll look at
;;; output devices, first. 

(define (MIDI::getOutDevCaps)
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
     
(define rgMOCs (MIDI::getOutDevCaps))
                      
;;; UINT midiOutOpen(
;;;   LPHMIDIOUT lphmo,          
;;;   UINT uDeviceID,            
;;;   DWORD dwCallback,          
;;;   DWORD dwCallbackInstance,  
;;;   DWORD dwFlags              
;;; );
 
(define (MIDI::openOutDev devNumber)
  (let* ((pHMIDIOUT (LocalAlloc #x40 4))
         (retval   (midiOutOpen pHMIDIOUT devNumber 0 0 0)))
    (if (not (= retval MMSYSERR_NOERROR))
        (begin
          (LocalFree pHMIDIOUT)
          (FormatMessage retval))
        pHMIDIOUT)))

;;; typedef struct { 
;;;     LPSTR  lpData; 
;;;     DWORD  dwBufferLength; 
;;;     DWORD  dwBytesRecorded; 
;;;     DWORD  dwUser; 
;;;     DWORD  dwFlags; 
;;;     struct midihdr_tag far * lpNext; 
;;;     DWORD  reserved; 
;;;     DWORD  dwOffset; 
;;;     DWORD  dwReserved[4]; 
;;; } MIDIHDR; 
 
(define MIDIHDR
  (struct 'MIDIHDR `(lpData
                     dwBufferLength
                     dwBytesRecorded
                     dwUser
                     dwFlags
                     lpNext
                     reserved
                     dwOffset (dwReserved . 16))))

(define (MIDI::outPrepareHeader hDevice)
  (let* ((hdr  (new-MIDIHDR))
         (len  256)
         (buf (LocalAlloc #x40 len)))
    (MIDIHDR::set-lpData         hdr buf)
    (MIDIHDR::set-dwBufferLength hdr len)
    (MIDIHDR::set-dwFlags        hdr   0)
    (let ((ret (midiOutPrepareHeader hDevice hdr MIDIHDR)))
      (if (not (= ret MMSYSERR_NOERROR))
          (FormatMessage ret))
      hdr)))

;;; UINT sendMIDIEvent(HMIDIOUT hmo, BYTE bStatus, BYTE bData1, BYTE bData2) 
;;; { 
;;;     union { 
;;;         DWORD dwData; 
;;;         BYTE bData[4]; 
;;;     } u; 
;;;  
;;;     // Construct the MIDI message. 
;;;  
;;;     u.bData[0] = bStatus;  // MIDI status byte 
;;;     u.bData[1] = bData1;   // first MIDI data byte 
;;;     u.bData[2] = bData2;   // second MIDI data byte 
;;;     u.bData[3] = 0; 
;;;  
;;;     // Send the message. 
;;;     return midiOutShortMsg(hmo, u.dwData); 
;;; } 

(define (MIDI::sendEvent HMIDIOUT statusByte dataByte1 dataByte2)
  (midiOutShortMsg HMIDIOUT (| statusByte
                               (<< (| dataByte1
                                      (<< dataByte2 8)) 8))))

(define (MIDIMsg::noteOn HMIDIOUT note channel velocity)
  (let* ((chan (& #xF  channel))
         (stat (| #x90 chan))
         (note (& #xFF note))
         (velc (& #xFF velocity)))
    (MIDI::sendEvent HMIDIOUT stat note velc)))

(define (MIDIMsg::noteOff HMIDIOUT note channel velocity)
  (let* ((chan (& #xF  channel))
         (stat (| #x80 chan))
         (note (& #xFF note))
         (velc (& #xFF velocity)))
    (MIDI::sendEvent HMIDIOUT stat note velc)))

(define middleC 60)

(define (interval::m2 note) (+ note  1))
(define (interval::M2 note) (+ note  2))
(define (interval::m3 note) (+ note  3))
(define (interval::M3 note) (+ note  4))
(define (interval::P4 note) (+ note  5))
(define (interval::A4 note) (+ note  6))
(define (interval::d5 note) (+ note  6))
(define (interval::P5 note) (+ note  7))
(define (interval::A5 note) (+ note  8))
(define (interval::m6 note) (+ note  8))
(define (interval::M6 note) (+ note  9))
(define (interval::d7 note) (+ note  9))
(define (interval::m7 note) (+ note 10))
(define (interval::M7 note) (+ note 11))

(define (MIDIMsgs::majorTriad HMIDI bass-note channel velocity millisecs)
  (MIDIMsg::noteOn  HMIDI               bass-note  channel velocity)
  (MIDIMsg::noteOn  HMIDI (interval::M3 bass-note) channel velocity)
  (MIDIMsg::noteOn  HMIDI (interval::P5 bass-note) channel velocity)
  (Sleep millisecs)
  (MIDIMsg::noteOff HMIDI               bass-note  channel velocity)
  (MIDIMsg::noteOff HMIDI (interval::M3 bass-note) channel velocity)
  (MIDIMsg::noteOff HMIDI (interval::P5 bass-note) channel velocity))

(define (MIDIMsgs::minorTriad HMIDI bass-note channel velocity millisecs)
  (MIDIMsg::noteOn  HMIDI               bass-note  channel velocity)
  (MIDIMsg::noteOn  HMIDI (interval::m3 bass-note) channel velocity)
  (MIDIMsg::noteOn  HMIDI (interval::P5 bass-note) channel velocity)
  (Sleep millisecs)
  (MIDIMsg::noteOff HMIDI               bass-note  channel velocity)
  (MIDIMsg::noteOff HMIDI (interval::m3 bass-note) channel velocity)
  (MIDIMsg::noteOff HMIDI (interval::P5 bass-note) channel velocity))

(define (MIDIMsgs::augmentedTriad HMIDI bass-note channel velocity millisecs)
  (MIDIMsg::noteOn  HMIDI               bass-note  channel velocity)
  (MIDIMsg::noteOn  HMIDI (interval::M3 bass-note) channel velocity)
  (MIDIMsg::noteOn  HMIDI (interval::A5 bass-note) channel velocity)
  (Sleep millisecs)
  (MIDIMsg::noteOff HMIDI               bass-note  channel velocity)
  (MIDIMsg::noteOff HMIDI (interval::M3 bass-note) channel velocity)
  (MIDIMsg::noteOff HMIDI (interval::A5 bass-note) channel velocity))

(define (MIDIMsgs::diminishedTriad HMIDI bass-note channel velocity millisecs)
  (MIDIMsg::noteOn  HMIDI               bass-note  channel velocity)
  (MIDIMsg::noteOn  HMIDI (interval::m3 bass-note) channel velocity)
  (MIDIMsg::noteOn  HMIDI (interval::d5 bass-note) channel velocity)
  (Sleep millisecs)
  (MIDIMsg::noteOff HMIDI               bass-note  channel velocity)
  (MIDIMsg::noteOff HMIDI (interval::m3 bass-note) channel velocity)
  (MIDIMsg::noteOff HMIDI (interval::d5 bass-note) channel velocity))

(define (MIDIMsgs::triad type H b c v m)
  (cond
   ((equal? type 'maj) (MIDIMsgs::majorTriad      H b c v m))
   ((equal? type 'min) (MIDIMsgs::minorTriad      H b c v m))
   ((equal? type 'aug) (MIDIMsgs::augmentedTriad  H b c v m))
   ((equal? type 'dim) (MIDIMsgs::diminishedTriad H b c v m))
   (t nil)))
            
(define (MIDIMsgs::majorSeventh H b c v m)
  (MIDIMsg::noteOn  H               b  c v)
  (MIDIMsg::noteOn  H (interval::M3 b) c v)
  (MIDIMsg::noteOn  H (interval::P5 b) c v)
  (MIDIMsg::noteOn  H (interval::M7 b) c v)
  (Sleep m)                       
  (MIDIMsg::noteOff H               b  c v)
  (MIDIMsg::noteOff H (interval::M3 b) c v)
  (MIDIMsg::noteOff H (interval::P5 b) c v)
  (MIDIMsg::noteOff H (interval::M7 b) c v))

(define (MIDIMsgs::minorSeventh H b c v m)
  (MIDIMsg::noteOn  H               b  c v)
  (MIDIMsg::noteOn  H (interval::m3 b) c v)
  (MIDIMsg::noteOn  H (interval::P5 b) c v)
  (MIDIMsg::noteOn  H (interval::m7 b) c v)
  (Sleep m)                       
  (MIDIMsg::noteOff H               b  c v)
  (MIDIMsg::noteOff H (interval::m3 b) c v)
  (MIDIMsg::noteOff H (interval::P5 b) c v)
  (MIDIMsg::noteOff H (interval::m7 b) c v))

(define (MIDIMsgs::dominantSeventh H b c v m)
  (MIDIMsg::noteOn  H               b  c v)
  (MIDIMsg::noteOn  H (interval::M3 b) c v)
  (MIDIMsg::noteOn  H (interval::P5 b) c v)
  (MIDIMsg::noteOn  H (interval::m7 b) c v)
  (Sleep m)                       
  (MIDIMsg::noteOff H               b  c v)
  (MIDIMsg::noteOff H (interval::M3 b) c v)
  (MIDIMsg::noteOff H (interval::P5 b) c v)
  (MIDIMsg::noteOff H (interval::m7 b) c v))

(define (MIDIMsgs::augmentedSeventh H b c v m)
  (MIDIMsg::noteOn  H               b  c v)
  (MIDIMsg::noteOn  H (interval::M3 b) c v)
  (MIDIMsg::noteOn  H (interval::A5 b) c v)
  (MIDIMsg::noteOn  H (interval::m7 b) c v)
  (Sleep m)                       
  (MIDIMsg::noteOff H               b  c v)
  (MIDIMsg::noteOff H (interval::M3 b) c v)
  (MIDIMsg::noteOff H (interval::A5 b) c v)
  (MIDIMsg::noteOff H (interval::m7 b) c v))

(define (MIDIMsgs::halfDiminished H b c v m)
  (MIDIMsg::noteOn  H               b  c v)
  (MIDIMsg::noteOn  H (interval::m3 b) c v)
  (MIDIMsg::noteOn  H (interval::d5 b) c v)
  (MIDIMsg::noteOn  H (interval::m7 b) c v)
  (Sleep m)                       
  (MIDIMsg::noteOff H               b  c v)
  (MIDIMsg::noteOff H (interval::m3 b) c v)
  (MIDIMsg::noteOff H (interval::d5 b) c v)
  (MIDIMsg::noteOff H (interval::m7 b) c v))

(define (MIDIMsgs::fullDiminished H b c v m)
  (MIDIMsg::noteOn  H               b  c v)
  (MIDIMsg::noteOn  H (interval::m3 b) c v)
  (MIDIMsg::noteOn  H (interval::d5 b) c v)
  (MIDIMsg::noteOn  H (interval::d7 b) c v)
  (Sleep m)                       
  (MIDIMsg::noteOff H               b  c v)
  (MIDIMsg::noteOff H (interval::m3 b) c v)
  (MIDIMsg::noteOff H (interval::d5 b) c v)
  (MIDIMsg::noteOff H (interval::d7 b) c v))

(define (MIDIMsgs::seventh type H b c v m)
  (cond
   ((equal? type 'M7)   (MIDIMsgs::majorSeventh     H b c v m))
   ((equal? type 'm7)   (MIDIMsgs::minorSeventh     H b c v m))
   ((equal? type '7)    (MIDIMsgs::dominantSeventh  H b c v m))
   ((equal? type 'A7)   (MIDIMsgs::augmentedSeventh H b c v m))
   ((equal? type 'dim)  (MIDIMsgs::fullDiminished   H b c v m))
   ((equal? type 'hdim) (MIDIMsgs::halfDiminished   H b c v m))
   (t nil)))
            
(define (t2 hh)
  (midiOutShortMsg hh #xFF3C90)
  (Sleep 400)
  (midiOutShortMsg hh #xFF3C80))

(define (t1 devnum)
  (let* ((ph (MIDI::openOutDev devnum))
         (hh (val ph)))
;    (t2 hh)
    (MIDIMsgs::triad 'maj hh    middleC     0 127 200)
    (MIDIMsgs::triad 'min hh (+ middleC  2) 0 127 200)
    (MIDIMsgs::triad 'min hh (+ middleC  4) 0 127 200)
    (MIDIMsgs::triad 'maj hh (+ middleC  5) 0 127 200)
    (MIDIMsgs::triad 'maj hh (+ middleC  7) 0 127 200)
    (MIDIMsgs::triad 'min hh (+ middleC  9) 0 127 200)
    (MIDIMsgs::triad 'dim hh (+ middleC 11) 0 127 200)
    (MIDIMsgs::triad 'maj hh (+ middleC 12) 0 127 200)

    (MIDIMsgs::seventh 'M7   hh    middleC     0 127 150) (Sleep 50)
    (MIDIMsgs::seventh 'm7   hh (+ middleC  2) 0 127 150) (Sleep 50)
    (MIDIMsgs::seventh 'm7   hh (+ middleC  4) 0 127 150) (Sleep 50)
    (MIDIMsgs::seventh 'M7   hh (+ middleC  5) 0 127 150) (Sleep 50)
    (MIDIMsgs::seventh '7    hh (+ middleC  7) 0 127 150) (Sleep 50)
    (MIDIMsgs::seventh 'm7   hh (+ middleC  9) 0 127 150) (Sleep 50)
    (MIDIMsgs::seventh 'hdim hh (+ middleC 11) 0 127 150) (Sleep 50)
    (MIDIMsgs::seventh 'M7   hh (+ middleC 12) 0 127 150) (Sleep 50)

    (Sleep 1000)

    (midiOutClose hh)
    (LocalFree ph)))
    
