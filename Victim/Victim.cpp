#include <stdio.h>
#include <string.h>

__declspec (dllexport) int __stdcall
TestVictim0 ()
{
    return 42 ;
}

__declspec (dllexport) int __stdcall
TestVictim3 (long x, long y, long z)
{
    return x + y + z ;
}

__declspec (dllexport) char * __stdcall
TV4 (char * s)
{
    printf("Got this: \"%s\"\n", s) ;
    return s ;
}

__declspec (dllexport) char * __cdecl
TV5cdecl (char * s, char * t)
{
	return strcat (s, t) ;
}

typedef int (*PFII   ) (int) ;
typedef int (*PFIII  ) (int, int) ;
typedef int (*PFIIIII) (int, int, int, int) ;

__declspec (dllexport) int __stdcall
TVcallback (int i1, int i2, PFII f)
{
	int i = f ( i1 * i2 ) ;

	return i ;
}

__declspec (dllexport) int __stdcall
TVBinaryCallback (int i1, int i2, PFIII f)
{
	int i = f ( i1, i2 ) ;

    return i ;
}

__declspec (dllexport) int __stdcall
TVQuaternaryCallback (int i1, int i2, int i3, int i4, PFIIIII f)
{
	int i = f ( i1, i2, i3, i4 ) ;

	return i ;
}
