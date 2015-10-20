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
 * @file TestCharFifo.cpp
 * @brief Unit Tests for checking the character Fifo.
 */

// library includes
#include <IrrIMGUI/UnitTest/UnitTest.h>
#include <IrrIMGUI/CCharFifo.h>
#include <IrrIMGUI/IrrIMGUIDebug.h>

using namespace IrrIMGUI;

TEST_GROUP(CharacterFifo)
{
  TEST_SETUP()
  {
  }

  TEST_TEARDOWN()
  {
  }
};

TEST(CharacterFifo, checkEmptyFifoAtCreation)
{
  CCharFifo Fifo;

  CHECK_EQUAL(true,  Fifo.isEmpty());
  CHECK_EQUAL(0,     Fifo.getNumberOfElements())
  CHECK_EQUAL(false, Fifo.isFull());

  return;
}

TEST(CharacterFifo, checkAddToFifo)
{
  CCharFifo Fifo;

  Fifo.addChar('A');
  CHECK_EQUAL(1,     Fifo.getNumberOfElements())
  CHECK_EQUAL(false,  Fifo.isEmpty());
  CHECK_EQUAL(false,  Fifo.isFull());

  Fifo.addChar('b');
  CHECK_EQUAL(2,     Fifo.getNumberOfElements())
  CHECK_EQUAL(false,  Fifo.isEmpty());
  CHECK_EQUAL(false,  Fifo.isFull());

  Fifo.addChar('c');
  CHECK_EQUAL(3,     Fifo.getNumberOfElements())
  CHECK_EQUAL(false,  Fifo.isEmpty());
  CHECK_EQUAL(false,  Fifo.isFull());

  Fifo.addChar('d');
  CHECK_EQUAL(4,     Fifo.getNumberOfElements())
  CHECK_EQUAL(false,  Fifo.isEmpty());
  CHECK_EQUAL(false,  Fifo.isFull());

  Fifo.addChar('e');
  CHECK_EQUAL(5,     Fifo.getNumberOfElements())
  CHECK_EQUAL(false,  Fifo.isEmpty());
  CHECK_EQUAL(false,  Fifo.isFull());

  Fifo.addChar('f');
  CHECK_EQUAL(6,     Fifo.getNumberOfElements())
  CHECK_EQUAL(false,  Fifo.isEmpty());
  CHECK_EQUAL(false,  Fifo.isFull());

  Fifo.addChar('g');
  CHECK_EQUAL(7,     Fifo.getNumberOfElements())
  CHECK_EQUAL(false,  Fifo.isEmpty());
  CHECK_EQUAL(false,  Fifo.isFull());

  Fifo.addChar('h');
  CHECK_EQUAL(8,     Fifo.getNumberOfElements())
  CHECK_EQUAL(false,  Fifo.isEmpty());
  CHECK_EQUAL(false,  Fifo.isFull());

  return;
}

TEST(CharacterFifo, checkReadFromFifo)
{
  CCharFifo Fifo;

  Fifo.addChar('A');
  Fifo.addChar('b');
  Fifo.addChar('c');
  Fifo.addChar('d');
  Fifo.addChar('e');
  Fifo.addChar('f');
  Fifo.addChar('g');
  Fifo.addChar('h');

  CHECK_EQUAL('A', Fifo.getChar())
  CHECK_EQUAL(7,     Fifo.getNumberOfElements())
  CHECK_EQUAL('b', Fifo.getChar())
  CHECK_EQUAL(6,     Fifo.getNumberOfElements())
  CHECK_EQUAL('c', Fifo.getChar())
  CHECK_EQUAL(5,     Fifo.getNumberOfElements())
  CHECK_EQUAL('d', Fifo.getChar())
  CHECK_EQUAL(4,     Fifo.getNumberOfElements())
  CHECK_EQUAL('e', Fifo.getChar())
  CHECK_EQUAL(3,     Fifo.getNumberOfElements())
  CHECK_EQUAL('f', Fifo.getChar())
  CHECK_EQUAL(2,     Fifo.getNumberOfElements())
  CHECK_EQUAL('g', Fifo.getChar())
  CHECK_EQUAL(1,     Fifo.getNumberOfElements())
  CHECK_EQUAL('h', Fifo.getChar())
  CHECK_EQUAL(0,     Fifo.getNumberOfElements())

  CHECK_EQUAL(true,   Fifo.isEmpty());
  CHECK_EQUAL(false,  Fifo.isFull());

  return;
}

TEST(CharacterFifo, checkFifoIsFull)
{
  CCharFifo Fifo;

  for (int i = 0; i < 255; i++)
  {
    Fifo.addChar(i);
  }

  CHECK_EQUAL(255,    Fifo.getNumberOfElements())
  CHECK_EQUAL(false,  Fifo.isEmpty());
  CHECK_EQUAL(true,   Fifo.isFull());

  return;
}

TEST(CharacterFifo, checkFifoCanHandlePointerOverflow)
{
  CCharFifo Fifo;

  for (int i = 0; i < 255/2; i++)
  {
    Fifo.addChar(i);
    CHECK_EQUAL(i, Fifo.getChar());
  }

  CHECK_EQUAL(true,  Fifo.isEmpty());
  CHECK_EQUAL(false, Fifo.isFull());
  CHECK_EQUAL(0,     Fifo.getNumberOfElements())

  for (int i = 0; i < 255; i++)
  {
    Fifo.addChar(255-i);
  }

  CHECK_EQUAL(255,    Fifo.getNumberOfElements())
  CHECK_EQUAL(false,  Fifo.isEmpty());
  CHECK_EQUAL(true,   Fifo.isFull());

  for (int i = 0; i < 255; i++)
  {
    CHECK_EQUAL(255-i, Fifo.getChar());
  }

  CHECK_EQUAL(0,      Fifo.getNumberOfElements())
  CHECK_EQUAL(true,   Fifo.isEmpty());
  CHECK_EQUAL(false,  Fifo.isFull());

  return;
}

TEST(CharacterFifo, checkFifoIgnoresCharsWhenFull)
{
  CCharFifo Fifo;

  for (int i = 0; i < 255; i++)
  {
    Fifo.addChar('B');
  }

  CHECK_EQUAL(false, Fifo.isEmpty());
  CHECK_EQUAL(true,  Fifo.isFull());
  CHECK_EQUAL(255,   Fifo.getNumberOfElements())

  Fifo.addChar('A');

  CHECK_EQUAL(false, Fifo.isEmpty());
  CHECK_EQUAL(true,  Fifo.isFull());
  CHECK_EQUAL(255,   Fifo.getNumberOfElements())

  CHECK_EQUAL('B', Fifo.getChar());

  return;
}

TEST(CharacterFifo, checkFifoThrowsAssertionWhenEmpty)
{
  CCharFifo Fifo;

  IrrIMGUI::Debug::AreUnitTestAssertionsEnabled = false;

  CHECK_THROWS(IrrIMGUI::Debug::ExAssert, Fifo.getChar());

  IrrIMGUI::Debug::AreUnitTestAssertionsEnabled = true;

  return;
}
