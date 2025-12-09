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

  long beamCount = 0;
  vector<long> beams(lineWidth, 0);
  beams[startPos] = 1;

  for (int i = 1; i < lines.size(); i++) {
    line = lines[i];
    vector<long> newBeams(lineWidth, 0);
    for (int j = 0; j < lineWidth; j++) {
      if (beams[j] && line[j] == '^') {
        newBeams[j - 1] += beams[j];
        newBeams[j + 1] += beams[j];
      }
      else if (beams[j]) {
        newBeams[j] += beams[j];
      }
    }

    beams = newBeams;
  }

  long timelines = 0;
  for (auto n : beams) {
    timelines += n;
  }

  cout << timelines << endl;
  

  /* Solution goes above! */

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Execution time: " << duration.count() << " microseconds\n";

  return 0;
}
