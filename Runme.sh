#!/bin/bash
cd src/
echo "---------------------------";
echo "          Compile          ";
echo "---------------------------";
make clean && make all

echo "---------------------------";
echo "          Running          ";
echo "---------------------------";

./PixelPaintersACC 1
echo "OMP Implementation";
./PixelPaintersMP
echo "SEQ Implementation";
./PixelPaintersSEQ

if[[$# -ne 1]]; then
echo "ORIG Implementation";

if[[$# -ne 1]]; then
./PixelPaintersORIG

exit 1