#pragma once
#include <atlstr.h> 
template<class T>
class CProxy_IGraphCtlEvents :
	public ATL::IConnectionPointImpl<T, &__uuidof(_IGraphCtlEvents)>
{
public:
	HRESULT Fire_ShowGraph(BOOL sb)
	{		
		HRESULT hr = S_OK;
		T* pThis = static_cast<T*>(this);
		int cConnections = m_vec.GetSize();

		for (int iConnection = 0; iConnection < cConnections; iConnection++)
		{
			pThis->Lock();
			CComPtr<IUnknown> punkConnection = m_vec.GetAt(iConnection);
			pThis->Unlock();

			IDispatch* pConnection = static_cast<IDispatch*>(punkConnection.p);

			if (pConnection)
			{
				CComVariant avarParams[2];
				avarParams[1] = sb;
				avarParams[1].vt = VT_BOOL;
				DISPPARAMS params = { avarParams, NULL, 1, 0 };
				hr = pConnection->Invoke(1, IID_NULL, LOCALE_USER_DEFAULT,
					DISPATCH_METHOD, &params, NULL, NULL, NULL);

				// Для отладки. 
				CString strMessage;
				strMessage.Format(_T("Сработал Fire_ShowGraph\nhr = 0x%08X\nsb = %s"),
					hr, (sb == TRUE) ? _T("VARIANT_TRUE") : _T("VARIANT_FALSE"));

				/*::MessageBox(nullptr, strMessage, _T("Сообщение"),
					MB_OK | MB_ICONINFORMATION);*/
			}
		}
		return hr;

	}
	
};

