#include <iostream>
#include "../src/MemoryAllocators/MonotonicAllocator.h"

using namespace std;
using namespace EngineTools;

struct Sample {
  int arg1;
  double arg2;
  float arg3;

  Sample() {
    cout << "Constructing" << endl;
    arg1 = 99;
    arg2 = 15.0;
    arg3 = 15.0f;
  }

  ~Sample() {
    cout << "Destructing" << endl;
  }
};



int main() {
  MonotonicAllocator<16> target{ 32 };

  Sample* ptr = target.NewObject<Sample>();

  cout << ptr->arg1 << endl;
  cout << ptr->arg2 << endl;
  cout << ptr->arg3 << endl;

  return 0;
}