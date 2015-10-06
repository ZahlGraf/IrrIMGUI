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
 * @file   IIMGUIHandle.h
 * @author Andre Netzeband
 * @brief  Contains a interface for a IMGUI handle.
 * @addtogroup IrrIMGUI
 */

#ifndef IRRIMGUI_INCLUDE_IRRIMGUI_IIMGUIHANDLE_H_
#define IRRIMGUI_INCLUDE_IRRIMGUI_IIMGUIHANDLE_H_

// module includes
#include "IGUITexture.h"
#include "IReferenceCounter.h"
#include "SIMGUISettings.h"

/**
 * @addtogroup IrrIMGUI
 * @{
 */
namespace IrrIMGUI
{
  /**
   * @brief A interface to an IMGUI handle. Use this interface for mocking and dependency injection of the real IMGUI handle.
   */
  class IIMGUIHandle : public IReferenceCounter
  {
    public:
      /// @brief Destructor.
      virtual ~IIMGUIHandle(void) {};

      /// @{
      /// @name Render and drawing methods

      /// @brief Call this methods before you draw the IMGUI elements and before calling "drawAll()".
      virtual void startGUI(void) = 0;

      /// @brief Call this function after "startGUI()" and after you draw your GUI elements. It will render all elements to the screen (do not call it before rendering the 3D Scene!).
      virtual void drawAll(void) = 0;

      /// @}

      /// @{
      /// @name GUI settings

      /// @return Returns a constant reference to the currently applied settings structure.
      virtual SIMGUISettings const &getSettings(void) const = 0;

      /// @param rSettings is a reference to a Setting structure that should be applied.
      /// @note  The settings are applied to all GUI handles at the same time, since IMGUI uses internally a single instance.
      virtual void setSettings(SIMGUISettings const &rSettings) = 0;

      /// @}

      /// @{
      /// @anchor LoadFonts
      /// @name Font operations

      /**
       * @brief Adds a font to the IMGUI memory.
       * @param pFontConfig Is a pointer to the font configuration.
       * @return Returns a pointer to the font for later usage with PushFont(...) to activate this font.
       */
      virtual ImFont * addFont(ImFontConfig const * pFontConfig) = 0;

      /**
       * @brief Adds the default font to the IMGUI memory.
       * @param pFontConfig Is a pointer to the font configuration.
       * @return Returns a pointer to the font for later usage with PushFont(...) to activate this font.
       */
      virtual ImFont * addDefaultFont(ImFontConfig const * pFontConfig = NULL) = 0;

      /**
       * @brief Adds a font from a TTF file to the IMGUI memory.
       * @param pFileName       Is the name of the file to add.
       * @param FontSizeInPixel Is the desired font size to use.
       * @param pFontConfig     Is a pointer to the font configuration.
       * @param pGlyphRanges    Is the Glyph-Range to select the correct character set.
       * @return Returns a pointer to the font for later usage with PushFont(...) to activate this font.
       */
      virtual ImFont * addFontFromFileTTF(char const * pFileName, float FontSizeInPixel, ImFontConfig const * pFontConfig = NULL, ImWchar const * pGlyphRanges = NULL) = 0;

      /**
       * @brief Adds a font from a TTF byte array to the IMGUI memory.
       * @param pTTFData        Is a pointer to the byte array.
       * @param TTFSize         Is the size of the array in byte.
       * @param FontSizeInPixel Is the desired font size to use.
       * @param pFontConfig     Is a pointer to the font configuration.
       * @param pGlyphRanges    Is the Glyph-Range to select the correct character set.
       * @return Returns a pointer to the font for later usage with PushFont(...) to activate this font.
       *
       * @attention This function transfers the ownership of 'pTTFData' to the IMGUI System and will be deleted automatically. Do not delete it by yourself!
       */
      virtual ImFont * addFontFromMemoryTTF(void * pTTFData, int TTFSize, float FontSizeInPixel, ImFontConfig const * pFontConfig = NULL, ImWchar const * pGlyphRanges = NULL) = 0;

      /**
       * @brief Adds a font from a compressed TTF byte array to the IMGUI memory.
       * @param pCompressedTTFData Is a pointer to the byte array.
       * @param CompressedTTFSize  Is the size of the array in byte.
       * @param FontSizeInPixel    Is the desired font size to use.
       * @param pFontConfig        Is a pointer to the font configuration.
       * @param pGlyphRanges       Is the Glyph-Range to select the correct character set.
       * @return Returns a pointer to the font for later usage with PushFont(...) to activate this font.
       *
       * @note This function does not transfer the ownership of the byte array. You are responsible for delete this memory after the font is in graphic memory.
       */
      virtual ImFont * addFontFromMemoryCompressedTTF(void const * pCompressedTTFData, int CompressedTTFSize, float FontSizeInPixel, ImFontConfig const * pFontConfig = NULL, ImWchar const * pGlyphRanges = NULL) = 0;

      /**
       * @brief Adds a font from a compressed TTF byte array that uses the base85 character encoding to the IMGUI memory.
       * @param pCompressedTTFDataBase85 Is a pointer to the char array.
       * @param FontSizeInPixel          Is the desired font size to use.
       * @param pFontConfig              Is a pointer to the font configuration.
       * @param pGlyphRanges             Is the Glyph-Range to select the correct character set.
       * @return Returns a pointer to the font for later usage with PushFont(...) to activate this font.
       *
       * @note This function does not transfer the ownership of the byte array. You are responsible for delete this memory after the font is in graphic memory.
       */
      virtual ImFont * addFontFromMemoryCompressedBase85TTF(char const * pCompressedTTFDataBase85, float FontSizeInPixel, ImFontConfig const * pFontConfig = NULL, const ImWchar * pGlyphRanges = NULL) = 0;

      /// @brief This function copies all fonts that have been added with "addFont/addDefaultFont" into graphic memory.
      /// @attention Call this function before using the fonts that have been added.
      virtual void compileFonts(void) = 0;

      /// @brief Resets the font memory and restores the default font as the one and only font in the system.
      virtual void resetFonts(void) = 0;

      /// @}


      /// @{
      /// @name Common Font Glyph-Ranges

      /// @return Returns the Basic Latin and Extended Latin Range.
      virtual ImWchar const * getGlyphRangesDefault(void) = 0;

      /// @return Returns the Default + Hiragana, Katakana, Half-Width, Selection of 1946 Ideographs
      virtual ImWchar const * getGlyphRangesJapanese(void) = 0;

      /// @return Returns the Japanese + full set of about 21000 CJK Unified Ideographs
      virtual ImWchar const * getGlyphRangesChinese(void) = 0;

      /// @return Default + about 400 Cyrillic characters
      virtual ImWchar const * getGlyphRangesCyrillic(void) = 0;

      /// @}

      /// @{
      /// @anchor CreateTextures
      /// @name Image and Texture methods

      /// @brief Creates a GUI texture object out of an Irrlicht image.
      /// @param pImage Is a pointer to an Irrlicht image object.
      /// @return Returns an GUI texture object.
      virtual IGUITexture *createTexture(irr::video::IImage * pImage) = 0;

      /// @brief Creates a GUI texture object out of an Irrlicht texture.
      /// @param pTexture Is a pointer to an Irrlicht texture object.
      /// @return Returns an GUI texture object.
      virtual IGUITexture *createTexture(irr::video::ITexture * pTexture) = 0;

      /// @brief Updates a GUI texture object with an Irrlicht image.
      /// @param pGUITexture Is a pointer to the GUI texture object.
      /// @param pImage      Is a pointer to an Irrlicht image object.
      virtual void updateTexture(IGUITexture * pGUITexture, irr::video::IImage * pImage) = 0;

      /// @brief Updates a GUI texture object with an Irrlicht texture.
      /// @param pGUITexture Is a pointer to the GUI texture object.
      /// @param pTexture    Is a pointer to an Irrlicht image object.
      virtual void updateTexture(IGUITexture * pGUITexture, irr::video::ITexture * pTexture) = 0;

      /**
       * @brief Deletes an texture from graphic memory.
       * @param pGUITexture Is a pointer to the texture to delete. Do not use it afterwards!
       */
      virtual void deleteTexture(IGUITexture * pGUITexture) = 0;

      /// @}

    protected:
      /// @{
      /// @name Constructor and Destructor

      /// @brief Forbidden Constructor.
      IIMGUIHandle(void) {};

      /// @}

  };

}
/**
 * @}
 */

#endif /* IRRIMGUI_INCLUDE_IRRIMGUI_CIMGUIHANDLE_H_ */

