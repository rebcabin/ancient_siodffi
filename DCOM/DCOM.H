#pragma once

#define _WIN32_DCOM

#include <windows.h>
#include <objbase.h>

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>
#include <signal.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#include <stdarg.h>

#ifdef UNICODE
#error "This module must not be compiled for UNICODE"
#endif

#ifdef _UNICODE
#error "This module must not be compiled for UNICODE"
#endif

#include "siod.h"
#include "sioddata.h"

#define STR(x) ((x)->storage_as.string.data)
#define SYM(x) ((x)->storage_as.symbol.pname)
#define DIM(x) ((x)->storage_as.string.dim)

#define STRINGDATA(x) (TYPE(x) == tc_string ? STR(x) : SYM(x))

#define FORWARD /* NIL */

_declspec(selectany) long tc_guid      = 0;
_declspec(selectany) long tc_hresult   = 0;
_declspec(selectany) long tc_interface = 0;
_declspec(selectany) long tc_typeattr  = 0;
_declspec(selectany) long tc_funcdesc  = 0;
_declspec(selectany) long tc_vardesc   = 0;
_declspec(selectany) long tc_typedesc  = 0;
_declspec(selectany) long tc_bstr      = 0;
