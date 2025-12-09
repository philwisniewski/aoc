#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <queue>

using namespace std;

class Point {
public:
  long x;
  long y;
  long z;

  Point(long a, long b, long c) : x(a), y(b), z(c) { }
};

long distance(Point& p1, Point& p2) {
  long x_dist = p1.x - p2.x;
  long y_dist = p1.y - p2.y;
  long z_dist = p1.z - p2.z;
  return x_dist * x_dist + y_dist * y_dist + z_dist * z_dist;
}

struct Comparator {
  bool operator()(const vector<long>& a, const vector<long>& b) {
    return a[0] > b[0];
  }
};

long find(long x, vector<long>& u) {
  if (x != u[x]) {
    u[x] = find(u[x], u);
  }
  return u[x];
}

bool union_merge(long x, long y, vector<long>& u, vector<long>& s) {
  long p = find(x, u);
  long q = find(y, u);
  long pSize = s[p];
  long qSize = s[q];

  if (p == q) {
    return false;
  }

  if (pSize < qSize) {
    s[q] += pSize;
    s[p] = 0;
    u[p] = q;
  }
  else {
    s[p] += qSize;
    s[q] = 0;
    u[q] = p;
  }
  return true;
}

int main(int argc, char *argv[]) {
  auto start = std::chrono::high_resolution_clock::now();
	
  std::ifstream file("input.txt");

  if (!file.is_open()) {
    std::cerr << "Failed to open input.txt" << std::endl;
    return 1;
  }  

  std::string line;
  int numPoints = 0;
  std::vector<Point> points;
  while (std::getline(file, line)) {
    size_t commaPos = line.find(',');
    long x = stol(line.substr(0, commaPos));
    line = line.substr(commaPos + 1);
    commaPos = line.find(',');
    long y = stol(line.substr(0, commaPos));
    line = line.substr(commaPos + 1);
    long z = stol(line);
    numPoints++;
    points.push_back(Point(x, y, z));
  }

  /* Solution goes below! */

  priority_queue<vector<long>, vector<vector<long>>, Comparator> minHeap;


  int maxMinHeapSize = 1000;
  if (argc > 1) {
    maxMinHeapSize = stoi(string(argv[1]));
  }
  for (int i = 0; i < numPoints; i++) {
    for (int j = i + 1; j < numPoints; j++) {
      vector<long> myVec = { distance(points[i], points[j]), i, j };
      minHeap.push(myVec);
    }
  }

  vector<long> u(numPoints);
  for (long i = 0; i < numPoints; i++) {
    u[i] = i;
  }
  vector<long> size(numPoints, 1);

  int merges = 0;
  while (!minHeap.empty() && merges < maxMinHeapSize) {
    auto v = minHeap.top();
    minHeap.pop();
    merges++;
    if (union_merge(v[1], v[2], u, size)) {

      cout << "Merged points " << v[1] << "=(" << points[v[1]].x << ", "
         << points[v[1]].y << ", " << points[v[1]].z << ") and " << v[2]
         << "=(" << points[v[2]].x << ", "
         << points[v[2]].y << ", " << points[v[2]].z << ")" << endl;
    }
  }

  vector<long> threeHighest(3, -1);

  for (long v = 0; v < numPoints; v++) {
    cout << v << ": " << size[v] << endl;
    if (threeHighest[2] == -1 || size[v] > size[threeHighest[2]]) {
      threeHighest[0] = threeHighest[1];
      threeHighest[1] = threeHighest[2];
      threeHighest[2] = v;
    }
    else if (threeHighest[1] == -1 || size[v] > size[threeHighest[1]]) {
      threeHighest[0] = threeHighest[1];
      threeHighest[1] = v;
    }
    else if (threeHighest[0] == -1 || size[v] > size[threeHighest[0]]) {
      threeHighest[0] = v;
    }
  }


  long res = size[threeHighest[0]] * size[threeHighest[1]] * size[threeHighest[2]];

  cout << res << endl;


  /* Solution goes above! */

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Execution time: " << duration.count() << " microseconds\n";

  return 0;
}
