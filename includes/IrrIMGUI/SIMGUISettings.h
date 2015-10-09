/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015-2016 Andre Netzeband
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
 */
/**
 * @file       SIMGUISettings.h
 * @author     Andre Netzeband
 * @brief      A storage the settings of the IMGUI.
 * @addtogroup IrrIMGUI
 */

#ifndef IRRIMGUI_INCLUDE_IRRIMGUI_SIMGUISETTINGS_H_
#define IRRIMGUI_INCLUDE_IRRIMGUI_SIMGUISETTINGS_H_

// module includes
#include "IrrIMGUIConfig.h"

/**
 * @addtogroup IrrIMGUI
 * @{
 */

namespace IrrIMGUI
{

  /// @brief Stores the settings of the IMGUI.
  struct IRRIMGUI_DLL_API SIMGUISettings
  {
    public:

      /// @brief Constructor to set the standard settings.
      SIMGUISettings(void):
        mIsGUIMouseCursorEnabled(true)
      {}

      /// @{
      /// @name Settings

      /// @brief When this is true, the IMGUI draws it's own mouse courser and the system mouse cursor will turned off automatically (default: true).
      bool mIsGUIMouseCursorEnabled;

      /// @}

      bool operator==(SIMGUISettings const &rCompareSettings)
      {
        bool AreAllSettingsEqual = true;

        AreAllSettingsEqual = AreAllSettingsEqual && (mIsGUIMouseCursorEnabled == rCompareSettings.mIsGUIMouseCursorEnabled);

        return AreAllSettingsEqual;
      }
  };
}

/**
 * @}
 */

#endif /* IRRIMGUI_INCLUDE_IRRIMGUI_SIMGUISETTINGS_H_ */
