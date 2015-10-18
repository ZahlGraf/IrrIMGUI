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
 * @file TestMemoryLeakDetection.cpp
 * @brief Contains unit tests to check the basic memory leak detection.
 */

// library includes
#include <IrrIMGUI/UnitTest/UnitTest.h>
#include <IrrIMGUI/Tools/CBasicMemoryLeakDetection.h>
#include <IrrIMGUI/IrrIMGUIDebug.h>
#include <sstream>
#include <iostream>
#include <string>

using namespace IrrIMGUI;

#ifdef _ENABLE_MEMORY_LEAK_DETECTION_

TEST_GROUP(TestMemoryLeakDetection)
{
  TEST_SETUP()
  {
  }

  TEST_TEARDOWN()
  {
  }
};

TEST(TestMemoryLeakDetection, checkIfNoMemoryLeakIsDetectedWithDestructor)
{
  std::stringstream ErrorStream;
  IrrIMGUI::Debug::ErrorOutput.setupStream(ErrorStream);

  {
    IrrIMGUI::Tools::CBasicMemoryLeakDetection MemoryLeakDetection;

    int * const pVariable = new int;
    delete pVariable;
  }

  size_t const ErrorPosition = ErrorStream.str().find("[Error]   Memory Leak detected");

  CHECK(std::string::npos == ErrorPosition);
}

TEST(TestMemoryLeakDetection, checkIfMemoryLeakIsDetectedWithDestructor)
{
  std::stringstream ErrorStream;
  IrrIMGUI::Debug::ErrorOutput.setupStream(ErrorStream);

  int * pVariable;
  {
    IrrIMGUI::Tools::CBasicMemoryLeakDetection MemoryLeakDetection;

    pVariable = new int;
  }
  delete pVariable;

  size_t const ErrorPosition = ErrorStream.str().find("[Error]   Memory Leak detected");
  CHECK(std::string::npos != ErrorPosition);
}

TEST(TestMemoryLeakDetection, checkIfNoMemoryLeakIsDetectedWithMethod)
{
  std::stringstream ErrorStream;
  IrrIMGUI::Debug::ErrorOutput.setupStream(ErrorStream);

  {
    IrrIMGUI::Tools::CBasicMemoryLeakDetection MemoryLeakDetection;

    int * const pVariable = new int;
    delete pVariable;

    int const MemoryLeak = MemoryLeakDetection.compareMemoryState();
    CHECK_EQUAL(0, MemoryLeak);
  }
}

TEST(TestMemoryLeakDetection, checkIfMemoryLeakIsDetectedWithMethod)
{
  std::stringstream ErrorStream;
  IrrIMGUI::Debug::ErrorOutput.setupStream(ErrorStream);

  int * pVariable;
  {
    IrrIMGUI::Tools::CBasicMemoryLeakDetection MemoryLeakDetection;

    pVariable = new int;

    int const MemoryLeak = MemoryLeakDetection.compareMemoryState();
    CHECK_NOT_EQUAL(0, MemoryLeak);
  }
  delete pVariable;
}

TEST(TestMemoryLeakDetection, checkIfMemoryLeakIsNotReportedByDestructorWhenManualCheckWasDone)
{
  std::stringstream ErrorStream;
  IrrIMGUI::Debug::ErrorOutput.setupStream(ErrorStream);

  int * pVariable;
  {
    IrrIMGUI::Tools::CBasicMemoryLeakDetection MemoryLeakDetection;

    pVariable = new int;

    int const MemoryLeak = MemoryLeakDetection.compareMemoryState();
    CHECK_NOT_EQUAL(0, MemoryLeak);
  }
  delete pVariable;

  size_t const ErrorPosition = ErrorStream.str().find("[Error]   Memory Leak detected");
  CHECK(std::string::npos == ErrorPosition);
}

TEST(TestMemoryLeakDetection, checkIfMemoryLeakIsReportedTwice)
{
  std::stringstream ErrorStream;
  IrrIMGUI::Debug::ErrorOutput.setupStream(ErrorStream);

  int * pVariable;
  {
    IrrIMGUI::Tools::CBasicMemoryLeakDetection MemoryLeakDetection;

    pVariable = new int;

    int const MemoryLeak1 = MemoryLeakDetection.compareMemoryState();
    CHECK_NOT_EQUAL(0, MemoryLeak1);

    int const MemoryLeak2 = MemoryLeakDetection.compareMemoryState();
    CHECK_NOT_EQUAL(0, MemoryLeak2);
  }
  delete pVariable;
}

TEST(TestMemoryLeakDetection, checkIfResetPreventLeakDetection)
{
  std::stringstream ErrorStream;
  IrrIMGUI::Debug::ErrorOutput.setupStream(ErrorStream);

  int * pVariable;
  {
    IrrIMGUI::Tools::CBasicMemoryLeakDetection MemoryLeakDetection;

    pVariable = new int;

    MemoryLeakDetection.resetMemoryState();

    int const MemoryLeak = MemoryLeakDetection.compareMemoryState();
    CHECK_EQUAL(0, MemoryLeak);
  }
  delete pVariable;
}

TEST(TestMemoryLeakDetection, checkIfResetEnablesNewDetectionByMethod)
{
  std::stringstream ErrorStream;
  IrrIMGUI::Debug::ErrorOutput.setupStream(ErrorStream);

  int * pVariable;
  int * pVariable2;
  {
    IrrIMGUI::Tools::CBasicMemoryLeakDetection MemoryLeakDetection;

    pVariable = new int;

    MemoryLeakDetection.resetMemoryState();

    pVariable2 = new int;

    int const MemoryLeak = MemoryLeakDetection.compareMemoryState();
    CHECK_NOT_EQUAL(0, MemoryLeak);
  }
  delete pVariable;
  delete pVariable2;
}

TEST(TestMemoryLeakDetection, checkIfResetEnablesNewDetectionByDestructor)
{
  std::stringstream ErrorStream;
  IrrIMGUI::Debug::ErrorOutput.setupStream(ErrorStream);

  int * pVariable;
  int * pVariable2;
  {
    IrrIMGUI::Tools::CBasicMemoryLeakDetection MemoryLeakDetection;

    pVariable = new int;

    int const MemoryLeak = MemoryLeakDetection.compareMemoryState();
    CHECK_NOT_EQUAL(0, MemoryLeak);

    MemoryLeakDetection.resetMemoryState();

    pVariable2 = new int;
  }
  delete pVariable;
  delete pVariable2;

  size_t const ErrorPosition = ErrorStream.str().find("[Error]   Memory Leak detected");
  CHECK(std::string::npos != ErrorPosition);

}

#endif // _ENABLE_MEMORY_LEAK_DETECTION_
