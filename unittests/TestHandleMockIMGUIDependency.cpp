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
 * @file TestHandleMockIMGUIDependency.cpp
 * @brief Unit Tests for dependencies between IrrIMGUI Handle Mock and IMGUI library.
 */

// library includes
#include <IrrIMGUI/UnitTest/UnitTest.h>
#include <IrrIMGUI/UnitTest/IIMGUIHandleMock.h>
#include <iostream>

using namespace IrrIMGUI;

TEST_GROUP(MockIMGUIDependency)
{
  TEST_SETUP()
  {
    UnitTest::IIMGUIHandleMock::enableMock();
  }

  TEST_TEARDOWN()
  {
    UnitTest::IIMGUIHandleMock::disableMock();
  }
};

TEST(MockIMGUIDependency, checkMinimumGameLoop)
{

  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  CIMGUIEventStorage EventStorage;
  SIMGUISettings Settings;

  Settings.mIsGUIMouseCursorEnabled = true;

  // We don't want to check mock-calls, just if the mock work together with IMGUI
  mock().ignoreOtherCalls();

  irr::ITimer               * const pTimer        = pDevice->getTimer();
  CHECK_NOT_EQUAL(nullptr, pTimer);
  pTimer->setTime(0);

  IIMGUIHandle * const pGUI = createIMGUI(pDevice, &EventStorage, &Settings);

  irr::video::IVideoDriver  * const pDriver       = pDevice->getVideoDriver();
  irr::scene::ISceneManager * const pSceneManager = pDevice->getSceneManager();

  CHECK_NOT_EQUAL(nullptr, pDriver);
  CHECK_NOT_EQUAL(nullptr, pSceneManager);

  // Start main loop
  irr::u32 Frames = 0;
  irr::u32 const TimeDelta = 16;
  while(pDevice->run())
  {
    Frames++;

    // 16ms per Frame time difference
    pTimer->setTime((Frames+1)*TimeDelta);
    pDriver->beginScene(true, true, irr::video::SColor(255,100,101,140));

    pGUI->startGUI();
    ImGui::Begin("TestWindow", NULL, ImGuiWindowFlags_ShowBorders);
    ImGui::Text("Hello Earth");
    ImGui::Text("Hello Mars");
    if (ImGui::Button("Exit to Mars", ImVec2(40, 20)))
    {
      pDevice->closeDevice();
    }
    ImVec2 const ButtonPosition = ImGui::GetItemRectMin();
    ImVec2 const ButtonSize     = ImGui::GetItemRectSize();
    ImGui::End();

    pSceneManager->drawAll();
    pGUI->drawAll();

    CHECK_EQUAL_TOLERANCE(static_cast<float>(TimeDelta)/1000.0f, 0.5f, ImGui::GetIO().DeltaTime);

    pDriver->endScene();

    if ((Frames >= 100) && (Frames < 110))
    {
      // simulates a click on the Exit button
      EventStorage.mMousePositionX = ButtonPosition.x + ButtonSize.x/2.0f;
      EventStorage.mMousePositionY = ButtonPosition.y + ButtonSize.y/2.0f;
      EventStorage.mIsLeftMouseButtonPressed = true;
    }

    if (Frames >= 110)
    {
      // to finish the click, we need to release the mouse button again
      EventStorage.mIsLeftMouseButtonPressed = false;
    }

    if (Frames >= 1000)
    {
      CHECK_TEXT(false, "Exit not pressed!");
    }
  }

  pDevice->drop();
  pGUI->drop();

  return;
}

TEST(MockIMGUIDependency, checkFontGameLoop)
{

  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  CIMGUIEventStorage EventStorage;
  SIMGUISettings Settings;

  Settings.mIsGUIMouseCursorEnabled = false;

  // We don't want to check mock-calls, just if the mock work together with IMGUI
  mock().ignoreOtherCalls();

  irr::ITimer               * const pTimer        = pDevice->getTimer();
  CHECK_NOT_EQUAL(nullptr, pTimer);
  pTimer->setTime(0);

  IIMGUIHandle * const pGUI = createIMGUI(pDevice, &EventStorage, &Settings);

  irr::video::IVideoDriver  * const pDriver       = pDevice->getVideoDriver();
  irr::scene::ISceneManager * const pSceneManager = pDevice->getSceneManager();

  CHECK_NOT_EQUAL(nullptr, pDriver);
  CHECK_NOT_EQUAL(nullptr, pSceneManager);

  ImFont *pCousine16   = pGUI->addFontFromFileTTF("../../media/Cousine-Regular.ttf", 16.0f);
  ImFont *pCousine24   = pGUI->addFontFromFileTTF("../../media/Cousine-Regular.ttf", 24.0f);
  ImFont *pDroidSans16 = pGUI->addFontFromFileTTF("../../media/DroidSans.ttf",       16.0f);
  ImFont *pDroidSans24 = pGUI->addFontFromFileTTF("../../media/DroidSans.ttf",       24.0f);
  ImFont *pKarla16     = pGUI->addFontFromFileTTF("../../media/Karla-Regular.ttf",   16.0f);
  ImFont *pKarla24     = pGUI->addFontFromFileTTF("../../media/Karla-Regular.ttf",   24.0f);
  ImFont *pProggy16    = pGUI->addFontFromFileTTF("../../media/ProggyClean.ttf",     16.0f);
  ImFont *pProggy24    = pGUI->addFontFromFileTTF("../../media/ProggyClean.ttf",     24.0f);
  pGUI->compileFonts();

  // Start main loop
  irr::u32 Frames = 0;
  irr::u32 const TimeDelta = 16;
  while(pDevice->run())
  {
    // 16ms per Frame time difference
    pTimer->setTime((Frames+1)*TimeDelta);
    pDriver->beginScene(true, true, irr::video::SColor(255,100,101,140));
    pGUI->startGUI();

    ImGui::Begin("Different Fonts", NULL, ImGuiWindowFlags_ShowBorders);
    ImGui::Text("Default Font");
    ImGui::PushFont(pCousine16);
    ImGui::Text("Cousine-Regular.ttf; 16px");
    ImGui::PopFont(); // switch back to last font (in this case default)
    ImGui::PushFont(pCousine24);
    ImGui::Text("Cousine-Regular.ttf; 24px");
    ImGui::PushFont(pDroidSans16);
    ImGui::Text("DroidSans.ttf; 16px");
    ImGui::PushFont(pDroidSans24);
    ImGui::Text("DroidSans.ttf; 24px");
    ImGui::PopFont(); // switch back to last font (in this case pDroisSans16)
    ImGui::PopFont(); // switch back to last font (in this case pCousine24)
    ImGui::PopFont(); // switch back to last font (in this case default)
    ImGui::PushFont(pKarla16);
    ImGui::Text("Karla-Regular.ttf; 16px");
    ImGui::PopFont(); // switch back to last font (in this case default)
    ImGui::PushFont(pKarla24);
    ImGui::Text("Karla-Regular.ttf; 24px");
    ImGui::PopFont(); // switch back to last font (in this case default)
    ImGui::PushFont(pProggy16);
    ImGui::Text("ProggyClean.ttf; 16px");
    ImGui::PopFont(); // switch back to last font (in this case default)
    ImGui::PushFont(pProggy24);
    ImGui::Text("ProggyClean.ttf; 24px");
    ImGui::PopFont(); // switch back to last font (in this case default)
    ImGui::End();

    ImGui::Begin("TestWindow", NULL, ImGuiWindowFlags_ShowBorders);
    ImGui::Text("Hello Earth");
    ImGui::Text("Hello Mars");
    if (ImGui::Button("Exit to Mars", ImVec2(40, 20)))
    {
      pDevice->closeDevice();
    }
    ImVec2 const ButtonPosition = ImGui::GetItemRectMin();
    ImVec2 const ButtonSize     = ImGui::GetItemRectSize();
    ImGui::End();

    pSceneManager->drawAll();
    pGUI->drawAll();

    CHECK_EQUAL_TOLERANCE(static_cast<float>(TimeDelta)/1000.0f, 0.5f, ImGui::GetIO().DeltaTime);

    pDriver->endScene();

    Frames++;
    if ((Frames >= 100) && (Frames < 110))
    {
      // simulates a click on the Exit button
      EventStorage.mMousePositionX = ButtonPosition.x + ButtonSize.x/2.0f;
      EventStorage.mMousePositionY = ButtonPosition.y + ButtonSize.y/2.0f;
      EventStorage.mIsLeftMouseButtonPressed = true;
    }

    if (Frames >= 110)
    {
      // to finish the click, we need to release the mouse button again
      EventStorage.mIsLeftMouseButtonPressed = false;
    }

    if (Frames >= 1000)
    {
      CHECK_TEXT(false, "Exit not pressed!");
    }
  }

  pDevice->drop();
  pGUI->drop();

  return;
}

TEST(MockIMGUIDependency, checkResetFontGameLoop)
{

  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  CIMGUIEventStorage EventStorage;
  SIMGUISettings Settings;

  Settings.mIsGUIMouseCursorEnabled = false;

  // We don't want to check mock-calls, just if the mock work together with IMGUI
  mock().ignoreOtherCalls();

  irr::ITimer               * const pTimer        = pDevice->getTimer();
  CHECK_NOT_EQUAL(nullptr, pTimer);
  pTimer->setTime(0);

  IIMGUIHandle * const pGUI = createIMGUI(pDevice, &EventStorage, &Settings);
  pGUI->compileFonts();

  irr::video::IVideoDriver  * const pDriver       = pDevice->getVideoDriver();
  irr::scene::ISceneManager * const pSceneManager = pDevice->getSceneManager();

  CHECK_NOT_EQUAL(nullptr, pDriver);
  CHECK_NOT_EQUAL(nullptr, pSceneManager);

  ImFont *pCousine16   = pGUI->addFontFromFileTTF("../../media/Cousine-Regular.ttf", 16.0f);
  ImFont *pProggy24    = pGUI->addFontFromFileTTF("../../media/ProggyClean.ttf",     24.0f);
  pGUI->compileFonts();

  // Start main loop
  irr::u32 Frames = 0;
  irr::u32 const TimeDelta = 16;
  while(pDevice->run())
  {
    // 16ms per Frame time difference
    pTimer->setTime((Frames+1)*TimeDelta);
    pDriver->beginScene(true, true, irr::video::SColor(255,100,101,140));
    pGUI->startGUI();

    ImGui::Begin("Different Fonts", NULL, ImGuiWindowFlags_ShowBorders);
    if (pCousine16)
    {
      ImGui::PushFont(pCousine16);
    }
    ImGui::Text("ProggyClean.ttf; 24px");
    if (pCousine16)
    {
      ImGui::PopFont(); // switch back to last font (in this case default)
    }
    ImGui::End();

    ImGui::Begin("TestWindow", NULL, ImGuiWindowFlags_ShowBorders);
    ImGui::Text("Hello Earth");
    ImGui::Text("Hello Mars");
    if (ImGui::Button("Exit to Mars", ImVec2(40, 20)))
    {
      pDevice->closeDevice();
    }
    ImVec2 const ButtonPosition = ImGui::GetItemRectMin();
    ImVec2 const ButtonSize     = ImGui::GetItemRectSize();
    ImGui::End();

    pSceneManager->drawAll();
    pGUI->drawAll();

    CHECK_EQUAL_TOLERANCE(static_cast<float>(TimeDelta)/1000.0f, 0.5f, ImGui::GetIO().DeltaTime);

    pDriver->endScene();

    Frames++;
    if (Frames == 50)
    {
      pGUI->resetFonts();
      pCousine16 = nullptr;
    }

    if ((Frames >= 100) && (Frames < 110))
    {
      // simulates a click on the Exit button
      EventStorage.mMousePositionX = ButtonPosition.x + ButtonSize.x/2.0f;
      EventStorage.mMousePositionY = ButtonPosition.y + ButtonSize.y/2.0f;
      EventStorage.mIsLeftMouseButtonPressed = true;
    }

    if (Frames >= 110)
    {
      // to finish the click, we need to release the mouse button again
      EventStorage.mIsLeftMouseButtonPressed = false;
    }

    if (Frames >= 1000)
    {
      CHECK_TEXT(false, "Exit not pressed!");
    }
  }

  pDevice->drop();
  pGUI->drop();

  return;
}

TEST(MockIMGUIDependency, checkImageFontGameLoop)
{

  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  CIMGUIEventStorage EventStorage;
  SIMGUISettings Settings;

  Settings.mIsGUIMouseCursorEnabled = true;

  // We don't want to check mock-calls, just if the mock work together with IMGUI
  mock().ignoreOtherCalls();

  irr::ITimer               * const pTimer        = pDevice->getTimer();
  CHECK_NOT_EQUAL(nullptr, pTimer);
  pTimer->setTime(0);

  IIMGUIHandle * const pGUI = createIMGUI(pDevice, &EventStorage, &Settings);
  pGUI->compileFonts();

  irr::video::IVideoDriver  * const pDriver       = pDevice->getVideoDriver();
  irr::scene::ISceneManager * const pSceneManager = pDevice->getSceneManager();

  CHECK_NOT_EQUAL(nullptr, pDriver);
  CHECK_NOT_EQUAL(nullptr, pSceneManager);

  irr::video::IImage * pSoyuz  = pDriver->createImage(irr::video::ECF_A8R8G8B8, irr::core::dimension2d<irr::u32>(100, 100));
  irr::video::IImage * pSpaceX = pDriver->createImage(irr::video::ECF_A8R8G8B8, irr::core::dimension2d<irr::u32>(100, 100));

  IGUITexture &rSoyuz  = *pGUI->createTexture(pSoyuz);
  IGUITexture &rSpaceX = *pGUI->createTexture(pSpaceX);

  // Start main loop
  irr::u32 Frames = 0;
  irr::u32 const TimeDelta = 16;
  while(pDevice->run())
  {
    // 16ms per Frame time difference
    pTimer->setTime((Frames+1)*TimeDelta);
    pDriver->beginScene(true, true, irr::video::SColor(255,100,101,140));
    pGUI->startGUI();

    ImGui::Begin("Images", NULL, ImGuiWindowFlags_ShowBorders);
    ImGui::Image(rSoyuz, ImVec2(100.0f, 100.0f));
    ImGui::Image(rSpaceX, ImVec2(200.0f, 200.0f));
    ImGui::End();

    ImGui::Begin("TestWindow", NULL, ImGuiWindowFlags_ShowBorders);
    ImGui::Text("Hello Earth");
    ImGui::Text("Hello Mars");
    if (ImGui::Button("Exit to Mars", ImVec2(40, 20)))
    {
      pDevice->closeDevice();
    }
    ImVec2 const ButtonPosition = ImGui::GetItemRectMin();
    ImVec2 const ButtonSize     = ImGui::GetItemRectSize();
    ImGui::End();

    pSceneManager->drawAll();
    pGUI->drawAll();

    CHECK_EQUAL_TOLERANCE(static_cast<float>(TimeDelta)/1000.0f, 0.5f, ImGui::GetIO().DeltaTime);

    pDriver->endScene();

    Frames++;
    if ((Frames >= 100) && (Frames < 110))
    {
      // simulates a click on the Exit button
      EventStorage.mMousePositionX = ButtonPosition.x + ButtonSize.x/2.0f;
      EventStorage.mMousePositionY = ButtonPosition.y + ButtonSize.y/2.0f;
      EventStorage.mIsLeftMouseButtonPressed = true;
    }

    if (Frames >= 110)
    {
      // to finish the click, we need to release the mouse button again
      EventStorage.mIsLeftMouseButtonPressed = false;
    }

    if (Frames >= 1000)
    {
      CHECK_TEXT(false, "Exit not pressed!");
    }
  }

  pDevice->drop();
  pGUI->drop();

  return;
}


