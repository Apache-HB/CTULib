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

#pragma once

#include "Internal/Button.h"
#include "Graphics/Types.h"
#include "Image.h"

namespace Cthulhu::Graphics
{

using Button = struct MacButton
{
    MacButton();
    virtual void BeginHover(Event& Evt) {}
    virtual void EndHover(Event& Evt) {}
    
    virtual void MouseUp(Event& Evt) {}
    virtual void MouseDown(Event& Evt) {}

    void Resize(const Size& NewSize);
    Size GetSize() const;

    void Move(const Point& NewLocation);
    Point Location() const;

    void SetDimensions(const Dimensions& NewDimensions);
    Dimensions GetDimensions() const;

    void SetText(const String& Text);
    const String& GetText() const;

    void SetImage(const Image& NewImage);
    const Image& GetImage() const;

    void* Native() const { return Handle; }
private:
    void* Handle;
};

}