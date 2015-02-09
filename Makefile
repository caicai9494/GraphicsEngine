#LDLIBS=-lglut -lGLEW -lGL -lSOIL -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi
LDLIBS=-lSOIL -lGLEW -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi
CFLAGs=-c -Wall -g -O
SRC= gameMainApp.cpp common/shader.cpp
OBJ=$(SRC:.cpp=.o)
EXE= gameMainApp

#all: $(SRC) $(EXE)
	
#$(EXE): $(OBJ)
#		g++ -o $@ $(LDLIBS) $(OBJ) 
#.cpp.o:
#	g++ $(CFLAGS) $< -o $@


#triangle: ../common/shader_utils.o

all:
	g++ $(SRC) $(CFLAGS) $(LDLIBS) -o $(EXE)  

clean:
	rm -f *.o $(EXE)

.PHONY: all clean
