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
  f32 Rotation = 0.0;
  f32 RotPerSec = 0.01f;
  bool IsFirstLoop = true;

  /// **********************************************************************
  /// Step 1 - Load images into Irrlicht
  /// **********************************************************************
  video::IImage * pSoyuz  = pDriver->createImageFromFile("../../media/Soyuz.jpg");
  video::IImage * pSpaceX = pDriver->createImageFromFile("../../media/SpaceX.jpg");

  /// **********************************************************************
  /// Step 2 - Pass images to GUI to load them up into GPU memory
  /// **********************************************************************
  IGUITexture &rSoyuz  = *GUI.createTexture(pSoyuz);
  IGUITexture &rSpaceX = *GUI.createTexture(pSpaceX);

  /// **********************************************************************
  /// Step 3 - Delete temporary memory from Irrlicht
  /// **********************************************************************
  pSoyuz->drop();
  pSpaceX->drop();

  int SpaceShip = -1;
  ImFont * pRussianFont = GUI.addFontFromFileTTF("../../media/azoft-sans.ttf", 14.0f, NULL, GUI.getGlyphRangesCyrillic());
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
      ImGui::SetNextWindowSize(ImVec2(500.0f, 150.0f));
    }
    ImGui::Begin("Picture sources");
    ImGui::Text("Background picture from Manuel Tellur / pixelio.de (Image-ID: 642831)");
    ImGui::Text("Moon (Phobos) texture from http://nasa3d.arc.nasa.gov");
    ImGui::Text("Soyuz image from https://pixabay.com (ID: 67718)");
    ImGui::Text("SpaceX image from https://pixabay.com (ID: 693216)");
    ImGui::Text("Cyrillic font from http://www.fontsquirrel.com/fonts/azoft-sans");
    if (ImGui::Button("Exit", ImVec2(40, 20)))
    {
      pDevice->closeDevice();
    }
    ImGui::End();

    if (IsFirstLoop)
    {
      ImGui::SetNextWindowPos(ImVec2(20.0f, 200.0f));
      ImGui::SetNextWindowSize(ImVec2(400.0f, 300.0f));
    }

    /// **********************************************************************
    /// Step 4 - Use ImGui::Image(...) to show an image from a texture ID
    /// **********************************************************************
    ImGui::Begin("Chose your favorite Spaceship!");
    ImGui::BeginGroup();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY()+60.0f);
    ImGui::RadioButton("#1", &SpaceShip, 0);
    ImGui::EndGroup();
    ImGui::SameLine(0.0f, 10.0f);
    ImGui::Image(rSoyuz, ImVec2(200.0f, 132.0f));
    ImGui::Separator();
    ImGui::BeginGroup();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY()+60.0f);
    ImGui::RadioButton("#2", &SpaceShip, 1);
    ImGui::EndGroup();
    ImGui::SameLine(0.0f, 10.0f);
    ImGui::Image(rSpaceX, ImVec2(200.0f, 132.0f));
    ImGui::End();

    if (IsFirstLoop)
    {
      ImGui::SetNextWindowPos(ImVec2(600.0f, 50.0f));
      ImGui::SetNextWindowSize(ImVec2(300.0f, 250.0f));
    }
    ImGui::Begin("Selection", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders);
    ImGui::SetCursorPosX(ImGui::GetCursorPosX()+42.5f);
    switch(SpaceShip)
    {
      case 0:
        ImGui::Image(rSoyuz, ImVec2(200.0f, 132.0f));
        ImGui::PushFont(pRussianFont);
        ImGui::Text("Союз (Soyuz)");
        ImGui::PopFont();
        ImGui::Bullet();
        ImGui::Text("Build in the 1960s in Russia");
        ImGui::Bullet();
        ImGui::Text("Used until today");
        ImGui::Bullet();
        ImGui::Text("Very robust transportation system");
        break;

      case 1:
        ImGui::Image(rSpaceX, ImVec2(200.0f, 132.0f));
        ImGui::PushFont(pRussianFont);
        ImGui::Text("Dragon");
        ImGui::PopFont();
        ImGui::Bullet();
        ImGui::Text("First usage December 8th, 2010");
        ImGui::Bullet();
        ImGui::Text("Build by SpaceX company from Elon Musk");
        ImGui::Bullet();
        ImGui::Text("Modern transportation system");
        break;
    }
    ImGui::End();

    pSceneManager->drawAll();
    GUI.drawAll();

    pDriver->endScene();

    u32 const Time = pDevice->getTimer()->getRealTime();
    u32 const DeltaTime = Time - LastTime;
    if (DeltaTime > 0)
    {
      Rotation += (360.0f * RotPerSec) / (DeltaTime * 1000.0f);
      LastTime = Time;
    }
    pMoon->setRotation(irr::core::vector3df(0,Rotation,0));
    IsFirstLoop = false;
  }

  /// **********************************************************************
  /// Step 5 - Delete GPU memory used for images
  /// **********************************************************************
  GUI.deleteTexture(&rSoyuz);
  GUI.deleteTexture(&rSpaceX);

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
