#pragma once

NS_CC_BEGIN

class IWP8Win
{
public:
	virtual ID3D11Device1* GetDevice() = 0;
	virtual ID3D11DeviceContext1* GetContext() = 0;	
};

NS_CC_END
