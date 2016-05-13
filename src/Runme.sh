#!/bin/bash
echo "Compiling Code";
make clean && make all
echo "Running ACC";
./PixelPaintersACC
echo "Running OMP";
./PixelPaintersMP
echo "Running SEQ";
./PixelPaintersSEQ
echo "Running ORIG";
./PixelPaintersORIG