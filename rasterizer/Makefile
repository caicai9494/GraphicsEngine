CC=g++
LDLIBS=-lGL -lGLU -lglut 
CFLAGs=-c -Wall -g -O
OBJ= main.o matrix.o vector.o draw.o
TARGET= rasterizer

	
all: 	$(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDLIBS)

.c.o:
	$(CC) $(CFLAGS) $< -g


clean:
	rm -rf $(OBJ) $(TARGET)

.PHONY: all clean
