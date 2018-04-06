#include <iostream>
#include "../src/Containers/Vector.h"
#include "MemoryAllocators/MonotonicAllocator.h"
#include <algorithm>

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
  MonotonicAllocator<16> alloc{ 4 };
  Vector<int> v{ 16, &alloc };

  //cout << v.GetSize() << endl;

  v.Push(40);
  v.Push(20);
  v.Push(10);
  v.Push(30);

  //cout << "Idx: " << v.Find(20) << endl;
  //v.Remove(20);

  std::sort(v.Begin(), v.End());

  for (auto it = v.Begin(); it != v.End(); ++it) {
    cout << *it << endl;
  }

  //cout << "0: " << v[0] << endl;
  //cout << "1: " << v[1] << endl;
  //cout << "2: " << v[2] << endl;
  //cout << "3: " << v[3] << endl;

  return 0;
}