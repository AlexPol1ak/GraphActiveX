// dllmain.h: объявление класса модуля.

class CGraphActiveXModule : public ATL::CAtlDllModuleT< CGraphActiveXModule >
{
public :
	DECLARE_LIBID(LIBID_GraphActiveXLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_GRAPHACTIVEX, "{60818e62-e786-4da7-b7d0-dfe0b3997ad9}")
};

extern class CGraphActiveXModule _AtlModule;
