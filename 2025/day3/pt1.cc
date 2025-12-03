#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

int main() {
  auto start = std::chrono::high_resolution_clock::now();
	
  std::ifstream file("input.txt");

  if (!file.is_open()) {
    std::cerr << "Failed to open input.txt" << std::endl;
    return 1;
  }  

  int res = 0;
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
    int leftNum = -1;
    int leftIdx = -1;
    for (int i = line.size() - 2; i >= 0; i--) {
      int n = line[i] - '0';
      if (n >= leftNum) {
        leftNum = n;
        leftIdx = i;
      }
    }
    int rightNum = -1;
    for (int i = leftIdx + 1; i < line.size(); i++) {
      int n = line[i] - '0';
      if (n > rightNum) {
        rightNum = n;
      }
    }
    int v = 10 * leftNum + rightNum;
    res += v;
  }

  /* Solution goes below! */

  std::cout << "Res = " << res << std::endl;

  /* Solution goes above! */

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Execution time: " << duration.count() << " microseconds\n";

  return 0;
}
