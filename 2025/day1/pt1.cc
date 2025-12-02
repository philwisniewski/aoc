#include <iostream>
#include <fstream>
#include <string>

int main() {
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
  return 0;
}
