/* The MIT License (MIT)
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
 * @file TestSettings.cpp
 * @brief Contains unit tests to check if settings are applied correctly.
 */

// library includes
#include <IrrIMGUI/UnitTest/UnitTest.h>
#include <IrrIMGUI/IIMGUIHandle.h>
#include <IrrIMGUI/IrrIMGUI.h>

using namespace IrrIMGUI;

TEST_GROUP(TestIMGUISettings)
{
  TEST_SETUP()
  {
  }

  TEST_TEARDOWN()
  {
  }
};

TEST(TestIMGUISettings, checkIfMouseCursorEnableIsApplied)
{
  ImGuiIO &rIMGUI = ImGui::GetIO();

  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  SIMGUISettings Settings;

  {
    Settings.mIsGUIMouseCursorEnabled = false;

    IIMGUIHandle * const pGUI = createIMGUI(pDevice, nullptr, &Settings);

    CHECK_EQUAL(false, rIMGUI.MouseDrawCursor);
    CHECK_EQUAL(true,  pDevice->getCursorControl()->isVisible());
    CHECK_EQUAL(false, pGUI->getSettings().mIsGUIMouseCursorEnabled);

    Settings.mIsGUIMouseCursorEnabled = true;
    pGUI->setSettings(Settings);

    CHECK_EQUAL(true,  rIMGUI.MouseDrawCursor);
    CHECK_EQUAL(false, pDevice->getCursorControl()->isVisible());
    CHECK_EQUAL(true,  pGUI->getSettings().mIsGUIMouseCursorEnabled);

    Settings.mIsGUIMouseCursorEnabled = false;
    pGUI->setSettings(Settings);

    CHECK_EQUAL(false, rIMGUI.MouseDrawCursor);
    CHECK_EQUAL(true,  pDevice->getCursorControl()->isVisible());
    CHECK_EQUAL(false, pGUI->getSettings().mIsGUIMouseCursorEnabled);

    pGUI->drop();
  }

  {
    Settings.mIsGUIMouseCursorEnabled = true;

    IIMGUIHandle * const pGUI = createIMGUI(pDevice, nullptr, &Settings);

    CHECK_EQUAL(true,  rIMGUI.MouseDrawCursor);
    CHECK_EQUAL(false, pDevice->getCursorControl()->isVisible());
    CHECK_EQUAL(true,  pGUI->getSettings().mIsGUIMouseCursorEnabled);

    Settings.mIsGUIMouseCursorEnabled = false;
    pGUI->setSettings(Settings);

    CHECK_EQUAL(false, rIMGUI.MouseDrawCursor);
    CHECK_EQUAL(true,  pDevice->getCursorControl()->isVisible());
    CHECK_EQUAL(false, pGUI->getSettings().mIsGUIMouseCursorEnabled);

    Settings.mIsGUIMouseCursorEnabled = true;
    pGUI->setSettings(Settings);

    CHECK_EQUAL(true,  rIMGUI.MouseDrawCursor);
    CHECK_EQUAL(false, pDevice->getCursorControl()->isVisible());
    CHECK_EQUAL(true,  pGUI->getSettings().mIsGUIMouseCursorEnabled);

    pGUI->drop();
  }

  pDevice->drop();

  return;
}




