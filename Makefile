#LDLIBS=-lglut -lGLEW -lGL -lSOIL -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi
CC=g++
LDLIBS=-lSOIL -lGLEW -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi
CFLAGs=-c -Wall -g -O
OBJ= main.o common/controls.o common/shader.o data.o vertexBufferObject.o scene.o light.o common/objloader.o common/texture.o
TARGET= gameMainApp

	
all: 	$(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDLIBS)

.c.o:
	$(CC) $(CFLAGS) $< -g


clean:
	rm -rf $(OBJ) $(TARGET)

.PHONY: all clean
