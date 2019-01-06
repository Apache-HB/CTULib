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

#include "Core/Collections/Map.h"
#include "Graphics/Types.h"
#include "Graphics/Path.h"
#include "Graphics/Image.h"
#include "Graphics/DrawHandle.h"

#pragma once

namespace Cthulhu::Graphics
{

using Window = struct MacWindow
{
    //impl
    MacWindow(const Dimensions& WindowDimensions, const String& Title = "CthulhuWindow");

    //impl
    void Display();

    void SetDimensions(const Dimensions& NewDimensions);
    Dimensions GetDimensions() const;

    void Resize(const Size NewSize);
    Size GetSize() const;

    void Move(const Point NewLocation);
    Point Location() const;

    String Name() const;
    void Rename(const String& NewName);

    void TriggerRedraw();

    virtual void Draw(DrawHandle& Drawer){}

    virtual void MouseMoved(Event MouseEvent, Point From, Point To){}
    virtual void MouseDown(Event MouseEvent){}
    virtual void MouseUp(Event MouseEvent){}

    virtual void KeyDown(Event KeyEvent){}
    virtual void KeyUp(Event KeyEvent){}

    virtual void MouseEntered(Event MouseEvent){}
    virtual void MouseExited(Event MouseEvent){}

    virtual void WindowMove(){}
    virtual void WindowResize(){}
    virtual void WindowMinimize(){}
    virtual void WindowClose(){}
    virtual void WindowOpen(){}
    virtual void WindowEnterFullscreen(){}
    virtual void WindowExitFullscreen(){}

    virtual void Initialize(){}
    virtual void PreInitialize(){}

    virtual void AnyEvent(){}

    void* Native() const { return Handle; }
private:
    void* Handle;
    Array<Path*> Paths;
    Array<Image*> Images;
};

}




















#if 0

#include "Core/Collections/CthulhuString.h"

#pragma once

namespace Cthulhu::Graphics
{

struct Image;
struct Path;
struct Font;

struct MacWindow
{
    MacWindow();
    MacWindow(const String& Title);
    MacWindow(const Dimensions& Size);

    ~MacWindow();

    void DrawImage(const Image& Img, const Point Location);
    void DrawPath(const Path& InPath, const Point Location);
    void DrawText(const String& Text, const Font& InFont, const Point Location);

    void Hide();
    void Display();
    void HackToFront();

    void Enable();
    void Disable();

    void Rename(const String& NewName);
    String Title() const;

    void SetDimensions(const Dimensions& NewDimensions);
    Dimensions GetDimensions() const;

    void Resize(const Size NewSize);
    Size GetSize() const;

    Point Location() const;
    void Move(const Point NewLocation);

    void SetMinSize(const Size MinSize);
    Size MinSize() const;

    void SetMaxSize(const Size MaxSize);
    Size MaxSize() const;

    virtual void OnMimimize(){}
    virtual void OnMaximize(){}
    virtual void OnEnterFullscreen(){}
    virtual void OnExitFullscreen(){}

    virtual void OnWindowMove(Point Origin, Point NewLocation){}
    virtual void OnClose(){}

    virtual void OnLeftMouseDown(Event MouseEvent){}
    virtual void OnLeftMouseUp(Event MouseEvent){}
    
    virtual void OnRightMouseDown(Event MouseEvent){}
    virtual void OnRightMouseUp(Event MouseEvent){}
    
    virtual void OnOtherMouseDown(Event MouseEvent){}
    virtual void OnOtherMouseUp(Event MouseEvent){}

    virtual void OnMouseMove(Event MouseEvent, Point From, Point To){}

    virtual void PreInitialize(){}
    virtual void PostInitialize(){}

    virtual void Tick(F64 DeltaTime){}

    virtual void OnScroll(Event MouseEvent, Direction ScrollDirection){}

    void* Native() const { return Handle; }
private:
    void* Handle;
};

using Window = MacWindow;

}

#endif