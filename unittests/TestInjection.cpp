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
 * @brief Contains unit tests for the injection feature.
 */

// library includes
#include <IrrIMGUI/UnitTest/UnitTest.h>
#include <IrrIMGUI/Inject/IrrIMGUIInject.h>
#include <IrrIMGUIInject_priv.h>

using namespace IrrIMGUI;

TEST_GROUP(IrrIMGUIInject)
{
  Inject::IMGUIFactory * mpTempFactory;

  void setup(void)
  {
    // store default
    mpTempFactory = Inject::getIMGUIFactory();
  }

  void teardown()
  {
    // reset to default
    Inject::setIMGUIFactory(mpTempFactory);
  }
};

TEST(IrrIMGUIInject, checkDefaultInjection)
{
  CHECK_EQUAL(Private::createRealIMGUI, Inject::getIMGUIFactory());
}

IIMGUIHandle * testFactory(irr::IrrlichtDevice * pDevice, CIMGUIEventStorage * pEventStorage, SIMGUISettings const * pSettings)
{
  MOCK_FUNC("testFactory").MOCK_ARG(pDevice).MOCK_ARG(pEventStorage).withConstPointerParameter("pSettings", pSettings);

  return static_cast<IIMGUIHandle *>(mock().returnPointerValueOrDefault(nullptr));
}

TEST(IrrIMGUIInject, checkInjectionOfOwnFactory)
{
  Inject::setIMGUIFactory(testFactory);

  irr::IrrlichtDevice * const pDevice       = reinterpret_cast<irr::IrrlichtDevice *>(static_cast<size_t>(0xABABABAB));
  CIMGUIEventStorage          EventStorage;
  SIMGUISettings              Settings;
  IIMGUIHandle        * const pReturnHandle = reinterpret_cast<IIMGUIHandle *>(static_cast<size_t>(0xEF456A0));

  mock().expectOneCall("testFactory")
      .withParameter("pDevice", pDevice)
      .withParameter("pEventStorage", &EventStorage)
      .withConstPointerParameter("pSettings", &Settings)
      .andReturnValue(pReturnHandle);

  IIMGUIHandle * const pGUI = createIMGUI(pDevice, &EventStorage, &Settings);

  CHECK_EQUAL(pReturnHandle, pGUI);

}

TEST(IrrIMGUIInject, checkResettingInjection)
{
  // first inject a own factory
  Inject::setIMGUIFactory(testFactory);

  CHECK_EQUAL(testFactory, Inject::getIMGUIFactory());

  // reset injection to default
  Inject::setIMGUIFactory();

  CHECK_EQUAL(Private::createRealIMGUI, Inject::getIMGUIFactory());
}


