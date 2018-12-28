/**   Copyright 2018 Elliot Haisley Brown
 *
 *  Licensed under the (modified) Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      https://github.com/Apache-HB/CTULib/blob/master/LICENSE
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "Graphics/Types.h"
#include "Core/Collections/Array.h"

#pragma once

namespace Cthulhu::Graphics
{

struct MacView;

struct MacWindow
{
    MacWindow();
    MacWindow(const String& WindowTitle);
    MacWindow(const Dimensions& WindowDimensions);

    void SetTitle(const String& NewTitle);
    String Title() const;

    void Resize(const Size NewSize);
    Size GetSize() const;

    void Move(const Point NewLocation);
    Point Location() const;

    void SetDimensions(const Dimensions& NewDimensions);
    Dimensions GetDimensions() const;

    void SetView(MacView* NewView);
    MacView* GetView() const;
    
    void Display();
    void Hide();

    void Miniaturize();
    void Deminiaturize();

    void Close();

    void OnDeminiaturize(Lambda<void()> Function);
    void OnMiniaturize(Lambda<void()> Function);

    void OnClose(Lambda<void()> Function);
    void OnResize(Lambda<void()> Function);

    void* Native() const;
public:
    Lambda<void()> DeminiaturizeCallback = []{};
    Lambda<void()> MiniaturizeCallback = []{};

    Lambda<void()> OnCloseCallback = []{};
    Lambda<void()> OnResizeCallback = []{};

public:

    MacView* View = nullptr;
    void* Handle = nullptr;
};

void Run(Lambda<void()> Callback);

using Window = MacWindow; 

}
