/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Feb 18 11:33:01 2000
 */
/* Compiler settings for ComTest1.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "ComTest1.h"

#define TYPE_FORMAT_STRING_SIZE   1033                              
#define PROC_FORMAT_STRING_SIZE   253                               

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IComTestObject, ver. 0.0,
   GUID={0x9E21484F,0xE8CF,0x11D0,{0x95,0x06,0x44,0x45,0x53,0x54,0x00,0x00}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IComTestObject_ServerInfo;

#pragma code_seg(".orpc")
extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[2];

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x50100a4, /* MIDL Version 5.1.164 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    1,  /* Flags */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

static const unsigned short IComTestObject_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    28,
    56,
    84,
    112,
    140,
    168,
    196,
    224
    };

static const MIDL_SERVER_INFO IComTestObject_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IComTestObject_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IComTestObject_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IComTestObject_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(16) _IComTestObjectProxyVtbl = 
{
    &IComTestObject_ProxyInfo,
    &IID_IComTestObject,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* IComTestObject::SayHello */ ,
    (void *)-1 /* IComTestObject::get_ShortProp */ ,
    (void *)-1 /* IComTestObject::put_ShortProp */ ,
    (void *)-1 /* IComTestObject::get_LongProp */ ,
    (void *)-1 /* IComTestObject::put_LongProp */ ,
    (void *)-1 /* IComTestObject::get_VariantProp */ ,
    (void *)-1 /* IComTestObject::put_VariantProp */ ,
    (void *)-1 /* IComTestObject::get_BstrProp */ ,
    (void *)-1 /* IComTestObject::put_BstrProp */
};


static const PRPC_STUB_FUNCTION IComTestObject_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IComTestObjectStubVtbl =
{
    &IID_IComTestObject,
    &IComTestObject_ServerInfo,
    16,
    &IComTestObject_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

#pragma data_seg(".rdata")

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[2] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            },
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            }

        };


#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, [wire_marshal] or [user_marshal] attribute, more than 32 methods in the interface.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure SayHello */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x7 ),	/* 7 */
#ifndef _ALPHA_
/*  8 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter bszOut */

/* 16 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 18 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 20 */	NdrFcShort( 0x1e ),	/* Type Offset=30 */

	/* Return value */

/* 22 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 24 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 26 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ShortProp */

/* 28 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 30 */	NdrFcLong( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0x8 ),	/* 8 */
#ifndef _ALPHA_
/* 36 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 38 */	NdrFcShort( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0xe ),	/* 14 */
/* 42 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 44 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 46 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 48 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 50 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 52 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 54 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_ShortProp */

/* 56 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 58 */	NdrFcLong( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x9 ),	/* 9 */
#ifndef _ALPHA_
/* 64 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 66 */	NdrFcShort( 0x6 ),	/* 6 */
/* 68 */	NdrFcShort( 0x8 ),	/* 8 */
/* 70 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 72 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 74 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 76 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 78 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 80 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 82 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_LongProp */

/* 84 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 86 */	NdrFcLong( 0x0 ),	/* 0 */
/* 90 */	NdrFcShort( 0xa ),	/* 10 */
#ifndef _ALPHA_
/* 92 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 94 */	NdrFcShort( 0x0 ),	/* 0 */
/* 96 */	NdrFcShort( 0x10 ),	/* 16 */
/* 98 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 100 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 102 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 104 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 106 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 108 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 110 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_LongProp */

/* 112 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 114 */	NdrFcLong( 0x0 ),	/* 0 */
/* 118 */	NdrFcShort( 0xb ),	/* 11 */
#ifndef _ALPHA_
/* 120 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 122 */	NdrFcShort( 0x8 ),	/* 8 */
/* 124 */	NdrFcShort( 0x8 ),	/* 8 */
/* 126 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 128 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 130 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 132 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 134 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 136 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 138 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_VariantProp */

/* 140 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 142 */	NdrFcLong( 0x0 ),	/* 0 */
/* 146 */	NdrFcShort( 0xc ),	/* 12 */
#ifndef _ALPHA_
/* 148 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 150 */	NdrFcShort( 0x0 ),	/* 0 */
/* 152 */	NdrFcShort( 0x8 ),	/* 8 */
/* 154 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 156 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
#ifndef _ALPHA_
/* 158 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 160 */	NdrFcShort( 0x3e2 ),	/* Type Offset=994 */

	/* Return value */

/* 162 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 164 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 166 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_VariantProp */

/* 168 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 170 */	NdrFcLong( 0x0 ),	/* 0 */
/* 174 */	NdrFcShort( 0xd ),	/* 13 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 176 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
#else
			NdrFcShort( 0x1c ),	/* MIPS & PPC Stack size/offset = 28 */
#endif
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 178 */	NdrFcShort( 0x0 ),	/* 0 */
/* 180 */	NdrFcShort( 0x8 ),	/* 8 */
/* 182 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 184 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 186 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* MIPS & PPC Stack size/offset = 8 */
#endif
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 188 */	NdrFcShort( 0x3f0 ),	/* Type Offset=1008 */

	/* Return value */

/* 190 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 192 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
#else
			NdrFcShort( 0x18 ),	/* MIPS & PPC Stack size/offset = 24 */
#endif
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 194 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_BstrProp */

/* 196 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 198 */	NdrFcLong( 0x0 ),	/* 0 */
/* 202 */	NdrFcShort( 0xe ),	/* 14 */
#ifndef _ALPHA_
/* 204 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 206 */	NdrFcShort( 0x0 ),	/* 0 */
/* 208 */	NdrFcShort( 0x8 ),	/* 8 */
/* 210 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 212 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 214 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 216 */	NdrFcShort( 0x1e ),	/* Type Offset=30 */

	/* Return value */

/* 218 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 220 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 222 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_BstrProp */

/* 224 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 226 */	NdrFcLong( 0x0 ),	/* 0 */
/* 230 */	NdrFcShort( 0xf ),	/* 15 */
#ifndef _ALPHA_
/* 232 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 234 */	NdrFcShort( 0x0 ),	/* 0 */
/* 236 */	NdrFcShort( 0x8 ),	/* 8 */
/* 238 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 240 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 242 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 244 */	NdrFcShort( 0x3fe ),	/* Type Offset=1022 */

	/* Return value */

/* 246 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 248 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 250 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/*  4 */	NdrFcShort( 0x1a ),	/* Offset= 26 (30) */
/*  6 */	
			0x13, 0x0,	/* FC_OP */
/*  8 */	NdrFcShort( 0xc ),	/* Offset= 12 (20) */
/* 10 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 12 */	NdrFcShort( 0x2 ),	/* 2 */
/* 14 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 16 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 18 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 20 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 22 */	NdrFcShort( 0x8 ),	/* 8 */
/* 24 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (10) */
/* 26 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 28 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 30 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 32 */	NdrFcShort( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0x4 ),	/* 4 */
/* 36 */	NdrFcShort( 0x0 ),	/* 0 */
/* 38 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (6) */
/* 40 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 42 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 44 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 46 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 48 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 50 */	NdrFcShort( 0x3b0 ),	/* Offset= 944 (994) */
/* 52 */	
			0x13, 0x0,	/* FC_OP */
/* 54 */	NdrFcShort( 0x398 ),	/* Offset= 920 (974) */
/* 56 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 58 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 60 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 62 */	NdrFcShort( 0x2 ),	/* Offset= 2 (64) */
/* 64 */	NdrFcShort( 0x10 ),	/* 16 */
/* 66 */	NdrFcShort( 0x2b ),	/* 43 */
/* 68 */	NdrFcLong( 0x3 ),	/* 3 */
/* 72 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 74 */	NdrFcLong( 0x11 ),	/* 17 */
/* 78 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 80 */	NdrFcLong( 0x2 ),	/* 2 */
/* 84 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 86 */	NdrFcLong( 0x4 ),	/* 4 */
/* 90 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 92 */	NdrFcLong( 0x5 ),	/* 5 */
/* 96 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 98 */	NdrFcLong( 0xb ),	/* 11 */
/* 102 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 104 */	NdrFcLong( 0xa ),	/* 10 */
/* 108 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 110 */	NdrFcLong( 0x6 ),	/* 6 */
/* 114 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (328) */
/* 116 */	NdrFcLong( 0x7 ),	/* 7 */
/* 120 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 122 */	NdrFcLong( 0x8 ),	/* 8 */
/* 126 */	NdrFcShort( 0xffffff88 ),	/* Offset= -120 (6) */
/* 128 */	NdrFcLong( 0xd ),	/* 13 */
/* 132 */	NdrFcShort( 0xca ),	/* Offset= 202 (334) */
/* 134 */	NdrFcLong( 0x9 ),	/* 9 */
/* 138 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (352) */
/* 140 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 144 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (370) */
/* 146 */	NdrFcLong( 0x24 ),	/* 36 */
/* 150 */	NdrFcShort( 0x2f0 ),	/* Offset= 752 (902) */
/* 152 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 156 */	NdrFcShort( 0x2ea ),	/* Offset= 746 (902) */
/* 158 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 162 */	NdrFcShort( 0x2e8 ),	/* Offset= 744 (906) */
/* 164 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 168 */	NdrFcShort( 0x2e6 ),	/* Offset= 742 (910) */
/* 170 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 174 */	NdrFcShort( 0x2e4 ),	/* Offset= 740 (914) */
/* 176 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 180 */	NdrFcShort( 0x2e2 ),	/* Offset= 738 (918) */
/* 182 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 186 */	NdrFcShort( 0x2e0 ),	/* Offset= 736 (922) */
/* 188 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 192 */	NdrFcShort( 0x2ce ),	/* Offset= 718 (910) */
/* 194 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 198 */	NdrFcShort( 0x2cc ),	/* Offset= 716 (914) */
/* 200 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 204 */	NdrFcShort( 0x2d2 ),	/* Offset= 722 (926) */
/* 206 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 210 */	NdrFcShort( 0x2c8 ),	/* Offset= 712 (922) */
/* 212 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 216 */	NdrFcShort( 0x2ca ),	/* Offset= 714 (930) */
/* 218 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 222 */	NdrFcShort( 0x2c8 ),	/* Offset= 712 (934) */
/* 224 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 228 */	NdrFcShort( 0x2c6 ),	/* Offset= 710 (938) */
/* 230 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 234 */	NdrFcShort( 0x2c4 ),	/* Offset= 708 (942) */
/* 236 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 240 */	NdrFcShort( 0x2c2 ),	/* Offset= 706 (946) */
/* 242 */	NdrFcLong( 0x10 ),	/* 16 */
/* 246 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 248 */	NdrFcLong( 0x12 ),	/* 18 */
/* 252 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 254 */	NdrFcLong( 0x13 ),	/* 19 */
/* 258 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 260 */	NdrFcLong( 0x16 ),	/* 22 */
/* 264 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 266 */	NdrFcLong( 0x17 ),	/* 23 */
/* 270 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 272 */	NdrFcLong( 0xe ),	/* 14 */
/* 276 */	NdrFcShort( 0x2a6 ),	/* Offset= 678 (954) */
/* 278 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 282 */	NdrFcShort( 0x2ac ),	/* Offset= 684 (966) */
/* 284 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 288 */	NdrFcShort( 0x2aa ),	/* Offset= 682 (970) */
/* 290 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 294 */	NdrFcShort( 0x268 ),	/* Offset= 616 (910) */
/* 296 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 300 */	NdrFcShort( 0x266 ),	/* Offset= 614 (914) */
/* 302 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 306 */	NdrFcShort( 0x260 ),	/* Offset= 608 (914) */
/* 308 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 312 */	NdrFcShort( 0x25a ),	/* Offset= 602 (914) */
/* 314 */	NdrFcLong( 0x0 ),	/* 0 */
/* 318 */	NdrFcShort( 0x0 ),	/* Offset= 0 (318) */
/* 320 */	NdrFcLong( 0x1 ),	/* 1 */
/* 324 */	NdrFcShort( 0x0 ),	/* Offset= 0 (324) */
/* 326 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (325) */
/* 328 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 330 */	NdrFcShort( 0x8 ),	/* 8 */
/* 332 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 334 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 336 */	NdrFcLong( 0x0 ),	/* 0 */
/* 340 */	NdrFcShort( 0x0 ),	/* 0 */
/* 342 */	NdrFcShort( 0x0 ),	/* 0 */
/* 344 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 346 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 348 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 350 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 352 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 354 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 358 */	NdrFcShort( 0x0 ),	/* 0 */
/* 360 */	NdrFcShort( 0x0 ),	/* 0 */
/* 362 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 364 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 366 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 368 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 370 */	
			0x13, 0x10,	/* FC_OP */
/* 372 */	NdrFcShort( 0x2 ),	/* Offset= 2 (374) */
/* 374 */	
			0x13, 0x0,	/* FC_OP */
/* 376 */	NdrFcShort( 0x1fc ),	/* Offset= 508 (884) */
/* 378 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 380 */	NdrFcShort( 0x18 ),	/* 24 */
/* 382 */	NdrFcShort( 0xa ),	/* 10 */
/* 384 */	NdrFcLong( 0x8 ),	/* 8 */
/* 388 */	NdrFcShort( 0x58 ),	/* Offset= 88 (476) */
/* 390 */	NdrFcLong( 0xd ),	/* 13 */
/* 394 */	NdrFcShort( 0x78 ),	/* Offset= 120 (514) */
/* 396 */	NdrFcLong( 0x9 ),	/* 9 */
/* 400 */	NdrFcShort( 0x94 ),	/* Offset= 148 (548) */
/* 402 */	NdrFcLong( 0xc ),	/* 12 */
/* 406 */	NdrFcShort( 0xbc ),	/* Offset= 188 (594) */
/* 408 */	NdrFcLong( 0x24 ),	/* 36 */
/* 412 */	NdrFcShort( 0x114 ),	/* Offset= 276 (688) */
/* 414 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 418 */	NdrFcShort( 0x130 ),	/* Offset= 304 (722) */
/* 420 */	NdrFcLong( 0x10 ),	/* 16 */
/* 424 */	NdrFcShort( 0x148 ),	/* Offset= 328 (752) */
/* 426 */	NdrFcLong( 0x2 ),	/* 2 */
/* 430 */	NdrFcShort( 0x160 ),	/* Offset= 352 (782) */
/* 432 */	NdrFcLong( 0x3 ),	/* 3 */
/* 436 */	NdrFcShort( 0x178 ),	/* Offset= 376 (812) */
/* 438 */	NdrFcLong( 0x14 ),	/* 20 */
/* 442 */	NdrFcShort( 0x190 ),	/* Offset= 400 (842) */
/* 444 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (443) */
/* 446 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 448 */	NdrFcShort( 0x4 ),	/* 4 */
/* 450 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 452 */	NdrFcShort( 0x0 ),	/* 0 */
/* 454 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 456 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 458 */	NdrFcShort( 0x4 ),	/* 4 */
/* 460 */	NdrFcShort( 0x0 ),	/* 0 */
/* 462 */	NdrFcShort( 0x1 ),	/* 1 */
/* 464 */	NdrFcShort( 0x0 ),	/* 0 */
/* 466 */	NdrFcShort( 0x0 ),	/* 0 */
/* 468 */	0x13, 0x0,	/* FC_OP */
/* 470 */	NdrFcShort( 0xfffffe3e ),	/* Offset= -450 (20) */
/* 472 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 474 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 476 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 478 */	NdrFcShort( 0x8 ),	/* 8 */
/* 480 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 482 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 484 */	NdrFcShort( 0x4 ),	/* 4 */
/* 486 */	NdrFcShort( 0x4 ),	/* 4 */
/* 488 */	0x11, 0x0,	/* FC_RP */
/* 490 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (446) */
/* 492 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 494 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 496 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 498 */	NdrFcShort( 0x0 ),	/* 0 */
/* 500 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 502 */	NdrFcShort( 0x0 ),	/* 0 */
/* 504 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 508 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 510 */	NdrFcShort( 0xffffff50 ),	/* Offset= -176 (334) */
/* 512 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 514 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 516 */	NdrFcShort( 0x8 ),	/* 8 */
/* 518 */	NdrFcShort( 0x0 ),	/* 0 */
/* 520 */	NdrFcShort( 0x6 ),	/* Offset= 6 (526) */
/* 522 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 524 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 526 */	
			0x11, 0x0,	/* FC_RP */
/* 528 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (496) */
/* 530 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 532 */	NdrFcShort( 0x0 ),	/* 0 */
/* 534 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 536 */	NdrFcShort( 0x0 ),	/* 0 */
/* 538 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 542 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 544 */	NdrFcShort( 0xffffff40 ),	/* Offset= -192 (352) */
/* 546 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 548 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 550 */	NdrFcShort( 0x8 ),	/* 8 */
/* 552 */	NdrFcShort( 0x0 ),	/* 0 */
/* 554 */	NdrFcShort( 0x6 ),	/* Offset= 6 (560) */
/* 556 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 558 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 560 */	
			0x11, 0x0,	/* FC_RP */
/* 562 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (530) */
/* 564 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 566 */	NdrFcShort( 0x4 ),	/* 4 */
/* 568 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 570 */	NdrFcShort( 0x0 ),	/* 0 */
/* 572 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 574 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 576 */	NdrFcShort( 0x4 ),	/* 4 */
/* 578 */	NdrFcShort( 0x0 ),	/* 0 */
/* 580 */	NdrFcShort( 0x1 ),	/* 1 */
/* 582 */	NdrFcShort( 0x0 ),	/* 0 */
/* 584 */	NdrFcShort( 0x0 ),	/* 0 */
/* 586 */	0x13, 0x0,	/* FC_OP */
/* 588 */	NdrFcShort( 0xfffffdb4 ),	/* Offset= -588 (0) */
/* 590 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 592 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 594 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 596 */	NdrFcShort( 0x8 ),	/* 8 */
/* 598 */	NdrFcShort( 0x0 ),	/* 0 */
/* 600 */	NdrFcShort( 0x6 ),	/* Offset= 6 (606) */
/* 602 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 604 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 606 */	
			0x11, 0x0,	/* FC_RP */
/* 608 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (564) */
/* 610 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 612 */	NdrFcLong( 0x2f ),	/* 47 */
/* 616 */	NdrFcShort( 0x0 ),	/* 0 */
/* 618 */	NdrFcShort( 0x0 ),	/* 0 */
/* 620 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 622 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 624 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 626 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 628 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 630 */	NdrFcShort( 0x1 ),	/* 1 */
/* 632 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 634 */	NdrFcShort( 0x4 ),	/* 4 */
/* 636 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 638 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 640 */	NdrFcShort( 0x10 ),	/* 16 */
/* 642 */	NdrFcShort( 0x0 ),	/* 0 */
/* 644 */	NdrFcShort( 0xa ),	/* Offset= 10 (654) */
/* 646 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 648 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 650 */	NdrFcShort( 0xffffffd8 ),	/* Offset= -40 (610) */
/* 652 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 654 */	
			0x13, 0x0,	/* FC_OP */
/* 656 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (628) */
/* 658 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 660 */	NdrFcShort( 0x4 ),	/* 4 */
/* 662 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 664 */	NdrFcShort( 0x0 ),	/* 0 */
/* 666 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 668 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 670 */	NdrFcShort( 0x4 ),	/* 4 */
/* 672 */	NdrFcShort( 0x0 ),	/* 0 */
/* 674 */	NdrFcShort( 0x1 ),	/* 1 */
/* 676 */	NdrFcShort( 0x0 ),	/* 0 */
/* 678 */	NdrFcShort( 0x0 ),	/* 0 */
/* 680 */	0x13, 0x0,	/* FC_OP */
/* 682 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (638) */
/* 684 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 686 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 688 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 690 */	NdrFcShort( 0x8 ),	/* 8 */
/* 692 */	NdrFcShort( 0x0 ),	/* 0 */
/* 694 */	NdrFcShort( 0x6 ),	/* Offset= 6 (700) */
/* 696 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 698 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 700 */	
			0x11, 0x0,	/* FC_RP */
/* 702 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (658) */
/* 704 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 706 */	NdrFcShort( 0x8 ),	/* 8 */
/* 708 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 710 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 712 */	NdrFcShort( 0x10 ),	/* 16 */
/* 714 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 716 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 718 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffff1 ),	/* Offset= -15 (704) */
			0x5b,		/* FC_END */
/* 722 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 724 */	NdrFcShort( 0x18 ),	/* 24 */
/* 726 */	NdrFcShort( 0x0 ),	/* 0 */
/* 728 */	NdrFcShort( 0xa ),	/* Offset= 10 (738) */
/* 730 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 732 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 734 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (710) */
/* 736 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 738 */	
			0x11, 0x0,	/* FC_RP */
/* 740 */	NdrFcShort( 0xffffff0c ),	/* Offset= -244 (496) */
/* 742 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 744 */	NdrFcShort( 0x1 ),	/* 1 */
/* 746 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 748 */	NdrFcShort( 0x0 ),	/* 0 */
/* 750 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 752 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 754 */	NdrFcShort( 0x8 ),	/* 8 */
/* 756 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 758 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 760 */	NdrFcShort( 0x4 ),	/* 4 */
/* 762 */	NdrFcShort( 0x4 ),	/* 4 */
/* 764 */	0x13, 0x0,	/* FC_OP */
/* 766 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (742) */
/* 768 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 770 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 772 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 774 */	NdrFcShort( 0x2 ),	/* 2 */
/* 776 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 778 */	NdrFcShort( 0x0 ),	/* 0 */
/* 780 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 782 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 784 */	NdrFcShort( 0x8 ),	/* 8 */
/* 786 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 788 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 790 */	NdrFcShort( 0x4 ),	/* 4 */
/* 792 */	NdrFcShort( 0x4 ),	/* 4 */
/* 794 */	0x13, 0x0,	/* FC_OP */
/* 796 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (772) */
/* 798 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 800 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 802 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 804 */	NdrFcShort( 0x4 ),	/* 4 */
/* 806 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 808 */	NdrFcShort( 0x0 ),	/* 0 */
/* 810 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 812 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 814 */	NdrFcShort( 0x8 ),	/* 8 */
/* 816 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 818 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 820 */	NdrFcShort( 0x4 ),	/* 4 */
/* 822 */	NdrFcShort( 0x4 ),	/* 4 */
/* 824 */	0x13, 0x0,	/* FC_OP */
/* 826 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (802) */
/* 828 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 830 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 832 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 834 */	NdrFcShort( 0x8 ),	/* 8 */
/* 836 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 838 */	NdrFcShort( 0x0 ),	/* 0 */
/* 840 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 842 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 844 */	NdrFcShort( 0x8 ),	/* 8 */
/* 846 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 848 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 850 */	NdrFcShort( 0x4 ),	/* 4 */
/* 852 */	NdrFcShort( 0x4 ),	/* 4 */
/* 854 */	0x13, 0x0,	/* FC_OP */
/* 856 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (832) */
/* 858 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 860 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 862 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 864 */	NdrFcShort( 0x8 ),	/* 8 */
/* 866 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 868 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 870 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 872 */	NdrFcShort( 0x8 ),	/* 8 */
/* 874 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 876 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 878 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 880 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (862) */
/* 882 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 884 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 886 */	NdrFcShort( 0x28 ),	/* 40 */
/* 888 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (870) */
/* 890 */	NdrFcShort( 0x0 ),	/* Offset= 0 (890) */
/* 892 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 894 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 896 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 898 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffdf7 ),	/* Offset= -521 (378) */
			0x5b,		/* FC_END */
/* 902 */	
			0x13, 0x0,	/* FC_OP */
/* 904 */	NdrFcShort( 0xfffffef6 ),	/* Offset= -266 (638) */
/* 906 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 908 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 910 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 912 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 914 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 916 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 918 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 920 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 922 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 924 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 926 */	
			0x13, 0x0,	/* FC_OP */
/* 928 */	NdrFcShort( 0xfffffda8 ),	/* Offset= -600 (328) */
/* 930 */	
			0x13, 0x10,	/* FC_OP */
/* 932 */	NdrFcShort( 0xfffffc62 ),	/* Offset= -926 (6) */
/* 934 */	
			0x13, 0x10,	/* FC_OP */
/* 936 */	NdrFcShort( 0xfffffda6 ),	/* Offset= -602 (334) */
/* 938 */	
			0x13, 0x10,	/* FC_OP */
/* 940 */	NdrFcShort( 0xfffffdb4 ),	/* Offset= -588 (352) */
/* 942 */	
			0x13, 0x10,	/* FC_OP */
/* 944 */	NdrFcShort( 0xfffffdc2 ),	/* Offset= -574 (370) */
/* 946 */	
			0x13, 0x10,	/* FC_OP */
/* 948 */	NdrFcShort( 0x2 ),	/* Offset= 2 (950) */
/* 950 */	
			0x13, 0x0,	/* FC_OP */
/* 952 */	NdrFcShort( 0xfffffc48 ),	/* Offset= -952 (0) */
/* 954 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 956 */	NdrFcShort( 0x10 ),	/* 16 */
/* 958 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 960 */	0x1,		/* FC_BYTE */
			0x38,		/* FC_ALIGNM4 */
/* 962 */	0x8,		/* FC_LONG */
			0x39,		/* FC_ALIGNM8 */
/* 964 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 966 */	
			0x13, 0x0,	/* FC_OP */
/* 968 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (954) */
/* 970 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 972 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 974 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 976 */	NdrFcShort( 0x20 ),	/* 32 */
/* 978 */	NdrFcShort( 0x0 ),	/* 0 */
/* 980 */	NdrFcShort( 0x0 ),	/* Offset= 0 (980) */
/* 982 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 984 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 986 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 988 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 990 */	NdrFcShort( 0xfffffc5a ),	/* Offset= -934 (56) */
/* 992 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 994 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 996 */	NdrFcShort( 0x1 ),	/* 1 */
/* 998 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1000 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1002 */	NdrFcShort( 0xfffffc4a ),	/* Offset= -950 (52) */
/* 1004 */	
			0x12, 0x0,	/* FC_UP */
/* 1006 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (974) */
/* 1008 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1010 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1012 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1014 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1016 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (1004) */
/* 1018 */	
			0x12, 0x0,	/* FC_UP */
/* 1020 */	NdrFcShort( 0xfffffc18 ),	/* Offset= -1000 (20) */
/* 1022 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1024 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1026 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1028 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1030 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (1018) */

			0x0
        }
    };

const CInterfaceProxyVtbl * _ComTest1_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IComTestObjectProxyVtbl,
    0
};

const CInterfaceStubVtbl * _ComTest1_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IComTestObjectStubVtbl,
    0
};

PCInterfaceName const _ComTest1_InterfaceNamesList[] = 
{
    "IComTestObject",
    0
};

const IID *  _ComTest1_BaseIIDList[] = 
{
    &IID_IDispatch,
    0
};


#define _ComTest1_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _ComTest1, pIID, n)

int __stdcall _ComTest1_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_ComTest1_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo ComTest1_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _ComTest1_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _ComTest1_StubVtblList,
    (const PCInterfaceName * ) & _ComTest1_InterfaceNamesList,
    (const IID ** ) & _ComTest1_BaseIIDList,
    & _ComTest1_IID_Lookup, 
    1,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
