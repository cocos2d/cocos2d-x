/****************************************************************************
Copyright (c) Microsoft Open Technologies, Inc.  All rights reserved.

The MIT License (MIT)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

Based upon code from the DirectX Tool Kit by Microsoft Corporation,
obtained from https://directxtk.codeplex.com
****************************************************************************/
#include "WICImageLoader-winrt.h"

NS_CC_BEGIN

#if defined(CC_USE_WIC)

	IWICImagingFactory* WICImageLoader::_wicFactory = NULL;

static WICConvert g_WICConvert[] = 
{
	// Note target GUID in this conversion table must be one of those directly supported formats (above).

	{ GUID_WICPixelFormatBlackWhite,            GUID_WICPixelFormat8bppGray }, // DXGI_FORMAT_R8_UNORM

	{ GUID_WICPixelFormat1bppIndexed,           GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
	{ GUID_WICPixelFormat2bppIndexed,           GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
	{ GUID_WICPixelFormat4bppIndexed,           GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
	{ GUID_WICPixelFormat8bppIndexed,           GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 

	{ GUID_WICPixelFormat2bppGray,              GUID_WICPixelFormat8bppGray }, // DXGI_FORMAT_R8_UNORM 
	{ GUID_WICPixelFormat4bppGray,              GUID_WICPixelFormat8bppGray }, // DXGI_FORMAT_R8_UNORM 

	{ GUID_WICPixelFormat16bppGrayFixedPoint,   GUID_WICPixelFormat16bppGrayHalf }, // DXGI_FORMAT_R16_FLOAT 
	{ GUID_WICPixelFormat32bppGrayFixedPoint,   GUID_WICPixelFormat32bppGrayFloat }, // DXGI_FORMAT_R32_FLOAT 

	{ GUID_WICPixelFormat16bppBGR555,           GUID_WICPixelFormat16bppBGRA5551 }, // DXGI_FORMAT_B5G5R5A1_UNORM

	{ GUID_WICPixelFormat32bppBGR101010,        GUID_WICPixelFormat32bppRGBA1010102 }, // DXGI_FORMAT_R10G10B10A2_UNORM

    { GUID_WICPixelFormat24bppBGR,              GUID_WICPixelFormat24bppRGB }, // DXGI_FORMAT_R8G8B8A8_UNORM 
    { GUID_WICPixelFormat24bppRGB,              GUID_WICPixelFormat24bppRGB }, // DXGI_FORMAT_R8G8B8A8_UNORM 
	{ GUID_WICPixelFormat32bppPBGRA,            GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
	{ GUID_WICPixelFormat32bppPRGBA,            GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 

	{ GUID_WICPixelFormat48bppRGB,              GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
	{ GUID_WICPixelFormat48bppBGR,              GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
	{ GUID_WICPixelFormat64bppBGRA,             GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
	{ GUID_WICPixelFormat64bppPRGBA,            GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
	{ GUID_WICPixelFormat64bppPBGRA,            GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM

	{ GUID_WICPixelFormat48bppRGBFixedPoint,    GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
	{ GUID_WICPixelFormat48bppBGRFixedPoint,    GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
	{ GUID_WICPixelFormat64bppRGBAFixedPoint,   GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
	{ GUID_WICPixelFormat64bppBGRAFixedPoint,   GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
	{ GUID_WICPixelFormat64bppRGBFixedPoint,    GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
	{ GUID_WICPixelFormat64bppRGBHalf,          GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
	{ GUID_WICPixelFormat48bppRGBHalf,          GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 

	{ GUID_WICPixelFormat128bppPRGBAFloat,      GUID_WICPixelFormat128bppRGBAFloat }, // DXGI_FORMAT_R32G32B32A32_FLOAT 
	{ GUID_WICPixelFormat128bppRGBFloat,        GUID_WICPixelFormat128bppRGBAFloat }, // DXGI_FORMAT_R32G32B32A32_FLOAT 
	{ GUID_WICPixelFormat128bppRGBAFixedPoint,  GUID_WICPixelFormat128bppRGBAFloat }, // DXGI_FORMAT_R32G32B32A32_FLOAT 
	{ GUID_WICPixelFormat128bppRGBFixedPoint,   GUID_WICPixelFormat128bppRGBAFloat }, // DXGI_FORMAT_R32G32B32A32_FLOAT 
	{ GUID_WICPixelFormat32bppRGBE,             GUID_WICPixelFormat128bppRGBAFloat }, // DXGI_FORMAT_R32G32B32A32_FLOAT 

	{ GUID_WICPixelFormat32bppCMYK,             GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
	{ GUID_WICPixelFormat64bppCMYK,             GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
	{ GUID_WICPixelFormat40bppCMYKAlpha,        GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
	{ GUID_WICPixelFormat80bppCMYKAlpha,        GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM

	//#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8) || defined(_WIN7_PLATFORM_UPDATE)
	//    { GUID_WICPixelFormat32bppRGB,              GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM
	//    { GUID_WICPixelFormat64bppRGB,              GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
	//    { GUID_WICPixelFormat64bppPRGBAHalf,        GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
	//#endif

	// We don't support n-channel formats
};

WICImageLoader::WICImageLoader() :
	_width(0),
	_height(0),
	_dataLen(0),
	_bpp(0),
	_data(0)
{
	memset((void*)&_format, 0, sizeof(_format));
}

WICImageLoader::~WICImageLoader()
{
	if(_data != NULL && _dataLen > 0) {
		delete[] _data;
		_data = NULL;
	}
}

bool WICImageLoader::decodeImageData(ImageBlob blob, size_t size)
{
	bool bRet = false;
	HRESULT hr = S_FALSE;

	IWICStream* pWicStream = NULL;
	IWICImagingFactory* pWicFactory = getWICFactory();

	if(NULL != pWicFactory)
	{
		hr = pWicFactory->CreateStream(&pWicStream);
	}

	if(SUCCEEDED(hr))
	{
		hr = pWicStream->InitializeFromMemory((BYTE*)blob, size);
	}

	IWICBitmapDecoder* pDecoder = NULL;

	if(SUCCEEDED(hr))
	{
		hr = pWicFactory->CreateDecoderFromStream(pWicStream, NULL, WICDecodeMetadataCacheOnLoad, &pDecoder);
	}

	bRet = processImage(pDecoder);

	SafeRelease(&pWicStream);
	SafeRelease(&pDecoder);

	return bRet;
}

bool WICImageLoader::processImage(IWICBitmapDecoder* pDecoder)
{
	HRESULT hr = S_FALSE;
	IWICBitmapFrameDecode* pFrame = NULL;

	if(NULL != pDecoder)
	{
		hr = pDecoder->GetFrame(0, &pFrame);
	}

	if(SUCCEEDED(hr))
	{
		hr = pFrame->GetPixelFormat(&_format);
	}

	IWICFormatConverter* pConv = NULL;

	if(SUCCEEDED(hr))
	{
		hr = convertFormatIfRequired(pFrame, &pConv);
	}

	if(SUCCEEDED(hr))
	{
		_bpp = getBitsPerPixel(_format); 

		if(NULL != pConv) 
		{
			hr = pConv->GetSize((UINT*)&_width, (UINT*)&_height);
		}
		else
		{
			hr = pFrame->GetSize((UINT*)&_width, (UINT*)&_height);
		}
	}

	assert(_bpp > 0);
	assert(_width > 0 && _height > 0);

	if(SUCCEEDED(hr))
	{
		size_t rowPitch = (_width * _bpp + 7) / 8;
		_dataLen = rowPitch * _height;
		_data = new (std::nothrow) BYTE[_dataLen];

		if(NULL != pConv)
		{
			hr = pConv->CopyPixels(NULL, rowPitch, _dataLen, _data);
		}
		else
		{
			hr = pFrame->CopyPixels(NULL, rowPitch, _dataLen, _data);
		}
	}

	SafeRelease(&pFrame);
	SafeRelease(&pConv);
	return SUCCEEDED(hr);
}

HRESULT WICImageLoader::convertFormatIfRequired(IWICBitmapFrameDecode* pFrame, IWICFormatConverter** ppConv)
{
	*ppConv = NULL;

	if(	(memcmp(&_format, &GUID_WICPixelFormat8bppGray, sizeof(WICPixelFormatGUID)) == 0) ||
		(memcmp(&_format, &GUID_WICPixelFormat8bppAlpha, sizeof(WICPixelFormatGUID)) == 0) ||
		(memcmp(&_format, &GUID_WICPixelFormat24bppRGB, sizeof(WICPixelFormatGUID)) == 0) ||
		(memcmp(&_format, &GUID_WICPixelFormat32bppRGBA, sizeof(WICPixelFormatGUID)) == 0))
	{
		return S_OK;
	}

	HRESULT hr = E_FAIL;
	IWICImagingFactory* pFactory = getWICFactory();
	IWICFormatConverter* pConv = NULL;

	if(NULL != pFactory)
	{
		hr = pFactory->CreateFormatConverter(&pConv);
	}

	WICPixelFormatGUID destFormat = GUID_WICPixelFormat32bppRGBA; // Fallback to RGBA 32-bit format which is supported by all devices

	for( size_t i=0; i < _countof(g_WICConvert); ++i )
	{
		if ( memcmp( &g_WICConvert[i].source, &_format, sizeof(WICPixelFormatGUID) ) == 0 )
		{
			memcpy( &destFormat, &g_WICConvert[i].target, sizeof(WICPixelFormatGUID) );
			break;
		}
	}

	BOOL bCanConv = FALSE;

	if(SUCCEEDED(hr))
	{
		hr = pConv->CanConvert(_format, destFormat, &bCanConv);
	}

	if(SUCCEEDED(hr) && bCanConv == TRUE)
	{
		hr = pConv->Initialize(pFrame, destFormat, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);
	}

	if(SUCCEEDED(hr))
	{
		memcpy(&_format, &destFormat, sizeof(WICPixelFormatGUID));
		*ppConv = pConv;
	}

	return SUCCEEDED(hr);
}

size_t WICImageLoader::getBitsPerPixel(WICPixelFormatGUID format)
{
	HRESULT hr = S_FALSE;

	IWICImagingFactory* pfactory = getWICFactory();

	IWICComponentInfo* pCInfo = NULL;

	if(pfactory != NULL)
	{
		hr = pfactory->CreateComponentInfo(format, &pCInfo);
	}

	WICComponentType cType;

	if(SUCCEEDED(hr))
	{
		hr = pCInfo->GetComponentType(&cType);
	}

	IWICPixelFormatInfo* pPInfo = NULL;

	if(SUCCEEDED(hr) && cType == WICPixelFormat)
	{
		hr = pCInfo->QueryInterface(IID_IWICPixelFormatInfo, (void**)&pPInfo);
	}

	UINT bpp = 0;

	if(SUCCEEDED(hr))
	{
		hr = pPInfo->GetBitsPerPixel(&bpp);
	}

	SafeRelease(&pCInfo);
	SafeRelease(&pPInfo);
	return bpp;
}

int WICImageLoader::getHeight()
{
	return _height;
}

int WICImageLoader::getWidth()
{
	return _width;
}

int WICImageLoader::getImageData(ImageBlob rawData, size_t dataLen)
{
	if(dataLen < _dataLen)
		return 0;

	memcpy((void*)rawData, _data, _dataLen);

	return _dataLen;
}

int WICImageLoader::getImageDataSize()
{
	return _dataLen;
}

WICPixelFormatGUID WICImageLoader::getPixelFormat()
{
	return _format;
}

bool WICImageLoader::encodeImageData(std::string path, const unsigned char* data, size_t dataLen, WICPixelFormatGUID pixelFormat, int width, int height, GUID containerFormat)
{
	assert(data != NULL);
	assert(dataLen > 0 && width > 0 && height > 0);

	IWICImagingFactory* pFact = getWICFactory();

	HRESULT hr = E_FAIL;
	IWICStream* pStream = NULL;

	if (NULL != pFact) {
		hr = pFact->CreateStream(&pStream);
	}

	if (SUCCEEDED(hr)) {
		std::wstring wpath;
		wpath.assign(path.begin(), path.end());
		hr = pStream->InitializeFromFilename(wpath.c_str(), GENERIC_WRITE);
	}

	IWICBitmapEncoder* pEnc = NULL;

	if (SUCCEEDED(hr)) {
		hr = pFact->CreateEncoder(containerFormat, NULL, &pEnc);
	}

	if (SUCCEEDED(hr)) {
		hr = pEnc->Initialize(pStream, WICBitmapEncoderNoCache);
	}

	IWICBitmapFrameEncode* pFrame = NULL;
	IPropertyBag2* pProp = NULL;

	if (SUCCEEDED(hr)) {
		hr = pEnc->CreateNewFrame(&pFrame, &pProp);
	}

	if (SUCCEEDED(hr)) {
		hr = pFrame->Initialize(pProp);
	}

	if (SUCCEEDED(hr)) {
		hr = pFrame->SetSize(width, height);
	}

	if (SUCCEEDED(hr)) {
		WICPixelFormatGUID targetFormat = pixelFormat;
		hr = pFrame->SetPixelFormat(&targetFormat);

		if (targetFormat != pixelFormat) {
			hr = E_INVALIDARG;
		}
	}

	if (SUCCEEDED(hr)) {
		size_t bpp = getBitsPerPixel(pixelFormat);
		size_t stride = (width * bpp + 7) / 8;

		hr = pFrame->WritePixels(height, stride, dataLen, (BYTE*)data);
	}

	if (SUCCEEDED(hr)) {
		hr = pFrame->Commit();
	}

	if (SUCCEEDED(hr)) {
		hr = pEnc->Commit();
	}

	SafeRelease(&pStream);
	SafeRelease(&pEnc);
	SafeRelease(&pFrame);
	SafeRelease(&pProp);
	return SUCCEEDED(hr);
}

IWICImagingFactory* WICImageLoader::getWICFactory()
{
	if(NULL == _wicFactory)
	{
		HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

		if(SUCCEEDED(hr))
		{
			hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&_wicFactory);
		}

		if(FAILED(hr))
		{
			SafeRelease(&_wicFactory);
		}
	}

	return _wicFactory;	
}

#endif

NS_CC_END
