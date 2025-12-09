#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include <algorithm>

int main() {
  auto start = std::chrono::high_resolution_clock::now();

  std::ifstream file("input.txt");

  if (!file.is_open()) {
    std::cerr << "Failed to open input.txt" << std::endl;
    return 1;
  }

  std::vector<std::pair<long, long>> ranges;
  std::vector<long> requests;

  std::string line;
  bool reachedMiddle = false;

  while (std::getline(file, line)) {
    if (!reachedMiddle) {
      if (line == "") {
        reachedMiddle = true;
        continue;
      }

      size_t dashIdx = line.find('-');
      long first = std::stol(line.substr(0, dashIdx));
      long second = std::stol(line.substr(dashIdx + 1));

      ranges.emplace_back(first, second);
    }
    else {
      if (!line.empty())
        requests.push_back(std::stol(line));
    }
  }

  // Sort ranges
  std::sort(ranges.begin(), ranges.end());

  // Merge intervals
  std::vector<std::pair<long, long>> merged;
  merged.push_back(ranges[0]);

  for (size_t i = 1; i < ranges.size(); i++) {
    auto &last = merged.back();

    // overlapping?
    if (last.second >= ranges[i].first) {
      last.second = std::max(last.second, ranges[i].second);
    } else {
      merged.push_back(ranges[i]);
    }
  }

  long res = 0;
  for (std::pair<long, long> p : merged) {
    res += p.second - p.first + 1;
  }

  std::cout << res << std::endl;

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  std::cout << "Execution time: " << duration.count() << " microseconds\n";

  return 0;
}

