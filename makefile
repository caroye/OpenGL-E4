CFLAGS= -I/usr/include/GL -I/usr/include/libdrm -Wall 
LIBS= -lGLEW -lGLU -lGL -lglfw 

#-std=c++11
all: window 

window: shader.o window.o cube.o
		g++ window.o -g $(CFLAGS) $(LIBS) -o window shader.o cube.o

window.o: window.cpp shader.h cube.h
		g++ -g $(CFLAGS) $(LIBS) -o window.o -c window.cpp 

shader.o: shader.cpp shader.h
		g++ -g $(CFLAGS) $(LIBS) -o shader.o -c shader.cpp 

cube.o: cube.cpp cube.h
		g++ -g $(CFLAGS) $(LIBS) -o cube.o -c cube.cpp 

clean:
		$(RM) *.o window 