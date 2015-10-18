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
 * @file TestReferenceCounter.cpp
 * @brief Contains unit tests for the IReferenceCounter interface class.
 */

// library includes
#include <IrrIMGUI/UnitTest/UnitTest.h>
#include <string>
#include <sstream>
#include <IrrIMGUI/IrrIMGUIDebug.h>
#include <IrrIMGUI/IReferenceCounter.h>

using namespace IrrIMGUI;

TEST_GROUP(ReferenceCounter)
{
  TEST_SETUP()
  {
    // store current error output stream buffer
    mpStoredBuffer = IrrIMGUI::Debug::ErrorOutput.rdbuf();
  }

  TEST_TEARDOWN()
  {
    // reset original error output stream buffer
    IrrIMGUI::Debug::ErrorOutput.rdbuf(mpStoredBuffer);
  }

  std::streambuf * mpStoredBuffer;
};

TEST(ReferenceCounter, createInstance)
{
  IReferenceCounter * const pTestCounter = new IReferenceCounter;

  CHECK_EQUAL(pTestCounter->getReferenceCount(), 1);

  delete(pTestCounter);

  return;
}

TEST(ReferenceCounter, deleteInstanceByDrop)
{
  IReferenceCounter * const pTestCounter = new IReferenceCounter;

  pTestCounter->drop();

  return;
}

TEST(ReferenceCounter, checkCounter)
{
  IReferenceCounter * const pTestCounter = new IReferenceCounter;

  pTestCounter->grab();

  CHECK_EQUAL(pTestCounter->getReferenceCount(), 2);

  pTestCounter->grab();

  CHECK_EQUAL(pTestCounter->getReferenceCount(), 3);

  pTestCounter->grab();

  CHECK_EQUAL(pTestCounter->getReferenceCount(), 4);

  pTestCounter->drop();

  CHECK_EQUAL(pTestCounter->getReferenceCount(), 3);

  pTestCounter->drop();

  CHECK_EQUAL(pTestCounter->getReferenceCount(), 2);

  pTestCounter->drop();

  CHECK_EQUAL(pTestCounter->getReferenceCount(), 1);

  pTestCounter->drop();

  return;
}

TEST(ReferenceCounter, checkErrorWhenCounterIsWrongAtDeletion)
{
  IReferenceCounter * const pTestCounter = new IReferenceCounter;

  pTestCounter->grab();

  // redirect to string
  std::stringstream CheckBuffer;
  IrrIMGUI::Debug::ErrorOutput.rdbuf(CheckBuffer.rdbuf());

  // store address of object
  std::stringstream ObjectAddress;
  ObjectAddress << std::hex << pTestCounter;

  // store current reference counter
  std::stringstream ReferenceNumber;
  ReferenceNumber << std::dec << (pTestCounter->getReferenceCount()-1);

  delete(pTestCounter);

  std::string const ErrorString = CheckBuffer.str();

  // check error string for description
  CHECK_NOT_EQUAL(ErrorString.find("there are still references in use"), std::string::npos);

  // check error string for object address
  std::size_t const AddressPosition = ErrorString.find("object address");
  CHECK_NOT_EQUAL(AddressPosition, std::string::npos);
  CHECK_NOT_EQUAL(ErrorString.find(ObjectAddress.str(), AddressPosition), std::string::npos);

  // check error string for reference counter
  std::size_t const CounterPosition = ErrorString.find("references");
  CHECK_NOT_EQUAL(CounterPosition, std::string::npos);
  CHECK_NOT_EQUAL(ErrorString.find(ReferenceNumber.str(), CounterPosition), std::string::npos);

  return;
}
