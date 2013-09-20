/*
* cocos2d-x   http://www.cocos2d-x.org
*
* Copyright (c) 2010-2011 - cocos2d-x community
* 
* Portions Copyright (c) Microsoft Open Technologies, Inc.
* All Rights Reserved
* 
* Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 
* You may obtain a copy of the License at 
* 
* http://www.apache.org/licenses/LICENSE-2.0 
* 
* Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an 
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
* See the License for the specific language governing permissions and limitations under the License.
*/

#pragma once

#include <wrl\client.h>
#include <ppl.h>
#include <ppltasks.h>
#include <memory>

namespace DX
{
    inline void ThrowIfFailed(HRESULT hr)
    {
        if (FAILED(hr))
        {
            // Set a breakpoint on this line to catch DirectX API errors
            throw Platform::Exception::CreateException(hr);
        }
    }

    struct ByteArray { Platform::Array<byte>^ data; };

    // function that reads from a binary file asynchronously
    inline Concurrency::task<ByteArray> ReadDataAsync(Platform::String^ filename)
    {
        using namespace Windows::Storage;
        using namespace Concurrency;

        auto folder = Windows::ApplicationModel::Package::Current->InstalledLocation;

        task<StorageFile^> getFileTask(folder->GetFileAsync(filename));

        // Create a local to allow the DataReader to be passed between lambdas.
        auto reader = std::make_shared<Streams::DataReader^>(nullptr);
        return getFileTask.then([](StorageFile^ file)
        {
            return file->OpenReadAsync();
        }).then([reader](Streams::IRandomAccessStreamWithContentType^ stream)
        {
            *reader = ref new Streams::DataReader(stream);
            return (*reader)->LoadAsync(static_cast<uint32>(stream->Size));
        }).then([reader](uint32 count)
        {
            auto a = ref new Platform::Array<byte>(count);
            (*reader)->ReadBytes(a);
            ByteArray ba = { a };
            return ba;
        });
    }
}
