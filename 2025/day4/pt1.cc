#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

int main() {
  auto start = std::chrono::high_resolution_clock::now();
	
  std::ifstream file("input.txt");

  if (!file.is_open()) {
    std::cerr << "Failed to open input.txt" << std::endl;
    return 1;
  }  

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }

  /* Solution goes below! */

  int rows = lines.size();
  int cols = lines[0].size();
  vector<vector<int>> arr(rows, vector<int>(cols, 0));
  int res = 0;

  array<pair<int, int>, 8> directions {{
    {1, 0}, {0, 1}, {-1, 0}, {0, -1},
    {1, 1}, {-1, 1}, {1, -1}, {-1, -1}
  }};

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (lines[i][j] == '@') {
        for (pair<int, int> p : directions) {
          int dx = p.first;
          int dy = p.second;
          int y = i + dy;
          int x = j + dx;

          if (x >= 0 && x < cols && y >= 0 && y < rows) {
            arr[y][x]++;
          }
        }
      }
    }
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < rows; j++) {
      if (lines[i][j] == '@' && arr[i][j] < 4) {
        res++;
      }
    }
  }

  cout << "Res: " << res << endl;

  /* Solution goes above! */

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Execution time: " << duration.count() << " microseconds\n";

  return 0;
}
