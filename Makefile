NAME = cthulhu.o
STD = -std=c++17

#all C++ code sources
DIRS = $(shell find ./Cthulhu -name '*.cpp')

PATHS = -I./Cthulhu

#if you get an error that looks like
#make: clang++: No such file or directory
#change this to your compiler of choice, (e.g g++)
CC = clang++

FRONT = $(CC) $(STD) $(DIRS) $(PATHS) -c

TESTS = $(shell find ./Programs/Tests -name '*.cpp')

LIB_NAME = cthulhu.a

BUILD_FILE = Build

main:
	#compile everything to object files
	#merge object files into .a archive
	$(FRONT) && make move
	#remove object files

DEBUG_FLAG = -DCTU_DEBUG

unity:
	sh Unity.sh && \
	$(CC) $(STD) $(DIRS) Build/Unity.cpp $(PATHS) $(DEBUG_FLAG) -g3 -fsanitize=address -fno-omit-frame-pointer -g -c

debug:
	$(FRONT) $(DEBUG_FLAG) -g3 -fsanitize=address -fno-omit-frame-pointer -g && make move

release:
	$(FRONT) -O3 && make move

tests:
	#create the binary, compile and run every test, then clean the last test
	make debug && \
	for test in $(TESTS); do $(CC) $(STD) $(PATHS) -fsanitize=address -fno-omit-frame-pointer -I./Programs/Tests $(BUILD_FILE)/$(LIB_NAME) $$test -o Test && ./Test; done; rm -rf Test

clean:
	rm -rf ./Build

setup:
	if [ ! -d "./$(BUILD_FILE)" ]; then mkdir $(BUILD_FILE); fi

move:
	make setup && ar cr $(BUILD_FILE)/$(LIB_NAME) *.o && rm -rf *.o

SUMMON_NAME = summon
SUMMON_PATH = Summon
SUMMON_DIRS = $(shell find ./Programs/Summon -name '*.cpp')

summon:
	if [ ! -d "./$(BUILD_FILE)/$(SUMMON_PATH)" ]; then mkdir $(BUILD_FILE)/$(SUMMON_PATH); fi && \
	make release && $(CC) $(STD) $(PATHS) -I./Programs/Summon $(BUILD_FILE)/$(LIB_NAME) $(SUMMON_DIRS) -o $(BUILD_FILE)/$(SUMMON_PATH)/$(SUMMON_NAME)