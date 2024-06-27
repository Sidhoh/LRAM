#include "raylib.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
#define precision 9999

float f(float x) {
  float y = (x+5);
  if (isinf(y)) {
    return y = 0;
  }
  return y;
}
vector<Vector2> points;
vector<Vector2> coords;

int main(int argc, char *argv[]) {

  cout << setprecision(5);

  bool end;
  bool _end;      // For the graph
  float b = 15;   // Upper Bound
  float a = 1;    // Lower Bound
  float n = 9999; // # of Rectangles

  cout << "Enter upper bound: ";
  cin >> b;

  cout << "Enter lower bound: ";
  cin >> a;

  cout << "Enter number of partitions: ";
  cin >> n;

  float partition = (b - a) / n;
  float _partition = (b - a) / precision; // for the graph

  cout << "Partitions: " << partition << endl << endl;
  float x = a;
  float _x = a; // for the graph

  float ySum = 0;

  do {
    if (_x < b) {
      points.push_back({(_x * 40) + 800, (f(_x) * -40) + 800});
      _x = _x + _partition;
    } else {
      _end = true;
    }
  } while (!_end);

  do {
    if (x < b) {
      ySum = ySum + f(x);
      // cout << "{" << x << " , " << f(x) << "}" << endl;
      coords.push_back({x, f(x)});
      x = x + partition;
    } else {
      end = true;
    }
  } while (!end);

  cout << "Area under f(x) = sin(x): " << partition * ySum << endl;

  SetTraceLogLevel(LOG_ERROR);
  InitWindow(1600, 1600, "graph");
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawLine(0, 800, 1600, 800, BLACK); // X Axis
    DrawLine(800, 0, 800, 1600, BLACK); // Y Axis

    DrawSplineLinear(points.data(), points.size(), 8.0f, RED);
    for (int i = -20; i <= 40; i++) {
      DrawText(TextFormat("%d", i - 20), (i * 40) - 10, 800, 20, BLACK);
      DrawText(TextFormat("%d", i - 20), 800, (i * 40) - 10, 20, BLACK);
    }

    for (auto x : coords) {
      DrawRectanglePro({x.x * 40 + 800, 0 + 800, partition * 40, f(x.x) * 40},
                       {00, 00}, -180.0f, GREEN);
      DrawRectanglePro({x.x * 40 + 800, 0 + 800, partition * 40, f(x.x) * -40},
                       {00, 00}, 0.0f, GREEN);
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
