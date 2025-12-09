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
  int lineWidth = lines[0].size();
  int startPos = -1;
  for (int i = 0; i < lineWidth; i++) {
    if (lines[0][i] == 'S') {
      startPos = i;
      break;
    }
  } 

  int beamCount = 0;
  int splits = 0;
  vector<bool> beams(lineWidth, false);
  beams[startPos] = true;

  for (int i = 1; i < lines.size(); i++) {
    line = lines[i];
    vector<bool> newBeams(lineWidth, false);
    for (int j = 1; j < lineWidth - 1; j++) {
      if (beams[j] && line[j] == '^') {
        newBeams[j - 1] = true;
        newBeams[j + 1] = true;
        splits++;
      }
      else if (beams[j]) {
        newBeams[j] = true;
      }
    }

    beams = newBeams;
  }

  cout << splits << endl;
  

  /* Solution goes above! */

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Execution time: " << duration.count() << " microseconds\n";

  return 0;
}
