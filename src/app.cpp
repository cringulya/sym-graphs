#include "app.hpp"
#include "graph.hpp"
#include "ogdf/basic/geometry.h"
#include "ogdf/energybased/SpringEmbedderGridVariant.h"
#include "ogdf/energybased/SpringEmbedderKK.h"
#include "ogdf/energybased/SpringForceModel.h"
#include "parser/parser.hpp"
#include "raylib.h"
#include "raymath.h"
#include <iostream>

#include "ogdf/basic/Graph.h"
#include "ogdf/basic/GraphAttributes.h"
#include <ogdf/energybased/SpringEmbedderFRExact.h>

App::App() {
  Parser parser;
  history_ = parser.parse("../../SerializedEpisodes/adjoint_0");

  if (!history_.empty()) {
    history_.front().update();
  }
}

void App::update() {
  draw();
}

void App::draw() {
  // float time = GetTime();
  // float max_time = 10;
  // float time_per_graph = max_time / history_.size();
  //
  // int id = fmin(history_.size() - 1, time / time_per_graph);
  // std::cout << time << std::endl;
  // std::cout << id << std::endl;
  //
  // if (id > 0 && id < history_.size()) {
  //   for (auto &[vid, v] : history_[id].vertecies) {
  //     v.pos = history_[id - 1].vertecies[vid].pos;
  //   }
  // }
  //
  // history_[id].update();
  // history_[id].draw();
  ogdf::Graph G;

  // Create a sample graph
  ogdf::node v1 = G.newNode();
  ogdf::node v2 = G.newNode();
  ogdf::node v3 = G.newNode();
  ogdf::node v4 = G.newNode();
  G.newEdge(v1, v2);
  G.newEdge(v2, v3);
  G.newEdge(v3, v4);
  G.newEdge(v4, v1);
  G.newEdge(v1, v3);

  ogdf::GraphAttributes GA(G);

  ogdf::SpringEmbedderGridVariant layout{};

  layout.forceModel(ogdf::SpringForceModel::FruchtermanReingold);
  layout.userBoundingBox(0, 0, GetScreenWidth(), GetScreenHeight());
  layout(GA);

  float scale = 1.f;
  for (ogdf::node v : G.nodes) {
    float x = GA.x(v) * scale;
    float y = GA.y(v) * scale;
    DrawCircleV({x, y}, 2.f, GREEN);
  }

  for (ogdf::edge e : G.edges) {
    Vector2 src = {static_cast<float>(GA.x(e->source())),
                   static_cast<float>(GA.y(e->source()))};
    Vector2 target = {static_cast<float>(GA.y(e->target())),
                      static_cast<float>(GA.y(e->target()))};
    DrawLineV(src * scale, target * scale, RAYWHITE);
  }
}
