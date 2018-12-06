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

#include "../TestMacros.h"

#include <FileSystem/File.h>

using namespace Cthulhu;
namespace FS = Cthulhu::FileSystem;

int main(int argc, const char** argv)
{
    Result<FS::File*, Errno> ResT = FS::Open("./Programs/Tests/Files/test.txt", FS::Mode::ReadText);
    ASSERT_TEST(ResT.Valid());

    auto* FT = ResT.Value();

    ASSERT_TEST(FT->Valid());
    ASSERT_TEST(FT->GetType() == FS::Type::Text);

    String N = FT->Name();

    ASSERT_TEST(FT->Name() == "test.txt");

    delete FT;

    ASSERT_TEST(FS::Exists("./Programs/Tests/Files/goat.txt"));

    Result<FS::File*, Errno> Goat = FS::Open("./Programs/Tests/Files/goat.txt", FS::Mode::ReadText);
    
    const String* S = Goat.Value()->ReadText();

    ASSERT_TEST(S->Equals("goatgoatgoat"));

    ASSERT_TEST(!FS::Exists("Some/Random/Path/File.txt"));

    delete Goat.Value();

    auto ThisBin = FS::Open(argv[0], FS::Mode::ReadBinary);

    ASSERT_TEST(ThisBin.Valid());

    auto Got = ThisBin.Value();
    
    ASSERT_TEST(Got->Valid());

    delete Got;

    FILE* f = fopen("./Programs/Tests/Files/t.txt", "wb");

    fprintf(f, "Yeet");
    fclose(f);

    auto NewFile = FS::Open("./Programs/Tests/Files/temp.txt", FS::Mode::WriteBinary);

    ASSERT_TEST(NewFile.Valid());

    NewFile.Value()->Write({ 0x25, 0x50, 0x55 });

    Errno err = FS::Delete("./Programs/Tests/Files/temp.txt");
    ASSERT_TEST(err == Errno::None);

    Errno erre = FS::Delete("./Programs/Tests/Files/t.txt");
    ASSERT_TEST(erre == Errno::None);

    delete NewFile.Value();

    ASSERT_TEST(!FS::Exists("./Programs/Tests/Files/cache.txt"))
    
    {
        auto CacheFile = FS::Open("./Programs/Tests/Files/cache.txt", FS::Mode::WriteText);
        auto* RealFile = CacheFile.Value();
        RealFile->Write("Some data");
        delete RealFile;

        auto Edited = FS::LastEdited("./Programs/Tests/Files/cache.txt");

        ASSERT_TEST(Edited.Valid());
        U64 Ed = Edited.Value();

        printf("[%llu]\n", Ed);

        ASSERT_TEST(Ed == FS::LastEdited("./Programs/Tests/Files/cache.txt").Value());

        ASSERT_TEST(FS::Delete("./Programs/Tests/Files/cache.txt") == Errno::None);
    }
}