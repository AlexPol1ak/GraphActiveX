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
		m_clrBackColor = RGB(255, 0, 0);
		m_clrForeColor = RGB(255, 10, 50);
		m_MaxX = 40;
		m_MinX = -5;
		m_MaxY = 40;
		m_MinY = -5;
	}
private:
	std::vector<POINT> m_points; // Хранение точек графика

public:
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
		HDC hdc = di.hdcDraw;

		RECT& rc = *(RECT*)di.prcBounds;

		// 1. Рассчитываем точки
		CalcPoints(rc);

		// 2. Заполняем фон
		HBRUSH hBrushBackground = CreateSolidBrush(RGB(240, 240, 240)); // Светло-серый фон
		FillRect(hdc, &rc, hBrushBackground);
		DeleteObject(hBrushBackground);

		// 3. Рисуем оси координат
		HPEN hAxisPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // Чёрные оси
		SelectObject(hdc, hAxisPen);

		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;

		// Горизонтальная ось
		MoveToEx(hdc, 0, height / 2, NULL);
		LineTo(hdc, width, height / 2);

		// Вертикальная ось
		MoveToEx(hdc, width / 2, 0, NULL);
		LineTo(hdc, width / 2, height);

		DeleteObject(hAxisPen);

		// 4. Рисуем функцию
		HPEN hGraphPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0)); // Красная линия для функции
		SelectObject(hdc, hGraphPen);

		if (!m_points.empty())
		{
			MoveToEx(hdc, m_points[0].x, m_points[0].y, NULL);

			for (size_t i = 1; i < m_points.size(); ++i)
			{
				LineTo(hdc, m_points[i].x, m_points[i].y);
			}
		}

		DeleteObject(hGraphPen);

		return S_OK;
	}

	OLE_COLOR m_clrBackColor = RGB(255, 0, 0);
	SHORT m_MinX = 1;
	SHORT m_MaxX = 50;
	SHORT m_MinY = 1;
	SHORT m_MaxY = 50;

	void OnBackColorChanged()
	{
		ATLTRACE(_T("OnBackColorChanged\n"));
	}
	OLE_COLOR m_clrForeColor = RGB(255, 10, 50);
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
	STDMETHOD(get_MinX)(SHORT* pVal);
	STDMETHOD(put_MinX)(SHORT newVal);
	STDMETHOD(get_MaxX)(SHORT* pVal);
	STDMETHOD(put_MaxX)(SHORT newVal);
	STDMETHOD(get_MinY)(SHORT* pVal);
	STDMETHOD(put_MinY)(SHORT newVal);
	STDMETHOD(get_MaxY)(SHORT* pVal);
	STDMETHOD(put_MaxY)(SHORT newVal);

	void CalcPoints(const RECT& rc);

};

OBJECT_ENTRY_AUTO(__uuidof(GraphCtl), CGraphCtl)
