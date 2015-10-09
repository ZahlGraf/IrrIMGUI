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
 * @file   IIMGUIHandleMock.cpp
 * @author Andre Netzeband
 * @brief  Contains a CppUMock compatible mock of the IIMGUIHanlde class.
 * @addtogroup IrrIMGUIUTest
 */

#ifndef UNITTESTS_MOCKIIMGUIHANDLE_H_
#define UNITTESTS_MOCKIIMGUIHANDLE_H_

// library includes
#include <IrrIMGUI/UnitTest/UnitTest.h>
#include <IrrIMGUI/CIMGUIEventStorage.h>
#include <IrrIMGUI/IIMGUIHandle.h>

// module includes
#include <IrrIMGUI/Inject/IrrIMGUIInject.h>

/*
 * @addtogroup IrrIMGUIUTest
 *
 * @{
 */

namespace IrrIMGUI
{

/// @brief Contains test related definitions
namespace UnitTest
{

class IIMGUIHandleMock : public IrrIMGUI::IIMGUIHandle
{
  public:
    IIMGUIHandleMock(irr::IrrlichtDevice * const pDevice, IrrIMGUI::CIMGUIEventStorage * const pEventStorage = nullptr, IrrIMGUI::SIMGUISettings const * const pSettings = nullptr)
    {
      MOCK_FUNC().MOCK_ARG(pDevice).MOCK_ARG(pEventStorage).MOCK_ARG(pSettings);
      return;
    }

    virtual ~IIMGUIHandleMock(void)
    {
      MOCK_FUNC();
      return;
    };

    virtual void startGUI(void)
    {
      MOCK_FUNC();
      return;
    }

    virtual void drawAll(void)
    {
      MOCK_FUNC();
      return;
    }

    virtual IrrIMGUI::SIMGUISettings const &getSettings(void) const
    {
      MOCK_FUNC();

      IrrIMGUI::SIMGUISettings const * const pReturnSettings = static_cast<IrrIMGUI::SIMGUISettings const *>(mock().returnConstPointerValueOrDefault(reinterpret_cast<void const *>(&mDefaultSettings)));
      return *pReturnSettings;
    }

    virtual void setSettings(IrrIMGUI::SIMGUISettings const &rSettings)
    {
      MOCK_FUNC().MOCK_ARG(&rSettings);
      mDefaultSettings = rSettings;

      return;
    }

    virtual ImFont * addFont(ImFontConfig const * pFontConfig)
    {
      MOCK_FUNC().MOCK_ARG(pFontConfig);

      return static_cast<ImFont*>(mock().returnPointerValueOrDefault(ImGui::GetIO().Fonts->AddFontDefault()));
    }

    virtual ImFont * addDefaultFont(ImFontConfig const * pFontConfig = NULL)
    {
      MOCK_FUNC().MOCK_ARG(pFontConfig);

      return static_cast<ImFont*>(mock().returnPointerValueOrDefault(ImGui::GetIO().Fonts->AddFontDefault()));
    }

    virtual ImFont * addFontFromFileTTF(char const * pFileName, float FontSizeInPixel, ImFontConfig const * pFontConfig = NULL, ImWchar const * pGlyphRanges = NULL)
    {
      MOCK_FUNC().MOCK_ARG(pFileName).MOCK_ARG(FontSizeInPixel).MOCK_ARG(pFontConfig).MOCK_ARG(pGlyphRanges);

      return static_cast<ImFont*>(mock().returnPointerValueOrDefault(ImGui::GetIO().Fonts->AddFontDefault()));
    }

    virtual ImFont * addFontFromMemoryTTF(void * pTTFData, int TTFSize, float FontSizeInPixel, ImFontConfig const * pFontConfig = NULL, ImWchar const * pGlyphRanges = NULL)
    {
      MOCK_FUNC().MOCK_ARG(pTTFData).MOCK_ARG(FontSizeInPixel).MOCK_ARG(TTFSize).MOCK_ARG(pFontConfig).MOCK_ARG(pGlyphRanges);

      return static_cast<ImFont*>(mock().returnPointerValueOrDefault(ImGui::GetIO().Fonts->AddFontDefault()));
    }

    virtual ImFont * addFontFromMemoryCompressedTTF(void const * pCompressedTTFData, int CompressedTTFSize, float FontSizeInPixel, ImFontConfig const * pFontConfig = NULL, ImWchar const * pGlyphRanges = NULL)
    {
      MOCK_FUNC().MOCK_ARG(pCompressedTTFData).MOCK_ARG(CompressedTTFSize).MOCK_ARG(FontSizeInPixel).MOCK_ARG(pFontConfig).MOCK_ARG(pGlyphRanges);

      return static_cast<ImFont*>(mock().returnPointerValueOrDefault(ImGui::GetIO().Fonts->AddFontDefault()));
    }

    virtual ImFont * addFontFromMemoryCompressedBase85TTF(char const * pCompressedTTFDataBase85, float FontSizeInPixel, ImFontConfig const * pFontConfig = NULL, const ImWchar * pGlyphRanges = NULL)
    {
      MOCK_FUNC().MOCK_ARG(pCompressedTTFDataBase85).MOCK_ARG(FontSizeInPixel).MOCK_ARG(pFontConfig).MOCK_ARG(pGlyphRanges);

      return static_cast<ImFont*>(mock().returnPointerValueOrDefault(ImGui::GetIO().Fonts->AddFontDefault()));
    }

    virtual void compileFonts(void)
    {
      MOCK_FUNC();

      return;
    }

    virtual void resetFonts(void)
    {
      MOCK_FUNC();

      return;
    }

    virtual ImWchar const * getGlyphRangesDefault(void)
    {
      return static_cast<ImWchar const *>(MOCK_FUNC().returnConstPointerValueOrDefault(ImGui::GetIO().Fonts->GetGlyphRangesDefault()));
    }

    virtual ImWchar const * getGlyphRangesJapanese(void)
    {
      return static_cast<ImWchar const *>(MOCK_FUNC().returnConstPointerValueOrDefault(ImGui::GetIO().Fonts->GetGlyphRangesJapanese()));
    }

    virtual ImWchar const * getGlyphRangesChinese(void)
    {
      return static_cast<ImWchar const *>(MOCK_FUNC().returnConstPointerValueOrDefault(ImGui::GetIO().Fonts->GetGlyphRangesChinese()));
    }

    virtual ImWchar const * getGlyphRangesCyrillic(void)
    {
      return static_cast<ImWchar const *>(MOCK_FUNC().returnConstPointerValueOrDefault(ImGui::GetIO().Fonts->GetGlyphRangesCyrillic()));
    }

    virtual IrrIMGUI::IGUITexture *createTexture(irr::video::IImage * pImage)
    {
      MOCK_FUNC().MOCK_ARG(pImage);

      return (static_cast<IrrIMGUI::IGUITexture*>(mock().returnPointerValueOrDefault(nullptr)));
    }

    virtual IrrIMGUI::IGUITexture *createTexture(irr::video::ITexture * pTexture)
    {
      MOCK_FUNC().MOCK_ARG(pTexture);

      return (static_cast<IrrIMGUI::IGUITexture*>(mock().returnPointerValueOrDefault(nullptr)));
    }

    virtual void updateTexture(IrrIMGUI::IGUITexture * pGUITexture, irr::video::IImage * pImage)
    {
      MOCK_FUNC().MOCK_ARG(pGUITexture).MOCK_ARG(pImage);

      return;
    }

    virtual void updateTexture(IrrIMGUI::IGUITexture * pGUITexture, irr::video::ITexture * pTexture)
    {
      MOCK_FUNC().MOCK_ARG(pGUITexture).MOCK_ARG(pTexture);

      return;
    }

    virtual void deleteTexture(IrrIMGUI::IGUITexture * pGUITexture)
    {
      MOCK_FUNC().MOCK_ARG(pGUITexture);

      return;
    }

    static IIMGUIHandle * createMock(irr::IrrlichtDevice * const pDevice, IrrIMGUI::CIMGUIEventStorage * const pEventStorage = nullptr, IrrIMGUI::SIMGUISettings const * const pSettings = nullptr)
    {
      return new IIMGUIHandleMock(pDevice, pEventStorage, pSettings);
    }

    static void enableMock(void)
    {
      IrrIMGUI::Inject::setIMGUIFactory(createMock);
      return;
    }

    static void disableMock(void)
    {
      IrrIMGUI::Inject::setIMGUIFactory(IrrIMGUI::createIMGUI);
      return;
    }

  private:
    IrrIMGUI::SIMGUISettings mDefaultSettings;
};

}
}

/**
 * @}
 */

#endif /* UNITTESTS_MOCKIIMGUIHANDLE_H_ */
