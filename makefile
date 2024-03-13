# Directories
S_DIR=src
B_DIR=bin

# Files
S_FILES=$(S_DIR)/*.cpp

# Output
EXEC=$(B_DIR)/out

# Build settings
CC=g++
# SDL options
CC_SDL=-lSDL2 -lSDL2_image -lSDL2_ttf `sdl-config --cflags --libs`


all:build_run

Build:
	$(CC) $(S_FILES) -o $(EXEC) -I include $(CC_SDL)

build_run:Build
	$(EXEC)

clean:
	rm -rf $(B_DIR)/*
