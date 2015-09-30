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
  //IrrlichtParams.DriverType    = video::EDT_DIRECT3D9;
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
  CIMGUIHandle * const pGUI = new CIMGUIHandle(pDevice, &EventReceiver);

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

  video::IImage * const pSoyuzImage  = pDriver->createImageFromFile("../../media/Soyuz.jpg");
  video::IImage * const pSpaceXImage = pDriver->createImageFromFile("../../media/SpaceX.jpg");

  IGUITexture &rSoyuz  = *pGUI->createTexture(pSoyuzImage);
  IGUITexture &rSpaceX = *pGUI->createTexture(pSpaceXImage);

  pSoyuzImage->drop();
  pSpaceXImage->drop();

  int SpaceShip = -1;
  int DraggedSpaceShip = -1;
  int HoveredSpaceShip = -1;
  ImFont * pRussianFont = pGUI->addFontFromFileTTF("../../media/azoft-sans.ttf", 14.0f, NULL, pGUI->getGlyphRangesCyrillic());
  pGUI->compileFonts();

  // Start main loop
  while(pDevice->run())
  {
    pDriver->beginScene(true, true, irr::video::SColor(255,100,101,140));

    pGUI->startGUI();

    // create first window with picture sources
    if (IsFirstLoop)
    {
      ImGui::SetNextWindowPos(ImVec2(20.0f, 20.0f));
      ImGui::SetNextWindowSize(ImVec2(500.0f, 150.0f));
    }
    ImGui::Begin("Picture sources", NULL, ImGuiWindowFlags_ShowBorders);
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
      ImGui::SetNextWindowSize(ImVec2(222.0f, 366.0f));
    }

    if (HoveredSpaceShip != -1)
    {
      ImGui::Begin("Available Ships", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_ShowBorders);
    }
    else
    {
      ImGui::Begin("Available Ships", NULL, ImGuiWindowFlags_ShowBorders);
    }
    ImGui::Text("Drag your favorite");
    ImGui::Text("Space Ship into the");
    ImGui::Text("empty Window!");
    HoveredSpaceShip = -1;
    ImGui::Image(rSoyuz, ImVec2(200.0f, 132.0f));
    if (ImGui::IsItemHovered())
    {
      HoveredSpaceShip = 0;
    }
    ImGui::Separator();
    ImGui::Image(rSpaceX, ImVec2(200.0f, 132.0f));
    if (ImGui::IsItemHovered())
    {
      HoveredSpaceShip = 1;
    }

    if (ImGui::IsMouseDragging(0))
    {
      if (DraggedSpaceShip == -1)
      {
        DraggedSpaceShip = HoveredSpaceShip;
      }
    }

    if (DraggedSpaceShip != -1)
    {
      ImVec2 DraggablePos(ImGui::GetMousePos().x - 50.0f,ImGui::GetMousePos().y - 33.0f);
      switch(DraggedSpaceShip)
      {
        case 0:
          ImGui::SetNextWindowPos(DraggablePos);
          ImGui::Begin("DraggedSoyuz", NULL,
              ImGuiWindowFlags_NoTitleBar |
              ImGuiWindowFlags_NoResize |
              ImGuiWindowFlags_NoMove |
              ImGuiWindowFlags_NoScrollbar |
              ImGuiWindowFlags_NoScrollWithMouse |
              ImGuiWindowFlags_NoCollapse |
              ImGuiWindowFlags_AlwaysAutoResize |
              ImGuiWindowFlags_ShowBorders |
              ImGuiWindowFlags_NoSavedSettings |
              ImGuiWindowFlags_NoInputs
          );
          ImGui::Image(rSoyuz, ImVec2(100.0f, 66.0f));
          ImGui::End();
          break;
        case 1:
          ImGui::SetNextWindowPos(DraggablePos);
          ImGui::Begin("DraggedSoyuz", NULL,
              ImGuiWindowFlags_NoTitleBar |
              ImGuiWindowFlags_NoResize |
              ImGuiWindowFlags_NoMove |
              ImGuiWindowFlags_NoScrollbar |
              ImGuiWindowFlags_NoScrollWithMouse |
              ImGuiWindowFlags_NoCollapse |
              ImGuiWindowFlags_AlwaysAutoResize |
              ImGuiWindowFlags_ShowBorders |
              ImGuiWindowFlags_NoSavedSettings |
              ImGuiWindowFlags_NoInputs
          );
          ImGui::Image(rSpaceX, ImVec2(100.0f, 66.0f));
          ImGui::End();
          break;
      }
    }

    ImGui::End();

    if (IsFirstLoop)
    {
      ImGui::SetNextWindowPos(ImVec2(600.0f, 50.0f));
      ImGui::SetNextWindowSize(ImVec2(300.0f, 250.0f));
    }
    ImGui::Begin("Selection", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders);

    if (!ImGui::IsMouseDragging(0))
    {
      if ((DraggedSpaceShip != -1) && ImGui::IsWindowHovered())
      {
        SpaceShip = DraggedSpaceShip;
        DraggedSpaceShip = -1;
      }
      else
      {
        DraggedSpaceShip = -1;
      }
    }

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
    pGUI->drawAll();

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
      core::stringw TempString = L"A quick and dirty Drag'n Drop implementation - FPS: ";
      TempString += LastFPS;
      pDevice->setWindowCaption(TempString.c_str());
    }

    IsFirstLoop = false;
  }

  pGUI->deleteTexture(&rSoyuz);
  pGUI->deleteTexture(&rSpaceX);

  delete(pGUI);
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
  }

  return 0;
}
