#include "dcom.h"

    //==========================================================================
   //
  // HRESULTs
 //
//==========================================================================

static HRESULT HresultFromLisp(LISP h)
{
    if (TYPE(h) != tc_hresult)
        return -1;
    else
        return ((HRESULT)(STR(h)));
}

static LISP LispFromHresult(HRESULT h)
{
    LISP z = newcell(tc_hresult);
    STR(z) = (char*)h;
    DIM(z) = 0;
    return z;
}

LISP LispHresultFromLispVal(LISP val)
{
    if (TYPE(val) != tc_flonum)
        return err("wta LispHresultFromLispVal", val);

    return LispFromHresult((HRESULT)FLONM(val));
}

static inline void SetErrobjToHresult(HRESULT hr)
{
    setvar(sym_errobj, LispFromHresult(hr), NIL);
}

static inline void MustSucceed(HRESULT hr)
{
    if (FAILED(hr))
        SetErrobjToHresult(hr);
}

void HresultPrin1(LISP h, struct gen_printio *f)
{
    LPSTR lpBuffer;

    FormatMessage
    (
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,               // pointer to message source
        HresultFromLisp(h), // requested message identifier
        0,                  // language identifier for requested message
        (LPTSTR)&lpBuffer,  // pointer to message buffer
        1,                  // maximum size of message buffer
        NULL                // address of array of message inserts
    );

    char sz[512];
    // kill the newline
    if (NULL == lpBuffer)
    {
        sprintf(sz, "#{HRESULT 0x%08x \"Unknown or new error\"}", HresultFromLisp(h));
    }
    else
    {
        DWORD cbBuf = strlen(lpBuffer);
        if (lpBuffer[cbBuf-2] == '\015')
            lpBuffer[cbBuf-2] = '\0';

        sprintf(sz, "#{HRESULT 0x%08x \"%s\"}", HresultFromLisp(h), lpBuffer);
        LocalFree(lpBuffer);
    }
    gput_st(f, sz);
}

LISP HresultEqual(LISP a, LISP b)
{
    if (  (TYPE(a) != tc_hresult)
       || (TYPE(b) != tc_hresult)
       || (DIM(a)  != DIM(b))
       || (DIM(a)  != 0)
       )
        return NIL;

    BOOL f = (HRESULT)STR(a) == (HRESULT)STR(b);

    // do it the kindergarten way, so we can see it with the debugger.
    if (f)
        return sym_t;
    else
        return NIL;
}

    //==========================================================================
   //
  // OLE & LISP strings
 //
//==========================================================================

static char * SzFromOleString(LPOLESTR sz, DWORD& dw)
{
    if (sz == NULL)
    {
        dw = 0;
        return NULL;
    }

    DWORD cbNeeded = WideCharToMultiByte (CP_ACP, 0, sz, -1, NULL, 0, NULL, NULL);
    char *szOut    = 0;
    DWORD cbCheck;

    if (cbNeeded == 0)
    {
        szOut = (char*)malloc(1);
        if (szOut == NULL)
        {
            return NULL;
        }
        szOut[0] = '\0';
        dw = 1;
        return szOut;
    }
    else
    {
        szOut = (char*)malloc(cbNeeded);
        cbCheck  = WideCharToMultiByte (CP_ACP, 0, sz, -1, szOut, cbNeeded, NULL, NULL);
        dw = cbCheck - 1; // don't include NULL
        return szOut;
    }
}

static LISP StringFromOleStringDimHasNoNull(LPOLESTR sz)
{
    DWORD cb;
    char * szOut = SzFromOleString(sz, cb);
    return strcons(cb, szOut);
}

static inline LISP LispFromString(char* szIn)
{
    return strcons(-1, szIn);
}

static LPOLESTR OleStringFromString(LISP s)
{
    if (s == NIL)
        return NULL;

    DWORD cbNeeded = MultiByteToWideChar(CP_ACP, 0, STR(s), -1, NULL, 0);
    LPOLESTR szOut = (LPOLESTR)malloc(cbNeeded*sizeof(OLECHAR));
    DWORD cbCheck  = MultiByteToWideChar (CP_ACP, 0, STR(s), -1, szOut, cbNeeded);
    if (cbCheck < cbNeeded)
    {
        // TODO: Handle this error (figure out error handling later)
    }
    return szOut;
}

    //==========================================================================
   //
  // The GUID ADT
 //
//==========================================================================

void LispGuidGcFree(LISP ptr)
{
    GUID *h;

    if ((h = (GUID*)STR(ptr)))
    {
        free(h);
        STR(ptr) = NULL;
        DIM(ptr) = 0;
    }
}

LISP LispGuidEqual(LISP a, LISP b)
{
    if (  (TYPE(a) != tc_guid)
       || (TYPE(b) != tc_guid)
       || (DIM(a)  != DIM(b))
       || (DIM(a)  != sizeof(GUID))
       )
    {
        return NIL;
    }

    BOOL f = memcmp(STR(a), STR(b), sizeof(GUID)) == 0 ;

    // do it the kindergarten way, so we can see it with the debugger.
    if (f)
        return sym_t;
    else
        return NIL;
}

static BOOL FGetGuidFromLispGuid(GUID* pg, LISP g)
{
    if ((pg == 0) || (g == 0) || (TYPE(g) != tc_guid) || (STR(g) == 0))
        return FALSE;

    memcpy (pg, STR(g), sizeof(GUID));

    return TRUE;
}

LISP StringFromLispGuid(LISP g)
{
    GUID guid;

    if (! FGetGuidFromLispGuid(&guid, g))
        return NIL;

    OLECHAR sztemp[40];

    HRESULT hr = StringFromGUID2(guid, sztemp, 40*sizeof(OLECHAR));

    SetErrobjToHresult(hr);

    if (FAILED(hr))
        return NIL;

    return StringFromOleStringDimHasNoNull(sztemp);
}

void LispGuidPrin1(LISP g, struct gen_printio *f)
{
    GUID guid;

    if (! FGetGuidFromLispGuid(&guid, g))
        gput_st(f, "#{INVALID GUID}");

    else
    {
        LISP s = StringFromLispGuid(g);
        char buff[64];
        strcpy(buff, "#{GUID ");
        strncat(buff, STR(s)+1, 37);
        gput_st(f, buff);
    }
}

LISP LispGuidFromString(LISP s)
{
    if ((s == 0) || (TYPE(s) != tc_string) || (STR(s) == 0))
        return NIL;

    LPOLESTR sztemp = OleStringFromString(s);

    LISP z = newcell(tc_guid);
    DIM(z) = 0;
    STR(z) = (char*)malloc(sizeof(GUID)+1);

    if (STR(z) != 0)
    {
        memset(STR(z), 0, sizeof(GUID)+1);
        DIM(z) = sizeof(GUID);
        HRESULT hr = CLSIDFromString(sztemp, (GUID*)STR(z));
        free(sztemp);
        SetErrobjToHresult(hr);
        if (FAILED(hr))
            return NIL;

        return z;
    }
    else
    {
        SetErrobjToHresult(E_OUTOFMEMORY);
        return NIL;
    }
}

LISP LispGuidFromProgIDString(LISP s)
{
    if ((s == 0) || (TYPE(s) != tc_string) || (STR(s) == 0))
        return NIL;

    LPOLESTR sztemp = OleStringFromString(s);

    LISP z = newcell(tc_guid);
    DIM(z) = 0;
    STR(z) = (char*)malloc(sizeof(GUID)+1);

    if (STR(z) != 0)
    {
        memset(STR(z), 0, sizeof(GUID)+1);
        DIM(z) = sizeof(GUID);

        HRESULT hr = CLSIDFromProgID(sztemp, (GUID*)STR(z));

        free(sztemp);
        SetErrobjToHresult(hr);

        if (FAILED(hr))
            return NIL;

        return z;
    }
    else
    {
        SetErrobjToHresult(E_OUTOFMEMORY);
        return NIL;
    }
}

LISP LispGuidGen(void)
{
    GUID guid = GUID_NULL;
    ::CoCreateGuid(&guid);

    LISP z = newcell(tc_guid);
    STR(z) = (char*)malloc(sizeof(GUID)+1);
    if (STR(z) != 0)
        memset(STR(z), 0, sizeof(GUID)+1);
    if (STR(z) != 0)
        memcpy(STR(z), &guid, sizeof(GUID));

    return z;
}

    //==========================================================================
   //
  // Interface Pointers
 //
//==========================================================================
#define SYMBOLIC_INTERFACES 0

#if SYMBOLIC_INTERFACES
struct SInterface
{
    LISP      sym;
    IUnknown *pUnk;
};

#   define SINT(l)  ((SInterface*)(STR(l)))
#   define PSINT(l) ((SInterface**)(&(STR(l))))
#   define PUNK(l)  (0) // TODO
#   define DISP(l)  (0) // TODO
#   define TYPI(l)  (0) // TODO
#else
#   define PUNK(l)  ((IUnknown*) (STR(l)))
#   define DISP(l)  ((IDispatch*)(STR(l)))
#   define TYPI(l)  ((ITypeInfo*)(STR(l)))
#endif

#if SYMBOLIC_INTERFACES
LISP LispFromInterface(IUnknown* i_pUnk, LISP i_sym)
#else
LISP LispFromInterface(IUnknown* i_pUnk)
#endif
{
    LISP z = newcell(tc_interface);

#   if SYMBOLIC_INTERFACES
        SInterface *psi = new SInterface;
        psi->pUnk       = i_pUnk;
        psi->sym        = i_sym;
        *PSINT(z)       = psi;
#   else
        STR(z) = (char*)i_pUnk;
#   endif

    DIM(z) = 4;
    return z;
}

LISP LispInterfaceFromLispVal(LISP val)
{
    LISP z = newcell(tc_interface);

    if (TYPE(val) == tc_cptr)
    {
        STR(z) = (char*)CPTR(val);
        DIM(z) = 4;
    }
    else if (TYPE(val) == tc_flonum)
    {
        LISP z = newcell(tc_interface);
        STR(z) = (char*)(IUnknown*)(DWORD)FLONM(val);
        DIM(z) = 4;
    }
    else
    {
        return err("wta Interface", val);
    }

    return z;
}

LISP LispInterfaceEqual(LISP a, LISP b)
{
    BOOL f;

    if (  (TYPE(a) != tc_interface)
       || (TYPE(b) != tc_interface)
       || (DIM(a)  != DIM(b))
       || (DIM(a)  != 4)
       )
    {
        return NIL;
    }

#   if SYMBOLIC_INTERFACES
        SInterface *psiA, *psiB;

        psiA = SINT(a);
        psiB = SINT(b);

        f = (psiA->pUnk == psiB->pUnk);
        LISP symCheck = equal(psiA->sym, psiB->sym);
        f = (f && (symCheck == sym_t));
#   else
        f = (STR(a) == STR(b));
#   endif

    // do it the kindergarten way, so we can see it with the debugger.
    if (f)
        return sym_t;
    else
        return NIL;
}

void LispInterfacePrin1(LISP g, struct gen_printio *f)
{
    char sz[64];
#   if SYMBOLIC_INTERFACES
        sprintf(sz, "#{INTERFACE 0x%08x \"%s\"}", SINT(g)->pUnk, SYM(SINT(g)->sym));
#   else
        sprintf(sz, "#{INTERFACE 0x%08x}", PUNK(g));
#   endif
    gput_st(f, sz);
}

void LispInterfaceFree(LISP ptr)
{
    IUnknown* pUnk;
    if (pUnk = PUNK(ptr))
    {
        pUnk->Release();
    }
}

    //==========================================================================
   //
  // COM APIs
 //
//==========================================================================
LISP SiodCoInitialize(void)
{
    HRESULT hr = CoInitialize(NULL);
    SetErrobjToHresult(hr);
    return FAILED(hr) ? NIL : sym_t;
}

LISP SiodCoUninitialize(void)
{
    CoUninitialize();
    SetErrobjToHresult(S_OK);
    return sym_t;
}

static inline DWORD DwFromFlonum(LISP f)
{
    return DWORD(FLONM(f));
}

LISP SiodCoCreateInstance(LISP clsid, LISP iid, LISP flagflonum)
{
    GUID gclsid;
    GUID giid;

    if (! FGetGuidFromLispGuid(&gclsid, clsid))
    {
        setvar(sym_errobj, clsid, NIL);
        return NIL;
    }
    if (! FGetGuidFromLispGuid(&giid, iid))
    {
        setvar(sym_errobj, iid, NIL);
        return NIL;
    }

    DWORD dwContext = DwFromFlonum(flagflonum);

    IUnknown* pUnk;

    HRESULT hr = CoCreateInstance
    (
        gclsid,         //Class identifier (CLSID) of the object
        NULL,           //Pointer to whether object is or isn’t part of an aggregate
        dwContext,      //Context for running executable code
        giid,           //Reference to the identifier of the interface
        (void**)&pUnk   //Indirect pointer to requested interface
    );

    SetErrobjToHresult(hr);

    return LispFromInterface(pUnk);
}

LISP SiodQueryInterface(LISP punk, LISP iid)
{
    if (! (TYPE(punk) == tc_interface))
        return err("wta IUnknown", punk);

    if (PUNK(punk) == NULL)
        return err("Null IUnknown", punk);

    GUID giid;

    if (! FGetGuidFromLispGuid(&giid, iid))
    {
        setvar(sym_errobj, iid, NIL);
        return NIL;
    }

    IUnknown* pUnkNew; // can't hard code the queried interface!

    HRESULT hr = PUNK(punk)->QueryInterface
    (
        giid,
        (void**)&pUnkNew
    );

    SetErrobjToHresult(hr);

    return LispFromInterface(pUnkNew);
}

LISP SiodAddRef(LISP punk)
{
    if (! (TYPE(punk) == tc_interface))
        return err("wta IUnknown", punk);

    if (PUNK(punk) == NULL)
        return err("Null IUnknown", punk);

    DWORD dwNewCount = PUNK(punk)->AddRef();

    SetErrobjToHresult(S_OK);

    return flocons(dwNewCount);
}

LISP SiodRelease(LISP punk)
{
    if (! (TYPE(punk) == tc_interface))
        return err("wta IUnknown", punk);

    if (PUNK(punk) == NULL)
        return err("Null IUnknown", punk);

    DWORD dwNewCount = PUNK(punk)->Release();

    SetErrobjToHresult(S_OK);

    return flocons(dwNewCount);
}

LISP SiodGetTypeInfoCount(LISP disp)
{
    if (! (TYPE(disp) == tc_interface))
        return err("wta IDispatch", disp);

    if (DISP(disp) == NULL)
        return err("Null IDispatch", disp);

    UINT uintInfo;

    HRESULT hr = DISP(disp)->GetTypeInfoCount(&uintInfo);

    SetErrobjToHresult(hr);

    return flocons(uintInfo);
}

//----------------------------------------------------------------
// Function:       SiodGetTypeInfo
// Inputs:         idispatch
//                 index (0-based)
//                 LCID integer
// Returns:        ITypeInfo interface
// Outputs:
// Error Handling: Sets errobj to HRESULT
// Notes:
//----------------------------------------------------------------
LISP SiodGetTypeInfo(LISP disp, LISP i_itinfo, LISP i_lcid)
{
    if (! (TYPE(disp) == tc_interface))
        return err("wta IDispatch", disp);

    if (DISP(disp) == NULL)
        return err("Null IDispatch", disp);

    if (i_itinfo == NULL)
        return err ("Null itinfo index", i_itinfo) ;

    if (i_lcid == NULL)
        return err ("Null LCID", i_lcid) ;

    UINT itinfo = (UINT)FLONM(i_itinfo);
    LCID lcid   = (LCID)FLONM(i_lcid);
    ITypeInfo *pITI;

    HRESULT hr = DISP(disp)->GetTypeInfo(itinfo, lcid, &pITI);

    SetErrobjToHresult(hr);

    return LispFromInterface(pITI);
}

    //==========================================================================
   //
  // LISP Support funcs
 //
//==========================================================================
LISP ListFromLisps(LISP last, ...)
{
    LISP val = last;

    LISP x = NIL;

    va_list(marker);

    va_start(marker, last);

    while(val != NIL)
    {
        x = cons(val, x);

        val = va_arg(marker, LISP);
    }

    va_end(marker);

    return x;
}

LISP AlistFromLisps(LISP lastKey, ...)
{
    LISP key = lastKey;
    LISP val = NIL;

    LISP x = NIL;
    LISP y = NIL;

    va_list(marker);

    va_start(marker, lastKey);

    while(key != NIL)
    {
        val = va_arg(marker, LISP);

        y = cons(val, NIL);
        y = cons(key, y);

        x = cons(y, x);

        key = va_arg(marker, LISP);
    }

    va_end(marker);

    return x;
}

     //==========================================================================
    //
   // ADT Boilerplate (templates won't work because of lack of token pasting)
  // This is for Lisp representations of pointers-to-structs
 //
//==========================================================================

#define DEFINE_LISP_FROM_ADT_FUNC(T, t) \
LISP LispFrom ## T (T* pt)               \
{   if (pt == NULL) return NIL;           \
    LISP s = newcell(tc_ ## t);            \
    T* pt2 = new T;                         \
    if (pt2 == NULL) return NIL;             \
    memcpy(pt2, pt, sizeof(T));               \
    STR(s) = (char*)pt2;                       \
    DIM(s) = sizeof(T);                         \
    return s;                                    \
}

#define DEFINE_ADT_FROM_LISP_FUNC(T, t) \
T * T ## FromLisp(LISP z)                \
{   if (  (TYPE(z) != tc_ ## t)           \
       || (DIM(z)  != sizeof(T))           \
       )                                    \
       return 0;                             \
    return (T*)STR(z);                        \
}

#define DEFINE_FREE_FUNC(T)   \
void Lisp ## T ## Free(LISP z) \
{   T* pt;                      \
    if (pt = (T*)STR(z))         \
    {   delete pt;                \
        STR(z) = NULL;             \
        DIM(z) = 0;                 \
    }                                \
}

#define DEFINE_EQUAL_FUNC(T, t)               \
LISP Lisp ## T ## Equal(LISP a, LISP b)        \
{   if (  (TYPE(a) != tc_ ## t)                 \
       || (TYPE(b) != tc_ ## t)                  \
       || (DIM(a)  != DIM(b))                     \
       || (DIM(a)  != sizeof(T))                   \
       )                                            \
       return NIL;                                   \
    if (STR(a) == NULL || STR(b) == NULL) return NIL; \
    BOOL f = (memcmp(STR(a), STR(b), sizeof(T)) == 0); \
    if (f) return sym_t; else return NIL;               \
}

#define DEFINE_PRINT_FUNC(T, t)                       \
void Lisp ## T ## Prin1(LISP g, struct gen_printio *f) \
{   if (! T ## FromLisp(g))                             \
        gput_st(f, "#{INVALID " # T "}");                \
    else                                                  \
    {   char sz[64];                                       \
        sprintf(sz, "#{" # T " 0x%08x}", STR(g));           \
        gput_st(f, sz);                                      \
    }                                                         \
}

#define DEFINE_LISP_TYPE(T, t)        \
        DEFINE_LISP_FROM_ADT_FUNC(T, t)\
        DEFINE_ADT_FROM_LISP_FUNC(T, t) \
        DEFINE_FREE_FUNC(T)              \
        DEFINE_EQUAL_FUNC(T, t)           \
        DEFINE_PRINT_FUNC(T, t)

#define SET_GC_HOOKS(T, t)                  \
    set_gc_hooks(tc_ ## t, NULL, NULL, NULL, \
                Lisp ## T ## Free, &lGcKind);

#define SET_PRINT_HOOKS(T, t) \
    set_print_hooks(tc_ ## t, Lisp ## T ## Prin1);

#define SET_OTHER_HOOKS(T, t)                      \
    pUserTypeHooks = get_user_type_hooks(tc_ ## t); \
    pUserTypeHooks->equal = Lisp ## T ## Equal;


    //==========================================================================
   //
  // TYPEATTR ADT
 //
//==========================================================================
DEFINE_LISP_TYPE(TYPEATTR, typeattr)

#define GET_MEMBER(member, type, lisp) \
    (((type*)STR(lisp))->member)

#define GET_FLONM(member, type, lisp) \
    flocons((double)GET_MEMBER(member, type, lisp))

inline LISP CFuncsFromLispTypeattr(LISP z) {return GET_FLONM(cFuncs, TYPEATTR, z);}
inline LISP CVarsFromLispTypeattr (LISP z) {return GET_FLONM(cVars,  TYPEATTR, z);}

    //==========================================================================
   //
  // FUNCDESC ADT
 //
//==========================================================================
DEFINE_LISP_TYPE(FUNCDESC, funcdesc)



//----------------------------------------------------------------
// Function:       SiodGetFuncDesc
// Inputs:         itypeinfo, index (0-based)
// Returns:            FUNCDESC
// Outputs:
// Error Handling: Sets errobj to HRESULT or bad object
// Notes:
//----------------------------------------------------------------
LISP SiodGetFuncDesc(LISP tinfo, LISP index)
{
    if (! (TYPE(tinfo) == tc_interface))
    {
        // TODO: no way currently to check that it's actually an IUnknown*
        setvar(sym_errobj, tinfo, NIL);
        return NIL;
    }
    WORD windex = (WORD)FLONM(index);

    LPFUNCDESC pFuncDesc;

    HRESULT hr = TYPI(tinfo)->GetFuncDesc(windex, &pFuncDesc);

    SetErrobjToHresult(hr);

    LISP z = LispFromFUNCDESC(pFuncDesc);

    TYPI(tinfo)->ReleaseFuncDesc(pFuncDesc);

    return z;
}

    //==========================================================================
   //
  // VARDESC ADT
 //
//==========================================================================
DEFINE_LISP_TYPE(VARDESC, vardesc)

//----------------------------------------------------------------
// Function:       SiodGetVarDesc
// Inputs:         itypeinfo, index (0-based)
// Returns:            VARDESC
// Outputs:
// Error Handling: Sets errobj to HRESULT or bad object
// Notes:
//----------------------------------------------------------------
LISP SiodGetVarDesc(LISP tinfo, LISP index)
{
    if (! (TYPE(tinfo) == tc_interface))
    {
        // TODO: no way currently to check that it's actually an IUnknown*
        setvar(sym_errobj, tinfo, NIL);
        return NIL;
    }
    WORD windex = (WORD)FLONM(index);

    LPVARDESC pVarDesc;

    HRESULT hr = TYPI(tinfo)->GetVarDesc(windex, &pVarDesc);

    SetErrobjToHresult(hr);

    LISP z = LispFromVARDESC(pVarDesc);

    TYPI(tinfo)->ReleaseVarDesc(pVarDesc);

    return z;
}

    //==========================================================================
   //
  // TYPEDESC ADT
 //
//==========================================================================
DEFINE_LISP_TYPE(TYPEDESC, typedesc)

LISP LispStringFromTYPEDESC(const TYPEDESC& rtd, int iIndirectionCount)
{
    VARTYPE vt = rtd.vt;

    if (vt == VT_ILLEGAL)
        return strcons(-1, "[*]IllegalVartype");

    if (vt == VT_PTR) // Indirect one more time: VB & VBScript do this
        return LispStringFromTYPEDESC(rtd.lptdesc[0], 1+iIndirectionCount);

    char * szReserved = (vt & VT_RESERVED) ? " | VT_RESERVED" : "";
    char * szByref    = (vt & VT_BYREF)    ? " | VT_BYREF"    : "";
    char * szArray    = (vt & VT_ARRAY)    ? " | VT_ARRAY"    : "";
    char * szVector   = (vt & VT_VECTOR)   ? " | VT_VECTOR"   : "";

    char * szBaseType = 0;
    char * szTemp     = 0;

#   define BASETYPECASE(vt, val) \
    case vt: szBaseType = "[" # val "]" # vt; break;

    int iBaseType = vt & VT_TYPEMASK;

    switch (iBaseType)
    {
        BASETYPECASE(VT_EMPTY,            0)
        BASETYPECASE(VT_NULL,             1)
        BASETYPECASE(VT_I2,               2)
        BASETYPECASE(VT_I4,               3)
        BASETYPECASE(VT_R4,               4)
        BASETYPECASE(VT_R8,               5)
        BASETYPECASE(VT_CY,               6)
        BASETYPECASE(VT_DATE,             7)
        BASETYPECASE(VT_BSTR,             8)
        BASETYPECASE(VT_DISPATCH,         9)
        BASETYPECASE(VT_ERROR,           10)
        BASETYPECASE(VT_BOOL,            11)
        BASETYPECASE(VT_VARIANT,         12)
        BASETYPECASE(VT_UNKNOWN,         13)
        BASETYPECASE(VT_DECIMAL,         14)
        BASETYPECASE(VT_I1,              16)
        BASETYPECASE(VT_UI1,             17)
        BASETYPECASE(VT_UI2,             18)
        BASETYPECASE(VT_UI4,             19)
        BASETYPECASE(VT_I8,              20)
        BASETYPECASE(VT_UI8,             21)
        BASETYPECASE(VT_INT,             22)
        BASETYPECASE(VT_UINT,            23)
        BASETYPECASE(VT_VOID,            24)
        BASETYPECASE(VT_HRESULT,         25)
        BASETYPECASE(VT_PTR,             26)
        BASETYPECASE(VT_SAFEARRAY,       27)
        BASETYPECASE(VT_CARRAY,          28)
        BASETYPECASE(VT_USERDEFINED,     29)
        BASETYPECASE(VT_LPSTR,           30)
        BASETYPECASE(VT_LPWSTR,          31)
        BASETYPECASE(VT_FILETIME,        64)
        BASETYPECASE(VT_BLOB,            65)
        BASETYPECASE(VT_STREAM,          66)
        BASETYPECASE(VT_STORAGE,         67)
        BASETYPECASE(VT_STREAMED_OBJECT, 68)
        BASETYPECASE(VT_STORED_OBJECT,   69)
        BASETYPECASE(VT_BLOB_OBJECT,     70)
        BASETYPECASE(VT_CF,              71)
        BASETYPECASE(VT_CLSID,           72)

        default:
        {
            szTemp = new char [64];
            sprintf(szTemp, "[0x%x,%d]BadVartype", vt, iBaseType);
            szBaseType = szTemp;
            break;
        }
    }

    char sz[256];
    memset(sz, 0, 256);
    int i;
    for (i=0; i<iIndirectionCount; i++)
        strcat(sz, "*");

    strcat(sz, szBaseType);
    strcat(sz, szReserved);
    strcat(sz, szByref);
    strcat(sz, szArray);
    strcat(sz, szVector);

    if (szTemp)
        delete [] szTemp;

    return strcons(-1, sz);

#undef BASETYPECASE
}

    //==========================================================================
   //
  // SiodGetFuncdescDocumentation ADT
 //
//==========================================================================

#define MAX_NAMES 128

//----------------------------------------------------------------
// Function:       SiodGetFuncdescDocumentation
// Inputs:         itypeinfo, FUNCDESC
// Returns:            Documentation alist
// Outputs:
// Error Handling: Sets errobj to HRESULT or bad object
// Notes:
//----------------------------------------------------------------
LISP SiodGetFuncdescDocumentation(LISP itypeinfo, LISP funcdesc)
{
    if (! (TYPE(itypeinfo) == tc_interface))
    {
        // TODO: no way currently to check that it's actually an IUnknown*
        setvar(sym_errobj, itypeinfo, NIL);
        return NIL;
    }

    if (! (TYPE(funcdesc) == tc_funcdesc))
    {
        // TODO: no way currently to check that it's actually an IUnknown*
        setvar(sym_errobj, funcdesc, NIL);
        return NIL;
    }

    FUNCDESC *pF = FUNCDESCFromLisp(funcdesc);
    if (pF == NULL)
        return NIL;

    BSTR  bstrName;
    BSTR  bstrDoc;
    DWORD dwHelpID;
    BSTR  bstrHelp;
    BSTR  rgBstrNames[MAX_NAMES];
    UINT  cNames;
    UINT  i;

    HRESULT hr = S_OK;

    LISP  lName               = NIL;
    LISP  lType               = NIL;
    LISP  lResult             = NIL;

    LISP xHelp                = NIL;
    LISP xHelpID              = NIL;
    LISP xDoc                 = NIL;
    LISP xDocName             = NIL;
    LISP xName                = NIL;
    LISP xMemID               = NIL;
    LISP xCParams             = NIL;
    LISP xCParamsOpt          = NIL;
    LISP xRequiredParamsAlist = NIL;
    LISP xOptionalParamsAlist = NIL;

    LISP sHelp                = NIL;
    LISP sHelpID              = NIL;
    LISP sDoc                 = NIL;
    LISP sDocName             = NIL;
    LISP sName                = NIL;
    LISP sMemID               = NIL;
    LISP sCParams             = NIL;
    LISP sCParamsOpt          = NIL;
    LISP sRequiredParamsAlist = NIL;
    LISP sOptionalParamsAlist = NIL;

    hr = TYPI(itypeinfo)->GetDocumentation
    (
        pF->memid,
        &bstrName,
        &bstrDoc,
        &dwHelpID,
        &bstrHelp
    );

    SetErrobjToHresult(hr);
    if (FAILED(hr))
        goto bail;

    // Get parameter list
    hr = TYPI(itypeinfo)->GetNames
    (
        pF->memid,
        rgBstrNames,
        MAX_NAMES,
        &cNames
    );

    SetErrobjToHresult(hr);
    if (FAILED(hr))
        goto bail;

    xName = StringFromOleStringDimHasNoNull(rgBstrNames[0]);
    SysFreeString(rgBstrNames[0]);
    sName = rintern("Name");

    xRequiredParamsAlist = NIL;
    for (i = 0; (int)i < (pF->cParams - pF->cParamsOpt); i++)
    {
        if ((i+1) < cNames)
        {
            lName = StringFromOleStringDimHasNoNull(rgBstrNames[i+1]);
            SysFreeString(rgBstrNames[i+1]);
        }
        else
            lName = LispFromString("");

        //lType = StringFromOleStringDimHasNoNull(pF->lprgelemdescParam[i]);
        //lType = flocons(pF->lprgelemdescParam[i].tdesc.hreftype);
        lType = LispStringFromTYPEDESC(pF->lprgelemdescParam[i].tdesc, 0);

        xRequiredParamsAlist = cons
        (
            ListFromLisps(lType, lName, NIL),
            xRequiredParamsAlist
        );
    }

    xOptionalParamsAlist = NIL;
    for (i = (pF->cParams - pF->cParamsOpt); (int)i < pF->cParams; i++)
    {
        if ((i+1) < cNames)
        {
            lName = StringFromOleStringDimHasNoNull(rgBstrNames[i+1]);
            SysFreeString(rgBstrNames[i+1]);
        }
        else
        {
            lName = LispFromString("");
        }

        //lType = StringFromOleStringDimHasNoNull(pF->lprgelemdescParam[i]);
        //lType = flocons(pF->lprgelemdescParam[i].tdesc.hreftype);
        lType = LispStringFromTYPEDESC(pF->lprgelemdescParam[i].tdesc, 0);

        xOptionalParamsAlist = cons
        (
            ListFromLisps(lType, lName, NIL),
            xOptionalParamsAlist
        );
    }

    xHelp                = StringFromOleStringDimHasNoNull(bstrHelp);
    xHelpID              = flocons(dwHelpID);
    xDoc                 = StringFromOleStringDimHasNoNull(bstrDoc);
    xDocName             = StringFromOleStringDimHasNoNull(bstrName);
    xMemID               = flocons(pF->memid);

    sHelp                = rintern("Help");
    sHelpID              = rintern("HelpID");
    sDoc                 = rintern("Documentation");
    sDocName             = rintern("DocName");
    sMemID               = rintern("memid");

    xCParams             = flocons(pF->cParams);
    xCParamsOpt          = flocons(pF->cParamsOpt);
    sCParams             = rintern("CParams");
    sCParamsOpt          = rintern("CParamsOpt");
    sRequiredParamsAlist = rintern("RequiredParams");
    sOptionalParamsAlist = rintern("OptionalParams");

    lResult = AlistFromLisps
    (
        sOptionalParamsAlist, xOptionalParamsAlist,
        sCParamsOpt,          xCParamsOpt,
        sRequiredParamsAlist, xRequiredParamsAlist,
        sCParams,             xCParams,
        sHelpID,              xHelpID,
        sHelp,                xHelp,
        sMemID,               xMemID,
        sDoc,                 xDoc,
        sDocName,             xDocName,
        sName,                xName,
        NIL
    );
bail:

    SysFreeString(bstrHelp);
    SysFreeString(bstrDoc);
    SysFreeString(bstrName);

    return lResult; 
}

//----------------------------------------------------------------
// Function:       SiodGetVardescDocumentation
// Inputs:         itypeinfo, FUNCDESC
// Returns:            Documentation alist
// Outputs:
// Error Handling: Sets errobj to HRESULT or bad object
// Notes:
//----------------------------------------------------------------
LISP SiodGetVardescDocumentation(LISP itypeinfo, LISP vardesc)
{
    if (! (TYPE(itypeinfo) == tc_interface))
    {
        // TODO: no way currently to check that it's actually an IUnknown*
        setvar(sym_errobj, itypeinfo, NIL);
        return NIL;
    }

    if (! (TYPE(vardesc) == tc_vardesc))
    {
        // TODO: no way currently to check that it's actually an IUnknown*
        setvar(sym_errobj, vardesc, NIL);
        return NIL;
    }

    VARDESC *pV = VARDESCFromLisp(vardesc);
    if (pV == NULL)
        return NIL;

    BSTR  bstrName;
    BSTR  bstrDoc;
    DWORD dwHelpID;
    BSTR  bstrHelp;
    BSTR  rgBstrNames[1];
    UINT  cNames;

    HRESULT hr = S_OK;

    LISP  lResult = NIL;

    LISP xHelp    = NIL;
    LISP xHelpID  = NIL;
    LISP xDoc     = NIL;
    LISP xDocName = NIL;
    LISP xName    = NIL;
    LISP xType    = NIL;
    LISP xMemID   = NIL;

    LISP sHelp    = NIL;
    LISP sHelpID  = NIL;
    LISP sDoc     = NIL;
    LISP sDocName = NIL;
    LISP sName    = NIL;
    LISP sType    = NIL;
    LISP sMemID   = NIL;

    hr = TYPI(itypeinfo)->GetDocumentation
    (
        pV->memid,
        &bstrName,
        &bstrDoc,
        &dwHelpID,
        &bstrHelp
    );

    SetErrobjToHresult(hr);
    if (FAILED(hr))
        goto bail;

    hr = TYPI(itypeinfo)->GetNames
    (
        pV->memid,
        rgBstrNames,
        1,
        &cNames
    );

    SetErrobjToHresult(hr);
    if (FAILED(hr))
        goto bail;

    if (cNames != 1)
    {
        return err("Number of Names in VARDESC was not correct", vardesc);
    }

    xName  = StringFromOleStringDimHasNoNull(rgBstrNames[0]);
    SysFreeString(rgBstrNames[0]);
    sName = rintern("Name");

    SysFreeString(rgBstrNames[0]);

    xHelp    = StringFromOleStringDimHasNoNull(bstrHelp);
    xHelpID  = flocons(dwHelpID);
    xDoc     = StringFromOleStringDimHasNoNull(bstrDoc);
    xDocName = StringFromOleStringDimHasNoNull(bstrName);
    xType    = flocons(pV->varkind);
    xMemID   = flocons(pV->memid);

    sHelp    = rintern("Help");
    sHelpID  = rintern("HelpID");
    sDoc     = rintern("Documentation");
    sDocName = rintern("DocName");
    sType    = rintern("Type");
    sMemID   = rintern("memid");

    lResult = AlistFromLisps
    (
        sHelpID,  xHelpID,
        sHelp,    xHelp,
        sMemID,   xMemID,
        sDoc,     xDoc,
        sType,    xType,
        sDocName, xDocName,
        sName,    xName,
        NIL
    );
bail:

    SysFreeString(bstrHelp);
    SysFreeString(bstrDoc);
    SysFreeString(bstrName);

    return lResult;
}

//----------------------------------------------------------------
// Function:       SiodGetTypeAttr
// Inputs:         ITypeInfo
// Returns:            TYPEATTR as an association list
// Outputs:
// Error Handling: Sets errobj to HRESULT
// Notes:
//----------------------------------------------------------------
LISP SiodGetTypeAttr(LISP itypeinfo)
{
    if (! (TYPE(itypeinfo) == tc_interface))
    {
        // TODO: no way currently to check that it's actually an IUnknown*
        setvar(sym_errobj, itypeinfo, NIL);
        return NIL;
    }
    TYPEATTR *pTA;

    HRESULT hr = TYPI(itypeinfo)->GetTypeAttr(&pTA);

    SetErrobjToHresult(hr);

    LISP z = LispFromTYPEATTR(pTA);

    TYPI(itypeinfo)->ReleaseTypeAttr(pTA);

    return z;
}

    //==========================================================================
   //
  // BSTRs
 //
//==========================================================================

BSTR BstrFromLisp(LISP s)
{
    if (TYPE(s) == tc_bstr)
        return (BSTR)STR(s);

    if (TYPE(s) != tc_string && TYPE(s) != tc_symbol)
        return NULL;
    else
    {
        BSTR b;

        OLECHAR * sz;

        DWORD cchNeeded = MultiByteToWideChar
        (
            CP_ACP,
            MB_PRECOMPOSED | MB_USEGLYPHCHARS,
            STRINGDATA(s),
            -1, // s had better be NULL-terminated
            NULL,
            0
        );

        if (cchNeeded == 0)
            err("BstrFromLisp failed", LispFromHresult(HRESULT_FROM_WIN32(GetLastError())));

        DWORD cbNeeded = (cchNeeded + 1) * sizeof(OLECHAR);

        sz = (OLECHAR*)malloc(cbNeeded);

        if (sz == 0)
            err("BstrFromLisp out of memory", LispFromHresult(E_OUTOFMEMORY));

        DWORD cchActual = MultiByteToWideChar
        (
            CP_ACP,
            MB_PRECOMPOSED | MB_USEGLYPHCHARS,
            STRINGDATA(s),
            -1, // s had better be NULL-terminated
            sz,
            cchNeeded
        );

        if (cchActual == 0)
            err("BstrFromLisp failed", LispFromHresult(HRESULT_FROM_WIN32(GetLastError())));

        b = SysAllocString(sz);

        free(sz);

        return b;
    }
}

LISP LispFromBstr(BSTR b)
{
    LISP z  = newcell(tc_bstr);
    STR(z)  = (char*)b;
    DIM(z)  = lstrlenW(b);
    return z;
}

void VLispBstrFree(LISP b)
{
    SysFreeString((BSTR)STR(b));
    STR(b) = 0;
    DIM(b) = 0;
}

LISP LispBstrEqual(LISP a, LISP b)
{
    if (  (TYPE(a) != tc_bstr)
       || (TYPE(b) != tc_bstr)
       || (DIM(a)  != DIM(b))
       )
    {
        return NIL;
    }

    BOOL f = memcmp(STR(a), STR(b), DIM(a)) == 0 ;

    // do it the kindergarten way, so we can see it with the debugger.
    if (f)
        return sym_t;
    else
        return NIL;
}

void VLispBstrPrin1(LISP b, struct gen_printio *f)
{
    DWORD cb;
    char * sz = SzFromOleString((BSTR)STR(b), cb);
    char * sz2 = (char*)malloc(cb + 3);
    if (sz2)
    {
        strcpy(sz2, "\"");
        strcat(sz2, sz);
        strcat(sz2, "\"");
        gput_st(f, sz2);
        free(sz2);
        free(sz);
    }
    else
    {
        gput_st(f, sz);
        free (sz);
    }
}

    //==========================================================================
   //
  // How to call IDispatch
 //
//==========================================================================

/* * /
Most of the work for variants can be done at the Lisp level.  A LISP variant
shall be a list whose first element is a string denoting the type of the
Variant and whose second element is the value.

TODO: SAFEARRAYs are not thought out
       CURRENCY is not done.
           BSTRs are not checked.

       lots of work for all the ByRef types
/* */

#define NUVAR(vtype, type, var, conver) {  \
    pVarg->vt  = vtype;                     \
    pVarg->var = (type)conver(CAR(CDR(asc)));\
    return;                             }

#define TESTNUVAR(lispstring, vtype, type, var, conver) \
    if (0 == _stricmp(PNAME(x), lispstring)) NUVAR(vtype, type, var, conver)

#define NUBYREF(vtype, type, var) {            \
    pVarg->vt     = vtype | VT_BYREF;           \
    pVarg->var    = (type*)malloc(sizeof(type)); \
    pVarg->var[0] = 0;                            \
    return;                       }

#define TESTNUBYREF(lispstring, vtype, type, var) \
    if (0 == _stricmp(PNAME(x), lispstring)) NUBYREF(vtype, type, var)

static void VariantargFromLisp
(
    VARIANTARG *pVarg,
    LISP        asc
)
{
    LISP x ;

    if (asc == NIL || (x = CAR(asc)) == NIL)
    {
        err ("Invalid LISP Variant", asc) ;
    }

    TESTNUVAR ("short",     VT_I2,       short,        iVal,        FLONM       )
    TESTNUVAR ("long",      VT_I4,       long,         lVal,        FLONM       )
    TESTNUVAR ("float",     VT_R4,       float,        fltVal,      FLONM       )
    TESTNUVAR ("double",    VT_R8,       double,       dblVal,      FLONM       )
    TESTNUVAR ("BOOL",      VT_BOOL,     VARIANT_BOOL, boolVal,     FLONM       )
    TESTNUVAR ("SCODE",     VT_ERROR,    SCODE,        scode,       FLONM       )
    TESTNUVAR ("CY",        VT_CY,       LONGLONG,     cyVal.int64, FLONM       )
    TESTNUVAR ("DATE",      VT_DATE,     DATE,         date,        FLONM       )
    TESTNUVAR ("BSTR",      VT_BSTR,     BSTR,         bstrVal,     BstrFromLisp)
    TESTNUVAR ("IUnknown",  VT_UNKNOWN,  IUnknown*,    punkVal,     PUNK        )
    TESTNUVAR ("IDispatch", VT_DISPATCH, IDispatch*,   pdispVal,    DISP        )
    TESTNUVAR ("SAFEARRAY", VT_ARRAY,    SAFEARRAY*,   parray,      STR         )

    TESTNUBYREF ("short-ref",     VT_I2,       short,        piVal    )
    TESTNUBYREF ("long-ref",      VT_I4,       long,         plVal    )
    TESTNUBYREF ("float-ref",     VT_R4,       float,        pfltVal  )
    TESTNUBYREF ("double-ref",    VT_R8,       double,       pdblVal  )
    TESTNUBYREF ("BOOL-REF",      VT_BOOL,     VARIANT_BOOL, pboolVal )
    TESTNUBYREF ("SCODE-REF",     VT_ERROR,    SCODE,        pscode   )
    TESTNUBYREF ("DATE-REF",      VT_DATE,     DATE,         pdate    )
    TESTNUBYREF ("BSTR-REF",      VT_BSTR,     BSTR,         pbstrVal )
    TESTNUBYREF ("IUnknown-Ref",  VT_UNKNOWN,  IUnknown*,    ppunkVal )
    TESTNUBYREF ("IDispatch-Ref", VT_DISPATCH, IDispatch*,   ppdispVal)

    if (0 == _stricmp(PNAME(x), "CY-REF"))
    {
        pVarg->vt            = VT_CY | VT_BYREF;
        pVarg->pcyVal        = (CY*)malloc(sizeof(CY));
        pVarg->pcyVal->int64 = 0;
        return;
    }

    if (0 == _stricmp(PNAME(x), "empty"))
    {
        pVarg->vt   = VT_EMPTY;
        pVarg->iVal = NULL;
        return;
    }

    if (0 == _stricmp(PNAME(x), "null"))
    {
        pVarg->vt   = VT_NULL;
        pVarg->iVal = NULL;
        return;
    }

    err ("Unknown LISP Variant type", asc);
}

#undef NUVAR
#undef NUBYREF
#undef TESTNUVAR
#undef TESTNUBYREF

FORWARD LISP LispFromSafearray(/*const*/ SAFEARRAY* parray, VARTYPE vtype);

#define NUVALALIST(sym, conser, mem, pmem)\
    s = rintern(sym);                      \
    if (fByRef) {                           \
        v = conser(*(varg.pmem));            \
        free(varg.pmem);          }           \
    else v = conser(varg.mem); break;

LISP LispFromVariantarg(const VARIANTARG &varg)
{
    LISP s;
    LISP v;

    BOOL fByRef = varg.vt & VT_BYREF;
    BOOL fArray = varg.vt & VT_ARRAY;

    VARTYPE vtype  = varg.vt;


    if (fByRef)
    {
        vtype ^= VT_BYREF;
    }

    if (fArray)
    {
        if (fByRef)
            v = LispFromSafearray(*(varg.pparray), vtype);
        else
            v = LispFromSafearray(varg.parray, vtype);

        s = rintern("SAFEARRAY");

    }
    else
    {

        switch(vtype)
        {
        case VT_I2:           NUVALALIST("short",     flocons,           iVal,     piVal    )
        case VT_I4:       NUVALALIST("long",      flocons,           lVal,     plVal    )
        case VT_R4:       NUVALALIST("float",     flocons,           fltVal,   pfltVal  )
        case VT_R8:       NUVALALIST("double",    flocons,           dblVal,   pdblVal  )
        case VT_BOOL:     NUVALALIST("BOOL",      flocons,           boolVal,  pboolVal )
        case VT_ERROR:    NUVALALIST("SCODE",     flocons,           scode,    pscode   )
        case VT_DATE:     NUVALALIST("DATE",      flocons,           date,     pdate    )
        case VT_BSTR:     NUVALALIST("BSTR",      LispFromBstr,      bstrVal,  pbstrVal )
        case VT_UNKNOWN:  NUVALALIST("IUnknown",  LispFromInterface, punkVal,  ppunkVal )
        case VT_DISPATCH: NUVALALIST("IDispatch", LispFromInterface, pdispVal, ppdispVal)

        case VT_EMPTY:
            if (fByRef)
                return err("EMPTY BYREF is weird", NIL);

            s = rintern("empty");
            v = NIL;
            break ;

        case VT_NULL:
            if (fByRef)
                return err("NULL BYREF not legal", NIL);

            s = rintern("null");
            v = NIL;
            break ;

        case VT_CY:
            s = rintern("CY");
            if (fByRef)
            {
                v = flocons(varg.pcyVal->Lo);
                free(varg.pcyVal);
            }
            else
            {
                v = flocons(varg.cyVal.Lo);
            }
            // TODO: too bad if Hi is set (need real 64-bit stuff)
            break;

        default:
                s = rintern("unknownVariantArg");
                v = NIL;
                return err ("Unknown or unimplemented Variant Arg type", cons(s, cons(v, NIL)));
                break;
        }
    }

    return cons (s, cons (v, NIL));
}

#undef NUVALALIST

#define VAL(conser, mem, pmem)  \
    return (fByRef ? conser(*(varg.pmem)) : conser(varg.mem));

LISP LispValFromVariantarg(const VARIANTARG &varg)
{
    BOOL fByRef = varg.vt & VT_BYREF;
    BOOL fArray = varg.vt & VT_ARRAY;

    if (fArray)
        return err("wta LispValFromVariantarg", NIL);

    VARTYPE vtype  = varg.vt;

    if (fByRef)
    {
        vtype ^= VT_BYREF;
    }

    switch(vtype)
    {
    case VT_I2:           VAL(flocons,           iVal,     piVal    )
    case VT_I4:       VAL(flocons,           lVal,     plVal    )
    case VT_R4:       VAL(flocons,           fltVal,   pfltVal  )
    case VT_R8:       VAL(flocons,           dblVal,   pdblVal  )
    case VT_BOOL:     VAL(flocons,           boolVal,  pboolVal )
    case VT_ERROR:    VAL(flocons,           scode,    pscode   )
    case VT_DATE:     VAL(flocons,           date,     pdate    )
    case VT_BSTR:     VAL(LispFromBstr,      bstrVal,  pbstrVal )
    case VT_UNKNOWN:  VAL(LispFromInterface, punkVal,  ppunkVal )
    case VT_DISPATCH: VAL(LispFromInterface, pdispVal, ppdispVal)

    case VT_EMPTY:
        if (fByRef)
            return err("LispValFromVariantarg: EMPTY BYREF is weird", NIL);

        return NIL;

    case VT_NULL:
        if (fByRef)
            return err("LispValFromVariantarg: NULL BYREF not legal", NIL);

        return NIL;

    case VT_CY:
        return (fByRef) ? flocons(varg.pcyVal->Lo) : flocons(varg.cyVal.Lo);

    default:
        return err ("LispValFromVariantarg: Unknown or unimplemented Variant Arg type", NIL);

    }
}

#undef VAL


LISP LispFromSafearray(/*const*/ SAFEARRAY* parray, VARTYPE vtype)
{
    SafeArrayLock(parray);

    LISP lcDims      = flocons(parray->cDims);
    LISP lFeatures   = flocons(parray->fFeatures);
    LISP lcbElements = flocons(parray->cbElements);
    LISP lcLocks     = flocons(parray->cLocks);

    LISP scDims      = rintern("cDims");
    LISP sFeatures   = rintern("fFeatures");
    LISP scbElements = rintern("cbElements");
    LISP scLocks     = rintern("cLocks");

    int iDim;
    HRESULT hr;

    int   cbElt = SafeArrayGetElemsize(parray);
    void *pbElt = must_malloc(cbElt);

    long * rgIndices  = (long*)must_malloc(parray->cDims * sizeof(long));
    long * rgLoBounds = (long*)must_malloc(parray->cDims * sizeof(long));
    long * rgHiBounds = (long*)must_malloc(parray->cDims * sizeof(long));
    long   lTest ;

    for (iDim=0; iDim<parray->cDims; iDim++)
    {
        hr = SafeArrayGetLBound(parray, iDim, &(rgLoBounds[iDim]));
        if (FAILED(hr))
            return err("LispFromSafearray\\LBound", LispFromHresult(hr));

        hr = SafeArrayGetUBound(parray, iDim, &(rgHiBounds[iDim]));
        if (FAILED(hr))
            return err("LispFromSafearray\\UBound", LispFromHresult(hr));

        rgIndices[iDim] = rgLoBounds[iDim] ;

        /* * /
        long lBound = 0;
        long uBound = 0;

        LISP lDim    = flocons(iDim);

        LISP lLBound = flocons(SafeArrayGetLBound(parray, iDim, &lBound));
        LISP sLBound = rintern("lBound");

        LISP lUBound = flocons(SafeArrayGetUBound(parray, iDim, &uBound));
        LISP sUBound = rintern("uBound");

        if (uBound < lBound)
            return err("LispFromSafeArray BUGCHECK: uBound < lBound", NIL);

        for (jElt = lBound; jElt <= uBound; jElt++)
        {
            //SafeArrayGetElement
        }
        /* */
    }

    /* * /
    Here's the algorithm for counting through all the entries in the SafeArray:
    /* */
    do
    {
        lTest = rgIndices[0] + 1;
        if (lTest > rgHiBounds[0])
        {
            rgIndices[0] = rgLoBounds[0];
            if (parray->cDims > 0)
            {
                // recurse
            }
        }
    }
    while (lTest);

    SafeArrayUnlock(parray);

    free (pbElt);
    free (rgIndices);
    free (rgLoBounds);
    free (rgHiBounds);

    return NIL;
}

LISP LispFromInvokeResults
(
    const VARIANTARG &varg,
    const DISPPARAMS &dispparams
)
{
    LISP x = LispFromVariantarg(varg);
    x = cons(x, NIL); // listify it

    for (DWORD i = 0; i<dispparams.cArgs; i++)
    {
        if (dispparams.rgvarg[i].vt & VT_BYREF)
        {
            x = cons(LispFromVariantarg(dispparams.rgvarg[i]), x);
        }
    }

    return x;
}

static void DispidsFromLisp(DISPID* pDispid, LISP elem)
{
    *pDispid = (long)FLONM(elem);
}

static void DispParamsFromLisp
(
    DISPPARAMS  *pdispparams,
    LISP         i_dispparams
)
{
    LISP x = i_dispparams;

    if (pdispparams)
        memset(pdispparams, 0, sizeof(DISPPARAMS));
    else
    {
        __asm {int 3} // TODO: Really, really, now.
    }

    if (x == NULL)
    {
        return;
    }

    LISP l_rgvarg = CAR(x);
    x = CDR(x);

    LISP l_rgdispidNamedArgs = CAR(x);
    x = CDR(x);

    pdispparams->cArgs = (UINT)FLONM(CAR(x));
    x = CDR(x);

    pdispparams->cNamedArgs = (UINT)FLONM(CAR(x));

    if (pdispparams->cArgs)
    {
        pdispparams->rgvarg =
            (VARIANTARG*)malloc(sizeof(VARIANTARG)*pdispparams->cArgs);

        if (pdispparams->rgvarg)
        {
            x = l_rgvarg;
            for (DWORD i=0; i<pdispparams->cArgs; i++)
            {
                VariantargFromLisp(pdispparams->rgvarg+i, CAR(x));
                x = CDR(x);
            }
        }
    }

    if (pdispparams->cNamedArgs)
    {
        pdispparams->rgdispidNamedArgs =
            (DISPID*)malloc(sizeof(DISPID)*pdispparams->cNamedArgs);

        if (pdispparams->rgdispidNamedArgs)
        {
            x = l_rgdispidNamedArgs;
            for (DWORD i=0; i<pdispparams->cNamedArgs; i++)
            {
                DispidsFromLisp(pdispparams->rgdispidNamedArgs+i, CAR(x));
                x = CDR(x);
            }
        }
    }
}

static void ClearDispParams(DISPPARAMS* pdispparams)
{
    if (pdispparams->rgvarg)
    {
        free(pdispparams->rgvarg);
        pdispparams->rgvarg = 0;
    }
    if (pdispparams->rgdispidNamedArgs)
    {
        free(pdispparams->rgdispidNamedArgs);
        pdispparams->rgdispidNamedArgs = 0;
    }
}

LISP SiodCallInvoke
(
    LISP i_idispatch,
    LISP i_memid,
    // LISP i_riid; // TODO: must use f_subr, m_subr, or init_subr6 (which doesn't exist)
    // LISP i_lcid, // TODO: Lisp can't be UNICODE or MultiByte
    LISP i_wFlags,
    LISP i_dispparams
)
{
    HRESULT         hr;

    VARIANT         varResult;
    EXCEPINFO       excepinfo;
    UINT            uArgErr;
    DISPPARAMS      dispparams;

    if (TYPE(i_idispatch) != tc_interface)
        return err("wta to Invoke", i_idispatch);

    if (TYPE(i_memid) != tc_flonum)
        return err("wta to Invoke", i_memid);

    if (TYPE(i_wFlags) != tc_flonum)
        return err("wta to Invoke", i_wFlags);

    if (i_dispparams && (TYPE(i_dispparams) != tc_cons))
        return err("wta to Invoke", i_dispparams);

    WORD    wFlags = (WORD)FLONM(i_wFlags);
    LONG    memid  = (LONG)FLONM(i_memid);
    LCID    lcid   = 0; // (LCID)FLONM(i_lcid);

    DispParamsFromLisp(&dispparams, i_dispparams);

    hr = DISP(i_idispatch)->Invoke
    (
        memid,
        IID_NULL,
        lcid,
        wFlags,
        &dispparams,
        &varResult,
        &excepinfo,
        &uArgErr
    );

    if (FAILED(hr))
    {
        ClearDispParams(&dispparams);
        return err("Invoke failed", LispFromHresult(hr));
    }

    LISP l = LispFromInvokeResults(varResult, dispparams);
    ClearDispParams(&dispparams);
    return l;
}


    //==========================================================================
   //
  // Init functions required by SIOD.
 //
//==========================================================================

static void MakeTypes(void)
{
    tc_guid      = allocate_user_tc();
    tc_hresult   = allocate_user_tc();
    tc_interface = allocate_user_tc();
    tc_typeattr  = allocate_user_tc();
    tc_funcdesc  = allocate_user_tc();
    tc_vardesc   = allocate_user_tc();
    tc_typedesc  = allocate_user_tc();
    tc_bstr      = allocate_user_tc();
}

static void SetGcHooks(void)
{
    long lGcKind;

    set_gc_hooks
    (
        tc_guid,           // user-defined type
        NULL,              // user-defined relocation function
        NULL,              // user-defined scan function
        NULL,              // user-defined mark function
        LispGuidGcFree,    // user-defined free function
        &lGcKind           // returned type of garbage collection
    );

    set_gc_hooks
    (
        tc_interface,      // user-defined type
        NULL,              // user-defined relocation function
        NULL,              // user-defined scan function
        NULL,              // user-defined mark function
        LispInterfaceFree, // user-defined free function
        &lGcKind           // returned type of garbage collection
    );

    set_gc_hooks
    (
        tc_bstr,           // user-defined type
        NULL,              // user-defined relocation function
        NULL,              // user-defined scan function
        NULL,              // user-defined mark function
        VLispBstrFree,     // user-defined free function
        &lGcKind           // returned type of garbage collection
    );

    SET_GC_HOOKS(TYPEATTR, typeattr);
    SET_GC_HOOKS(FUNCDESC, funcdesc);
    SET_GC_HOOKS(VARDESC,  vardesc);
    SET_GC_HOOKS(TYPEDESC, typedesc);
}

static void SetPrintHooks(void)
{
    set_print_hooks(tc_guid,      LispGuidPrin1);
    set_print_hooks(tc_hresult,       HresultPrin1);
    set_print_hooks(tc_interface, LispInterfacePrin1);
    set_print_hooks(tc_bstr,      VLispBstrPrin1);

    SET_PRINT_HOOKS(TYPEATTR, typeattr);
    SET_PRINT_HOOKS(FUNCDESC, funcdesc);
    SET_PRINT_HOOKS(VARDESC,  vardesc);
    SET_PRINT_HOOKS(TYPEDESC, typedesc);
}

static void SetOtherHooks(void)
{
    struct user_type_hooks *pUserTypeHooks;

    pUserTypeHooks        = get_user_type_hooks(tc_guid);
    pUserTypeHooks->equal = LispGuidEqual;

    pUserTypeHooks        = get_user_type_hooks(tc_hresult);
    pUserTypeHooks->equal = HresultEqual;

    pUserTypeHooks        = get_user_type_hooks(tc_interface);
    pUserTypeHooks->equal = LispInterfaceEqual;

    pUserTypeHooks        = get_user_type_hooks(tc_bstr);
    pUserTypeHooks->equal = LispBstrEqual;

    SET_OTHER_HOOKS(TYPEATTR, typeattr) // no semicolon
    SET_OTHER_HOOKS(FUNCDESC, funcdesc) // no semicolon
    SET_OTHER_HOOKS(VARDESC,  vardesc)  // no semicolon
    SET_OTHER_HOOKS(TYPEDESC, typedesc)  // no semicolon
}

static void SetSubrs(void)
{
    init_subr_1("guid->string",             StringFromLispGuid);
    init_subr_1("string->guid",             LispGuidFromString);
    init_subr_1("Interface",                LispInterfaceFromLispVal);
    init_subr_1("Hresult",                  LispHresultFromLispVal);
    init_subr_0("new-guid",                 LispGuidGen);
    init_subr_0("CoInitialize",             SiodCoInitialize);
    init_subr_0("CoUninitialize",           SiodCoUninitialize);
    init_subr_3("CoCreateInstance",         SiodCoCreateInstance);
    init_subr_2("QueryInterface",           SiodQueryInterface);
    init_subr_1("AddRef",                   SiodAddRef);
    init_subr_1("Release",                  SiodRelease);
    init_subr_1("GetTypeinfoCount",         SiodGetTypeInfoCount);
    init_subr_3("GetTypeinfo",              SiodGetTypeInfo);
    init_subr_1("GetTypeattr",              SiodGetTypeAttr);
    init_subr_1("GetTypeattrCfuncs",        CFuncsFromLispTypeattr);
    init_subr_1("GetTypeattrCvars",         CVarsFromLispTypeattr);
    init_subr_2("GetTypeinfoFuncdesc",      SiodGetFuncDesc);
    init_subr_2("GetTypeinfoVardesc",       SiodGetVarDesc);
    init_subr_2("GetFuncdescDocumentation", SiodGetFuncdescDocumentation);
    init_subr_2("GetVardescDocumentation",  SiodGetVardescDocumentation);
    init_subr_1("CLSIDFromProgID",          LispGuidFromProgIDString);
    init_subr_4("Invoke",                   SiodCallInvoke);
}


extern "C" 
{
    __declspec (dllexport) void init_dcom(void)
    {
        MakeTypes();
        SetGcHooks();
        SetPrintHooks();
        SetOtherHooks();
        SetSubrs();
    }
} // extern "C"

