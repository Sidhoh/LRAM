#include "raylib.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
#define precision 9999

float f(float x) {
  float y = sin(x);
  if (isinf(y)) {
    return y = 0;
  }
  return y;
}
vector<Vector2> points;
vector<Vector2> coords;
int zoom = 40;
int moveX;
int moveY;

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
      points.push_back({_x, f(_x)});
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
    DrawLine(0 + moveX, 800 + moveY, 1600 + moveX, 800 + moveY,
             BLACK); // X Axis
    DrawLine(800 + moveX, 0 + moveY, 800 + moveX, 1600 + moveY,
             BLACK); // Y Axis

    // Rendering Graph
    for (int i = 0; i < points.size() - 1; i++) {
      DrawLineEx({(points[i].x * zoom) + 800 + moveX,
                  (points[i].y * -zoom) + 800 + moveY},
                 {(points[i + 1].x * zoom) + 800 + moveX,
                  (points[i + 1].y * -zoom) + 800 + moveY},
                 7, RED);
    }

    for (int i = -100; i <= 100; i++) {
      DrawText(TextFormat("%d", i), (i * zoom) - 10 + 800 + moveX, 800 + moveY,
               20,
               BLACK); // X axis Numbers
      DrawText(TextFormat("%d", i), 800 + moveX, (i * zoom) - 10 + 800 + moveY,
               20,
               BLACK); /// Y axis Numbers
    }

    // Drawing rectangles
    for (auto x : coords) {
      DrawRectanglePro({x.x * zoom + 800 + moveX, (x.x * 0) + moveY + 0 + 800,
                        partition * zoom, f(x.x) * zoom},
                       {0, 0}, -180.0f, GREEN);
      DrawRectanglePro({x.x * zoom + 800 + moveX, (x.x * 0) + moveY + 0 + 800,
                        partition * zoom, f(x.x) * -zoom},
                       {0, 0}, 0.0f, GREEN);
    }

    // Movement
    float wheel = GetMouseWheelMove();
    if (wheel < 0) {
      zoom -= 1;
    }
    if (wheel > 0) {
      zoom += 1;
    }
    if (IsKeyDown(KEY_A)) {
      moveX += 1;
    }
    if (IsKeyDown(KEY_D)) {
      moveX -= 1;
    }
    if (IsKeyDown(KEY_W)) {
      moveY += 1;
    }
    if (IsKeyDown(KEY_S)) {
      moveY -= 1;
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
