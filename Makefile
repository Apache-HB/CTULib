NAME = cthulhu.o
STD = -std=c++17

#all C++ code sources
DIRS = $(shell find ./Source -name '*.cpp')

PATHS = -I./Source

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

debug:
	$(FRONT) -g3 -fsanitize=address -g && make move

release:
	$(FRONT) -O3 && make move

tests:
	#create the binary, compile and run every test, then clean the last test
	make debug && \
	$(CC) $(STD) $(PATHS) $(BUILD_FILE)/$(LIB_NAME) -I./Programs/Tests Programs/Tests/Core/Types/Lambda.cpp -o Test && ./Test
	#&& \
	#for test in $(TESTS); 	\
	#do 	$(CC) $(STD) $(PATHS) -I./Programs/Tests $(DIRS) $(BUILD_FILE)/$(LIB_NAME) $(test) -o Test; \ 
	#	./Test; \
	#done; && \
	#rm -rf Test 
	#$(foreach file, $(TESTS), $(CC) $(STD) $(PATHS) -I./Programs/Tests $(DIRS) $(BUILD_FILE)/$(LIB_NAME) $(file) -o Test && ./Test) && \
	#rm -rf Test

clean:
	rm -rf ./Build

setup:
	if [ ! -d "./$(BUILD_FILE)" ]; then mkdir $(BUILD_FILE); fi

move:
	make setup && \
	ar rsc $(BUILD_FILE)/$(LIB_NAME) *.o && \
	rm -rf *.o
