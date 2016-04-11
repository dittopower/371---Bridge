#ifndef _random_h
#define _random_h

/// INB371 Workshop 3 - random.h
/// This class provides several functions for generating random numbers.
class Random {
public:

   /// Initialize the randomizer.
   Random();

   /// Generates a random integer number greater than or equal to low and less than high.
   int randomInteger(int low, int high);


private:

   /// Initializes the random-number generator so that its results are unpredictable.  If this
   /// function is not called the other functions will return the same values on each run.
   void randomize();
};

#endif // _random_h
