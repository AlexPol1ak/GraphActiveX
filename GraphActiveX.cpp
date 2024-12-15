// GraphActiveX.cpp: реализация экспортов DLL.


#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "GraphActiveX_i.h"
#include "dllmain.h"


using namespace ATL;

// Используется, чтобы определить, можно ли выгрузить DLL средствами OLE.
_Use_decl_annotations_
STDAPI DllCanUnloadNow(void)
{
	return _AtlModule.DllCanUnloadNow();
}

// Возвращает фабрику класса для создания объекта требуемого типа.
_Use_decl_annotations_
STDAPI DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID* ppv)
{
	return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}

// DllRegisterServer - добавляет записи в системный реестр.
_Use_decl_annotations_
STDAPI DllRegisterServer(void)
{
	// регистрирует объект, библиотеку типов и все интерфейсы в библиотеке типов
	HRESULT hr = _AtlModule.DllRegisterServer();
	return hr;
}

// DllUnregisterServer - удаляет записи из системного реестра.
_Use_decl_annotations_
STDAPI DllUnregisterServer(void)
{
	HRESULT hr = _AtlModule.DllUnregisterServer();
	return hr;
}

// DllInstall - добавляет и удаляет записи системного реестра для конкретного пользователя и компьютера.
STDAPI DllInstall(BOOL bInstall, _In_opt_  LPCWSTR pszCmdLine)
{
	HRESULT hr = E_FAIL;
	static const wchar_t szUserSwitch[] = L"user";

	if (pszCmdLine != nullptr)
	{
		if (_wcsnicmp(pszCmdLine, szUserSwitch, _countof(szUserSwitch)) == 0)
		{
			ATL::AtlSetPerUserRegistration(true);
		}
	}

	if (bInstall)
	{
		hr = DllRegisterServer();
		if (FAILED(hr))
		{
			DllUnregisterServer();
		}
	}
	else
	{
		hr = DllUnregisterServer();
	}

	return hr;
}


