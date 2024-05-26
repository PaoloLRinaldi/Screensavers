#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

using namespace std;

class Line {
public:
  Line(int l): pts(l, 0) {
    srand48(time(0));
    int beg;
    while ((beg = drand48() * l) == l);
    pts[beg] = randdir();
  }
  
  void print() {
    cout << "O";
    for (auto a : pts)
      cout << (!a ? " " : "*");
    cout << "O" << endl;
  }
  
  void next() {
    for (int i = 0; i < pts.size(); ++i)
      if (pts[i]) step(i++);
  }
  
  void put_here(int dir, int pos) {
    if (pos < 0 || pos >= pts.size()) return;
    pts[pos] = pts[pos] ? randdir() : dir;
  }
  
  int left(int i) { return pts[i] < 0 ? i : pts.size() - 1 - i; }
  void step(int ind) {
    if (drand48() <= 1. / (left(ind) + 1)) {
      put_here(-1, ind - 1);
      put_here(1, ind + 1);
    } else {
      put_here(pts[ind], ind + pts[ind]);
    }
    pts[ind] = 0;
  }
  void play() {
    while (true) {
      print();
      next();
      usleep(50000);
    }
  }
  
  int randdir() const { return drand48() < 0.5 ? -1 : 1; }

private:
  vector<int> pts;
};

int main() {
  Line l(70);
  l.play();
  return 0;
}

// nano ssbg2.cpp
// g++ -std=gnu++11 -o screensaver_by_gigi2 ssbg2.cpp