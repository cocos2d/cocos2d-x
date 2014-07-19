//--------------------------------------------------------------------------------------
// File: DirectXHelpers.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// http://go.microsoft.com/fwlink/?LinkId=248929
//--------------------------------------------------------------------------------------

#pragma once

#if defined(_XBOX_ONE) && defined(_TITLE)
#include <d3d11_x.h>
#define NO_D3D11_DEBUG_NAME
#else
#include <d3d11_1.h>
#endif

#if !defined(NO_D3D11_DEBUG_NAME) && ( defined(_DEBUG) || defined(PROFILE) )
#pragma comment(lib,"dxguid.lib")
#endif

#include <exception>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <stdint.h>
#pragma warning(pop)

//
// The core Direct3D headers provide the following helper C++ classes
//  CD3D11_RECT
//  CD3D11_BOX
//  CD3D11_DEPTH_STENCIL_DESC
//  CD3D11_BLEND_DESC, CD3D11_BLEND_DESC1
//  CD3D11_RASTERIZER_DESC, CD3D11_RASTERIZER_DESC1
//  CD3D11_BUFFER_DESC
//  CD3D11_TEXTURE1D_DESC
//  CD3D11_TEXTURE2D_DESC
//  CD3D11_TEXTURE3D_DESC
//  CD3D11_SHADER_RESOURCE_VIEW_DESC
//  CD3D11_RENDER_TARGET_VIEW_DESC
//  CD3D11_VIEWPORT
//  CD3D11_DEPTH_STENCIL_VIEW_DESC
//  CD3D11_UNORDERED_ACCESS_VIEW_DESC
//  CD3D11_SAMPLER_DESC
//  CD3D11_QUERY_DESC
//  CD3D11_COUNTER_DESC
//


namespace DirectX
{
    // simliar to std::lock_guard for exception-safe Direct3D 11 resource locking
    class MapGuard : public D3D11_MAPPED_SUBRESOURCE
    {
    public:
        MapGuard( _In_ ID3D11DeviceContext* context,
                  _In_ ID3D11Resource *resource,
                  _In_ UINT subresource,
                  _In_ D3D11_MAP mapType,
                  _In_ UINT mapFlags )
            : mContext(context), mResource(resource), mSubresource(subresource)
        {
            HRESULT hr = mContext->Map( resource, subresource, mapType, mapFlags, this );
            if (FAILED(hr))
            {
                throw std::exception();
            }
        }

        ~MapGuard()
        {
            mContext->Unmap( mResource, mSubresource );
        }

        uint8_t* get() const
        {
            return reinterpret_cast<uint8_t*>( pData );
        }
        uint8_t* get(size_t slice) const
        {
            return reinterpret_cast<uint8_t*>( pData ) + ( slice * DepthPitch );
        }

        uint8_t* scanline(size_t row) const
        {
            return reinterpret_cast<uint8_t*>( pData ) + ( row * RowPitch );
        }
        uint8_t* scanline(size_t slice, size_t row) const
        {
            return reinterpret_cast<uint8_t*>( pData ) + ( slice * DepthPitch ) + ( row * RowPitch );
        }

    private:
        ID3D11DeviceContext*    mContext;
        ID3D11Resource*         mResource;
        UINT                    mSubresource;

        MapGuard(MapGuard const&);
        MapGuard& operator= (MapGuard const&);
    };


    // Helper sets a D3D resource name string (used by PIX and debug layer leak reporting).
    template<UINT TNameLength>
    inline void SetDebugObjectName(_In_ ID3D11DeviceChild* resource, _In_z_ const char (&name)[TNameLength])
    {
        #if !defined(NO_D3D11_DEBUG_NAME) && ( defined(_DEBUG) || defined(PROFILE) )
            resource->SetPrivateData(WKPDID_D3DDebugObjectName, TNameLength - 1, name);
        #else
            UNREFERENCED_PARAMETER(resource);
            UNREFERENCED_PARAMETER(name);
        #endif
    }
}