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

#include "Meta/Aliases.h"
#include "Core/Collections/CthulhuString.h"

#pragma once

namespace Cthulhu
{

/**
 * @brief mirrors the cstdlib errno #defines
 * 
 * @description identical to the lists from <a href="http://www.virtsync.com/c-error-codes-include-errno">Virtsync.com</a>
 * 
 */
enum class Errno : U8
{
    None                    = 0,
    NotPermitted            = 1,
    FileNotFound            = 2,
    NoProccess              = 3,
    InterruptedSystemCall   = 4,
    IOError                 = 5,
    NoDeviceOrAddress       = 6,
    ArgsToLong              = 7,
    ExecFormatError         = 8,
    BadFileNumber           = 9,
    NoChildProccess         = 10,
    TryAgain                = 11,
    OutOfMemory             = 12,
    PermissionDenied        = 13,
    BadAddress              = 14,
    BlockDeviceRequired     = 15,
    Busy                    = 16,
    FileExists              = 17,
    DeviceLink              = 18,
    NoDevice                = 19,
    NotADir                 = 20,
    IsADir                  = 21,
    InvalidArg              = 22,
    FileTableOverflow       = 23,
    TooManyOpenFiles        = 24,
    NotATypewriter          = 25,
    FileBusy                = 26,
    FileTooBig              = 27,
    NoSpaceLeft             = 28,
    IllegalSeek             = 29,
    ReadOnlyFile            = 30,
    TooManyLinks            = 31,
    BrokenPipe              = 32,
    Domain                  = 33,
    Range                   = 34,
    Deadlock                = 35,
    NameTooLong             = 36,
    Locks                   = 37,
    NotImplemented          = 38,
    DirNotEmpty             = 39,
    SymbolicLinks           = 40,
    WouldBlock              = 41,
    MessageType             = 42,
    IdentRemoved            = 43,
    ChannelRange            = 44,
    Level2Sync              = 45,
    Level3Halt              = 46,
    Level3Reset             = 47,
    NumberOutOfRange        = 48,
    NotAttatched            = 49,
    CSIStructure            = 50,
    Level2Halt              = 51,
    InvalidExchange         = 52,
    InvalidRequest          = 53,
    ExchangeFull            = 54,
    Anode                   = 55,
    RequestCode             = 56,
    InvalidSlot             = 57,
    BadFont                 = 59,
    NotAStream              = 60,
    NoData                  = 61,
    TimerExpired            = 62,
    StreamResource          = 63,
    NoNetwork               = 64,
    NoPackage               = 65,
    RemoteObject            = 66,
    SeveredLink             = 67,
    AdvertiseError          = 68,
    MountError              = 69,
    SendError               = 70,
    Protocol                = 71,
    MultiHop                = 72,
    RFSError                = 73,
    DataMessage             = 74,
    TooLarge                = 75,
    NotUnique               = 76,
    BadFileDescriptor       = 77,
    RemoteAddressChanged    = 78,
    SharedAccess            = 79,
    CorruptedLib            = 80,
    CorruptedLibInExec      = 81,
    TooManyLibs             = 82,
    SharedExec              = 83,
    IllegalByte             = 84,
    SyscallRestart          = 85,
    PipeError               = 86,
    TooManyUsers            = 87,
    NotASocket              = 88,
    NoDestination           = 89,
    MessageLength           = 90,
    WrongSocketType         = 91,
    NotAvailable            = 92,
    NotSupported            = 93,
    SocketNotSupported      = 94,
    TransportNotSupported   = 95,
    ProtocolNotSupported    = 96,
    AddressNotSupported     = 97,
    AddressInUse            = 98,
    CannotAssign            = 99,
    NetworkDown             = 100,
    NetowrkUnreachable      = 101,
    DroppedNetwork          = 102,
    ConnectionAbort         = 103,
    ConnectionReset         = 104,
    NoBufferSpace           = 105,
    AlreadyConnected        = 106,
    NotConnected            = 107,
    EndpointShutdown        = 108,
    ToManyRefs              = 109,
    TimedOut                = 110,
    ConnectionRefused       = 111,
    HostDown                = 112,
    NoRoute                 = 113,
    AlreadyInProgress       = 114,
    InProgress              = 115,
    StaleFile               = 116,
    DirtyStructure          = 117,
    NotXENIX                = 118,
    NoSemaphore             = 119,
    IsAFileType             = 120,
    RemoteIO                = 121,
    QuoteExceeded           = 122,
    NoMedium                = 123,
    WrongMedium             = 124,
    OperationCancelled      = 125,
    KeyNotAvailable         = 126,
    ExpiredKey              = 127,
    RevokedKey              = 128,
    RejectedKey             = 129,
    OwnerDied               = 130,
    NotRecoverable          = 131,
};

/**
 * @brief Turn an Errno into a string to print
 * 
 * @param Err The errno to turn into a string
 * @return String the errno as a string
 */
String ToString(Errno Err);

}