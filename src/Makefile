SRC := PixelPainters.cpp
ifdef ACC
  TARGET := PixelPaintersACC
  CXX := pgc++
  CXXFLAGS := -acc -ta=nvidia,cuda7.5,maxwell,pinned -O3 -Minfo=acc -std=c++11
else
    TARGET := PixelPaintersSEQ
    CXX := icpc
    CXXFLAGS := -O3 -march=native -std=c++11

endif

BIN := $(SRC:.cpp=)

default : $(TARGET)

$(TARGET) : $(BIN)
	-mv $(BIN) $(TARGET)

all :
	make ACC=1
	make
	g++ PixelPaintersORIG.cpp -o PixelPaintersORIG
clean :
	-rm -rf PixelPaintersACC PixelPaintersSEQ PixelPaintersORIG
