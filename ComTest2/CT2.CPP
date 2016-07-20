// CT2.cpp : Implementation of CCT2
#include "stdafx.h"
#include "ComTest2.h"
#include "CT2.h"

/////////////////////////////////////////////////////////////////////////////
// CCT2


STDMETHODIMP CCT2::SayHello(BSTR * pbstr)
{
	if (pbstr)
	{
		if (*pbstr)
			SysFreeString (*pbstr) ;
		*pbstr = SysAllocString (L"Hello from ComTest2 (out of proc)");
	}

	return S_OK;
}

STDMETHODIMP CCT2::MoreHellos(BSTR *pbOut1, BSTR *pbOut2, BSTR *pbOut3, BSTR *pbOut4)
{
	*pbOut1 = SysAllocString (L"Hello from ComTest2 String 1") ;
	*pbOut2 = SysAllocString (L"Hello from ComTest2 String 2") ;
	*pbOut3 = SysAllocString (L"Hello from ComTest2 String 3") ;
	*pbOut4 = SysAllocString (L"Hello from ComTest2 String 4") ;

	return S_OK;
}

STDMETHODIMP CCT2::ShortTest(short *pShort)
{
	*pShort = 42 ;

	return S_OK;
}
