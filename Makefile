SRC := PixelPainters.cpp
ifdef ACC
  TARGET := PixelPaintersACC
  CXX := pgc++
  CXXFLAGS := -acc -ta=nvidia,cuda7.5,maxwell,pinned -O3 -Minfo=acc -std=c++11
else
  ifdef OMP
    TARGET := PixelPaintersOMP
    CXX := icpc
    CXXFLAGS := -O3 -march=native -std=c++11 -openmp
  else
    TARGET := PixelPaintersCPU
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
clean :
	-rm -rf PixelPaintersOMP PixelPaintersACC PixelPaintersCPU
