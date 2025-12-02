#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cmath>

bool hasRepeated(long long num) {
  std::string x = std::to_string(num);
  size_t n = x.size();
  for (size_t i = 0; i <= n / 2; i++) {
    if (n % i != 0)
      continue;

    std::string comp = x.substr(0, i);
    bool found = true;
    for (size_t j = i; j < n; j += i) {
      std::string s = x.substr(j, i);
      if (s != comp) {
        found = false;
        break;
      }
    }
    if (found)
      return true;
  }
  return false;
}

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
      if (hasRepeated(i)) {
        res += i;
      }
    }
  }
    int dash_index = line.find('-');
    long long start = std::stoi(line.substr(startIdx, dash_index - startIdx));
    long long end = std::stoi(line.substr(dash_index + 1));
    for (long long i = start; i <= end; i++) {
      if (hasRepeated(i)) {
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
