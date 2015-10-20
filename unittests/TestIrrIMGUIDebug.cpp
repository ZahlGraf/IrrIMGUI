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
 * @file TestIrrIMGUIDebug.cpp
 * @brief Contains unit tests to check Debug classes functionality.
 */

// library includes
#include <IrrIMGUI/UnitTest/UnitTest.h>
#include <IrrIMGUI/IrrIMGUIDebug.h>
#include <IrrIMGUIDebug_priv.h>
#include <iostream>
#include <sstream>

using namespace IrrIMGUI;

TEST_GROUP(TestIrrIMGUIDebug)
{
  TEST_SETUP()
  {
  }

  TEST_TEARDOWN()
  {
    Debug::AreUnitTestAssertionsEnabled = true;
  }
};

TEST(TestIrrIMGUIDebug, checkCreateChannel)
{
  std::stringstream OutputStream;

  // create channel and connect it to output stream
  Debug::CChannel TestChannel(OutputStream, "[Test] ");
}

TEST(TestIrrIMGUIDebug, checkOutputSingleLine)
{
  std::stringstream OutputStream;

  // create channel and connect it to output stream
  Debug::CChannel TestChannel(OutputStream, "[Test] ");

  TestChannel << "Hello World";

  CHECK_NOT_EQUAL(std::string::npos, OutputStream.str().find("[Test] Hello World"));
}

TEST(TestIrrIMGUIDebug, checkOutputSingleLinePlusNewlineOnly)
{
  std::stringstream OutputStream;

  // create channel and connect it to output stream
  Debug::CChannel TestChannel(OutputStream, "[Test] ");

  TestChannel << "Hello World\n";

  CHECK_NOT_EQUAL(std::string::npos, OutputStream.str().find("[Test] Hello World\n"));
}

TEST(TestIrrIMGUIDebug, checkOutputMultiLine)
{
  std::stringstream OutputStream;

  // create channel and connect it to output stream
  Debug::CChannel TestChannel(OutputStream, "[Test] ");

  TestChannel << "Hello World\n";
  TestChannel << "\n";
  TestChannel << "Hello Mars!";

  CHECK_NOT_EQUAL(std::string::npos, OutputStream.str().find("[Test] Hello World\n[Test] \n[Test] Hello Mars!"));
}

TEST(TestIrrIMGUIDebug, checkChangePrefix)
{
  std::stringstream OutputStream;

  // create channel and connect it to output stream
  Debug::CChannel TestChannel(OutputStream, "");

  TestChannel.setupPrefix("[Mars] ");
  TestChannel << "Hello Earth!\n";
  TestChannel.setupPrefix("[Earth] ");
  TestChannel << "Hello Mars!\n";

  CHECK_NOT_EQUAL(std::string::npos, OutputStream.str().find("[Mars] Hello Earth!\n[Earth] Hello Mars!\n"));
}

TEST(TestIrrIMGUIDebug, checkDisableChannel)
{
  std::stringstream OutputStream;

  // create channel and connect it to output stream
  Debug::CChannel TestChannel(OutputStream, "[Planet] ");

  TestChannel << "Hello Earth!\n";
  TestChannel << "Hello Mars!\n";
  TestChannel.disable();
  TestChannel << "Hello small friends!\n";
  TestChannel.setupStream(OutputStream, true);
  TestChannel << "I cannot see Jupiter!\n";

  CHECK_NOT_EQUAL(std::string::npos, OutputStream.str().find("[Planet] Hello Earth!\n[Planet] Hello Mars!\n[Planet] I cannot see Jupiter!"));
}

TEST(TestIrrIMGUIDebug, checkDisableChannelWithoutNewline)
{
  std::stringstream OutputStream;

  // create channel and connect it to output stream
  Debug::CChannel TestChannel(OutputStream, "[Planet] ");

  TestChannel << "Hello Earth!\n";
  TestChannel << "Hello Mars!\n";
  TestChannel.disable();
  TestChannel << "Hello small friends!\n";
  TestChannel.setupStream(OutputStream, false);
  TestChannel << "I cannot see Jupiter!\n";

  CHECK_NOT_EQUAL(std::string::npos, OutputStream.str().find("[Planet] Hello Earth!\n[Planet] Hello Mars!\nI cannot see Jupiter!"));
}

TEST(TestIrrIMGUIDebug, checkAssertionMacro)
{
  Debug::AreUnitTestAssertionsEnabled = false;
  bool WasExceptionTriggered = false;

  try
  {
    FASSERT(false);
  }
  catch(Debug::ExAssert &rException)
  {
    WasExceptionTriggered = true;
    std::stringstream AssertionText(rException.what());
    CHECK_NOT_EQUAL(std::string::npos, AssertionText.str().find("Assertion failed: '(false)'"));
  }

  CHECK_EQUAL(true, WasExceptionTriggered);
}
