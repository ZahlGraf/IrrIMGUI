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
#include <IrrIMGUI/UnitTest/UnitTest.h>
#include <IrrIMGUI/IIMGUIHandle.h>
#include <IrrIMGUI/IrrIMGUI.h>
#include <IrrIMGUI/Inject/IrrIMGUIInject.h>
#include <IrrIMGUI/IrrIMGUIConstants.h>

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

  irr::u32 const IrrDeviceRefCount = pDevice->getReferenceCount();

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

TEST(TestIMGUIHandle, checkFontMethods)
{
  ImGuiIO &rIMGUI = ImGui::GetIO();

  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  IIMGUIHandle * const pGUI = createIMGUI(pDevice);

  CHECK_EQUAL(1, rIMGUI.Fonts->Fonts.size());

  ImFontConfig FontConfig = *(rIMGUI.Fonts->Fonts[0]->ConfigData);
  FontConfig.FontDataOwnedByAtlas = false;
  irr::u8 Data[100];

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
  delete[] pData;
  pGUI->compileFonts();

  CHECK_EQUAL(5, rIMGUI.Fonts->Fonts.size());

  // TODO: We need a compressed and a base85 coded font to test the other two methods.
  //       If someone has a nice free and small font for that available, please share it...

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

// TODO: check glyph methods
// TODO: check texture creation methods
// TODO: check texture update methods
// TODO: check texture delete method
