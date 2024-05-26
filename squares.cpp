#include <iostream>
#include <string>
#include <unistd.h>
#include <algorithm>

using namespace std;

string half(int holes, int l) {
  return string(l - holes - 1, ' ') + "O" + string(holes, ' ');
}

string line(int holes, int l) {
  int delta = l % 2;
  string ret, halfs = half(holes, l / 2 + delta);
  ret = halfs;
  reverse(halfs.begin(), halfs.end() - delta);
  return ret + halfs;
}

void square(int dim, int l) {
  for (int i = 0; i != dim; ++i) {
    cout << line(i, l) << endl;
    usleep(5000);
  }
  for (int i = 0; i != dim; ++i) {
    cout << line(dim - 1 - i, l) << endl;
    usleep(5000);
  }
}

int main() {
  
  while(true) {
    for (int i = 0; i != 36; ++i) {
      square(i, 72);
    }
    for (int i = 0; i != 36; ++i) {
      square(36 - 1 - i, 72);
    }
  }
  return 0;
}