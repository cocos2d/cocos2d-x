/*
 * Copyright 2007, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); 
 * you may not use this file except in compliance with the License. 
 * You may obtain a copy of the License at 
 *
 *     http://www.apache.org/licenses/LICENSE-2.0 
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 */

#ifndef IMAGE_CODEC_BMPDECODERHELPER_H__
#define IMAGE_CODEC_BMPDECODERHELPER_H__

///////////////////////////////////////////////////////////////////////////////
// this section is my current "glue" between google3 code and android.
// will be fixed soon

#include "SkTypes.h"
#include <limits.h>
#define DISALLOW_EVIL_CONSTRUCTORS(name)
#define CHECK(predicate)  SkASSERT(predicate)
typedef uint8_t uint8;
typedef uint32_t uint32;

template <typename T> class scoped_array {
private:
  T* ptr_;
  scoped_array(scoped_array const&);
  scoped_array& operator=(const scoped_array&);

public:
  explicit scoped_array(T* p = 0) : ptr_(p) {}
  ~scoped_array() {
    delete[] ptr_;
  }
  
  void reset(T* p = 0) {
    if (p != ptr_) {
      delete[] ptr_;
      ptr_ = p;
    }
  }
  
  T& operator[](int i) const {
    return ptr_[i];
  }
};

///////////////////////////////////////////////////////////////////////////////

namespace image_codec {

class BmpDecoderCallback {
 public:
  BmpDecoderCallback() { }
  virtual ~BmpDecoderCallback() {}
  
  /**
   * This is called once for an image. It is passed the width and height and
   * should return the address of a buffer that is large enough to store
   * all of the resulting pixels (widht * height * 3 bytes). If it returns NULL,
   * then the decoder will abort, but return true, as the caller has received
   * valid dimensions.
   */
  virtual uint8* SetSize(int width, int height) = 0;
   
 private:
  DISALLOW_EVIL_CONSTRUCTORS(BmpDecoderCallback);
};

class BmpDecoderHelper {
 public:
  BmpDecoderHelper() { }
  ~BmpDecoderHelper() { }
  bool DecodeImage(const char* data,
                   int len,
                   int max_pixels,
                   BmpDecoderCallback* callback);

 private:
  DISALLOW_EVIL_CONSTRUCTORS(BmpDecoderHelper);

  void DoRLEDecode();
  void DoStandardDecode();
  void PutPixel(int x, int y, uint8 col);

  int GetInt();
  int GetShort();
  uint8 GetByte();
  int CalcShiftRight(uint32 mask);
  int CalcShiftLeft(uint32 mask);

  const uint8* data_;
  int pos_;
  int len_;
  int width_;
  int height_;
  int bpp_;
  int pixelPad_;
  int rowPad_;
  scoped_array<uint8> colTab_;
  uint32 redBits_;
  uint32 greenBits_;
  uint32 blueBits_;
  int redShiftRight_;
  int greenShiftRight_;
  int blueShiftRight_;
  int redShiftLeft_;
  int greenShiftLeft_;
  int blueShiftLeft_;
  uint8* output_;
  bool inverted_;
};
  
} // namespace

#endif
