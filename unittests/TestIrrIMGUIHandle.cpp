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
 * @file TestIrrIMGUIHandle.cpp
 * @brief Contains unit tests the handle object.
 */

// library includes
#include <typeinfo>
#include <iostream>
#define STB_DEFINE
#include "stb_compress_only.h"
#include <IrrIMGUI/UnitTest/UnitTest.h>
#include <IrrIMGUI/IIMGUIHandle.h>
#include <IrrIMGUI/IrrIMGUI.h>
#include <IrrIMGUI/Inject/IrrIMGUIInject.h>
#include <IrrIMGUI/IrrIMGUIConstants.h>
#include <IrrIMGUIDebug_priv.h>
#include <CGUITexture.h>

using namespace IrrIMGUI;

TEST_GROUP(TestIMGUIHandle)
{
  TEST_SETUP()
  {
  }

  TEST_TEARDOWN()
  {
  }
};

TEST(TestIMGUIHandle, checkIfHandleGrabsAndDropsIrrlicht)
{
  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);

  irr::s32 const IrrDeviceRefCount = pDevice->getReferenceCount();

  IIMGUIHandle * const pGUI = createIMGUI(pDevice);

  CHECK(pDevice->getReferenceCount() > IrrDeviceRefCount);

  pGUI->drop();

  CHECK_EQUAL(IrrDeviceRefCount, pDevice->getReferenceCount());

  pDevice->drop();

  return;
}

TEST(TestIMGUIHandle, checkIfHandleSetupsIMGUIMouse)
{
  ImGuiIO &rIMGUI = ImGui::GetIO();

  for (int i = 0; i < Const::NumberOfMouseButtons; i++)
  {
    rIMGUI.MouseClicked[i]          = true;
    rIMGUI.MouseDoubleClicked[i]    = true;
    rIMGUI.MouseDown[i]             = true;
    rIMGUI.MouseClickedTime[i]      = 42.0f;
    rIMGUI.MouseDownDurationPrev[i] = 52.0f;
    rIMGUI.MouseDownDuration[i]     = 62.0f;
  }

  rIMGUI.MouseWheel = 2.0f;

  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  IIMGUIHandle * const pGUI = createIMGUI(pDevice);

  for (int i = 0; i < Const::NumberOfMouseButtons; i++)
  {
    CHECK_EQUAL(false,    rIMGUI.MouseClicked[i]);
    CHECK_EQUAL(false,    rIMGUI.MouseDoubleClicked[i]);
    CHECK_EQUAL(false,    rIMGUI.MouseDown[i]);
    CHECK_EQUAL(-FLT_MAX, rIMGUI.MouseClickedTime[i]);
    CHECK_EQUAL(-1.0f,    rIMGUI.MouseDownDurationPrev[i]);
    CHECK_EQUAL(-1.0f,    rIMGUI.MouseDownDuration[i]);
  }

  CHECK_EQUAL(0.0f, rIMGUI.MouseWheel);

  pGUI->drop();
  pDevice->drop();

  return;
}

TEST(TestIMGUIHandle, checkIfHandleSetupsFonts)
{
  ImGuiIO &rIMGUI = ImGui::GetIO();

  rIMGUI.Fonts->Clear();
  rIMGUI.Fonts->TexID = nullptr;

  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  IIMGUIHandle * const pGUI = createIMGUI(pDevice);

  CHECK_NOT_EQUAL(nullptr, rIMGUI.Fonts->TexID);
  CHECK_EQUAL(1,           rIMGUI.Fonts->Fonts.size());

  pGUI->drop();
  pDevice->drop();

  CHECK_EQUAL(0,    rIMGUI.Fonts->Fonts.size());

  return;
}

TEST(TestIMGUIHandle, checkIfHandleSetupsFunctionPointer)
{
  ImGuiIO &rIMGUI = ImGui::GetIO();

  rIMGUI.RenderDrawListsFn = nullptr;

  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  IIMGUIHandle * const pGUI = createIMGUI(pDevice);

  CHECK_NOT_EQUAL(nullptr, rIMGUI.RenderDrawListsFn);

  pGUI->drop();
  pDevice->drop();

  return;
}

TEST(TestIMGUIHandle, checkFrameUpdate)
{
  ImGuiIO &rIMGUI = ImGui::GetIO();

  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);

  pDevice->getTimer()->setTime(0);

  IIMGUIHandle * const pGUI = createIMGUI(pDevice);

  rIMGUI.DeltaTime = 0.0f;
  rIMGUI.DisplaySize = ImVec2(0.0f, 0.0f);
  int const LastFrame = ImGui::GetFrameCount();

  pDevice->getTimer()->setTime(16);

  pGUI->startGUI();

  CHECK_NOT_EQUAL(0.0f,    rIMGUI.DisplaySize.x);
  CHECK_NOT_EQUAL(0.0f,    rIMGUI.DisplaySize.y);
  CHECK_EQUAL_TOLERANCE(0.016f, 0.001f, ImGui::GetTime());
  CHECK_EQUAL(LastFrame+1, ImGui::GetFrameCount());

  pGUI->drawAll();

  pDevice->getTimer()->setTime(32);

  pGUI->startGUI();

  CHECK_NOT_EQUAL(0.0f,    rIMGUI.DisplaySize.x);
  CHECK_NOT_EQUAL(0.0f,    rIMGUI.DisplaySize.y);
  CHECK_EQUAL_TOLERANCE(0.032f, 0.001f, ImGui::GetTime());
  CHECK_EQUAL(LastFrame+2, ImGui::GetFrameCount());

  pGUI->drawAll();

  pGUI->drop();
  pDevice->drop();

  return;
}

static int ArgumentTest = 42;
void checkDrawCommand(ImDrawList const * const pParentList, ImDrawCmd const * const pCmd)
{
  MOCK_FUNC().withConstPointerParameter("pParentList", pParentList).withConstPointerParameter("pCmd", pCmd);

  POINTERS_EQUAL(&ArgumentTest, pCmd->UserCallbackData);

  return;
}

TEST(TestIMGUIHandle, checkDrawCallback)
{
  ImGuiIO &rIMGUI = ImGui::GetIO();

  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  IIMGUIHandle * const pGUI = createIMGUI(pDevice);

  pGUI->startGUI();

  ImGui::Begin("CallbackTest");
  ImGui::GetWindowDrawList()->AddCallback(checkDrawCommand, static_cast<void *>(&ArgumentTest));
  ImGui::End();

  mock().expectOneCall("checkDrawCommand").ignoreOtherParameters();
  mock().ignoreOtherCalls();

  pGUI->drawAll();

  pGUI->drop();
  pDevice->drop();

  return;
}


/**
 * The following three functions for Base85 encoding are mostly copied from:
 * https://github.com/ocornut/imgui/blob/master/extra_fonts/binary_to_compressed_c.cpp
 *
 * This file is part of the IMGUI project from Omar Cornut (https://github.com/ocornut/imgui)
 * Thus the implementation of "getEncodedBase85Size", "encodeBase85Byte", "encodeBase85" belongs
 * to the same license like the implementation in the original file!
 *
 */
size_t getEncodedBase85Size(size_t const InputDataLength)
{
  return ((InputDataLength+3)/4)*(5)+1;
}

irr::u8 encodeBase85Byte(irr::u32 const Data32Bit)
{
  irr::u32 Data = (Data32Bit % 85) + 35;
  Data = (Data >= '\\') ? Data + 1 : Data;

  // must fit in 8 bit
  FASSERT(Data <= 255);

  return Data;
}

void encodeBase85(irr::u8 * const pOutputData, irr::u8 * const pInputData, size_t const InputDataLength)
{
  size_t OutputIndex = 0;
  for(size_t i = 0; i < InputDataLength; i += 4)
  {
    irr::u32 const Data32Bit = *(reinterpret_cast<irr::u32 *>(&pInputData[i]));

    pOutputData[OutputIndex] = encodeBase85Byte(Data32Bit);
    OutputIndex++;
    pOutputData[OutputIndex] = encodeBase85Byte(Data32Bit/(85));
    OutputIndex++;
    pOutputData[OutputIndex] = encodeBase85Byte(Data32Bit/(85*85));
    OutputIndex++;
    pOutputData[OutputIndex] = encodeBase85Byte(Data32Bit/(85*85*85));
    OutputIndex++;
    pOutputData[OutputIndex] = encodeBase85Byte(Data32Bit/(85*85*85*85));
    OutputIndex++;
  }

  return;
}

TEST(TestIMGUIHandle, checkFontMethods)
{
  ImGuiIO &rIMGUI = ImGui::GetIO();

  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  IIMGUIHandle * const pGUI = createIMGUI(pDevice);

  CHECK_EQUAL(1, rIMGUI.Fonts->Fonts.size());

  ImFontConfig FontConfig = *(rIMGUI.Fonts->Fonts[0]->ConfigData);
  FontConfig.FontDataOwnedByAtlas = false;

  // test new font with reused data from default font
  pGUI->addFont(&FontConfig);
  pGUI->compileFonts();

  CHECK_EQUAL(2, rIMGUI.Fonts->Fonts.size());

  // test default font creation
  pGUI->addDefaultFont();
  pGUI->compileFonts();

  CHECK_EQUAL(3, rIMGUI.Fonts->Fonts.size());

  // test loading from ttf file
  pGUI->addFontFromFileTTF("../../media/DroidSans.ttf", 16.0f);
  pGUI->compileFonts();

  CHECK_EQUAL(4, rIMGUI.Fonts->Fonts.size());

  // test loading ttf file from memory (by reusing the default font data again)
  irr::u8 * const pData = new irr::u8[FontConfig.FontDataSize];
  for (int i = 0; i < FontConfig.FontDataSize; i++)
  {
    pData[i] = (static_cast<irr::u8*>(FontConfig.FontData))[i];
  }
  FontConfig.FontDataOwnedByAtlas = false;
  FontConfig.FontData = nullptr;
  pGUI->addFontFromMemoryTTF(pData, FontConfig.FontDataSize, FontConfig.SizePixels, &FontConfig);
  pGUI->compileFonts();

  CHECK_EQUAL(5, rIMGUI.Fonts->Fonts.size());

  size_t const Length = FontConfig.FontDataSize;
  size_t const MaxLength = stb_get_compression_length(Length);
  irr::u8 * const pCompressedData = new irr::u8[MaxLength];
  size_t const CompressedLength = stb_compress((stb_uchar*)pCompressedData, (stb_uchar*)pData, Length);
  pGUI->addFontFromMemoryCompressedTTF(pCompressedData, CompressedLength, FontConfig.SizePixels);

  CHECK_EQUAL(6, rIMGUI.Fonts->Fonts.size());

  irr::u8 * const pEncodedData = new irr::u8[getEncodedBase85Size(CompressedLength)];
  encodeBase85(pEncodedData, pCompressedData, CompressedLength);
  pGUI->addFontFromMemoryCompressedBase85TTF((char*)pEncodedData, FontConfig.SizePixels);

  CHECK_EQUAL(7, rIMGUI.Fonts->Fonts.size());

  delete[] pData;
  delete[] pCompressedData;
  delete[] pEncodedData;

  // reset all fonts to default
  pGUI->resetFonts();

  CHECK_EQUAL(1, rIMGUI.Fonts->Fonts.size());

  // also another compile (without another addFont...) must not change the number of stored fonts
  pGUI->compileFonts();

  CHECK_EQUAL(1, rIMGUI.Fonts->Fonts.size());

  pGUI->drop();
  pDevice->drop();

  return;
}

TEST(TestIMGUIHandle, checkGlyphMethods)
{
  ImGuiIO &rIMGUI = ImGui::GetIO();

  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  IIMGUIHandle * const pGUI = createIMGUI(pDevice);

  CHECK_EQUAL(rIMGUI.Fonts->GetGlyphRangesChinese(),  pGUI->getGlyphRangesChinese());
  CHECK_EQUAL(rIMGUI.Fonts->GetGlyphRangesCyrillic(), pGUI->getGlyphRangesCyrillic());
  CHECK_EQUAL(rIMGUI.Fonts->GetGlyphRangesDefault(),  pGUI->getGlyphRangesDefault());
  CHECK_EQUAL(rIMGUI.Fonts->GetGlyphRangesJapanese(), pGUI->getGlyphRangesJapanese());

  pGUI->drop();
  pDevice->drop();
}

TEST(TestIMGUIHandle, checkImageTextureCreation)
{
  ImGuiIO &rIMGUI = ImGui::GetIO();

  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  IIMGUIHandle * const pGUI = createIMGUI(pDevice);

  irr::video::IImage * const pImage1 = pDevice->getVideoDriver()->createImage(irr::video::ECF_A8R8G8B8, irr::core::dimension2du(100, 100));
  irr::video::IImage * const pImage2 = pDevice->getVideoDriver()->createImage(irr::video::ECF_A8R8G8B8, irr::core::dimension2du(200, 200));
  IGUITexture * const pGUITexture = pGUI->createTexture(pImage1);

  CHECK_NOT_EQUAL(nullptr, pGUITexture);
  STRCMP_EQUAL("class IrrIMGUI::Private::CGUITexture", typeid(*pGUITexture).name());

  Private::CGUITexture * const pRealGUITexture = dynamic_cast<IrrIMGUI::Private::CGUITexture*>(pGUITexture);

  CHECK_EQUAL(true,                pRealGUITexture->mIsValid);
  CHECK_EQUAL(Private::ETST_IMAGE, pRealGUITexture->mSourceType);
  CHECK_EQUAL(pImage1,             pRealGUITexture->mSource.ImageID);
  CHECK_NOT_EQUAL(NULL,            pRealGUITexture->mGPUTextureID);

  pGUI->updateTexture(pGUITexture, pImage2);

  CHECK_EQUAL(true,                pRealGUITexture->mIsValid);
  CHECK_EQUAL(Private::ETST_IMAGE, pRealGUITexture->mSourceType);
  CHECK_EQUAL(pImage2,             pRealGUITexture->mSource.ImageID);
  CHECK_NOT_EQUAL(NULL,            pRealGUITexture->mGPUTextureID);

  irr::video::ITexture * const pIrrTexture = pDevice->getVideoDriver()->addTexture("test1", pImage1);
  pGUI->updateTexture(pGUITexture, pIrrTexture);

  CHECK_EQUAL(true,                  pRealGUITexture->mIsValid);
  CHECK_EQUAL(Private::ETST_TEXTURE, pRealGUITexture->mSourceType);
  CHECK_EQUAL(pIrrTexture,           pRealGUITexture->mSource.TextureID);
  CHECK_NOT_EQUAL(NULL,              pRealGUITexture->mGPUTextureID);

  pGUI->deleteTexture(pGUITexture);

  pImage1->drop();
  pImage2->drop();
  pGUI->drop();
  pDevice->drop();
}

TEST(TestIMGUIHandle, checkTextureTextureCreation)
{
  ImGuiIO &rIMGUI = ImGui::GetIO();

  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  IIMGUIHandle * const pGUI = createIMGUI(pDevice);

  irr::video::IImage * const pImage1 = pDevice->getVideoDriver()->createImage(irr::video::ECF_A8R8G8B8, irr::core::dimension2du(100, 100));
  irr::video::IImage * const pImage2 = pDevice->getVideoDriver()->createImage(irr::video::ECF_A8R8G8B8, irr::core::dimension2du(200, 200));

  irr::video::ITexture * const pIrrTexture1 = pDevice->getVideoDriver()->addTexture("test1", pImage1);
  irr::video::ITexture * const pIrrTexture2 = pDevice->getVideoDriver()->addTexture("test2", pImage2);

  IGUITexture * const pGUITexture = pGUI->createTexture(pIrrTexture1);

  CHECK_NOT_EQUAL(nullptr, pGUITexture);
  STRCMP_EQUAL("class IrrIMGUI::Private::CGUITexture", typeid(*pGUITexture).name());

  Private::CGUITexture * const pRealGUITexture = dynamic_cast<IrrIMGUI::Private::CGUITexture*>(pGUITexture);

  CHECK_EQUAL(true,                  pRealGUITexture->mIsValid);
  CHECK_EQUAL(Private::ETST_TEXTURE, pRealGUITexture->mSourceType);
  CHECK_EQUAL(pIrrTexture1,          pRealGUITexture->mSource.TextureID);
  CHECK_NOT_EQUAL(NULL,              pRealGUITexture->mGPUTextureID);

  pGUI->updateTexture(pGUITexture, pIrrTexture2);

  CHECK_EQUAL(true,                  pRealGUITexture->mIsValid);
  CHECK_EQUAL(Private::ETST_TEXTURE, pRealGUITexture->mSourceType);
  CHECK_EQUAL(pIrrTexture2,          pRealGUITexture->mSource.TextureID);
  CHECK_NOT_EQUAL(NULL,              pRealGUITexture->mGPUTextureID);

  pGUI->updateTexture(pGUITexture, pImage1);

  CHECK_EQUAL(true,                pRealGUITexture->mIsValid);
  CHECK_EQUAL(Private::ETST_IMAGE, pRealGUITexture->mSourceType);
  CHECK_EQUAL(pImage1,             pRealGUITexture->mSource.ImageID);
  CHECK_NOT_EQUAL(NULL,            pRealGUITexture->mGPUTextureID);

  pGUI->deleteTexture(pGUITexture);

  pImage1->drop();
  pImage2->drop();
  pGUI->drop();
  pDevice->drop();
}
