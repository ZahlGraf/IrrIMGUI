/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015-2016 Andre Netzeband
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/**
 * @file   CGUITexture.h
 * @author Andre Netzeband
 * @brief  Contains the class for a GUITexture object.
 * @addtogroup IrrIMGUIPrivate
 */

#ifndef IRRIMGUI_CGUITEXTURE_H_
#define IRRIMGUI_CGUITEXTURE_H_

// library includes
#include <IrriMGUI/IncludeIrrlicht.h>

// module includes
#include <IrrIMGUI/IGUITexture.h>

/**
 * @addtogroup IrrIMGUIPrivate
 * @{
 */
namespace IrrIMGUI
{
namespace Private
{
  enum TextureSourceType
  {
    ETST_TEXTURE,
    ETST_IMAGE,
    ETST_RAWDATA,
    ETST_GUIFONT,
    ETST_UNKNOWN
  };

  union TextureSource
  {
      irr::video::ITexture *TextureID;
      irr::video::IImage   *ImageID;
      irr::u8              *RawDataID;
      irr::u8              *GUIFontID;
  };

  class CGUITexture : public IGUITexture
  {
    public:
      /// @brief Constructor.
      CGUITexture(void);

      /// @brief Destructor.
      virtual ~CGUITexture(void);

      bool                mIsUsingOwnMemory;
      TextureSourceType   mSourceType;
      TextureSource       mSource;
      bool                mIsValid;
      ImTextureID         mGPUTextureID;

    protected:
  };

}
}

/**
 * @}
 */

#endif  // IRRIMGUI_CGUITEXTURE_H_
