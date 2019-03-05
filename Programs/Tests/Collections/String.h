#include "Macros.h"

#include <Core/Collections/CthulhuString.h>

using namespace Cthulhu;

void StringTest()
{
    String A = "AA";

    //test == op
    TEST(A == "AA");
    TEST(A != "A");
    TEST(!(A == "AAAAAAAA"));
    TEST(!(A == ""));

    String C;

    //test != op
    TEST(C != "AA");
    TEST(C == "");

    //isempty
    TEST(C.IsEmpty());

    //valid index
    TEST(!A.ValidIndex(5));
    TEST(A.ValidIndex(1));
    //negative numbers issue a compiler warning

    String D(A);

    TEST(D == A);
    TEST(D.Equals(A));
    TEST(D.Len() == 2);
    TEST((bool)D);
    TEST(!(bool)C);

    String B;
    TEST(B.IsEmpty());
    B += "A";
    TEST(B == "A");

    B += 'B';
    TEST(B == "AB");
}