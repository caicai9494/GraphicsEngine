CXX=g++ -g
LDLIBS=-lGL -lGLU -lglut 
CFLAGs=-c -Wall -g -O
CXXFLAGs=-c -Wall -g -O
OBJ= main.o matrix.o vector.o draw.o
TARGET= rasterizer

	
all: 	$(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDLIBS) $(CXXFLAGS) 

.c.o:
	$(CXX) $(CXXFLAGS) $< -g 


clean:
	rm -rf $(OBJ) $(TARGET)

.PHONY: all clean
