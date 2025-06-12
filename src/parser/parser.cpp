#include "parser.hpp"

#include "graph.hpp"
#include "nlohmann/json.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string_view>
#include <vector>

namespace fs = std::filesystem;

std::vector<Graph> Parser::parse(fs::path dir) {

  std::vector<fs::directory_entry> files;

  for (auto &entry : fs::directory_iterator(dir)) {
    files.push_back(entry);
  }

  std::sort(files.begin(), files.end(),
            [](fs::directory_entry const &a, fs::directory_entry const &b) {
              return a.path().string() < b.path().string();
            });

  std::vector<Graph> gs;

  for (auto &entry : files) {
    Graph g;
    std::ifstream fs(entry.path());
    nlohmann::json j;
    fs >> j;

    std::string filename = entry.path().filename().string();
    std::cout << filename << std::endl;
    const std::string gameStateSuffix = "_gameState";
    const std::string movedStateSuffix = "_movedState";
    const std::string infoSuffix = "_statesInfo";
    if (filename.contains(gameStateSuffix)) {
      nlohmann::json j_vertices;
      nlohmann::json j_edges;
      nlohmann::json j_states;

      try {
        j_vertices = j.at("GraphVertices");
        j_edges = j.at("Map");
        j_states = j.at("States");
      } catch (...) {
        throw;
      }

      for (auto &s : j_states) {
        Graph::State state;
        int id;
        try {
          id = s.at("Id");
          state.position = s.at("Position");
          state.visited_again_vertices = s.at("VisitedAgainVertices");
          state.visited_not_covered_vertices_in_zone =
              s.at("VisitedNotCoveredVerticesInZone");
          state.visited_not_covered_vertices_out_of_zone =
              s.at("VisitedNotCoveredVerticesOutOfZone");
          state.step_when_moved_last_time = s.at("StepWhenMovedLastTime");
          state.instructions_visited_in_current_block =
              s.at("InstructionsVisitedInCurrentBlock");
          Graph::State::HistoryVertex hv;
          nlohmann::json j_history = s.at("History");
          for (auto &j_hv : j_history) {
            try {
              hv.id = j_hv.at("GraphVertexId");
              hv.num_of_visits = j_hv.at("NumOfVisits");
              hv.step_when_visited_last_time =
                  j_hv.at("StepWhenVisitedLastTime");
            } catch (...) {
              throw;
            }
            state.history.emplace_back(hv);
          }
        } catch (...) {
          throw;
        }

        g.states[id] = state;
      }

      for (auto &v : j_vertices) {
        Graph::Vertex vertex;
        int id;
        try {
          id = v.at("Id");
          vertex.contains_call = v.at("ContainsCall");
          vertex.contains_throw = v.at("ContainsThrow");
          vertex.covered_by_test = v.at("CoveredByTest");
          vertex.in_coverage_zone = v.at("InCoverageZone");
          vertex.visited_by_state = v.at("VisitedByState");
          vertex.touched_by_state = v.at("TouchedByState");
          vertex.states = v.at("States").get<std::vector<int>>();
        } catch (...) {
          throw;
        }
        g.vertices[id] = vertex;
      }

      for (auto &e : j_edges) {
        Graph::Edge edge;
        try {
          edge.from = e.at("VertexFrom");
          edge.to = e.at("VertexTo");
        } catch (...) {
          throw;
        }
        g.edges.push_back(edge);
      }
      gs.emplace_back(g);
    } else if (filename.contains(movedStateSuffix)) {
      std::cout << "move" << std::endl;
    } else if (filename.contains(infoSuffix)) {
      std::cout << "info" << std::endl;
    } else if (filename.contains("result")) {
      std::cout << "info" << std::endl;
    } else {
      std::cerr << "[Warning]: unexpected file " + filename << std::endl;
    }
  }
  return gs;
}
