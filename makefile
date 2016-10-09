CFLAGS= -I/usr/include/GL -I/usr/include/libdrm -Wall
LIBS= -lGLEW -lGLU -lGL -lglfw 


all: window 

window: shader.o window.o camera.o
		g++ window.o -g $(CFLAGS) $(LIBS) -o window shader.o

window.o: window.cpp shader.h Camera.h
		g++ -g $(CFLAGS) $(LIBS) -o window.o -c window.cpp 

shader.o: shader.cpp shader.h
		g++ -g $(CFLAGS) $(LIBS) -o shader.o -c shader.cpp 

camera.o: Camera.h
		g++ -g $(CFLAGS) $(LIBS) -o camera.o -c Camera.h

clean:
		$(RM) *.o window 