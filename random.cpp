#include <cstdlib>
#include <ctime>
#include "random.h"

///INB371 Workshop 3 - random.cpp
///This class provides several functions for generating pseud-random numbers.
Random::Random() {
   randomize();
}

///Generates a random integer number greater than or equal to low and less than or equal to high.
int Random::randomInteger(int low, int high) {
   double d = double(rand()) / (double(RAND_MAX) + 1);
   int k = int(d * (high - low  + 1));
   return low + k;
}


///Initializes the random-number generator so that its results are unpredictable. If this function
/// is not called the other functions will return the same values on each run.
void Random::randomize() {
   srand(int(time(NULL)));
}
