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
 * @file   IIMGUIHandleMock.h
 * @author Andre Netzeband
 * @brief  Contains a CppUMock compatible mock of the IIMGUIHanlde class.
 * @addtogroup IrrIMGUIUTest
 */

#ifndef UNITTESTS_MOCKIIMGUIHANDLE_H_
#define UNITTESTS_MOCKIIMGUIHANDLE_H_

// module includes
#include <IrrIMGUI/Inject/IrrIMGUIInject.h>
#include <IrrIMGUI/IMGUIHelper.h>
#include <IrrIMGUI/CIMGUIEventStorage.h>
#include <IrrIMGUI/IIMGUIHandle.h>
#include <IrrIMGUI/UnitTest/UnitTest.h>
#include <IrrIMGUI/UnitTest/MockHelper.h>

/**
 * @addtogroup IrrIMGUIUTest
 * @{
 */

namespace IrrIMGUI
{

namespace UnitTest
{

class IIMGUIHandleMock : public IrrIMGUI::IIMGUIHandle
{
  public:
    /// @name IIMGUIHandle methods that are mocked
    /// @{

    IIMGUIHandleMock(irr::IrrlichtDevice * const pDevice, IrrIMGUI::CIMGUIEventStorage * const pEventStorage = nullptr, IrrIMGUI::SIMGUISettings const * const pSettings = nullptr):
      mpDevice(pDevice),
      mpEventStorage(pEventStorage),
      mLastTime(static_cast<irr::f32>(pDevice->getTimer()->getTime())/1000.0f)
    {
      MOCK_FUNC("IIMGUIHandleMock::IIMGUIHandleMock").MOCK_ARG(pDevice).MOCK_ARG(pEventStorage).MOCK_ARG(pSettings);

      if (areIMGUICallsEnabled())
      {
        createIMGUIDummyFont();
        ImGui::GetIO().RenderDrawListsFn = drawGUIList;
      }
      return;
    }

    virtual ~IIMGUIHandleMock(void)
    {
      MOCK_FUNC("IIMGUIHandleMock::~IIMGUIHandleMock");

      if (areIMGUICallsEnabled())
      {
        ImGui::GetIO().Fonts->Clear();
        ImGui::Shutdown();
        CHECK_EQUAL(0, ImGui::GetIO().MetricsAllocs);
      }
      return;
    };

    virtual void startGUI(void)
    {
      MOCK_FUNC("IIMGUIHandleMock::startGUI");

      if (areIMGUICallsEnabled())
      {
        updateIMGUIFrameValues(mpDevice, mpEventStorage, &mLastTime);
        ImGui::NewFrame();
      }

      return;
    }

    virtual void drawAll(void)
    {
      MOCK_FUNC("IIMGUIHandleMock::drawAll");

      if (areIMGUICallsEnabled())
      {
        ImGui::Render();
      }

      return;
    }

    virtual IrrIMGUI::SIMGUISettings const &getSettings(void) const
    {
      MOCK_FUNC("IIMGUIHandleMock::getSettings");

      IrrIMGUI::SIMGUISettings const * const pReturnSettings = static_cast<IrrIMGUI::SIMGUISettings const *>(mock().returnConstPointerValueOrDefault(reinterpret_cast<void const *>(&mDefaultSettings)));
      return *pReturnSettings;
    }

    virtual void setSettings(IrrIMGUI::SIMGUISettings const &rSettings)
    {
      MOCK_FUNC("IIMGUIHandleMock::setSettings").MOCK_ARG(&rSettings);
      mDefaultSettings = rSettings;

      return;
    }

    virtual ImFont * addFont(ImFontConfig const * pFontConfig)
    {
      MOCK_FUNC("IIMGUIHandleMock::addFont").MOCK_ARG(pFontConfig);

      return static_cast<ImFont*>(mock().returnPointerValueOrDefault(getDummyFont()));
    }

    virtual ImFont * addDefaultFont(ImFontConfig const * pFontConfig = NULL)
    {
      MOCK_FUNC("IIMGUIHandleMock::addDefaultFont").MOCK_ARG(pFontConfig);

      return static_cast<ImFont*>(mock().returnPointerValueOrDefault(getDummyFont()));
    }

    virtual ImFont * addFontFromFileTTF(char const * pFileName, float FontSizeInPixel, ImFontConfig const * pFontConfig = NULL, ImWchar const * pGlyphRanges = NULL)
    {
      MOCK_FUNC("IIMGUIHandleMock::addFontFromFileTTF").MOCK_ARG(pFileName).MOCK_ARG(FontSizeInPixel).MOCK_ARG(pFontConfig).MOCK_ARG(pGlyphRanges);

      return static_cast<ImFont*>(mock().returnPointerValueOrDefault(getDummyFont()));
    }

    virtual ImFont * addFontFromMemoryTTF(void * pTTFData, int TTFSize, float FontSizeInPixel, ImFontConfig const * pFontConfig = NULL, ImWchar const * pGlyphRanges = NULL)
    {
      MOCK_FUNC("IIMGUIHandleMock::addFontFromMemoryTTF").MOCK_ARG(pTTFData).MOCK_ARG(FontSizeInPixel).MOCK_ARG(TTFSize).MOCK_ARG(pFontConfig).MOCK_ARG(pGlyphRanges);

      return static_cast<ImFont*>(mock().returnPointerValueOrDefault(getDummyFont()));
    }

    virtual ImFont * addFontFromMemoryCompressedTTF(void const * pCompressedTTFData, int CompressedTTFSize, float FontSizeInPixel, ImFontConfig const * pFontConfig = NULL, ImWchar const * pGlyphRanges = NULL)
    {
      MOCK_FUNC("IIMGUIHandleMock::addFontFromMemoryCompressedTTF").MOCK_ARG(pCompressedTTFData).MOCK_ARG(CompressedTTFSize).MOCK_ARG(FontSizeInPixel).MOCK_ARG(pFontConfig).MOCK_ARG(pGlyphRanges);

      return static_cast<ImFont*>(mock().returnPointerValueOrDefault(getDummyFont()));
    }

    virtual ImFont * addFontFromMemoryCompressedBase85TTF(char const * pCompressedTTFDataBase85, float FontSizeInPixel, ImFontConfig const * pFontConfig = NULL, const ImWchar * pGlyphRanges = NULL)
    {
      MOCK_FUNC("IIMGUIHandleMock::addFontFromMemoryCompressedBase85TTF").MOCK_ARG(pCompressedTTFDataBase85).MOCK_ARG(FontSizeInPixel).MOCK_ARG(pFontConfig).MOCK_ARG(pGlyphRanges);

      return static_cast<ImFont*>(mock().returnPointerValueOrDefault(getDummyFont()));
    }

    virtual void compileFonts(void)
    {
      MOCK_FUNC("IIMGUIHandleMock::compileFonts");

      if (areIMGUICallsEnabled())
      {
        createIMGUIDummyFont();
      }

      return;
    }

    virtual void resetFonts(void)
    {
      MOCK_FUNC("IIMGUIHandleMock::resetFonts");

      if (areIMGUICallsEnabled())
      {
        ImGui::GetIO().Fonts->Clear();
        createIMGUIDummyFont();
      }

      return;
    }

    virtual ImWchar const * getGlyphRangesDefault(void)
    {
      MOCK_FUNC("IIMGUIHandleMock::getGlyphRangesDefault");

      ImWchar const * pGlyphRange = getGlyphRangesDummy();
      if (areIMGUICallsEnabled())
      {
        pGlyphRange = ImGui::GetIO().Fonts->GetGlyphRangesDefault();
      }

      return static_cast<ImWchar const *>(mock().returnConstPointerValueOrDefault(pGlyphRange));
    }

    virtual ImWchar const * getGlyphRangesJapanese(void)
    {
      MOCK_FUNC("IIMGUIHandleMock::getGlyphRangesJapanese");

      ImWchar const * pGlyphRange = getGlyphRangesDummy();
      if (areIMGUICallsEnabled())
      {
        pGlyphRange = ImGui::GetIO().Fonts->GetGlyphRangesJapanese();
      }

      return static_cast<ImWchar const *>(mock().returnConstPointerValueOrDefault(pGlyphRange));
    }

    virtual ImWchar const * getGlyphRangesChinese(void)
    {
      MOCK_FUNC("IIMGUIHandleMock::getGlyphRangesChinese");

      ImWchar const * pGlyphRange = getGlyphRangesDummy();
      if (areIMGUICallsEnabled())
      {
        pGlyphRange = ImGui::GetIO().Fonts->GetGlyphRangesChinese();
      }

      return static_cast<ImWchar const *>(mock().returnConstPointerValueOrDefault(pGlyphRange));
    }

    virtual ImWchar const * getGlyphRangesCyrillic(void)
    {
      MOCK_FUNC("IIMGUIHandleMock::getGlyphRangesCyrillic");

      ImWchar const * pGlyphRange = getGlyphRangesDummy();
      if (areIMGUICallsEnabled())
      {
        pGlyphRange = ImGui::GetIO().Fonts->GetGlyphRangesCyrillic();
      }

      return static_cast<ImWchar const *>(mock().returnConstPointerValueOrDefault(pGlyphRange));
    }

    virtual IrrIMGUI::IGUITexture *createTexture(irr::video::IImage * pImage)
    {
      MOCK_FUNC("IIMGUIHandleMock::createTexture").MOCK_ARG(pImage);

      return (static_cast<IrrIMGUI::IGUITexture*>(mock().returnPointerValueOrDefault(getDummyTexture())));
    }

    virtual IrrIMGUI::IGUITexture *createTexture(irr::video::ITexture * pTexture)
    {
      MOCK_FUNC("IIMGUIHandleMock::createTexture").MOCK_ARG(pTexture);

      return (static_cast<IrrIMGUI::IGUITexture*>(mock().returnPointerValueOrDefault(getDummyTexture())));
    }

    virtual void updateTexture(IrrIMGUI::IGUITexture * pGUITexture, irr::video::IImage * pImage)
    {
      MOCK_FUNC("IIMGUIHandleMock::updateTexture").MOCK_ARG(pGUITexture).MOCK_ARG(pImage);

      return;
    }

    virtual void updateTexture(IrrIMGUI::IGUITexture * pGUITexture, irr::video::ITexture * pTexture)
    {
      MOCK_FUNC("IIMGUIHandleMock::updateTexture").MOCK_ARG(pGUITexture).MOCK_ARG(pTexture);

      return;
    }

    virtual void deleteTexture(IrrIMGUI::IGUITexture * pGUITexture)
    {
      MOCK_FUNC("IIMGUIHandleMock::deleteTexture").MOCK_ARG(pGUITexture);

      return;
    }

    /// @}

    /// @name Methods to control the behavior of the Mock.
    /// @{
    static void enableMock(void)
    {
      IrrIMGUI::Inject::setIMGUIFactory(createMock);
      return;
    }

    static void disableMock(void)
    {
      IrrIMGUI::Inject::setIMGUIFactory();
      return;
    }

    static void enableIMGUICalls(bool const Enable = true)
    {
      MockHelper::mIsImGuiActivated = Enable;
      return;
    }

    static void disableIMGUICalls(void)
    {
      enableIMGUICalls(false);
      return;
    }

    static bool areIMGUICallsEnabled(void)
    {
      return MockHelper::mIsImGuiActivated;
    }

    /// @}

  private:
    /// @brief A dummy object for storing default settings.
    IrrIMGUI::SIMGUISettings             mDefaultSettings;

    /// @brief Stores the Irrlicht device pointer.
    irr::IrrlichtDevice          * const mpDevice;

    /// @brief Stores a pointer to an Event Storage.
    IrrIMGUI::CIMGUIEventStorage * const mpEventStorage;

    /// @brief Stores the last time in seconds, when an update was done.
    irr::f32                             mLastTime;

    /// @return Returns a dummy font in case of IMGUI is enabled or nullptr, when IMGUI is disabled.
    ImFont * getDummyFont(void)
    {
      ImFont * pFont = nullptr;
      if (areIMGUICallsEnabled())
      {
        pFont = ImGui::GetIO().Fonts->AddFontDefault();
      }

      return pFont;
    }

    /// @return Returns a dummy glyph range.
    ImWchar const * getGlyphRangesDummy(void)
    {
      static const ImWchar DummyRange[] =
      {
        0,
      };
      return &DummyRange[0];
    }

    /// @brief Factory method for the mock.
    static IIMGUIHandle * createMock(irr::IrrlichtDevice * const pDevice, IrrIMGUI::CIMGUIEventStorage * const pEventStorage = nullptr, IrrIMGUI::SIMGUISettings const * const pSettings = nullptr)
    {
      return new IIMGUIHandleMock(pDevice, pEventStorage, pSettings);
    }

    /// @brief Dummy draw method.
    static void drawGUIList(ImDrawData * pDrawData)
    {
      return;
    }

  };

}
}

/**
 * @}
 */

#endif /* UNITTESTS_MOCKIIMGUIHANDLE_H_ */
