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

  scene::ISceneNode    * const pMainScreen   = pSceneManager->addEmptySceneNode();
  scene::ISceneNode    * const pMoonScreen   = pSceneManager->addEmptySceneNode();

  pDriver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
  irr::scene::ISceneNode * const pSkybox = pSceneManager->addSkyBoxSceneNode(
      pDriver->getTexture("../../media/Background.jpg"),
      pDriver->getTexture("../../media/Background.jpg"),
      pDriver->getTexture("../../media/Background.jpg"),
      pDriver->getTexture("../../media/Background.jpg"),
      pDriver->getTexture("../../media/Background.jpg"),
      pDriver->getTexture("../../media/Background.jpg"),
      pMainScreen);
  pDriver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);

  // Create Planet object
  scene::IMeshSceneNode * const pMoon = pSceneManager->addSphereSceneNode(5.0f, 128, pMoonScreen);
  FASSERT(pMoon);
  pMoon->setPosition(irr::core::vector3df(0,0,25));
  pMoon->setMaterialTexture(0, pDriver->getTexture("../../media/Phobos.jpg"));
  pMoon->setMaterialFlag(irr::video::EMF_LIGHTING, false);

  // Add camera object
  irr::scene::ICameraSceneNode * const pMainCam = pSceneManager->addCameraSceneNode(pMainScreen, core::vector3df(0, 0, 0), core::vector3df(0,0,5));
  irr::scene::ICameraSceneNode * const pMoonCam = pSceneManager->addCameraSceneNode(pMoonScreen, core::vector3df(0, 0,15), core::vector3df(0,0,25));

  u32 LastTime = pDevice->getTimer()->getRealTime();
  f32 Rotation = 0.0;
  f32 RotPerSec = 0.01f;
  bool IsFirstLoop = true;
  int RotationDirection = 1;
  f32 Color[3] = {0.0f/256.0f, 43.0f/256.0f, 56.0f/256.0f};

  // Prepare double rendering
  video::ITexture * const pRenderTarget = pDriver->addRenderTargetTexture(core::dimension2d<u32>(384, 300), "Moon");
  IGUITexture * const pRenderTextureID  = GUI.createTexture(pRenderTarget);

  // Start main loop
  while(pDevice->run())
  {
    pDriver->beginScene(true, true, irr::video::SColor(255,100,101,140));

    // ****************************
    // Render Moon Scene
    // ****************************
    pDriver->setRenderTarget(pRenderTarget, true, true, video::SColor(255,(u32)(Color[0]*255.0f),(u32)(Color[1]*255.0f),(u32)(Color[2]*255.0f)));
    pMoonScreen->setVisible(true);
    pMainScreen->setVisible(false);
    pSceneManager->setActiveCamera(pMoonCam);

    pSceneManager->drawAll();

    pDriver->setRenderTarget(0, true, true, video::SColor(255,100,101,140));

    // ****************************
    // Render Main Scene
    // ****************************
    pMoonScreen->setVisible(false);
    pMainScreen->setVisible(true);
    pSceneManager->setActiveCamera(pMainCam);

    GUI.startGUI();

    // create first window with picture sources
    if (IsFirstLoop)
    {
      ImGui::SetNextWindowPos(ImVec2(20.0f, 20.0f));
      ImGui::SetNextWindowSize(ImVec2(500.0f, 100.0f));
    }
    ImGui::Begin("Picture sources");
    ImGui::Text("Background picture from Manuel Tellur / pixelio.de (Image-ID: 642831)");
    ImGui::Text("Moon (Phobos) texture from http://nasa3d.arc.nasa.gov");
    if (ImGui::Button("Exit", ImVec2(40, 20)))
    {
      pDevice->closeDevice();
    }
    ImGui::End();

    GUI.updateTexture(pRenderTextureID, pRenderTarget);

    if (IsFirstLoop)
    {
      ImGui::SetNextWindowPos(ImVec2(300.0f, 200.0f));
      ImGui::SetNextWindowSize(ImVec2(400.0f, 450.0f));
    }
    ImGui::Begin("Moon Window", NULL, ImGuiWindowFlags_ShowBorders);
    ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
    ImGui::Image(*pRenderTextureID, ImVec2(384, 300));
    ImGui::BeginGroup();
    ImGui::RadioButton("Left",  &RotationDirection, 1);
    ImGui::RadioButton("Stop",  &RotationDirection, 0);
    ImGui::RadioButton("Right", &RotationDirection, -1);
    ImGui::EndGroup();
    ImGui::SameLine(0.0f, 10.0f);
    ImGui::BeginGroup();
    ImGui::SliderFloat("Speed", &RotPerSec, 0.001f, 0.5f);
    ImGui::SliderFloat("Angle",     &Rotation,  0.0f, 360.0f);
    ImGui::ColorEdit3("Color", Color);
    ImGui::EndGroup();
    ImGui::End();

    pSceneManager->drawAll();
    GUI.drawAll();

    pDriver->endScene();

    u32 const Time = pDevice->getTimer()->getRealTime();
    u32 const DeltaTime = Time - LastTime;
    if (DeltaTime > 0)
    {
      Rotation += (360.0f * RotPerSec * ((float)RotationDirection)) * (DeltaTime / 1000.0f);
      if (Rotation > 360.0f)
      {
        Rotation -= 360.0f;
      }
      else if (Rotation < 0.0f)
      {
        Rotation += 360.0f;
      }
      LastTime = Time;
    }
    pMoon->setRotation(irr::core::vector3df(0,Rotation,0));
    IsFirstLoop = false;
  }

  GUI.deleteTexture(pRenderTextureID);
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
