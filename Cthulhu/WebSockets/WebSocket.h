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

#include "Core/Collections/CthulhuString.h"
#include "Core/Types/Lambda.h"
#include "Core/Threading/Thread.h"
#include "Core/Threading/Mutex.h"

#pragma once

namespace Cthulhu
{

namespace WebSockets
{

enum class ReadyState : char
{
    Connecting,
    Open,
    Closing,
    Closed
};

enum class MessageType : char
{
    Message,
    Open,
    Close,
    Error
};

struct ErrorInfo
{
    uint64 Retries;
    double WaitTime;
    int HttpStatus;
    String Reson;
};

struct Socket
{
    Socket(const String& Url);
    ~Socket();

    void Start();
    void Stop();
    void Close();
    bool Send(const String& Text);

    void ChangeUrl(const String& Url);

    void OnMessage(Lambda<void(MessageType, const String&, ErrorInfo)> Callback);

private:
    Mutex WriteMutex;
    Thread RunnerThread;
};

}

}