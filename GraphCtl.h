// GraphCtl.h: объявление CGraphCtl
#pragma once
#include "resource.h"       // основные символы
#include <atlctl.h>
#include "GraphActiveX_i.h"
#include "_IGraphCtlEvents_CP.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Однопотоковые COM-объекты не поддерживаются должным образом платформой Windows CE, например платформами Windows Mobile, в которых не предусмотрена полная поддержка DCOM. Определите _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA, чтобы принудить ATL поддерживать создание однопотоковых COM-объектов и разрешить использование его реализаций однопотоковых COM-объектов. Для потоковой модели в вашем rgs-файле задано значение 'Free', поскольку это единственная потоковая модель, поддерживаемая не-DCOM платформами Windows CE."
#endif

using namespace ATL;



// CGraphCtl
class ATL_NO_VTABLE CGraphCtl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CGraphCtl, IGraphCtl>,
	public IPersistStreamInitImpl<CGraphCtl>,
	public IOleControlImpl<CGraphCtl>,
	public IOleObjectImpl<CGraphCtl>,
	public IOleInPlaceActiveObjectImpl<CGraphCtl>,
	public IViewObjectExImpl<CGraphCtl>,
	public IOleInPlaceObjectWindowlessImpl<CGraphCtl>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CGraphCtl>,
	public CProxy_IGraphCtlEvents<CGraphCtl>,
	public IObjectWithSiteImpl<CGraphCtl>,
	public IServiceProviderImpl<CGraphCtl>,
	public IPersistStorageImpl<CGraphCtl>,
	public ISpecifyPropertyPagesImpl<CGraphCtl>,
	public IQuickActivateImpl<CGraphCtl>,
#ifndef _WIN32_WCE
	public IDataObjectImpl<CGraphCtl>,
#endif
	public IProvideClassInfo2Impl<&CLSID_GraphCtl, &__uuidof(_IGraphCtlEvents), &LIBID_GraphActiveXLib>,
	public IPropertyNotifySinkCP<CGraphCtl>,
	public IObjectSafetyImpl<CGraphCtl, INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public CComCoClass<CGraphCtl, &CLSID_GraphCtl>,
	public CComControl<CGraphCtl>
{
public:


	CGraphCtl()
	{
	}

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_INSIDEOUT |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_GRAPHCTL)


BEGIN_COM_MAP(CGraphCtl)
	COM_INTERFACE_ENTRY(IGraphCtl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
#ifndef _WIN32_WCE
	COM_INTERFACE_ENTRY(IDataObject)
#endif
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY(IObjectWithSite)
	COM_INTERFACE_ENTRY(IServiceProvider)
	COM_INTERFACE_ENTRY_IID(IID_IObjectSafety, IObjectSafety)
END_COM_MAP()

BEGIN_PROP_MAP(CGraphCtl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
#ifndef _WIN32_WCE
	PROP_ENTRY_TYPE("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage, VT_UI4)
#endif
#ifndef _WIN32_WCE
	PROP_ENTRY_TYPE("ForeColor", DISPID_FORECOLOR, CLSID_StockColorPage, VT_UI4)
#endif
	// Записи примеров
	// PROP_ENTRY_TYPE("Имя свойства", dispid, clsid, vtType)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CGraphCtl)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(__uuidof(_IGraphCtlEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CGraphCtl)
	CHAIN_MSG_MAP(CComControl<CGraphCtl>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Прототипы обработчика:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* const arr[] =
		{
			&IID_IGraphCtl,
		};

		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IGraphCtl
public:
	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		// Ограничивает область вырезания прямоугольником, указанным в di.prcBounds
		HRGN hRgnOld = nullptr;
		if (GetClipRgn(di.hdcDraw, hRgnOld) != 1)
			hRgnOld = nullptr;
		bool bSelectOldRgn = false;

		HRGN hRgnNew = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);

		if (hRgnNew != nullptr)
		{
			bSelectOldRgn = (SelectClipRgn(di.hdcDraw, hRgnNew) != ERROR);
		}

		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("GraphCtl");
#ifndef _WIN32_WCE
		TextOut(di.hdcDraw,
			(rc.left + rc.right) / 2,
			(rc.top + rc.bottom) / 2,
			pszText,
			lstrlen(pszText));
#else
		ExtTextOut(di.hdcDraw,
			(rc.left + rc.right) / 2,
			(rc.top + rc.bottom) / 2,
			ETO_OPAQUE,
			nullptr,
			pszText,
			ATL::lstrlen(pszText),
			nullptr);
#endif

		if (bSelectOldRgn)
			SelectClipRgn(di.hdcDraw, hRgnOld);

		DeleteObject(hRgnNew);

		return S_OK;
	}

	OLE_COLOR m_clrBackColor;
	void OnBackColorChanged()
	{
		ATLTRACE(_T("OnBackColorChanged\n"));
	}
	OLE_COLOR m_clrForeColor;
	void OnForeColorChanged()
	{
		ATLTRACE(_T("OnForeColorChanged\n"));
	}
	STDMETHOD(_InternalQueryService)(REFGUID /*guidService*/, REFIID /*riid*/, void** /*ppvObject*/)
	{
		return E_NOTIMPL;
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}
};

OBJECT_ENTRY_AUTO(__uuidof(GraphCtl), CGraphCtl)
