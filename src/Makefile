SRC := PixelPainters.cpp
ifdef ACC
  TARGET := PixelPaintersACC
  CXX := pgc++
  CXXFLAGS := -acc -ta=nvidia,cuda7.5,maxwell,pinned -O3 -Minfo=acc -std=c++11
else
  ifdef OMP
    TARGET := PixelPaintersMP
    CXX := icpc
    CXXFLAGS := -O3 -march=native -std=c++11 -openmp
  else
    TARGET := PixelPaintersSEQ
    CXX := icpc
    CXXFLAGS := -O3 -march=native -std=c++11
  endif
endif

BIN := $(SRC:.cpp=)

default : $(TARGET)

$(TARGET) : $(BIN)
	-mv $(BIN) $(TARGET)

all :
	make ACC=1
	make OMP=1
	make
	icpc -O3 -march=native -std=c++11 PixelPaintersORIG.cpp -o PixelPaintersORIG
	pgc++ -acc -ta=nvidia,cuda7.5,maxwell,pinned -O3 -Minfo=acc -std=c++11 PixelPaintersTest.cpp -o PixelPaintersTest
clean :
	-rm -rf PixelPaintersACC PixelPaintersSEQ PixelPaintersORIG PixelPaintersMP PixelPaintersTest
