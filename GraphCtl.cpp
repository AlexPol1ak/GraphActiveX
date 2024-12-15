// GraphCtl.cpp: реализация CGraphCtl
#include "pch.h"
#include "GraphCtl.h"


// CGraphCtl


STDMETHODIMP CGraphCtl::get_MinX(SHORT* pVal)
{
    *pVal = m_MinX;

    return S_OK;
}


STDMETHODIMP CGraphCtl::put_MinX(SHORT newVal)
{
    if (newVal < 1) return Error("The value must be greater than 1.");
    if (newVal >= m_MaxX) return Error("The minimum value of X must be less than the maximum value of X.");

    m_MinX = newVal;

    return S_OK;
}


STDMETHODIMP CGraphCtl::get_MaxX(SHORT* pVal)
{
    
    *pVal = m_MaxX;

    return S_OK;
}


STDMETHODIMP CGraphCtl::put_MaxX(SHORT newVal)
{
    
    if (newVal <= m_MinX) return Error("The maximum value of X must be greater than the minimum value of X.");
    m_MaxX = newVal;

    return S_OK;
}


STDMETHODIMP CGraphCtl::get_MinY(SHORT* pVal)
{
    *pVal = m_MinY;

    return S_OK;
}


STDMETHODIMP CGraphCtl::put_MinY(SHORT newVal)
{
    if (newVal < 1) return Error("The value must be greater than 1.");
    if (newVal >= m_MaxY) return Error("The minimum value of Y must be less than the maximum value of Y.");

    m_MinY = newVal;

    return S_OK;
}


STDMETHODIMP CGraphCtl::get_MaxY(SHORT* pVal)
{
    *pVal = m_MinY;

    return S_OK;
}


STDMETHODIMP CGraphCtl::put_MaxY(SHORT newVal)
{
    if (newVal <= m_MinY) return Error("The maximum value of Y must be greater than the minimum value of Y.");
    m_MaxY = newVal;

    return S_OK;
}
