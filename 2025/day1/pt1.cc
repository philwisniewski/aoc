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
  std::string line;
  int curPos = 50;
  while (std::getline(file, line)) {
    int val = std::stoi(line.substr(1));
    if (line[0] == 'R') {
      // right
      curPos = (curPos + val) % 100;
    }
    else {
      // left
      curPos = (curPos - val) % 100;
    }
    if (curPos == 0) {
      res++;
    }
  }

  std::cout << "Result: " << res << std::endl;

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

  return 0;
}
