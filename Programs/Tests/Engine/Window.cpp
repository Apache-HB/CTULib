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

#include <Graphics/Graphics.h>
#include <Graphics/Window.h>
#include <Graphics/Path.h>

using namespace Cthulhu;
using namespace Cthulhu::Graphics;

struct MyWindow : public Window
{
    using Super = Window;

    using Super::Super;

    Point MouseLocation = { 0, 0 };

    virtual void MouseDown(Event Evt) override
    {
        
    }

    virtual void MouseUp(Event Evt) override
    {

    }

    virtual void MouseMoved(Event Evt, Point From, Point To) override
    {
        MouseLocation = To;
        TriggerRedraw();
    }

    virtual void KeyDown(Event Evt) override
    {

    }

    virtual void KeyUp(Event Evt) override
    {

    }

    virtual void Draw(DrawHandle& Handle) override
    {
        Path P = MouseLocation;
        P.LineTo(MouseLocation - Point{ 50, 0 });
        P.LineTo(MouseLocation + Point{ 50, 50 });
        P.LineTo(MouseLocation - Point{ 0, 50 });
        P.Close();
        Handle.DrawPath(P);
    }
};

CTU_GRAPHCS_MAIN(Handle, Args)
{
    CTU_GRAPHICS_INIT(Handle);

    auto Wnd = MyWindow({100, 100, 400, 400}, "Yeet");
    Wnd.Display();

    Run([&](MainLoopEvent Event)
    {
        if(Event == MainLoopEvent::Launch)
            printf("Loaded\n");
    });
}
