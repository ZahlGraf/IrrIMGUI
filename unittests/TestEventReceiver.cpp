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
 * @file TestEventReceiver.cpp
 * @brief Unit Tests for checking the default Event Receiver and Event Storage.
 */

// library includes
#include <IrrIMGUI/UnitTest/UnitTest.h>
#include <IrrIMGUI/IrrIMGUI.h>
#include <IrrIMGUI/IrrIMGUIDebug.h>
#include <IrrIMGUI/IrrIMGUIConstants.h>
#include <type_traits>

using namespace IrrIMGUI;

TEST_GROUP(TestEventReceiver)
{
  TEST_SETUP()
  {
  }

  TEST_TEARDOWN()
  {
  }
};

/// @brief This struct is used to compare the IMGUI input state with the expected state.
struct SInputCompare
{
  public:
    SInputCompare(void)
    {
      mMousePos.x = 0.0f;
      mMousePos.y = 0.0f;
      mMouseWheel = 0.0f;

      for (int i = 0; i < Const::NumberOfMouseButtons; i++)
      {
        mMouseDown[i] = false;
      }

      for (int i = 0; i < NumberOfInputChars; i++)
      {
        mInputCharacters[i] = 0;
      }

      mKeyCtrl = false;
      mKeyShift = false;
      mKeyAlt = false;

      mImGuiKeyTab = false;
      mImGuiKeyLeftArrow = false;
      mImGuiKeyRightArrow = false;
      mImGuiKeyUpArrow = false;
      mImGuiKeyDownArrow = false;
      mImGuiKeyPageUp = false;
      mImGuiKeyPageDown = false;
      mImGuiKeyHome = false;
      mImGuiKeyEnd = false;
      mImGuiKeyDelete = false;
      mImGuiKeyBackspace = false;
      mImGuiKeyEnter = false;
      mImGuiKeyEscape = false;
      mImGuiKeyA = false;
      mImGuiKeyC = false;
      mImGuiKeyV = false;
      mImGuiKeyX = false;
      mImGuiKeyY = false;
      mImGuiKeyZ = false;

      return;
    }

    enum Constants {
      NumberOfInputChars   = sizeof(ImGuiIO::InputCharacters)/sizeof(ImWchar),
    };
    static_assert(std::is_same<ImWchar[NumberOfInputChars], decltype(ImGuiIO::InputCharacters)>::value, "The input character type is different between testcase and IMGUI!");

    ImVec2 mMousePos;
    static_assert(std::is_same<decltype(mMousePos), decltype(ImGuiIO::MousePos)>::value, "The mouse position vector is different between testcase and IMGUI!");

    float  mMouseWheel;
    static_assert(std::is_same<decltype(mMouseWheel), decltype(ImGuiIO::MouseWheel)>::value, "The mouse wheel type is different between testcase and IMGUI!");

    bool   mMouseDown[Const::NumberOfMouseButtons];
    static_assert(std::is_same<decltype(mMouseDown), decltype(ImGuiIO::MouseDown)>::value,       "The mouse down array type is different between testcase and IMGUI!");

    char   mInputCharacters[NumberOfInputChars];

    bool   mKeyCtrl;
    bool   mKeyShift;
    bool   mKeyAlt;

    bool   mImGuiKeyTab;
    bool   mImGuiKeyLeftArrow;
    bool   mImGuiKeyRightArrow;
    bool   mImGuiKeyUpArrow;
    bool   mImGuiKeyDownArrow;
    bool   mImGuiKeyPageUp;
    bool   mImGuiKeyPageDown;
    bool   mImGuiKeyHome;
    bool   mImGuiKeyEnd;
    bool   mImGuiKeyDelete;
    bool   mImGuiKeyBackspace;
    bool   mImGuiKeyEnter;
    bool   mImGuiKeyEscape;
    bool   mImGuiKeyA;
    bool   mImGuiKeyC;
    bool   mImGuiKeyV;
    bool   mImGuiKeyX;
    bool   mImGuiKeyY;
    bool   mImGuiKeyZ;

    void checkImGui(void)
    {

      ImGuiIO &rIMGUI = ImGui::GetIO();

      CHECK_EQUAL(mMousePos.x, rIMGUI.MousePos.x);
      CHECK_EQUAL(mMousePos.y, rIMGUI.MousePos.y);
      CHECK_EQUAL(mMouseWheel, rIMGUI.MouseWheel);

      for (int i = 0; i < Const::NumberOfMouseButtons; i++)
      {
        CHECK_EQUAL(mMouseDown[i], rIMGUI.MouseDown[i]);
      }

      // check default for other keys
      CHECK_EQUAL(mKeyCtrl,            rIMGUI.KeyCtrl);
      CHECK_EQUAL(mKeyShift,           rIMGUI.KeyShift);
      CHECK_EQUAL(mKeyAlt,             rIMGUI.KeyAlt);
      CHECK_EQUAL(mImGuiKeyTab,        rIMGUI.KeysDown[rIMGUI.KeyMap[ImGuiKey_Tab]]);
      CHECK_EQUAL(mImGuiKeyLeftArrow,  rIMGUI.KeysDown[rIMGUI.KeyMap[ImGuiKey_LeftArrow]]);
      CHECK_EQUAL(mImGuiKeyRightArrow, rIMGUI.KeysDown[rIMGUI.KeyMap[ImGuiKey_RightArrow]]);
      CHECK_EQUAL(mImGuiKeyUpArrow,    rIMGUI.KeysDown[rIMGUI.KeyMap[ImGuiKey_UpArrow]]);
      CHECK_EQUAL(mImGuiKeyDownArrow,  rIMGUI.KeysDown[rIMGUI.KeyMap[ImGuiKey_DownArrow]]);
      CHECK_EQUAL(mImGuiKeyPageUp,     rIMGUI.KeysDown[rIMGUI.KeyMap[ImGuiKey_PageUp]]);
      CHECK_EQUAL(mImGuiKeyPageDown,   rIMGUI.KeysDown[rIMGUI.KeyMap[ImGuiKey_PageDown]]);
      CHECK_EQUAL(mImGuiKeyHome,       rIMGUI.KeysDown[rIMGUI.KeyMap[ImGuiKey_Home]]);
      CHECK_EQUAL(mImGuiKeyEnd,        rIMGUI.KeysDown[rIMGUI.KeyMap[ImGuiKey_End]]);
      CHECK_EQUAL(mImGuiKeyDelete,     rIMGUI.KeysDown[rIMGUI.KeyMap[ImGuiKey_Delete]]);
      CHECK_EQUAL(mImGuiKeyBackspace,  rIMGUI.KeysDown[rIMGUI.KeyMap[ImGuiKey_Backspace]]);
      CHECK_EQUAL(mImGuiKeyEnter,      rIMGUI.KeysDown[rIMGUI.KeyMap[ImGuiKey_Enter]]);
      CHECK_EQUAL(mImGuiKeyEscape,     rIMGUI.KeysDown[rIMGUI.KeyMap[ImGuiKey_Escape]]);
      CHECK_EQUAL(mImGuiKeyA,          rIMGUI.KeysDown[rIMGUI.KeyMap[ImGuiKey_A]]);
      CHECK_EQUAL(mImGuiKeyC,          rIMGUI.KeysDown[rIMGUI.KeyMap[ImGuiKey_C]]);
      CHECK_EQUAL(mImGuiKeyV,          rIMGUI.KeysDown[rIMGUI.KeyMap[ImGuiKey_V]]);
      CHECK_EQUAL(mImGuiKeyX,          rIMGUI.KeysDown[rIMGUI.KeyMap[ImGuiKey_X]]);
      CHECK_EQUAL(mImGuiKeyY,          rIMGUI.KeysDown[rIMGUI.KeyMap[ImGuiKey_Y]]);
      CHECK_EQUAL(mImGuiKeyZ,          rIMGUI.KeysDown[rIMGUI.KeyMap[ImGuiKey_Z]]);

      // check character memory
      int i;
      for (i = 0; (rIMGUI.InputCharacters[i]) && (i < (NumberOfInputChars-1)); i++)
      {
        CHECK_TEXT(i < NumberOfInputChars, "ImGui Input characters exceed compare string length!");
        CHECK_EQUAL(mInputCharacters[i], rIMGUI.InputCharacters[i]);
      }
      // also compare NULL character
      CHECK_EQUAL(mInputCharacters[i], rIMGUI.InputCharacters[i]);

    }

    void setKey(irr::EKEY_CODE const Key, bool const IsPressed)
    {
      switch(Key)
      {
        case irr::KEY_TAB:
          mImGuiKeyTab = IsPressed;
          break;

        case irr::KEY_LCONTROL:
        case irr::KEY_RCONTROL:
        case irr::KEY_CONTROL:
          mKeyCtrl = IsPressed;
          break;

        case irr::KEY_LSHIFT:
        case irr::KEY_RSHIFT:
        case irr::KEY_SHIFT:
          mKeyShift = IsPressed;
          break;

        case irr::KEY_MENU:
          mKeyAlt = IsPressed;
          break;

        case irr::KEY_LEFT:
          mImGuiKeyLeftArrow = IsPressed;
          break;

        case irr::KEY_RIGHT:
          mImGuiKeyRightArrow = IsPressed;
          break;

        case irr::KEY_UP:
          mImGuiKeyUpArrow = IsPressed;
          break;

        case irr::KEY_DOWN:
          mImGuiKeyDownArrow = IsPressed;
          break;

        case irr::KEY_PRIOR:
          mImGuiKeyPageUp = IsPressed;
          break;

        case irr::KEY_NEXT:
          mImGuiKeyPageDown = IsPressed;
          break;

        case irr::KEY_HOME:
          mImGuiKeyHome = IsPressed;
          break;

        case irr::KEY_END:
          mImGuiKeyEnd = IsPressed;
          break;

        case irr::KEY_DELETE:
          mImGuiKeyDelete = IsPressed;
          break;

        case irr::KEY_BACK:
          mImGuiKeyBackspace = IsPressed;
          break;

        case irr::KEY_RETURN:
          mImGuiKeyEnter = IsPressed;
          break;

        case irr::KEY_ESCAPE:
          mImGuiKeyEscape = IsPressed;
          break;

        case irr::KEY_KEY_A:
          mImGuiKeyA = IsPressed;
          break;

        case irr::KEY_KEY_C:
          mImGuiKeyC = IsPressed;
          break;

        case irr::KEY_KEY_V:
          mImGuiKeyV = IsPressed;
          break;

        case irr::KEY_KEY_X:
          mImGuiKeyX = IsPressed;
          break;

        case irr::KEY_KEY_Y:
          mImGuiKeyY = IsPressed;
          break;

        case irr::KEY_KEY_Z:
          mImGuiKeyZ = IsPressed;
          break;

        default:
          CHECK_TEXT(false, "Unknown Irrlicht Key-Code!")
          break;
      }
      return;
    }
};

TEST(TestEventReceiver, checkIfNoEventTriggeredAtCreation)
{
  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  CIMGUIEventReceiver EventReceiver;

  IIMGUIHandle * const pGUI = createIMGUI(pDevice, &EventReceiver);

  SInputCompare InputCompare;

  // update inputs by received events
  pGUI->startGUI();
  InputCompare.checkImGui();

  pGUI->drawAll();

  pGUI->drop();
  pDevice->drop();

  return;
}

TEST(TestEventReceiver, checkMousePositionEvents)
{
  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  CIMGUIEventReceiver EventReceiver;

  IIMGUIHandle * const pGUI = createIMGUI(pDevice, &EventReceiver);

  SInputCompare InputCompare;

  irr::SEvent Event;
  Event.EventType = irr::EET_MOUSE_INPUT_EVENT;
  Event.MouseInput.Event = irr::EMIE_MOUSE_MOVED;
  Event.MouseInput.X = 50;
  Event.MouseInput.Y = 200;
  EventReceiver.OnEvent(Event);

  irr::u32 Frame = 0;
  irr::u32 FrameTime = 16;

  // *********************************************************************
  // Frame 1: update inputs by received events
  pDevice->getTimer()->setTime(Frame++ * FrameTime);
  pGUI->startGUI();

  InputCompare.mMousePos = ImVec2((float)Event.MouseInput.X, (float)Event.MouseInput.Y);
  InputCompare.checkImGui();

  pGUI->drawAll();
  // *********************************************************************

  Event.MouseInput.X = 100;
  Event.MouseInput.Y = 190;
  EventReceiver.OnEvent(Event);

  // *********************************************************************
  // Frame 2: update inputs by received events
  pDevice->getTimer()->setTime(Frame++ * FrameTime);
  pGUI->startGUI();

  InputCompare.mMousePos = ImVec2((float)Event.MouseInput.X, (float)Event.MouseInput.Y);
  InputCompare.checkImGui();

  pGUI->drawAll();
  // *********************************************************************

  pGUI->drop();
  pDevice->drop();

  return;
}

TEST(TestEventReceiver, checkMouseWheelEvents)
{
  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  CIMGUIEventReceiver EventReceiver;

  IIMGUIHandle * const pGUI = createIMGUI(pDevice, &EventReceiver);

  SInputCompare InputCompare;

  irr::SEvent Event;
  Event.EventType = irr::EET_MOUSE_INPUT_EVENT;
  Event.MouseInput.Event = irr::EMIE_MOUSE_WHEEL;
  Event.MouseInput.Wheel = 1.0f;
  EventReceiver.OnEvent(Event);

  irr::u32 Frame = 0;
  irr::u32 FrameTime = 16;

  // *********************************************************************
  // Frame 1: update inputs by received events
  pDevice->getTimer()->setTime(Frame++ * FrameTime);
  pGUI->startGUI();

  InputCompare.mMouseWheel = Event.MouseInput.Wheel;
  InputCompare.checkImGui();

  pGUI->drawAll();
  // *********************************************************************

  // *********************************************************************
  // Frame 2: update inputs by received events
  pDevice->getTimer()->setTime(Frame++ * FrameTime);
  pGUI->startGUI();

  // check self reset of mouse wheel value
  InputCompare.mMouseWheel = 0.0f;
  InputCompare.checkImGui();

  pGUI->drawAll();
  // *********************************************************************

  Event.MouseInput.Wheel = -1.0f;
  EventReceiver.OnEvent(Event);

  // *********************************************************************
  // Frame 3: update inputs by received events
  pDevice->getTimer()->setTime(Frame++ * FrameTime);
  pGUI->startGUI();

  InputCompare.mMouseWheel = Event.MouseInput.Wheel;
  InputCompare.checkImGui();

  pGUI->drawAll();
  // *********************************************************************

  // *********************************************************************
  // Frame 4: update inputs by received events
  pDevice->getTimer()->setTime(Frame++ * FrameTime);
  pGUI->startGUI();

  // check self reset of mouse wheel value
  InputCompare.mMouseWheel = 0.0f;
  InputCompare.checkImGui();

  pGUI->drawAll();
  // *********************************************************************

  pDevice->drop();
  pGUI->drop();

  return;
}

TEST(TestEventReceiver, checkMouseButtonEvents)
{
  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  CIMGUIEventReceiver EventReceiver;

  IIMGUIHandle * const pGUI = createIMGUI(pDevice, &EventReceiver);

  ImGuiIO &rIMGUI = ImGui::GetIO();

  for (int i = 0; i < 3; i++)
  {
    SInputCompare InputCompare;
    irr::u32 Frame = 0;
    irr::u32 FrameTime = 16;

    irr::SEvent Event;
    Event.EventType = irr::EET_MOUSE_INPUT_EVENT;
    switch(i)
    {
      case 0:
        Event.MouseInput.Event = irr::EMIE_LMOUSE_PRESSED_DOWN;
        break;

      case 1:
        Event.MouseInput.Event = irr::EMIE_RMOUSE_PRESSED_DOWN;
        break;

      case 2:
        Event.MouseInput.Event = irr::EMIE_MMOUSE_PRESSED_DOWN;
        break;

      default:
        CHECK_TEXT(false, "Unknown mouse button index!");
        break;
    }
    EventReceiver.OnEvent(Event);

    // prevent double click detection due to last testcase
    rIMGUI.MouseClickedTime[i] = -FLT_MAX;

    CHECK_EQUAL(false, rIMGUI.MouseClicked[i]);
    CHECK_EQUAL(false, rIMGUI.MouseDoubleClicked[i]);

    // *********************************************************************
    // Frame 1: update inputs by received events
    pDevice->getTimer()->setTime(Frame++ * FrameTime);
    pGUI->startGUI();

    InputCompare.mMouseDown[i] = true;
    InputCompare.checkImGui();
    CHECK_EQUAL(true,  rIMGUI.MouseClicked[i]);
    CHECK_EQUAL(false, rIMGUI.MouseDoubleClicked[i]);

    pGUI->drawAll();
    // *********************************************************************

    switch(i)
    {
      case 0:
        Event.MouseInput.Event = irr::EMIE_LMOUSE_LEFT_UP;
        break;

      case 1:
        Event.MouseInput.Event = irr::EMIE_RMOUSE_LEFT_UP;
        break;

      case 2:
        Event.MouseInput.Event = irr::EMIE_MMOUSE_LEFT_UP;
        break;

      default:
        CHECK_TEXT(false, "Unknown mouse button index!");
        break;
    }
    EventReceiver.OnEvent(Event);

    // *********************************************************************
    // Frame 2: update inputs by received events
    pDevice->getTimer()->setTime(Frame++ * FrameTime);
    pGUI->startGUI();

    InputCompare.mMouseDown[i] = false;
    InputCompare.checkImGui();
    CHECK_EQUAL(false, rIMGUI.MouseClicked[i]);
    CHECK_EQUAL(false, rIMGUI.MouseDoubleClicked[i]);

    pGUI->drawAll();
    // *********************************************************************

    switch(i)
    {
      case 0:
        Event.MouseInput.Event = irr::EMIE_LMOUSE_PRESSED_DOWN;
        break;

      case 1:
        Event.MouseInput.Event = irr::EMIE_RMOUSE_PRESSED_DOWN;
        break;

      case 2:
        Event.MouseInput.Event = irr::EMIE_MMOUSE_PRESSED_DOWN;
        break;

      default:
        CHECK_TEXT(false, "Unknown mouse button index!");
        break;
    }
    EventReceiver.OnEvent(Event);

    // *********************************************************************
    // Frame 3: update inputs by received events
    pDevice->getTimer()->setTime(Frame++ * FrameTime);
    pGUI->startGUI();

    InputCompare.mMouseDown[i] = true;
    InputCompare.checkImGui();
    CHECK_EQUAL(true,  rIMGUI.MouseClicked[i]);
    CHECK_EQUAL(true,  rIMGUI.MouseDoubleClicked[i]);

    pGUI->drawAll();
    // *********************************************************************

    switch(i)
    {
      case 0:
        Event.MouseInput.Event = irr::EMIE_LMOUSE_LEFT_UP;
        break;

      case 1:
        Event.MouseInput.Event = irr::EMIE_RMOUSE_LEFT_UP;
        break;

      case 2:
        Event.MouseInput.Event = irr::EMIE_MMOUSE_LEFT_UP;
        break;

      default:
        CHECK_TEXT(false, "Unknown mouse button index!");
        break;
    }
    EventReceiver.OnEvent(Event);

    // *********************************************************************
    // Frame 4: update inputs by received events
    pDevice->getTimer()->setTime(Frame++ * FrameTime);
    pGUI->startGUI();

    InputCompare.mMouseDown[i] = false;
    InputCompare.checkImGui();
    CHECK_EQUAL(false, rIMGUI.MouseClicked[i]);
    CHECK_EQUAL(false, rIMGUI.MouseDoubleClicked[i]);

    pGUI->drawAll();
    // *********************************************************************
  }

  pGUI->drop();
  pDevice->drop();

  return;
}

void testSingleKey(CIMGUIEventReceiver &rEventReceiver, irr::IrrlichtDevice * const pDevice, IIMGUIHandle * const pGUI, irr::u32 * const pFrame, irr::u32 const FrameTime, irr::EKEY_CODE const Key)
{
  SInputCompare InputCompare;

  irr::SEvent Event;
  Event.EventType = irr::EET_KEY_INPUT_EVENT;
  Event.KeyInput.Key = Key;
  Event.KeyInput.PressedDown = true;
  Event.KeyInput.Char = 0;
  rEventReceiver.OnEvent(Event);

  // *********************************************************************
  // Frame 1: update inputs by received events
  pDevice->getTimer()->setTime((*pFrame)++ * FrameTime);
  pGUI->startGUI();

  InputCompare.setKey(Key, true);
  InputCompare.checkImGui();

  pGUI->drawAll();
  // *********************************************************************

  Event.KeyInput.Key = Key;
  Event.KeyInput.PressedDown = false;
  rEventReceiver.OnEvent(Event);

  // *********************************************************************
  // Frame 2: update inputs by received events
  pDevice->getTimer()->setTime((*pFrame)++ * FrameTime);
  pGUI->startGUI();

  // check self reset of mouse wheel value
  InputCompare.setKey(Key, false);
  InputCompare.checkImGui();

  pGUI->drawAll();
  // *********************************************************************
  Event.KeyInput.Key = Key;
  Event.KeyInput.PressedDown = false;
  rEventReceiver.OnEvent(Event);

  // *********************************************************************
  // Frame 2: update inputs by received events
  pDevice->getTimer()->setTime((*pFrame)++ * FrameTime);
  pGUI->startGUI();

  // check self reset of mouse wheel value
  InputCompare.setKey(Key, false);
  InputCompare.checkImGui();

  pGUI->drawAll();
  // *********************************************************************

  return;
}

TEST(TestEventReceiver, checkSpecialButtonEvents)
{
  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  CIMGUIEventReceiver EventReceiver;

  IIMGUIHandle * const pGUI = createIMGUI(pDevice, &EventReceiver);

  irr::u32 Frame = 0;
  irr::u32 FrameTime = 16;

  testSingleKey(EventReceiver, pDevice, pGUI, &Frame, FrameTime, irr::KEY_CONTROL);
  testSingleKey(EventReceiver, pDevice, pGUI, &Frame, FrameTime, irr::KEY_SHIFT);
  testSingleKey(EventReceiver, pDevice, pGUI, &Frame, FrameTime, irr::KEY_MENU);
  testSingleKey(EventReceiver, pDevice, pGUI, &Frame, FrameTime, irr::KEY_TAB);
  testSingleKey(EventReceiver, pDevice, pGUI, &Frame, FrameTime, irr::KEY_LEFT);
  testSingleKey(EventReceiver, pDevice, pGUI, &Frame, FrameTime, irr::KEY_RIGHT);
  testSingleKey(EventReceiver, pDevice, pGUI, &Frame, FrameTime, irr::KEY_UP);
  testSingleKey(EventReceiver, pDevice, pGUI, &Frame, FrameTime, irr::KEY_DOWN);
  testSingleKey(EventReceiver, pDevice, pGUI, &Frame, FrameTime, irr::KEY_PRIOR);
  testSingleKey(EventReceiver, pDevice, pGUI, &Frame, FrameTime, irr::KEY_NEXT);
  testSingleKey(EventReceiver, pDevice, pGUI, &Frame, FrameTime, irr::KEY_HOME);
  testSingleKey(EventReceiver, pDevice, pGUI, &Frame, FrameTime, irr::KEY_END);
  testSingleKey(EventReceiver, pDevice, pGUI, &Frame, FrameTime, irr::KEY_DELETE);
  testSingleKey(EventReceiver, pDevice, pGUI, &Frame, FrameTime, irr::KEY_BACK);
  testSingleKey(EventReceiver, pDevice, pGUI, &Frame, FrameTime, irr::KEY_RETURN);
  testSingleKey(EventReceiver, pDevice, pGUI, &Frame, FrameTime, irr::KEY_ESCAPE);
  testSingleKey(EventReceiver, pDevice, pGUI, &Frame, FrameTime, irr::KEY_END);
  testSingleKey(EventReceiver, pDevice, pGUI, &Frame, FrameTime, irr::KEY_KEY_A);
  testSingleKey(EventReceiver, pDevice, pGUI, &Frame, FrameTime, irr::KEY_KEY_C);
  testSingleKey(EventReceiver, pDevice, pGUI, &Frame, FrameTime, irr::KEY_KEY_V);
  testSingleKey(EventReceiver, pDevice, pGUI, &Frame, FrameTime, irr::KEY_KEY_Y);
  testSingleKey(EventReceiver, pDevice, pGUI, &Frame, FrameTime, irr::KEY_KEY_Z);

  pDevice->drop();
  pGUI->drop();

  return;
}

TEST(TestEventReceiver, checkCharacterKeys)
{
  irr::IrrlichtDevice * const pDevice = irr::createDevice(irr::video::EDT_NULL);
  CIMGUIEventReceiver EventReceiver;

  IIMGUIHandle * const pGUI = createIMGUI(pDevice, &EventReceiver);

  SInputCompare InputCompare;
  irr::u32 Frame = 0;
  irr::u32 FrameTime = 16;

  irr::SEvent Event;
  Event.EventType = irr::EET_KEY_INPUT_EVENT;
  Event.KeyInput.Key = irr::KEY_OEM_CLEAR;
  Event.KeyInput.PressedDown = true;
  Event.KeyInput.Char = 'a';
  EventReceiver.OnEvent(Event);

  // *********************************************************************
  // Frame 1: update inputs by received events
  pDevice->getTimer()->setTime(Frame++ * FrameTime);
  pGUI->startGUI();

  InputCompare.mInputCharacters[0] = 'a';
  InputCompare.checkImGui();

  pGUI->drawAll();
  // *********************************************************************

  Event.KeyInput.PressedDown = false;
  Event.KeyInput.Char = 'a';
  EventReceiver.OnEvent(Event);

  // *********************************************************************
  // Frame 1: update inputs by received events
  pDevice->getTimer()->setTime(Frame++ * FrameTime);
  pGUI->startGUI();

  InputCompare.mInputCharacters[0] = '\0';
  InputCompare.checkImGui();

  pGUI->drawAll();
  // *********************************************************************

  Event.KeyInput.PressedDown = true;
  Event.KeyInput.Char = 'H';
  EventReceiver.OnEvent(Event);
  Event.KeyInput.PressedDown = true;
  Event.KeyInput.Char = 'e';
  EventReceiver.OnEvent(Event);
  Event.KeyInput.PressedDown = true;
  Event.KeyInput.Char = 'l';
  EventReceiver.OnEvent(Event);
  Event.KeyInput.PressedDown = true;
  Event.KeyInput.Char = 'l';
  EventReceiver.OnEvent(Event);
  Event.KeyInput.PressedDown = true;
  Event.KeyInput.Char = 'o';
  EventReceiver.OnEvent(Event);

  // *********************************************************************
  // Frame 1: update inputs by received events
  pDevice->getTimer()->setTime(Frame++ * FrameTime);
  pGUI->startGUI();

  InputCompare.mInputCharacters[0] = 'H';
  InputCompare.mInputCharacters[1] = 'e';
  InputCompare.mInputCharacters[2] = 'l';
  InputCompare.mInputCharacters[3] = 'l';
  InputCompare.mInputCharacters[4] = 'o';
  InputCompare.checkImGui();

  pGUI->drawAll();
  // *********************************************************************

  Event.KeyInput.PressedDown = false;
  Event.KeyInput.Char = 'a';
  EventReceiver.OnEvent(Event);

  // *********************************************************************
  // Frame 1: update inputs by received events
  pDevice->getTimer()->setTime(Frame++ * FrameTime);
  pGUI->startGUI();

  InputCompare.mInputCharacters[0] = '\0';
  InputCompare.mInputCharacters[1] = '\0';
  InputCompare.mInputCharacters[2] = '\0';
  InputCompare.mInputCharacters[3] = '\0';
  InputCompare.mInputCharacters[4] = '\0';
  InputCompare.checkImGui();

  pGUI->drawAll();
  // *********************************************************************

  pDevice->drop();
  pGUI->drop();

  return;
}
