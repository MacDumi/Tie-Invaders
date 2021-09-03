CC = g++
CXFLAGS  = -Wall -std=c++11
LIBS = ./libs
SFML_FLAGS =  -lX11 -lXinerama -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
BUILD    = ./bin
OBJ_DIR  = $(BUILD)
APP_DIR  = ./
TARGET   = tie_invaders
INCLUDE  = -Iinclude/ -Isrc -Ilibs/include
SRC      =                      \
   $(wildcard src/*/*.cpp) \
   $(wildcard src/*.cpp)

OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@ echo "[i] Building the executable"
	@ mkdir -p $(@D)
	@ $(CC) $(CXFLAGS) $(SFML_FLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.cpp 
	@ echo "	$^"
	@ mkdir -p $(@D)
	@ $(CC) $(CXFLAGS) $(INCLUDE) -c -o $@ $^

.PHONY: all build clean

build:
	@ echo "[i] Compiling ..."
	@ mkdir -p $(OBJ_DIR)

clean:
	@ echo "[i] Cleaning up"
	@ rm -rf $(OBJ_DIR)/*
ifneq ("$(wildcard $(APP_DIR)/$(TARGET))", "")
	@ rm $(APP_DIR)/$(TARGET)
endif

