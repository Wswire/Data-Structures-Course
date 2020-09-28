OBJS = mp1.o main.o PNG.o HSLAPixel.o lodepng.o

CXX = clang++
LD = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LDFLAGS = -std=c++1y -stdlib=libc++
#-1c++abi

mp1: $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o mp1

mp1.o: mp1.cpp mp1.h
	$(CXX) $(CXXFLAGS) mp1.cpp

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

PNG.o: cs225/PNG.cpp cs225/PNG.h HSLAPixel.o lodepng.o
	$(CXX) $(CXXFLAGS) cs225/PNG.cpp

HSLAPixel.o: cs225/HSLAPixel.cpp cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs225/HSLAPixel.cpp

lodepng.o: cs225/lodepng/lodepng.cpp cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/lodepng/lodepng.cpp

test : unit_tests.o mp1.o PNG.o HSLAPixel.o lodepng.o
	$(LD) unit_tests.o mp1.o PNG.o HSLAPixel.o lodepng.o $(LDFLAGS) -o test

unit_tests.o : tests/unit_tests.cpp tests/catch.hpp cs225/PNG.h cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) tests/unit_tests.cpp

clean:
	-rm -f *.o mp1 test

 
