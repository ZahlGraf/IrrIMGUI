/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015-2016 André Netzeband
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
 *
 */

/**
 * @file TestIIMGUIHandleMock.cpp
 * @brief Contains unit tests for the IIMGUIHandleMock.
 */

// library includes
#include <IrrIMGUI/UnitTest/UnitTest.h>
#include <IrrIMGUI/UnitTest/IIMGUIHandleMock.h>
#include <IrrIMGUI/IncludeIrrlicht.h>

using namespace IrrIMGUI;

TEST_GROUP(IIMGUIHandleMock)
{
  void setup(void)
  {
    IrrIMGUI::UnitTest::IIMGUIHandleMock::enableMock();
  }

  void teardown()
  {
    IrrIMGUI::UnitTest::IIMGUIHandleMock::disableMock();
  }
};

TEST(IIMGUIHandleMock, checkCreateAndDestory)
{
  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  CIMGUIEventStorage EventStorage;
  SIMGUISettings Settings;

  // check call to constructor
  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::IIMGUIHandleMock")
          .withParameter("pDevice",               pDevice)
          .withParameter("pEventStorage",         &EventStorage)
          .withConstPointerParameter("pSettings", &Settings);

  // check call to destructor
  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::~IIMGUIHandleMock");

  // ignore everything else (we don't want to be too rigid here)
  mock().ignoreOtherCalls();

  IIMGUIHandle * const pGUI = createIMGUI(pDevice, &EventStorage, &Settings);

  pGUI->drop();

  return;
}

TEST(IIMGUIHandleMock, checkStartGUIAndDrawAll)
{
  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);

  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::startGUI");
  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::drawAll");
  mock().ignoreOtherCalls();

  IIMGUIHandle * const pGUI = createIMGUI(pDevice);

  pGUI->startGUI();
  pGUI->drawAll();

  pGUI->drop();

  return;
}

TEST(IIMGUIHandleMock, checkSetAndGetSettings)
{
  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  SIMGUISettings Settings;
  Settings.mIsGUIMouseCursorEnabled = false;

  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::setSettings").withConstPointerParameter("&rSettings", &Settings);
  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::getSettings");
  mock().ignoreOtherCalls();

  IIMGUIHandle * const pGUI = createIMGUI(pDevice);

  pGUI->setSettings(Settings);
  SIMGUISettings ReturnSettings = pGUI->getSettings();

  CHECK(Settings == ReturnSettings);

  pGUI->drop();

  return;
}

TEST(IIMGUIHandleMock, checkFontFunctions)
{
  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  ImFontConfig FontConfig;

  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::addFont").withConstPointerParameter("pFontConfig", &FontConfig);
  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::addDefaultFont").withConstPointerParameter("pFontConfig", &FontConfig);

  char const TTFFileName[] = "TestFile.ttf";
  float const FontSizeInPixel = 12.0f;
  ImWchar const GlyphRanges[] = {0, 10};
  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::addFontFromFileTTF")
          .withParameter("pFileName", TTFFileName)
          .withParameter("FontSizeInPixel", FontSizeInPixel)
          .withConstPointerParameter("pFontConfig", &FontConfig)
          .withConstPointerParameter("pGlyphRanges", GlyphRanges);

  void * const pTTFData = reinterpret_cast<void *>(static_cast<size_t>(0x42));
  int const TTFSize = 100;
  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::addFontFromMemoryTTF")
          .withParameter("pTTFData", pTTFData)
          .withParameter("TTFSize", TTFSize)
          .withParameter("FontSizeInPixel", FontSizeInPixel)
          .withConstPointerParameter("pFontConfig", &FontConfig)
          .withConstPointerParameter("pGlyphRanges", GlyphRanges);

  void * const pCompressedTTFData = reinterpret_cast<void *>(static_cast<size_t>(0x10101010));
  int const CompressedTTFSize = 200;
  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::addFontFromMemoryCompressedTTF")
          .withConstPointerParameter("pCompressedTTFData", pCompressedTTFData)
          .withParameter("CompressedTTFSize", CompressedTTFSize)
          .withParameter("FontSizeInPixel", FontSizeInPixel)
          .withConstPointerParameter("pFontConfig", &FontConfig)
          .withConstPointerParameter("pGlyphRanges", GlyphRanges);

  char const pCompressedTTFDataBase85[]="123456789ABCDF";
  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::addFontFromMemoryCompressedBase85TTF")
          .withParameter("pCompressedTTFDataBase85", pCompressedTTFDataBase85)
          .withParameter("FontSizeInPixel", FontSizeInPixel)
          .withConstPointerParameter("pFontConfig", &FontConfig)
          .withConstPointerParameter("pGlyphRanges", GlyphRanges);

  mock().ignoreOtherCalls();

  IIMGUIHandle * const pGUI = createIMGUI(pDevice);

  ImFont * const pFont1 = pGUI->addFont(&FontConfig);
  ImFont * const pFont2 = pGUI->addDefaultFont(&FontConfig);
  ImFont * const pFont3 = pGUI->addFontFromFileTTF(TTFFileName, FontSizeInPixel, &FontConfig, GlyphRanges);
  ImFont * const pFont4 = pGUI->addFontFromMemoryTTF(pTTFData, TTFSize, FontSizeInPixel, &FontConfig, GlyphRanges);
  ImFont * const pFont5 = pGUI->addFontFromMemoryCompressedTTF(pCompressedTTFData, CompressedTTFSize, FontSizeInPixel, &FontConfig, GlyphRanges);
  ImFont * const pFont6 = pGUI->addFontFromMemoryCompressedBase85TTF(pCompressedTTFDataBase85, FontSizeInPixel, &FontConfig, GlyphRanges);

  pGUI->drop();

  return;
}

TEST(IIMGUIHandleMock, checkCompileAndResetFonts)
{
  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  SIMGUISettings Settings;
  Settings.mIsGUIMouseCursorEnabled = false;

  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::compileFonts");
  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::resetFonts");
  mock().ignoreOtherCalls();

  IIMGUIHandle * const pGUI = createIMGUI(pDevice);

  pGUI->compileFonts();
  pGUI->resetFonts();

  pGUI->drop();

  return;
}

TEST(IIMGUIHandleMock, checkGetGlyphRanges)
{
  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  SIMGUISettings Settings;
  Settings.mIsGUIMouseCursorEnabled = false;

  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::getGlyphRangesDefault");
  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::getGlyphRangesJapanese");
  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::getGlyphRangesChinese");
  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::getGlyphRangesCyrillic");
  mock().ignoreOtherCalls();

  IIMGUIHandle * const pGUI = createIMGUI(pDevice);

  ImWchar const * const pRange1 = pGUI->getGlyphRangesDefault();
  ImWchar const * const pRange2 = pGUI->getGlyphRangesJapanese();
  ImWchar const * const pRange3 = pGUI->getGlyphRangesChinese();
  ImWchar const * const pRange4 = pGUI->getGlyphRangesCyrillic();

  CHECK_EQUAL(ImGui::GetIO().Fonts->GetGlyphRangesDefault(),  pRange1);
  CHECK_EQUAL(ImGui::GetIO().Fonts->GetGlyphRangesJapanese(), pRange2);
  CHECK_EQUAL(ImGui::GetIO().Fonts->GetGlyphRangesChinese(),  pRange3);
  CHECK_EQUAL(ImGui::GetIO().Fonts->GetGlyphRangesCyrillic(), pRange4);

  pGUI->drop();

  return;
}

TEST(IIMGUIHandleMock, checkCreateTextures)
{
  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  SIMGUISettings Settings;
  Settings.mIsGUIMouseCursorEnabled = false;

  irr::video::IImage   * const pImage   = pDevice->getVideoDriver()->createImage(irr::video::ECF_A8R8G8B8, irr::core::dimension2d<irr::u32>(100, 100));
  irr::video::ITexture * const pTexture = pDevice->getVideoDriver()->addTexture("test", pImage);

  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::createTexture").withParameter("pImage", pImage);
  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::createTexture").withParameter("pTexture", pTexture);
  mock().ignoreOtherCalls();

  IIMGUIHandle * const pGUI = createIMGUI(pDevice);

  IGUITexture * const pGUITexture1 = pGUI->createTexture(pImage);
  IGUITexture * const pGUITexture2 = pGUI->createTexture(pTexture);

  pGUI->drop();

  return;
}

TEST(IIMGUIHandleMock, checkUpdateTextures)
{
  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  SIMGUISettings Settings;
  Settings.mIsGUIMouseCursorEnabled = false;

  irr::video::IImage   * const pImage   = pDevice->getVideoDriver()->createImage(irr::video::ECF_A8R8G8B8, irr::core::dimension2d<irr::u32>(100, 100));
  irr::video::ITexture * const pTexture = pDevice->getVideoDriver()->addTexture("test", pImage);

  IGUITexture * const pGUITexture1 = nullptr;
  IGUITexture * const pGUITexture2 = nullptr;

  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::updateTexture").withParameter("pGUITexture", pGUITexture2).withParameter("pImage", pImage);
  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::updateTexture").withParameter("pGUITexture", pGUITexture1).withParameter("pTexture", pTexture);
  mock().ignoreOtherCalls();

  IIMGUIHandle * const pGUI = createIMGUI(pDevice);

  pGUI->updateTexture(pGUITexture2, pImage);
  pGUI->updateTexture(pGUITexture1, pTexture);

  pGUI->drop();

  return;
}

TEST(IIMGUIHandleMock, checkDeleteTexture)
{
  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  SIMGUISettings Settings;
  Settings.mIsGUIMouseCursorEnabled = false;

  IGUITexture * const pGUITexture = nullptr;

  mock().expectOneCall("IrrIMGUI::UnitTest::IIMGUIHandleMock::deleteTexture").withParameter("pGUITexture", pGUITexture);
  mock().ignoreOtherCalls();

  IIMGUIHandle * const pGUI = createIMGUI(pDevice);

  pGUI->deleteTexture(pGUITexture);

  pGUI->drop();

  return;
}
