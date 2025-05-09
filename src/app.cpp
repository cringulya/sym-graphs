#include "app.h"
#include "graph.h"

Graph g;

App::App() {
  g.vertecies.resize(8);
  g.edges.push_back({0, 1});
  g.edges.push_back({1, 2});
  g.edges.push_back({2, 3});
  g.edges.push_back({3, 0});

  g.edges.push_back({4, 0});
  g.edges.push_back({4, 1});
  g.edges.push_back({4, 2});
  g.edges.push_back({4, 3});

  g.edges.push_back({4, 5});
  g.edges.push_back({5, 6});
  g.edges.push_back({6, 7});

  g.init();
}

void App::update() {
  draw();
}

void App::draw() {
  g.draw();
}
