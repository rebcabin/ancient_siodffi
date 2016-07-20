// ComTestObject.cpp : Implementation of CComTestObject
#include "stdafx.h"
#include "ComTest1.h"
#include "ComTestObject.h"

/////////////////////////////////////////////////////////////////////////////
// CComTestObject


STDMETHODIMP CComTestObject::SayHello(BSTR * bszOut)
{
	if (bszOut)
		*bszOut = SysAllocString(L"Hello from ComTest1");

	return S_OK;
}

STDMETHODIMP CComTestObject::get_ShortProp(short * pVal)
{
	if (pVal)
		*pVal = m_short;

	return S_OK;
}

STDMETHODIMP CComTestObject::put_ShortProp(short newVal)
{
	m_short = newVal;

	return S_OK;
}

STDMETHODIMP CComTestObject::get_LongProp(long * pVal)
{
	if (pVal)
		*pVal = m_long;

	return S_OK;
}

STDMETHODIMP CComTestObject::put_LongProp(long newVal)
{
	m_long = newVal;

	return S_OK;
}

STDMETHODIMP CComTestObject::get_VariantProp(VARIANT * pVal)
{
	if (pVal)
		*pVal = m_CComVariant;

	return S_OK;
}

STDMETHODIMP CComTestObject::put_VariantProp(VARIANT newVal)
{
	m_CComVariant = newVal;

	return S_OK;
}

STDMETHODIMP CComTestObject::get_BstrProp(BSTR * pVal)
{
	if (pVal)
		*pVal = m_bstr;

	return S_OK;
}

STDMETHODIMP CComTestObject::put_BstrProp(BSTR newVal)
{
	m_bstr = newVal;

	return S_OK;
}
