#add a flag to make quiet
MAKEFLAGS += --silent

#the name of the output library
NAME = cthulhu

#the C++ standard to use, should nearly always be C++17
STD = -std=c++17

#the name of the source directory for all code
SOURCE_DIR = Cthulhu

#all C++ source files to compile
DIRS = $(shell find ./$(SOURCE_DIR) -name '*.cpp')

#extra include paths
PATHS = -I./$(SOURCE_DIR)

#find out the compiler, use a shell script because its way simpler
CC = $(shell sh Build/Scripts/GetCC.sh)

BUILD_DIR = Build

#use for debug builds, enables asserts and better error checking
DEBUG_FLAG = -DCTU_DEBUG

#TODO: -arch i386 should only be for clang++
FLAGS = -fno-exceptions -fno-rtti -arch i386

#-fno-builtin -nostdinc -nostdlib

all:
	echo 'Building standard build' && \
	$(CC) $(STD) $(FLAGS) $(PATHS) $(DIRS) -c && \
	make finalize

#enable address sanatizer
#disable all obfusacting optimizations to make debugging easier
#generate all debug code
DEBUG_ARGS = -fsanitize=address -g3 -g 

MOVE = mv *.o $(BUILD_DIR)/Binaries/Objects

debug: 
	echo 'Building debug build' && \
	$(CC) $(STD) $(FLAGS) $(PATHS) $(DIRS) -c $(DEBUG_ARGS) $(DEBUG_FLAG) && \
	make finalize

RELEASE_ARGS = -Ofast 

release:
	echo 'Building release build' && \
	$(CC) $(STD) $(FLAGS) $(PATHS) $(DIRS) -c $(RELEASE_ARGS) && \
	make finalize

STANDALONE_ARGS = -DCTU_STANDALONE

standalone:
	echo 'Building standalone build' && \
	$(CC) $(STD) $(FLAGS) $(PATHS) $(DIRS) -c $(STANDALONE_ARGS) && \
	make finalize

clean:
	rm -rf $(BUILD_DIR)/Binaries/Libraries/Cthulhu/Cthulhu.a && \
	rm -rf $(BUILD_DIR)/Binaries/Objects/Cthulhu/*.o

TEST_NAME = Array.cpp

tests:
	echo 'Running tests' && \
	$(CC) $(STD) $(FLAGS) $(PATHS) $(DEBUG_ARGS) \
	Build/Binaries/Libraries/Cthulhu/Cthulhu.a \
	Programs/Tests/$(TEST_NAME) -o $(NAME).o

finalize:
	echo 'Moving Files to library' && \
	sh Build/Scripts/MakeLibrary.sh

.PHONY: all