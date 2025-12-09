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

  vector<char> ops;
  vector<long> totals;
  for (char c : lines[lines.size() - 1]) {
    if (c == ' ') {
      continue;
    }
    if (c == '*') {
      totals.push_back(1);
    }
    else {
      totals.push_back(0);
    }
    ops.push_back(c);
  }

  long res = 0;
  for (int i = 0; i < lines.size() - 1; i++) {
    string l = lines[i];
    char lastChar = ' ';
    string curNum = "";
    int j = 0;
    for (char c : l) {
      if (c == ' ') {
        if (lastChar != ' ') {
          if (j >= 0) {
            if (ops[j] == '*') {
              totals[j] *= stol(curNum);
            }
            else {
              totals[j] += stol(curNum);
            }
          }
          j++;
          curNum = "";
        }
        lastChar = c;
        continue;
      }
      if (lastChar == ' ') {
        curNum = c;
      }
      else {
        curNum += c;
      }
      lastChar = c;
    }
    if (lastChar != ' ') {
      if (ops[j] == '*') {
        totals[j] *= stol(curNum);
      }
      else {
        totals[j] += stol(curNum);
      }
    }
  }

  for (auto n : totals) {
    res += n;
  }

  cout << res << endl;

  /* Solution goes above! */

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Execution time: " << duration.count() << " microseconds\n";

  return 0;
}
