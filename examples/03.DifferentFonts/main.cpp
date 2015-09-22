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
 * @file main.cpp
 * @brief This example creates a simple Irrlicht scene with background and a simple IMGUI window.
 */

// standard library includes
#include <exception>
#include <iostream>

// library includes
#include <IrrIMGUI/IncludeIrrlicht.h>
#include <IrrIMGUI/IncludeIMGUI.h>
#include <IrrIMGUI/IrrIMGUI.h>
#include <IrrIMGUI/IrrIMGUIDebug.h>

// helper macros for reacting on unexpected states
#define _TOSTR(x) #x
#define TOSTR(x) _TOSTR(x)
#define FASSERT(expr) if (!(expr)) { throw IrrIMGUI::Debug::ExAssert(__FILE__ "[" TOSTR(__LINE__) "] Assertion failed: \'" TOSTR(expr) "'\n"); }

// builds up the Irrlicht scene
void runScene(void)
{
  using namespace IrrIMGUI;
  using namespace irr;

  // Create standard event receiver for the IrrIMGUI
  CIMGUIEventReceiver EventReceiver;

  // Irrlicht Settings
  SIrrlichtCreationParameters IrrlichtParams;
  IrrlichtParams.DriverType    = video::EDT_OPENGL;
  IrrlichtParams.WindowSize    = core::dimension2d<u32>(1024, 800);
  IrrlichtParams.Bits          = 32;
  IrrlichtParams.Fullscreen    = false;
  IrrlichtParams.Stencilbuffer = true;
  IrrlichtParams.AntiAlias     = 16;
  IrrlichtParams.Vsync         = false;
  IrrlichtParams.EventReceiver = &EventReceiver;

  IrrlichtDevice * const pDevice = createDeviceEx(IrrlichtParams);
  FASSERT(pDevice);

  // Create GUI object
  CIMGUIHandle GUI(pDevice, &EventReceiver);

  video::IVideoDriver  * const pDriver       = pDevice->getVideoDriver();
  scene::ISceneManager * const pSceneManager = pDevice->getSceneManager();

  pDriver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
  irr::scene::ISceneNode * const pSkybox = pSceneManager->addSkyBoxSceneNode(
      pDriver->getTexture("../../media/Background.jpg"),
      pDriver->getTexture("../../media/Background.jpg"),
      pDriver->getTexture("../../media/Background.jpg"),
      pDriver->getTexture("../../media/Background.jpg"),
      pDriver->getTexture("../../media/Background.jpg"),
      pDriver->getTexture("../../media/Background.jpg"));
  pDriver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);

  // Create Planet object
  scene::IMeshSceneNode * const pMoon = pSceneManager->addSphereSceneNode(5.0f, 128);
  FASSERT(pMoon);
  pMoon->setPosition(irr::core::vector3df(0,0,25));
  pMoon->setMaterialTexture(0, pDriver->getTexture("../../media/Phobos.jpg"));
  pMoon->setMaterialFlag(irr::video::EMF_LIGHTING, false);

  // Add camera object
  pSceneManager->addCameraSceneNode(0, core::vector3df(0, 0, 0), core::vector3df(0,0,5));

  u32 LastTime = pDevice->getTimer()->getRealTime();
  s32 LastFPS = 0;
  f32 Rotation = 0.0;
  f32 RotPerSec = 0.01f;
  bool IsFirstLoop = true;

  /// **********************************************************************
  /// Step 1 - Create handles to the fonts by loading them into GUI memory
  /// **********************************************************************
  ImFont *pCousine16   = GUI.addFontFromFileTTF("../../media/Cousine-Regular.ttf", 16.0f);
  ImFont *pCousine24   = GUI.addFontFromFileTTF("../../media/Cousine-Regular.ttf", 24.0f);
  ImFont *pDroidSans16 = GUI.addFontFromFileTTF("../../media/DroidSans.ttf",       16.0f);
  ImFont *pDroidSans24 = GUI.addFontFromFileTTF("../../media/DroidSans.ttf",       24.0f);
  ImFont *pKarla16     = GUI.addFontFromFileTTF("../../media/Karla-Regular.ttf",   16.0f);
  ImFont *pKarla24     = GUI.addFontFromFileTTF("../../media/Karla-Regular.ttf",   24.0f);
  ImFont *pProggy16    = GUI.addFontFromFileTTF("../../media/ProggyClean.ttf",     16.0f);
  ImFont *pProggy24    = GUI.addFontFromFileTTF("../../media/ProggyClean.ttf",     24.0f);

  /// **********************************************************************
  /// Step 2 - Compile all loaded fonts to a single texture and load it to the GPU memory
  /// **********************************************************************
  GUI.compileFonts();

  // Start main loop
  while(pDevice->run())
  {
    pDriver->beginScene(true, true, irr::video::SColor(255,100,101,140));

    GUI.startGUI();

    // create first window with picture sources
    if (IsFirstLoop)
    {
      ImGui::SetNextWindowPos(ImVec2(20.0f, 20.0f));
    }
    ImGui::Begin("Picture sources");
    ImGui::Text("Background picture from Manuel Tellur / pixelio.de (Image-ID: 642831)");
    ImGui::Text("Moon (Phobos) texture from http://nasa3d.arc.nasa.gov");
    if (ImGui::Button("Exit", ImVec2(40, 20)))
    {
      pDevice->closeDevice();
    }
    ImGui::End();

    // create second window with some control inputs
    if (IsFirstLoop)
    {
      ImGui::SetNextWindowPos(ImVec2(20.0f, 200.0f));
      ImGui::SetNextWindowSize(ImVec2(400.0f, 260.0f));
    }

    /// **********************************************************************
    /// Step 3 - Use PushFont()/PopFont() to switch between different Fonts
    /// **********************************************************************
    ImGui::Begin("Different Fonts");
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


    pSceneManager->drawAll();
    GUI.drawAll();

    pDriver->endScene();

    u32 const Time = pDevice->getTimer()->getRealTime();
    u32 const DeltaTime = Time - LastTime;
    if (DeltaTime > 0)
    {
      Rotation += (360.0f * RotPerSec) * (DeltaTime / 1000.0f);

      LastTime = Time;
    }
    pMoon->setRotation(irr::core::vector3df(0,Rotation,0));

    s32 const FPS = pDriver->getFPS();
    if (FPS != LastFPS)
    {
      LastFPS = FPS;
      core::stringw TempString = L"Using different fonts with IMGUI - FPS: ";
      TempString += LastFPS;
      pDevice->setWindowCaption(TempString.c_str());
    }

    IsFirstLoop = false;
  }

  /// **********************************************************************
  /// (optional) Step 4 - You can free up all font related memory and just
  ///                     load the default Font again by resettings all
  ///                     Font. If you don't do it, the GUI system will do
  ///                     it at shutdown.
  ///                     DO NOT use any loaded Font that have been loaded
  ///                     before.
  /// **********************************************************************
  GUI.resetFonts();

  pDevice->drop();

}

int main(void)
{
  try
  {
    runScene();
  }
  catch(std::exception &rEx)
  {
    std::cout << rEx.what() << std::flush;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
  }

  return 0;
}
