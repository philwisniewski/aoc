#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cmath>

int main() {
  auto start_time = std::chrono::high_resolution_clock::now();
	
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

  line = lines[0];
  int startIdx = 0;
  long long res = 0;

  size_t comma_index = line.find(',');
  while (comma_index != std::string::npos) {
    int dash_index = line.find('-');
    long long start = std::stoll(line.substr(startIdx, dash_index - startIdx));
    long long end = std::stoll(line.substr(dash_index + 1, comma_index - dash_index - 1));
    line = line.substr(comma_index + 1);
    comma_index = line.find(',');
    for (long long i = start; i <= end; i++) {
      
      long long digits = (int) std::log10(i) + 1;
      long long mid = digits / 2;
      long long div = std::pow(10, mid);

      long long left = i / div;
      long long right = i % div;

      if (left == right) {
        res += i;
      }
    }
  }
    int dash_index = line.find('-');
    long long start = std::stoi(line.substr(startIdx, dash_index - startIdx));
    long long end = std::stoi(line.substr(dash_index + 1));
    for (long long i = start; i <= end; i++) {
      
      long long digits = (int) std::log10(i) + 1;
      long long mid = digits / 2;
      long long div = std::pow(10, mid);

      long long left = i / div;
      long long right = i % div;

      if (left == right) {
        res += i;
      }
    }


  std::cout << "Res = " << res << std::endl;


  /* Solution goes above! */

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
  std::cout << "Execution time: " << duration.count() << " microseconds\n";

  return 0;
}
