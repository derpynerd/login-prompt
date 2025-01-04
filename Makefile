CXX = g++ # C++ compiler
CXXFLAGS = -Wall -g # C++ compiler flags

all: main run

main: main.cpp
	$(CXX) main.cpp $(CXXFLAGS) -o main

run: main.exe
	./main.exe

clean:
	rm main.exe