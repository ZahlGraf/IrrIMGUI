# Welcome to the %IrrIMGUI project
# Welcome to the %IrrIMGUI project

 * **Visit the GitHub repository:** [Repository](https://github.com/ZahlGraf/IrrIMGUI)
 * **Screenshots:** [Example Pictures](https://github.com/ZahlGraf/IrrIMGUI#ExampleImages)
 * **Download this library:** [Download](https://github.com/ZahlGraf/IrrIMGUI#Download)
 * **HowTo build this library:** [Build process](https://github.com/ZahlGraf/IrrIMGUI#HowToStart_Preparations)
 * **Online API documentation:** [Doxygen](http://zahlgraf.github.io/IrrIMGUI/index.html)
 * **Example description:** [Examples](https://github.com/ZahlGraf/IrrIMGUI/wiki/Example-1:-Hello-World)

# %IrrIMGUI API documentation

## Index

 * [Most Important API Bookmarks](#MostImportantBookmarks)
 
 * [Code Snippets](#ShortUsageReference)
 
  * [Getting started](#ShortUsageReferenceGettingStarted)
    * [Step 1: Include Header Files](#ShortUsageReferenceGettingStartedStep1)
    * [Step 2: Initialize Irrlicht Device and GUI](#ShortUsageReferenceGettingStartedStep2)
    * [Step 3: Start GUI Frame](#ShortUsageReferenceGettingStartedStep3)
    * [Step 4: Render GUI](#ShortUsageReferenceGettingStartedStep4)
	
  * [Use custom Event Receiver](#ShortUsageReferenceCustomEventReceiver)
    * [Method 1: Inherit from standard Event Receiver](#ShortUsageReferenceCustomEventReceiverMethod1)
    * [Method 2: An Event Receiver from the scratch](#ShortUsageReferenceCustomEventReceiverMethod2)
	
  * [Use TTF fonts](#ShortUsageReferenceFonts)
    * [Step 1: Load Fonts](#ShortUsageReferenceFontsStep1)
    * [Step 2: Compile Fonts](#ShortUsageReferenceFontsStep2)
    * [Step 3: Activate a Font](#ShortUsageReferenceFontsStep3)
    * [Optional: Reset Fonts](#ShortUsageReferenceFontsOptional)
	
  * [Use images](#ShortUsageReferenceImages)
    * [Step 1: Create Irrlicht Image](#ShortUsageReferenceImagesStep1)
    * [Step 2: Create GUI Texture](#ShortUsageReferenceImagesStep2)
    * [Step 3: Use image in GUI](#ShortUsageReferenceImagesStep3)
    * [Step 4: Free-up image memory](#ShortUsageReferenceImagesStep4)  

  * [Use Irrlicht textures](#ShortUsageReferenceTextures)
    * [Step 1: Create GUI Texture](#ShortUsageReferenceTexturesStep1)
    * [Optional: Update GUI Texture](#ShortUsageReferenceTexturesOptional)
    * [Step 2: Free-up GUI texture memory](#ShortUsageReferenceImagesStep2)  
	
 * [Additional Project Links](#AdditionalLinks)
 
## <a name="MostImportantBookmarks"></a> Most Important API Bookmarks
 
 * Class IrrIMGUI::CIMGUIHandle - Use this class as main handle to the Irrlicht IMGUI Binding
 * Class IrrIMGUI::CIMGUIEventReceiver - A standard Event Receiver for Irrlicht, that passes all Mouse and Keyboard events to the GUI
 * Class IrrIMGUI::IGUITexture - A general texture object for drawing images to the GUI
 
## <a name="ShortUsageReference"></a> Code Snippets 
 
### <a name="ShortUsageReferenceGettingStarted"></a> Getting started

**Full explanation:** [Example 1: HelloWorld](https://github.com/ZahlGraf/IrrIMGUI/wiki/Example-1:-Hello-World)

#### <a name="ShortUsageReferenceGettingStartedStep1"></a> Step 1: Include header files

```cpp
// include Irrlicht and IrrIMGUI header
#include <IrrIMGUI/IrrIMGUI.h>
#include <IrrIMGUI/IncludeIrrlicht.h>
```


#### <a name="ShortUsageReferenceGettingStartedStep2"></a> Step 2: Initialize Irrlicht Device and GUI

```cpp
  using namespace irr;
  using namespace IrrIMGUI;

  // Irrlicht OpenGL Settings
  SIrrlichtCreationParameters IrrlichtParams;
  IrrlichtParams.DriverType    = video::EDT_OPENGL;
  IrrlichtParams.WindowSize    = core::dimension2d<u32>(1024, 800);
  IrrlichtParams.Bits          = 32;
  IrrlichtParams.Fullscreen    = false;
  IrrlichtParams.Stencilbuffer = true;
  IrrlichtParams.AntiAlias     = 16;
  IrrlichtParams.Vsync         = false;
  
  // Create standard event receiver for the IrrIMGUI
  CIMGUIEventReceiver EventReceiver;  
  IrrlichtParams.EventReceiver = &EventReceiver;

  // Create Irrlicht device
  IrrlichtDevice * const pDevice = createDeviceEx(IrrlichtParams);
  
  // Create GUI object
  CIMGUIHandle GUI(pDevice, &EventReceiver);
```

#### <a name="ShortUsageReferenceGettingStartedStep3"></a> Step 3: Start GUI Frame
Inside the Main-Loop:
```cpp
	// create the GUI elements
    GUI.startGUI();
    ImGui::Begin("My first Window");
    ImGui::Text("Hello World!");
    if (ImGui::Button("Exit", ImVec2(40, 20)))
    {
      pDevice->closeDevice();
    }
    ImGui::End();
```


#### <a name="ShortUsageReferenceGettingStartedStep4"></a> Step 4: Render GUI
Inside the Main-Loop:
```cpp
	// render your Irrlicht scene
    pSceneManager->drawAll();
	
	// render the GUI
    GUI.drawAll();
```

	
### <a name="ShortUsageReferenceCustomEventReceiver"></a> Use custom Event Receiver
#### <a name="ShortUsageReferenceCustomEventReceiverMethod1"></a> Method 1: Inherit from standard Event Receiver

* Inherit from the IrrIMGUI::CIMGUIEventReceiver class
* Overwrite method IrrIMGUI::CIMGUIEventReceiver::OnEvent to handle the event first
```cpp
class CMyOwnEventReceiver : private IrrIMGUI::CIMGUIEventReceiver
{
  bool OnEvent(const irr::SEvent & rEvent)
  {
    // do your own stuff with rEvent...
	
    // when rEvent has not been consumed by your game logic pass it to the CIMGUIEventReceiver class
    return CIMGUIEventReceiver::OnEvent(rEvent);
  }
};
```

* Don't forget to call IrrIMGUI::CIMGUIEventReceiver::OnEvent when you want to pass this Event to the GUI
* Give a pointer of this custom Event Receiver while creating the GUI handle object and the Irrlicht Device

#### <a name="ShortUsageReferenceCustomEventReceiverMethod2"></a> Method 2: An Event Receiver from the scratch

* Create an Event Receiver class that inherits from `irr::IEventReceiver` and IrrIMGUI::CIMGUIEventStorage
* Overwrite the `irr::IEventReceiver::OnEvent` method to handle the event
* If you want to pass any input event information to the GUI, just write to the corresponding variables of IrrIMGUI::CIMGUIEventStorage
* Give a pointer of this custom Event Receiver while creating the GUI handle object and the Irrlicht Device
	
### <a name="ShortUsageReferenceFonts"></a> Use TTF fonts

**Full explanation:** [Example 2: Different Fonts](https://github.com/ZahlGraf/IrrIMGUI/wiki/Example-3:-Different-Fonts)

#### <a name="ShortUsageReferenceFontsStep1"></a> Step 1: Load Fonts

```cpp
// load the Cousine-Regular.ttf file from the media directory
ImFont *pCousine16 = GUI.addFontFromFileTTF("../../media/Cousine-Regular.ttf", 16.0f);
ImFont *pCousine24 = GUI.addFontFromFileTTF("../../media/Cousine-Regular.ttf", 24.0f);
```
* Hint: Look-up for further methods to load fonts in the GUI Handle class ( @ref LoadFonts )

#### <a name="ShortUsageReferenceFontsStep2"></a> Step 2: Compile Fonts

```cpp
GUI.compileFonts();
```

#### <a name="ShortUsageReferenceFontsStep3"></a> Step 3: Activate a Font

Inside the Main-Loop:
```cpp
    ImGui::Begin("Different Fonts", NULL, ImGuiWindowFlags_ShowBorders);
    ImGui::Text("Default Font");

	/// activate Cousine-Regular 16px font
    ImGui::PushFont(pCousine16);
    ImGui::Text("Cousine-Regular.ttf; 16px");
    ImGui::PopFont(); // switch back to last font (in this case default)

	/// activate Cousine-Regular 24px font
    ImGui::PushFont(pCousine24);
    ImGui::Text("Cousine-Regular.ttf; 24px");
    ImGui::PopFont(); // switch back to last font (in this case default)

    ImGui::End();
```

#### <a name="ShortUsageReferenceFontsOptional"></a> Optional: Reset Fonts

```cpp
GUI.resetFonts();
```
	
### <a name="ShortUsageReferenceImages"></a> Use images

**Full explanation:** [Example 4: Using Images](https://github.com/ZahlGraf/IrrIMGUI/wiki/Example-4:-Using-Images)

#### <a name="ShortUsageReferenceImagesStep1"></a> Step 1: Create Irrlicht Image

```cpp
irr::video::IVideoDriver * const pDriver = pDevice->getVideoDriver();

irr::video::IImage * pSoyuz  = pDriver->createImageFromFile("../../media/Soyuz.jpg");
irr::video::IImage * pSpaceX = pDriver->createImageFromFile("../../media/SpaceX.jpg");
``` 

#### <a name="ShortUsageReferenceImagesStep2"></a> Step 2: Create GUI Texture

```cpp
 IrrIMGUI::IGUITexture * pSoyuzTex  = GUI.createTexture(pSoyuz);
 IrrIMGUI::IGUITexture * pSpaceXTex = GUI.createTexture(pSpaceX);
```

* Hint: Look-up for further methods to create textures in the GUI Handle class ( @ref CreateTextures )

#### <a name="ShortUsageReferenceImagesStep3"></a> Step 3: Use image in GUI

Inside the Main-Loop:
```cpp
    ImGui::Begin("Images");

    ImGui::Image(pSoyuzTex, ImVec2(200.0f, 132.0f));

    ImGui::Separator();

    ImGui::Image(pSpaceXTex, ImVec2(200.0f, 132.0f));

    ImGui::End();
```

#### <a name="ShortUsageReferenceImagesStep4"></a> Step 4: Free-up image memory 

```cpp
  pSoyuz->drop();
  pSpaceX->drop();
  GUI.deleteTexture(pSoyuzTex);
  GUI.deleteTexture(pSpaceXTex);
```

### <a name="ShortUsageReferenceTextures"></a> Use Irrlicht textures

**Full explanation:** [Example 4: Using Images](https://github.com/ZahlGraf/IrrIMGUI/wiki/Example-4:-Using-Images)

#### <a name="ShortUsageReferenceTexturesStep1"></a> Step 1: Create GUI Texture

```cpp
  // Create Render Target texture in Irrlicht
  video::ITexture * const pRenderTarget = pDriver->addRenderTargetTexture(core::dimension2d<u32>(384, 300), "Moon");
  
  // create GUI Texture handle
  IGUITexture * const pRenderTextureID  = GUI.createTexture(pRenderTarget);
```

* Hint: Look-up for further methods to create textures in the GUI Handle class ( @ref CreateTextures )

#### <a name="ShortUsageReferenceTexturesOptional"></a> Optional: Update GUI Texture

Inside the Main-Loop:
```cpp
    GUI.updateTexture(pRenderTextureID, pRenderTarget);
```

#### <a name="ShortUsageReferenceImagesStep2"></a> Step 2: Free-up GUI texture memory

```cpp
  GUI.deleteTexture(pRenderTextureID);
```

### <a name="AdditionalLinks"></a> Additional Project Links

* [IMGUI GitHub Project](https://github.com/ocornut/imgui)
* [IMGUI Wiki](https://github.com/ocornut/imgui/wiki)
* [Irrlicht Project](http://irrlicht.sourceforge.net/)
* [Irrlicht Tutorials](http://irrlicht.sourceforge.net/tutorials/)
* [Irrlicht API](http://irrlicht.sourceforge.net/docu/)
* [Irrlicht Wiki](http://irrlicht3d.org/wiki/)