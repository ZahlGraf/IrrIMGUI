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

TEST(TestIMGUIHandle, createAndDestroyInstance)
{
  Inject::setIMGUIFactory();

  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  CIMGUIEventStorage EventStorage;
  SIMGUISettings Settings;

  irr::u32 const IrrDeviceRefCount = pDevice->getReferenceCount();

  IIMGUIHandle * const pGUI = createIMGUI(pDevice, &EventStorage, &Settings);

  CHECK(pDevice->getReferenceCount() > IrrDeviceRefCount);

  pGUI->drop();

  CHECK_EQUAL(IrrDeviceRefCount, pDevice->getReferenceCount());

  pDevice->drop();

  return;
}




