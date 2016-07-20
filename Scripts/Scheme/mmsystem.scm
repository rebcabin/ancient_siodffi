; /*==========================================================================
;  *
;  *  mmsystem.h -- Include file for Multimedia API's
;  *
;  *  Version 4.00
;  *
;  *  Copyright (C) 1992-1995 Microsoft Corporation.  All Rights Reserved.
;  *
;  *--------------------------------------------------------------------------
;  *
;  *  Define:         Prevent inclusion of:
;  *  --------------  --------------------------------------------------------
;  *  MMNODRV         Installable driver support
;  *  MMNOSOUND       Sound support
;  *  MMNOWAVE        Waveform support
;  *  MMNOMIDI        MIDI support
;  *  MMNOAUX         Auxiliary audio support
;  *  MMNOMIXER       Mixer support
;  *  MMNOTIMER       Timer support
;  *  MMNOJOY         Joystick support
;  *  MMNOMCI         MCI support
;  *  MMNOMMIO        Multimedia file I/O support
;  *  MMNOMMSYSTEM    General MMSYSTEM functions
;  *
;  *==========================================================================
;  */

; /****************************************************************************

;           General constants and data types

; ****************************************************************************/

; /* general constants */
(define MAXPNAMELEN             32) ; /* max product name length (including NULL) */
(define MAXERRORLENGTH         256) ; /* max error text length (including NULL) */
(define MAX_JOYSTICKOEMVXDNAME 260) ; /* max oem vxd name length (including NULL) */

(define MM_MICROSOFT             1) ;   /* Microsoft Corporation */

(define MM_MIDI_MAPPER           1) ;   /* MIDI Mapper */
(define MM_WAVE_MAPPER           2) ;   /* Wave Mapper */
(define MM_SNDBLST_MIDIOUT       3) ;   /* Sound Blaster MIDI output port */
(define MM_SNDBLST_MIDIIN        4) ;   /* Sound Blaster MIDI input port */
(define MM_SNDBLST_SYNTH         5) ;   /* Sound Blaster internal synthesizer */
(define MM_SNDBLST_WAVEOUT       6) ;   /* Sound Blaster waveform output */
(define MM_SNDBLST_WAVEIN        7) ;   /* Sound Blaster waveform input */
(define MM_ADLIB                 9) ;   /* Ad Lib-compatible synthesizer */
(define MM_MPU401_MIDIOUT       10) ;   /* MPU401-compatible MIDI output port */
(define MM_MPU401_MIDIIN        11) ;   /* MPU401-compatible MIDI input port */
(define MM_PC_JOYSTICK          12) ;   /* Joystick adapter */

(define TIME_MS             #x0001) ; time in milliseconds */
(define TIME_SAMPLES        #x0002) ; number of wave samples */
(define TIME_BYTES          #x0004) ; current byte offset */
(define TIME_SMPTE          #x0008) ; SMPTE time */
(define TIME_MIDI           #x0010) ; MIDI time */
(define TIME_TICKS          #x0020) ; Ticks within MIDI stream */

;/****************************************************************************

;        String resource number bases (internal use)

;****************************************************************************/

(define MMSYSERR_BASE             0)
(define WAVERR_BASE              32)
(define MIDIERR_BASE             64)
(define TIMERR_BASE              96)
(define JOYERR_BASE             160)
(define MCIERR_BASE             256)
(define MIXERR_BASE            1024)

(define MCI_STRING_OFFSET       512)
(define MCI_VD_OFFSET          1024)
(define MCI_CD_OFFSET          1088)
(define MCI_WAVE_OFFSET        1152)
(define MCI_SEQ_OFFSET         1216)

;/****************************************************************************

;            General error return values

;****************************************************************************/

;/* general error return values */
(define MMSYSERR_NOERROR      0);                  /* no error */
(define MMSYSERR_ERROR        (+ MMSYSERR_BASE 1)); /* unspecified error */
(define MMSYSERR_BADDEVICEID  (+ MMSYSERR_BASE 2)); /* device ID out of range */
(define MMSYSERR_NOTENABLED   (+ MMSYSERR_BASE 3)); /* driver failed enable */
(define MMSYSERR_ALLOCATED    (+ MMSYSERR_BASE 4)); /* device already allocated */
(define MMSYSERR_INVALHANDLE  (+ MMSYSERR_BASE 5)); /* device handle is invalid */
(define MMSYSERR_NODRIVER     (+ MMSYSERR_BASE 6)); /* no device driver present */
(define MMSYSERR_NOMEM        (+ MMSYSERR_BASE 7)); /* memory allocation error */
(define MMSYSERR_NOTSUPPORTED (+ MMSYSERR_BASE 8)); /* function isn't supported */
(define MMSYSERR_BADERRNUM    (+ MMSYSERR_BASE 9)); /* error value out of range */
(define MMSYSERR_INVALFLAG    (+ MMSYSERR_BASE 10));/* invalid flag passed */
(define MMSYSERR_INVALPARAM   (+ MMSYSERR_BASE 11));/* invalid parameter passed */
(define MMSYSERR_HANDLEBUSY   (+ MMSYSERR_BASE 12));/* handle being used */
                                                  ;/* simultaneously on another */
                                                  ;/* thread (eg callback) */
(define MMSYSERR_INVALIDALIAS (+ MMSYSERR_BASE 13));/* specified alias not found */
(define MMSYSERR_BADDB        (+ MMSYSERR_BASE 14));/* bad registry database */
(define MMSYSERR_KEYNOTFOUND  (+ MMSYSERR_BASE 15));/* registry key not found */
(define MMSYSERR_READERROR    (+ MMSYSERR_BASE 16));/* registry read error */
(define MMSYSERR_WRITEERROR   (+ MMSYSERR_BASE 17));/* registry write error */
(define MMSYSERR_DELETEERROR  (+ MMSYSERR_BASE 18));/* registry delete error */
(define MMSYSERR_VALNOTFOUND  (+ MMSYSERR_BASE 19));/* registry value not found */
(define MMSYSERR_NODRIVERCB   (+ MMSYSERR_BASE 20));/* driver does not call DriverCallback */
(define MMSYSERR_LASTERROR    (+ MMSYSERR_BASE 20));/* last error in range */

;/****************************************************************************

;                MIDI audio support

;****************************************************************************/

;/* MIDI error return values */
(define MIDIERR_UNPREPARED    (+ MIDIERR_BASE 0));   /* header not prepared */
(define MIDIERR_STILLPLAYING  (+ MIDIERR_BASE 1));   /* still something playing */
(define MIDIERR_NOMAP         (+ MIDIERR_BASE 2));   /* no configured instruments */
(define MIDIERR_NOTREADY      (+ MIDIERR_BASE 3));   /* hardware is still busy */
(define MIDIERR_NODEVICE      (+ MIDIERR_BASE 4));   /* port no longer connected */
(define MIDIERR_INVALIDSETUP  (+ MIDIERR_BASE 5));   /* invalid MIF */
(define MIDIERR_BADOPENMODE   (+ MIDIERR_BASE 6));   /* operation unsupported w/ open mode */
(define MIDIERR_DONT_CONTINUE (+ MIDIERR_BASE 7));   /* thru device 'eating' a message */
(define MIDIERR_LASTERROR     (+ MIDIERR_BASE 7));   /* last error in range */

(define MIDIMAPPER     -1);((UINT)-1)
(define MIDI_MAPPER    -1);((UINT)-1)

;/* flags for dwFlags parm of midiInOpen() */
(define MIDI_IO_STATUS      #x00000020)

;/* flags for wFlags parm of midiOutCachePatches(), midiOutCacheDrumPatches() */
(define MIDI_CACHE_ALL      1)
(define MIDI_CACHE_BESTFIT  2)
(define MIDI_CACHE_QUERY    3)
(define MIDI_UNCACHE        4)

;/* flags for wTechnology field of MIDIOUTCAPS structure */
(define MOD_MIDIPORT    1);  /* output port */
(define MOD_SYNTH       2);  /* generic internal synth */
(define MOD_SQSYNTH     3);  /* square wave internal synth */
(define MOD_FMSYNTH     4);  /* FM internal synth */
(define MOD_MAPPER      5);  /* MIDI mapper */

;/* flags for dwSupport field of MIDIOUTCAPS structure */
(define MIDICAPS_VOLUME          #x0001);  /* supports volume control */
(define MIDICAPS_LRVOLUME        #x0002);  /* separate left-right volume control */
(define MIDICAPS_CACHE           #x0004);
(define MIDICAPS_STREAM          #x0008);  /* driver supports midiStreamOut directly */

; /* MIDI data block header */
; typedef struct midihdr_tag {
;     LPSTR       lpData;               /* pointer to locked data block */
;     DWORD       dwBufferLength;       /* length of data in data block */
;     DWORD       dwBytesRecorded;      /* used for input only */
;     DWORD       dwUser;               /* for client's use */
;     DWORD       dwFlags;              /* assorted flags (see defines) */
;     struct midihdr_tag FAR *lpNext;   /* reserved for driver */
;     DWORD       reserved;             /* reserved for driver */
;     DWORD       dwOffset;             /* Callback offset into buffer */
;     DWORD       dwReserved[8];        /* Reserved for MMSYSTEM */
; } MIDIHDR, *PMIDIHDR, NEAR *NPMIDIHDR, FAR *LPMIDIHDR;

; typedef struct midievent_tag
; {
;     DWORD       dwDeltaTime;          /* Ticks since last event */
;     DWORD       dwStreamID;           /* Reserved; must be zero */
;     DWORD       dwEvent;              /* Event type and parameters */
;     DWORD       dwParms[1];           /* Parameters if this is a long event */
; } MIDIEVENT;

; typedef struct midistrmbuffver_tag
; {
;     DWORD       dwVersion;                  /* Stream buffer format version */
;     DWORD       dwMid;                      /* Manufacturer ID as defined in MMREG.H */
;     DWORD       dwOEMVersion;               /* Manufacturer version for custom ext */
; } MIDISTRMBUFFVER;

;/* flags for dwFlags field of MIDIHDR structure */
(define MHDR_DONE       #x00000001);       /* done bit */
(define MHDR_PREPARED   #x00000002);       /* set if header prepared */
(define MHDR_INQUEUE    #x00000004);       /* reserved for driver */
(define MHDR_ISSTRM     #x00000008);       /* Buffer is stream buffer */

; /* */
; /* Type codes which go in the high byte of the event DWORD of a stream buffer */
; /* */
; /* Type codes 00-7F contain parameters within the low 24 bits */
; /* Type codes 80-FF contain a length of their parameter in the low 24 */
; /* bits, followed by their parameter data in the buffer. The event */
; /* DWORD contains the exact byte length; the parm data itself must be */
; /* padded to be an even multiple of 4 bytes long. */
; /* */

(define MEVT_F_SHORT        #x00000000)
(define MEVT_F_LONG         #x80000000)
(define MEVT_F_CALLBACK     #x40000000)

(define (MEVT_EVENTTYPE x) (& #xFF (>> x 24)))
(define (MEVT_EVENTPARM x) (& #x00FFFFFF x))
;#define MEVT_EVENTTYPE(x)   ((BYTE)(((x)>>24)&0xFF))
;#define MEVT_EVENTPARM(x)   ((DWORD)((x)&0x00FFFFFFL))

(define MEVT_SHORTMSG   #x00); ((BYTE)#x00)    /* parm = shortmsg for midiOutShortMsg */
(define MEVT_TEMPO      #x01); ((BYTE)#x01)    /* parm = new tempo in microsec/qn     */
(define MEVT_NOP        #x02); ((BYTE)#x02)    /* parm = unused; does nothing         */

;/* #x04-#x7F reserved */

(define MEVT_LONGMSG    #x80); ((BYTE)#x80)    /* parm = bytes to send verbatim       */
(define MEVT_COMMENT    #x82); ((BYTE)#x82)    /* parm = comment data                 */
(define MEVT_VERSION    #x84); ((BYTE)#x84)    /* parm = MIDISTRMBUFFVER struct       */

;/* #x81-#xFF reserved */

(define MIDISTRM_ERROR  -2)

;/* */
;/* Structures and defines for midiStreamProperty */
;/* */
(define MIDIPROP_SET        #x80000000)
(define MIDIPROP_GET        #x40000000)

;/* These are intentionally both non-zero so the app cannot accidentally */
;/* leave the operation off and happen to appear to work due to default */
;/* action. */

(define MIDIPROP_TIMEDIV    #x00000001)
(define MIDIPROP_TEMPO      #x00000002)

;typedef struct midiproptimediv_tag
;{
;    DWORD       cbStruct;
;    DWORD       dwTimeDiv;
;} MIDIPROPTIMEDIV, FAR *LPMIDIPROPTIMEDIV

;typedef struct midiproptempo_tag
;{
;    DWORD       cbStruct;
;    DWORD       dwTempo;
;} MIDIPROPTEMPO, FAR *LPMIDIPROPTEMPO;


; /* MIDI function prototypes */
; WINMMAPI UINT WINAPI midiOutGetNumDevs(void);
; #if(WINVER >= 0x0400)
; WINMMAPI MMRESULT WINAPI midiStreamOpen(LPHMIDISTRM phms, LPUINT puDeviceID, DWORD cMidi, DWORD dwCallback, DWORD dwInstance, DWORD fdwOpen);
; WINMMAPI MMRESULT WINAPI midiStreamClose(HMIDISTRM hms);

; WINMMAPI MMRESULT WINAPI midiStreamProperty(HMIDISTRM hms, LPBYTE lppropdata, DWORD dwProperty);
; WINMMAPI MMRESULT WINAPI midiStreamPosition(HMIDISTRM hms, LPMMTIME lpmmt, UINT cbmmt);

; WINMMAPI MMRESULT WINAPI midiStreamOut(HMIDISTRM hms, LPMIDIHDR pmh, UINT cbmh);
; WINMMAPI MMRESULT WINAPI midiStreamPause(HMIDISTRM hms);
; WINMMAPI MMRESULT WINAPI midiStreamRestart(HMIDISTRM hms);
; WINMMAPI MMRESULT WINAPI midiStreamStop(HMIDISTRM hms);

; #ifdef _WIN32
; WINMMAPI MMRESULT WINAPI midiConnect(HMIDI hmi, HMIDIOUT hmo, LPVOID pReserved);
; WINMMAPI MMRESULT WINAPI midiDisconnect(HMIDI hmi, HMIDIOUT hmo, LPVOID pReserved);
; #endif
; #endif /* WINVER >= 0x0400 */

; #ifdef _WIN32

; WINMMAPI MMRESULT WINAPI midiOutGetDevCapsA(UINT uDeviceID, LPMIDIOUTCAPSA pmoc, UINT cbmoc);
; WINMMAPI MMRESULT WINAPI midiOutGetDevCapsW(UINT uDeviceID, LPMIDIOUTCAPSW pmoc, UINT cbmoc);
; #ifdef UNICODE
; #define midiOutGetDevCaps  midiOutGetDevCapsW
; #else
; #define midiOutGetDevCaps  midiOutGetDevCapsA
; #endif // !UNICODE

; #else
; MMRESULT WINAPI midiOutGetDevCaps(UINT uDeviceID, LPMIDIOUTCAPS pmoc, UINT cbmoc);
; #endif

; #if (WINVER >= 0x0400)
; WINMMAPI MMRESULT WINAPI midiOutGetVolume(HMIDIOUT hmo, LPDWORD pdwVolume);
; WINMMAPI MMRESULT WINAPI midiOutSetVolume(HMIDIOUT hmo, DWORD dwVolume);
; #else
; WINMMAPI MMRESULT WINAPI midiOutGetVolume(UINT uId, LPDWORD pdwVolume);
; WINMMAPI MMRESULT WINAPI midiOutSetVolume(UINT uId, DWORD dwVolume);
; #endif

; #ifdef _WIN32

; WINMMAPI MMRESULT WINAPI midiOutGetErrorTextA(MMRESULT mmrError, LPSTR pszText, UINT cchText);
; WINMMAPI MMRESULT WINAPI midiOutGetErrorTextW(MMRESULT mmrError, LPWSTR pszText, UINT cchText);
; #ifdef UNICODE
; #define midiOutGetErrorText  midiOutGetErrorTextW
; #else
; #define midiOutGetErrorText  midiOutGetErrorTextA
; #endif // !UNICODE

; #else
; WINMMAPI MMRESULT WINAPI midiOutGetErrorText(MMRESULT mmrError, LPSTR pszText, UINT cchText);
; #endif

; WINMMAPI MMRESULT WINAPI midiOutOpen(LPHMIDIOUT phmo, UINT uDeviceID,
;     DWORD dwCallback, DWORD dwInstance, DWORD fdwOpen);
; WINMMAPI MMRESULT WINAPI midiOutClose(HMIDIOUT hmo);
; WINMMAPI MMRESULT WINAPI midiOutPrepareHeader(HMIDIOUT hmo, LPMIDIHDR pmh, UINT cbmh);
; WINMMAPI MMRESULT WINAPI midiOutUnprepareHeader(HMIDIOUT hmo, LPMIDIHDR pmh, UINT cbmh);
; WINMMAPI MMRESULT WINAPI midiOutShortMsg(HMIDIOUT hmo, DWORD dwMsg);
; WINMMAPI MMRESULT WINAPI midiOutLongMsg(HMIDIOUT hmo, LPMIDIHDR pmh, UINT cbmh);
; WINMMAPI MMRESULT WINAPI midiOutReset(HMIDIOUT hmo);
; WINMMAPI MMRESULT WINAPI midiOutCachePatches(HMIDIOUT hmo, UINT uBank, LPWORD pwpa, UINT fuCache);
; WINMMAPI MMRESULT WINAPI midiOutCacheDrumPatches(HMIDIOUT hmo, UINT uPatch, LPWORD pwkya, UINT fuCache);
; WINMMAPI MMRESULT WINAPI midiOutGetID(HMIDIOUT hmo, LPUINT puDeviceID);

; #if (WINVER >= 0x030a)
; #ifdef _WIN32
; WINMMAPI MMRESULT WINAPI midiOutMessage(HMIDIOUT hmo, UINT uMsg, DWORD dw1, DWORD dw2);
; #else
; DWORD WINAPI midiOutMessage(HMIDIOUT hmo, UINT uMsg, DWORD dw1, DWORD dw2);
; #endif
; #endif /* ifdef WINVER >= 0x030a */

; WINMMAPI UINT WINAPI midiInGetNumDevs(void);

; #ifdef _WIN32

; WINMMAPI MMRESULT WINAPI midiInGetDevCapsA(UINT uDeviceID, LPMIDIINCAPSA pmic, UINT cbmic);
; WINMMAPI MMRESULT WINAPI midiInGetDevCapsW(UINT uDeviceID, LPMIDIINCAPSW pmic, UINT cbmic);
; #ifdef UNICODE
; #define midiInGetDevCaps  midiInGetDevCapsW
; #else
; #define midiInGetDevCaps  midiInGetDevCapsA
; #endif // !UNICODE
; WINMMAPI MMRESULT WINAPI midiInGetErrorTextA(MMRESULT mmrError, LPSTR pszText, UINT cchText);
; WINMMAPI MMRESULT WINAPI midiInGetErrorTextW(MMRESULT mmrError, LPWSTR pszText, UINT cchText);
; #ifdef UNICODE
; #define midiInGetErrorText  midiInGetErrorTextW
; #else
; #define midiInGetErrorText  midiInGetErrorTextA
; #endif // !UNICODE

; #else
; MMRESULT WINAPI midiInGetDevCaps(UINT uDeviceID, LPMIDIINCAPS pmic, UINT cbmic);
; WINMMAPI MMRESULT WINAPI midiInGetErrorText(MMRESULT mmrError, LPSTR pszText, UINT cchText);
; #endif

; WINMMAPI MMRESULT WINAPI midiInOpen(LPHMIDIIN phmi, UINT uDeviceID,
;     DWORD dwCallback, DWORD dwInstance, DWORD fdwOpen);
; WINMMAPI MMRESULT WINAPI midiInClose(HMIDIIN hmi);
; WINMMAPI MMRESULT WINAPI midiInPrepareHeader(HMIDIIN hmi, LPMIDIHDR pmh, UINT cbmh);
; WINMMAPI MMRESULT WINAPI midiInUnprepareHeader(HMIDIIN hmi, LPMIDIHDR pmh, UINT cbmh);
; WINMMAPI MMRESULT WINAPI midiInAddBuffer(HMIDIIN hmi, LPMIDIHDR pmh, UINT cbmh);
; WINMMAPI MMRESULT WINAPI midiInStart(HMIDIIN hmi);
; WINMMAPI MMRESULT WINAPI midiInStop(HMIDIIN hmi);
; WINMMAPI MMRESULT WINAPI midiInReset(HMIDIIN hmi);
; WINMMAPI MMRESULT WINAPI midiInGetID(HMIDIIN hmi, LPUINT puDeviceID);

; #if (WINVER >= 0x030a)
; #ifdef _WIN32
; WINMMAPI MMRESULT WINAPI midiInMessage(HMIDIIN hmi, UINT uMsg, DWORD dw1, DWORD dw2);
; #else
; DWORD WINAPI midiInMessage(HMIDIIN hmi, UINT uMsg, DWORD dw1, DWORD dw2);
; #endif
; #endif /* ifdef WINVER >= 0x030a */

; #endif /* ifndef _WIN32_VXD */

; #endif  /* ifndef MMNOMIDI */


; /* MCI extensions for MIDI sequencer devices */

; /* flags for the dwReturn field of MCI_STATUS_PARMS parameter block */
; /* MCI_STATUS command, (dwItem == MCI_SEQ_STATUS_DIVTYPE) */
(define     MCI_SEQ_DIV_PPQN            (+ 0 MCI_SEQ_OFFSET))
(define     MCI_SEQ_DIV_SMPTE_24        (+ 1 MCI_SEQ_OFFSET))
(define     MCI_SEQ_DIV_SMPTE_25        (+ 2 MCI_SEQ_OFFSET))
(define     MCI_SEQ_DIV_SMPTE_30DROP    (+ 3 MCI_SEQ_OFFSET))
(define     MCI_SEQ_DIV_SMPTE_30        (+ 4 MCI_SEQ_OFFSET))

; /* flags for the dwMaster field of MCI_SEQ_SET_PARMS parameter block */
; /* MCI_SET command, (dwFlags == MCI_SEQ_SET_MASTER) */
(define     MCI_SEQ_FORMAT_SONGPTR      #x4001)
(define     MCI_SEQ_FILE                #x4002)
(define     MCI_SEQ_MIDI                #x4003)
(define     MCI_SEQ_SMPTE               #x4004)
(define     MCI_SEQ_NONE                65533)
(define     MCI_SEQ_MAPPER              65535)

;/* flags for the dwItem field of MCI_STATUS_PARMS parameter block */
(define MCI_SEQ_STATUS_TEMPO            #x00004002)
(define MCI_SEQ_STATUS_PORT             #x00004003)
(define MCI_SEQ_STATUS_SLAVE            #x00004007)
(define MCI_SEQ_STATUS_MASTER           #x00004008)
(define MCI_SEQ_STATUS_OFFSET           #x00004009)
(define MCI_SEQ_STATUS_DIVTYPE          #x0000400A)
(define MCI_SEQ_STATUS_NAME             #x0000400B)
(define MCI_SEQ_STATUS_COPYRIGHT        #x0000400C)

;/* flags for the dwFlags parameter of MCI_SET command message */
(define MCI_SEQ_SET_TEMPO               #x00010000)
(define MCI_SEQ_SET_PORT                #x00020000)
(define MCI_SEQ_SET_SLAVE               #x00040000)
(define MCI_SEQ_SET_MASTER              #x00080000)
(define MCI_SEQ_SET_OFFSET              #x01000000)

; /* parameter block for MCI_SET command message */
; typedef struct tagMCI_SEQ_SET_PARMS {
;     DWORD   dwCallback;
;     DWORD   dwTimeFormat;
;     DWORD   dwAudio;
;     DWORD   dwTempo;
;     DWORD   dwPort;
;     DWORD   dwSlave;
;     DWORD   dwMaster;
;     DWORD   dwOffset;
; } MCI_SEQ_SET_PARMS, *PMCI_SEQ_SET_PARMS, FAR * LPMCI_SEQ_SET_PARMS;
