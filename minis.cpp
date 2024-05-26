#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <cstdio>
#include <algorithm>

using namespace std;

void rev(string &line) {
  reverse(line.begin(), line.end());
  for (auto &c : line) c = c == '/' ? '\\' : c == '\\' ? '/' : c == '>' ? '<' : c == '<' ? '>' : c;
}

int main() {
  int len = 72, step = 18, n_layers = 4;
  vector<vector<string>> sprites(2);
  sprites[0] = {"  O>",
                " /|\\",
                "/ | \\",
                "  |\\", 
                "  |/"};
  sprites[1] = {"  O>",
                " /|\\_",
                " ||", 
                "  |\\",
                " /  \\"};
  int bias = 0;
  while (true) { 
    vector<string> top(sprites[0].size(), string(len, ' '));
    for (int i = 0; i != top.size(); ++i) {
      for (int j = 0; j != len / step; ++j) {
        for (int k = 0; k != sprites[bias % sprites.size()][i].size(); ++k)
          top[i][(j * step + k + bias) % len] = sprites[bias % sprites.size()][i][k];
        for (int k = 0; k != step - sprites[bias % sprites.size()][i].size(); ++k)
          top[i][(j * step + sprites[bias % sprites.size()][i].size() + bias) % len] = ' ';
      }
    }
    bias = (bias + 1) % step;
    for (int j = 0; j != n_layers; ++j) {
      for (int i = 0; i != top.size(); rev(top[i]), ++i) {
	cout << top[i] << endl;
      }
    }
    usleep(50000);
    system("clear\n");
  }
  return 0;
}
