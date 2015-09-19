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
 * @file   IIMGUIDriver.h
 * @author Andre Netzeband
 * @brief  Contains a driver interface for IMGUI.
 * @addtogroup IrrIMGUIPrivate
 */

#ifndef SOURCE_IIMGUIDRIVER_H_
#define SOURCE_IIMGUIDRIVER_H_

/**
 * @defgroup IrrIMGUIPrivate Private
 * @brief Private definitions for Irrlicht IMGUI bindings, do not use them outside, the interface may change a lot of times!
 * @ingroup IrrIMGUI
 * @{
 */

// library includes
#include <IrrIMGUI/IrrIMGUI.h>

namespace IrrIMGUI
{
/// @brief Private definitions for the IMGUI Irrlicht binding. Do not use them outside, the interface may change a lot of times!
namespace Private
{

  /// @brief Interface for an IMGUI Driver to setup the IMGUI render system.
  /// @note  This is a singleton class, since IMGUI is a single instance system.
  class IIMGUIDriver
  {
    public:
      /// @{
      /// @name Destructor

      /// @brief Destructor
      virtual ~IIMGUIDriver(void);

      /// @}

      /// @{
      /// @name Instance handling

      /// @brief This method returns an instance of the driver. If no driver yet exists, it will create a new driver by it's own choice. Otherwise it will simply return the instance of the existing driver.
      /// @param pDevice is a pointer to the Irrlicht Device to use.
      /// @return Returns a pointer to the instance.
      static IIMGUIDriver * getInstance(irr::IrrlichtDevice * pDevice);

      /// @brief Tells the driver, that it is not needed anymore. It decided by it's own if it will delete the single instance or exist further. When the instance was deleted.
      /// @return Returns true, if the instance was destroyed by this calls. If there was not instance, or if the instance has not been destroyed, it will return false.
      static bool deleteInstance(void);

      /// @}

      /// @{
      /// @name Miscellaneous methods

      /// @return Returns a pointer to the irrlicht device.
      irr::IrrlichtDevice * getIrrDevice(void);

      /// @return Returns a constant reference to the settings that are currently used.
      static SIMGUISettings const &getSettings(void);

      /// @param rSettings is a reference of the new settings to apply. The settings will applied to the global IMGUI object.
      static void setSettings(SIMGUISettings const &rSettings);

      /// @}

      /// @{
      /// @name Font related methods

      /// @return Returns true when the font texture is loaded and ready for usage.
      bool isFontTextureValid(void);

      /// @brief Deletes the font texture.
      void deleteFontTexture(void);

      /// @brief Creates a new font texture.
      void createFontTexture(void);

      /// @}

      /// @{
      /// @name Image and Texture methods

      /**
       * @brief Creates an texture ID out of a Irrlicht image. This texture ID can be used draw images with ImGui::Image function.
       * @param pImage Is a pointer to an IImage object. After the texture has been created, the IImage object can be destroyed.
       * @return Returns an texture ID that can be used to draw images. To delete the texture from graphic memory use later deleteTexture(...)
       */
      ImTextureID createTextureFromImage(irr::video::IImage * pImage);

      /**
       * @brief Deletes an texture from graphic memory.
       * @param Texture Is the texture to delete. Do not use it with ImGui::Image(..) function afterwards.
       */
      void deleteTexture(ImTextureID Texture);

      /// @}

    protected:
      /// @brief Constructor is protected to prevent an external function to create an instance of this class.
      /// @param pDevice is a pointer to the Irrlicht Device to use.
      IIMGUIDriver(irr::IrrlichtDevice * const pDevice);

      /// @brief Setups the mouse controls to fit to Irrlicht.
      void setupMouseControl(void);

      /// @brief Setups the keyboard controls to fit to Irrlicht.
      void setupKeyControl(void);

      /// @brief Deletes the font texture.
      /// @param pTextureID is the texture to delete.
      virtual void deleteFontTexture(void * pTextureID) = 0;

      /// @brief Creates a new font texture.
      /// @return Returns a handle to this new texture.
      virtual void * createFontTextureWithHandle(void) = 0;

      /**
       * @brief Creates an texture ID out of a Irrlicht image. This texture ID can be used draw images with ImGui::Image function.
       * @param pImage Is a pointer to an IImage object. After the texture has been created, the IImage object can be destroyed.
       * @return Returns an texture ID that can be used to draw images. To delete the texture from graphic memory use later deleteTexture(...)
       */
      virtual ImTextureID createTextureFromImageInternal(irr::video::IImage * pImage) = 0;

      /**
       * @brief Deletes an texture from graphic memory.
       * @param Texture Is the texture to delete. Do not use it with ImGui::Image(..) function afterwards.
       */
      virtual void deleteTextureInternal(ImTextureID Texture) = 0;


    private:
      /// @brief Updated the settings of IMGUI.
      static void updateSettings(void);

      static irr::IrrlichtDevice * mpDevice;
      static IIMGUIDriver        * mpInstance;
      static irr::u32              mInstances;
      static SIMGUISettings        mSettings;
      static void                * mpFontTexture;
      static irr::u32              mImageCount;

  };

}
}

/**
 * @}
 */

#endif /* SOURCE_IIMGUIDRIVER_H_ */
