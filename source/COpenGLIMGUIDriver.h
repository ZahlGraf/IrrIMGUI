/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015-2016 Andre Netzeband and Omar Cornut
 *
 * The original OpenGL implementation where this driver is based on was implemented
 * by Omar Cornut as an example how to use the IMGUI with OpenGL.
 * You can find the IMGUI here: https://github.com/ocornut/imgui
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
 * @file       COpenGLIMGUIDriver.h
 * @author     Andre Netzeband
 * @brief      Contains a driver that uses native OpenGL functions to render the GUI.
 * @attention  This driver is just a test- and fallback implementation. It is not officially supported by the Irrlicht IMGUI binding.
 * @addtogroup IrrIMGUIPrivateDriver
 */

#ifndef IRRIMGUI_SOURCE_COPENGLIMGUIDRIVER_H_
#define IRRIMGUI_SOURCE_COPENGLIMGUIDRIVER_H_

/**
 * @defgroup IrrIMGUIPrivateDriver Driver
 * @brief Contains Driver classes for the IMGUI renderer.
 * @ingroup IrrIMGUIPrivate
 * @{
 */

// module includes
#include <IrrIMGUI/IrrIMGUI.h>
#include "IIMGUIDriver.h"

namespace IrrIMGUI
{
namespace Private
{

/// @brief Contains driver classes for the IMGUI render system.
namespace Driver
{

  /// @brief A driver that uses native OpenGL functions for rendering.
  /// @attention This is a test- and fallback-implementation and is not officially supported by the Irrlicht IMGUI binding.
  class COpenGLIMGUIDriver : public IrrIMGUI::Private::IIMGUIDriver
  {
    friend class IrrIMGUI::Private::IIMGUIDriver;
    public:
    private:
      /// @{
      /// @name Constructor and Destructor

      /// @brief The constructor.
      /// @param pDevice is a pointer to the Irrlicht Device.
      COpenGLIMGUIDriver(irr::IrrlichtDevice * const pDevice);

      /// @brief The Destructor
      ~COpenGLIMGUIDriver(void);

      /// @}

      /// @{
      /// @name Methods used for setup.

      /// @brief Setups the IMGUI function pointer.
      void setupFunctionPointer(void);

      /// @}

      /// @{
      /// @name Methods used for rendering.

      /// @brief Renders a full IMGUI draw list (called by the IMGUI system).
      /// @param pDrawData is a list of data to draw.
      static void drawGUIList(ImDrawData * pDrawData);

      /// @brief Renders a single command list.
      /// @param pCommandList is the list of commands to render.
      static void drawCommandList(ImDrawList * pCommandList);

      /// @}

      /// @{
      /// @name Font related methods.

      /// @brief Deletes the font texture.
      /// @param pTextureID is the texture to delete.
      void deleteFontTexture(void * pTextureID);

      /// @brief Creates a new font texture.
      /// @return Returns a handle to this new texture.
      virtual void * createFontTextureWithHandle(void);

      /// @}

      /// @{
      /// @name Image related methods.

      /**
       * @brief Creates an texture ID out of a Irrlicht image. This texture ID can be used draw images with ImGui::Image function.
       * @param pImage Is a pointer to an IImage object. After the texture has been created, the IImage object can be destroyed.
       * @return Returns an texture ID that can be used to draw images. To delete the texture from graphic memory use later deleteTexture(...)
       */
      virtual ImTextureID createTextureFromImageInternal(irr::video::IImage * pImage);

      /**
       * @brief Deletes an texture from graphic memory.
       * @param Texture Is the texture to delete. Do not use it with ImGui::Image(..) function afterwards.
       */
      virtual void deleteTextureInternal(ImTextureID Texture);

      /// @}

  };

}
}
}

/**
 * @}
 */


#endif /* IRRIMGUI_SOURCE_COPENGLIMGUIDRIVER_H_ */
