CC=g++ -g -Wall
LDLIBS=-lSOIL -lGLEW -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi
CFLAGs=-c -Wall -g -O
OBJ= main.o common/controls.o common/shader.o data.o vertexBufferObject.o scene.o light.o common/objloader.o common/texture.o texture.o shaderProgram.o color.o material.o
TARGET= gameMainApp

	
all: 	$(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDLIBS)

.c.o:
	$(CC) $(CFLAGS) $< -g


clean:
	rm -rf $(OBJ) $(TARGET)

.PHONY: all clean
