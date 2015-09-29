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
#include <IrrIMGUI/IrrIMGUIConfig.h>
#include <IrrIMGUI/IrrIMGUI.h>

namespace IrrIMGUI
{
/// @brief Private definitions for the IMGUI Irrlicht binding. Do not use them outside, the interface may change a lot of times!
namespace Private
{

  /// @brief The supported color formats for picture transformation and texture creating.
  enum EColorFormat
  {
    /// @brief 32bit word with Alpha at the MSB and Blue at the LSB.
    ECF_A8R8G8B8,
    /// @brief 32bit word with Red at the MSB and Blue at the LSB.
    ECF_R8G8B8A8,
    /// @brief 8bit value with Alpha only.
    ECF_A8
  };

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
      static irr::IrrlichtDevice * getIrrDevice(void);

      /// @return Returns a constant reference to the settings that are currently used.
      static SIMGUISettings const &getSettings(void);

      /// @param rSettings is a reference of the new settings to apply. The settings will applied to the global IMGUI object.
      static void setSettings(SIMGUISettings const &rSettings);

      /// @}

      /// @{
      /// @name Font methods

      /// @brief Copies the loaded Fonts into GPU memory to use them with the GUI.
      void compileFonts(void);

      /// @}

      /// @{
      /// @name Image, Texture and Font related methods

      /// @brief Creates a GUI texture object out of raw data.
      /// @param ColorFormat Is the format of the Color of every Pixel.
      /// @param pPixelData  Is a pointer to the pixel array.
      /// @param Width       Is the number of Pixels in X direction.
      /// @param Height      Is the number of Pixels in Y direction.
      /// @return Returns an GUI texture object.
      virtual IGUITexture *createTexture(EColorFormat ColorFormat, irr::u8 * pPixelData, irr::u32 Width, irr::u32 Height) = 0;

      /// @brief Creates a GUI texture object out of an Irrlicht image.
      /// @param pImage Is a pointer to an Irrlicht image object.
      /// @return Returns an GUI texture object.
      virtual IGUITexture *createTexture(irr::video::IImage * pImage) = 0;

      /// @brief Creates a GUI texture object out of an Irrlicht texture.
      /// @param pTexture Is a pointer to an Irrlicht texture object.
      /// @return Returns an GUI texture object.
      virtual IGUITexture *createTexture(irr::video::ITexture * pTexture) = 0;

      /// @brief Creates a GUI texture out of the currently loaded fonts.
      /// @return Returns an GUI texture object.
      virtual IGUITexture *createFontTexture(void) = 0;

      /// @brief Updates a GUI texture object with raw data.
      /// @param pGUITexture Is a pointer to the GUI texture object.
      /// @param ColorFormat Is the format of the Color of every Pixel.
      /// @param pPixelData  Is a pointer to the pixel array.
      /// @param Width       Is the number of Pixels in X direction.
      /// @param Height      Is the number of Pixels in Y direction.
      virtual void updateTexture(IGUITexture * pGUITexture, EColorFormat ColorFormat, irr::u8 * pPixelData, irr::u32 Width, irr::u32 Height) = 0;

      /// @brief Updates a GUI texture object with an Irrlicht image.
      /// @param pGUITexture Is a pointer to the GUI texture object.
      /// @param pImage      Is a pointer to an Irrlicht image object.
      virtual void updateTexture(IGUITexture * pGUITexture, irr::video::IImage * pImage) = 0;

      /// @brief Updates a GUI texture object with an Irrlicht texture.
      /// @param pGUITexture Is a pointer to the GUI texture object.
      /// @param pTexture    Is a pointer to an Irrlicht image object.
      virtual void updateTexture(IGUITexture * pGUITexture, irr::video::ITexture * pTexture) = 0;

      /// @brief Updates a GUI texture with the currently loaded fonts.
      /// @param pGUITexture Is a pointer to the GUI texture object.
      virtual void updateFontTexture(IGUITexture * pGUITexture) = 0;

      /**
       * @brief Deletes an texture from graphic memory.
       * @param pGUITexture Is a pointer to the texture to delete. Do not use it afterwards!
       */
      virtual void deleteTexture(IGUITexture * pGUITexture) = 0;

      /// @}

    protected:


      /// @brief Constructor is protected to prevent an external function to create an instance of this class.
      /// @param pDevice is a pointer to the Irrlicht Device to use.
      IIMGUIDriver(irr::IrrlichtDevice * const pDevice);

      /// @brief Setups the mouse controls to fit to Irrlicht.
      void setupMouseControl(void);

      /// @brief Setups the keyboard controls to fit to Irrlicht.
      void setupKeyControl(void);

      static irr::u32              mTextureInstances;

    private:
      /// @brief Updated the settings of IMGUI.
      static void updateSettings(void);

      static irr::IrrlichtDevice * mpDevice;
      static IIMGUIDriver        * mpInstance;
      static irr::u32              mInstances;
      static SIMGUISettings        mSettings;
      static IGUITexture         * mpFontTexture;

  };

}
}

/**
 * @}
 */

#endif /* SOURCE_IIMGUIDRIVER_H_ */
