CC=g++

CFLAGS= `pkg-config --cflags gstreamer-audio-1.0`
LD= `pkg-config --libs gstreamer-audio-1.0`
SRC= audio.cpp
EXE= audio

all:
	$(CC)  $(SRC) -o $(EXE) $(CFLAGS) $(LD)
