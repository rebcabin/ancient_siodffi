// ComTestObject.h : Declaration of the CComTestObject

#ifndef __COMTESTOBJECT_H_
#define __COMTESTOBJECT_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CComTestObject
class ATL_NO_VTABLE CComTestObject : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CComTestObject, &CLSID_ComTestObject>,
	public IDispatchImpl<IComTestObject, &IID_IComTestObject, &LIBID_COMTEST1Lib>
{
private:
	short       m_short;
	long        m_long;
	CComVariant m_CComVariant;
	BSTR		m_bstr;

public:
	CComTestObject()
	{
		Init();
	}

	void Init()
	{
		m_short = 0;
		m_long  = 0L;
		m_bstr  = NULL;
		m_CComVariant.Clear();
	}

DECLARE_REGISTRY_RESOURCEID(IDR_COMTESTOBJECT)

BEGIN_COM_MAP(CComTestObject)
	COM_INTERFACE_ENTRY(IComTestObject)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IComTestObject
public:
	STDMETHOD(get_BstrProp)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_BstrProp)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_VariantProp)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_VariantProp)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_LongProp)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_LongProp)(/*[in]*/ long newVal);
	STDMETHOD(get_ShortProp)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_ShortProp)(/*[in]*/ short newVal);
	STDMETHOD(SayHello)(/*[out]*/ BSTR* bszOut);
};

#endif //__COMTESTOBJECT_H_
