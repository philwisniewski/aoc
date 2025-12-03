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

  long res = 0;
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
    long battery = 0;
    int n = line.size();
    int farthestLeft = -1;
    for (int i = 0; i < 12; i++) {
      int leftNum = -1;
      int leftIdx = -1;
      
      for (int j = farthestLeft + 1; j <= n - 12 + i; j++) {
        int digit = line[j] - '0';
        if (digit > leftNum) {
          leftNum = digit;
          leftIdx = j;
        }
      }

      
      farthestLeft = leftIdx;
      battery = 10 * battery + leftNum;
    }

    res += battery;
  }

  /* Solution goes below! */

  std::cout << "Res = " << res << std::endl;

  /* Solution goes above! */

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Execution time: " << duration.count() << " microseconds\n";

  return 0;
}
