/*
 *
 * Modified by: Will Killian 
 * Basic simulation of Painter's Algorithm (REFERENCE COPY)
 *
 * Creates a "screen" or array of pixels defined by a number and depth
 * initializes array with number value "0"
 * Updates subsection of array to lower depth (closer) with number "1"
 * Prints before and after images
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <array>
#include <chrono>

using namespace std;

//Define a Pixel using rgb values
struct Pixel {
  int color;
  float depth;
  Pixel (int c, float d)
    : color (c), depth (d) { }
  Pixel ()
    : Pixel (0, 1.0f) { }
};

void printBuffer(const Pixel *zbuffer, int width);
float randDepth();
int randColor();

const int FPS = 100;
const int ITERS = 7;
const int DIM = 100;
const int MAX = DIM*(1 << ITERS);

int main()
{
  srand(time(NULL));

  auto randArrColor = new int[MAX][MAX];
  auto randArrDepth = new float[MAX][MAX];

  //Generate Random Arrays
  for (int j = 0; j < MAX; ++j) {
    for (int k = 0; k < MAX; ++k) {
      randArrColor[j][k] = randColor();
      randArrDepth[j][k] = randDepth();
    }
  }

  #pragma acc data copyin(randArrColor[0:MAX][0:MAX],randArrDepth[0:MAX][0:MAX])
  {
    for (int w = DIM; w <= MAX; w <<= 1) {

      Pixel* zbuffer = new Pixel[w * w]();
      if (ITERS < 3) {
        printBuffer(zbuffer, w);
      }

      std::chrono::time_point <std::chrono::steady_clock> begin, end;

      #pragma acc data copy(zbuffer[0:w * w])
      {
        begin = std::chrono::steady_clock::now();
        for (int b = 0; b < FPS; b++) {
          #pragma omp parallel for
          #pragma acc kernels loop independent copyin(b)
          for (int i = 0; i < w; i ++) {
            #pragma omp simd
            #pragma acc loop independent
            for (int j = 0; j < w; j++) {
              if (randArrDepth[i][(j+b)%MAX] < zbuffer[i * w + j].depth) {
                zbuffer[i * w + j] = Pixel { randArrColor[i][(j+b)%MAX], randArrDepth[i][(j+b)%MAX] };
              }
            }
          }
        }
        end = std::chrono::steady_clock::now();
      }

      if (ITERS < 3) {
        printBuffer(zbuffer, w);
      }

      printf("%d frame buffers of size %d x %d took %lf seconds to update\n",
             FPS, w, w,
             std::chrono::duration <double> { end - begin }.count());
      delete[] zbuffer;
    }
  }
  delete[] randArrColor;
  delete[] randArrDepth;
}

void printBuffer(const Pixel *zbuffer, int width) {
  for (int i = 0; i < width; i ++) {
    for (int j = 0; j < width; j++) {
      printf("%d", zbuffer[i*width+j].color);
    }
  }
}

float randDepth() {
  return (rand() % 10) / 10.0f;
}

int randColor() {
  return rand() % 10;
}

