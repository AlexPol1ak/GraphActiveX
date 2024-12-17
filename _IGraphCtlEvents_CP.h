#pragma once
template<class T>
class CProxy_IGraphCtlEvents :
	public ATL::IConnectionPointImpl<T, &__uuidof(_IGraphCtlEvents)>
{
public:
	HRESULT Fire_ShowGraph([in] VARIANT_BOOL sb)
	{

	}
	
};

