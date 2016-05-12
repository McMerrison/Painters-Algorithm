ifdef GPU
CXX := pgc++
CXXFLAGS := -acc -ta=nvidia,7.5,cc50 -O3 -Minfo=acc -std=c++11
SRC := PixelPaintersACC.cpp PixelPaintersWill.cpp
else
CXX := g++
CXXFLAGS := -O3 -march=native -std=c++11
SRC := PixelPaintersSerial.cpp PixelPainters.cpp
endif

TARGET := $(SRC:.cpp=)

default : $(TARGET)

all :
	make -C .
	make -C . GPU=1

clean :
	-rm -rf PixelPaintersACC PixelPaintersSerial PixelPainters PixelPaintersWill
