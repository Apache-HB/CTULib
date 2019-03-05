#pragma once

#include <stdio.h>

#define TEST(EXPR) if(!(EXPR)) printf("Test failed at [%s:%d] %s", __FILE__, __LINE__, #EXPR "\n");