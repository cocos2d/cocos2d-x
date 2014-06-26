//
// Copyright (c) 2002-2013 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// winrtangle.h: Defines the interface for the EGLNativeWindowType

#ifndef WINRT_ANGLE_H_
#define WINRT_ANGLE_H_

#include <unknwn.h>
#include <wrl.h>
#include <d3d11_1.h>

typedef enum {
    ANGLE_D3D_FEATURE_LEVEL_ANY = 0,
    ANGLE_D3D_FEATURE_LEVEL_9_1,
    ANGLE_D3D_FEATURE_LEVEL_9_2,
    ANGLE_D3D_FEATURE_LEVEL_9_3,
    ANGLE_D3D_FEATURE_LEVEL_10_0,
    ANGLE_D3D_FEATURE_LEVEL_10_1,
    ANGLE_D3D_FEATURE_LEVEL_11_0
} ANGLE_D3D_FEATURE_LEVEL;

struct __declspec(uuid("736E7573-FD24-433F-811E-893B36B7A078")) IWinrtEglWindow : IUnknown
{
    virtual ANGLE_D3D_FEATURE_LEVEL __stdcall GetAngleD3DFeatureLevel() const = 0;
    virtual D3D_FEATURE_LEVEL __stdcall getD3DFeatureLevel() const = 0;
    virtual IUnknown* __stdcall GetWindowInterface() const = 0;
    virtual ID3D11Device* __stdcall GetAngleD3DDevice() const = 0;
    virtual void __stdcall SetAngleD3DDevice(ID3D11Device* device) = 0;
};

struct __declspec(uuid("6B70903A-0D55-45BA-A10E-CA2D428E4867")) IWinPhone8XamlD3DWindow : IUnknown
{
    virtual ID3D11Device1* __stdcall GetDevice() const = 0;
    virtual ID3D11DeviceContext1* __stdcall GetContext() const = 0;
    virtual ID3D11RenderTargetView* __stdcall GetRenderTarget() const = 0;
    virtual HRESULT getBackBuffer(ID3D11Texture2D** buffer) const = 0;
    virtual void __stdcall Update(ID3D11Device1* device, ID3D11DeviceContext1* context, ID3D11RenderTargetView* renderTarget) = 0;
};


HRESULT __stdcall CreateWinrtEglWindow(IUnknown* windowInterface, ANGLE_D3D_FEATURE_LEVEL featureLevel, IWinrtEglWindow ** result);
HRESULT __stdcall CreateWinPhone8XamlWindow(IWinPhone8XamlD3DWindow ** result);

#endif   // WINRT_ANGLE_H_

