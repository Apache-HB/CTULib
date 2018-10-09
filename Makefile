NAME = cthulhu
STD = -std=c++17

#all C++ code sources
DIRS = $(shell find ./Source -name '*.cpp')

PATHS = -I ./Source/Core -I ./Source

#if you get an error that looks like
#make: clang++: No such file or directory
#change this to your compiler of choice, (e.g g++)
CC = clang++

FRONT = $(CC) $(STD) $(DIRS) $(PATHS)

main:
	$(FRONT)

debug:
	$(FRONT) -g3 -fsanitize=address -g

release:
	$(FRONT) -O3 -g