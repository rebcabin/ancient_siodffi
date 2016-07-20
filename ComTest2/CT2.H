// CT2.h : Declaration of the CCT2

#ifndef __CT2_H_
#define __CT2_H_

#include "resource.h"       // main symbols
#include <mtx.h>

/////////////////////////////////////////////////////////////////////////////
// CCT2
class ATL_NO_VTABLE CCT2 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCT2, &CLSID_CT2>,
	public IDispatchImpl<ICT2, &IID_ICT2, &LIBID_COMTEST2Lib>
{
public:
	CCT2()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CT2)
DECLARE_NOT_AGGREGATABLE(CCT2)

BEGIN_COM_MAP(CCT2)
	COM_INTERFACE_ENTRY(ICT2)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ICT2
public:
	STDMETHOD(ShortTest)(/*[out]*/ short * pShort);
	STDMETHOD(MoreHellos)(/*[out]*/ BSTR * pbOut1, /*[out]*/ BSTR * pbOut2, /*[out]*/ BSTR * pbOut3, /*[out]*/ BSTR * pbOut4);
	STDMETHOD(SayHello)(/*[out]*/ BSTR* pbstrOut);
};

#endif //__CT2_H_
