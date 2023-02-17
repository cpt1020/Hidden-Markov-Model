
INCLUDE_DIR = include
SOURCE_DIR = src
BUILD_DIR = build
EXECUTABLE_NAME = main

CXX_STANDARD = c++17
CXX = g++
CXXFLAGS = -std=$(CXX_STANDARD)
CPPFLAGS = -I $(INCLUDE_DIR)

CXX_COMPILER_CALL = $(CXX) $(CXXFLAGS) $(CPPFLAGS)

CXX_SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp)
CXX_OBJECTS = $(patsubst $(SOURCE_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CXX_SOURCES))

##############
## TARGETS  ##
##############
all: create build

create:
	@mkdir -p build

build: $(CXX_OBJECTS)
	$(CXX_COMPILER_CALL) $(CXX_OBJECTS) -o $(EXECUTABLE_NAME)

execute:
	./$(EXECUTABLE_NAME)

clean:
	rm -f $(BUILD_DIR)/*.o
	rm -f $(EXECUTABLE_NAME)

##############
## PATTERNS ##
##############
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CXX_COMPILER_CALL) -c $< -o $@

###########
## PHONY ##
###########
.PHONY: create build execute clean

#main: main.cpp
#	g++ main.cpp src/*.cpp -std=c++17 -o main