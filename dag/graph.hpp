/**
 * @file graph.hpp
 * @brief header of Graph class
 */

#pragma once

#include <unordered_set>
#include <unordered_map>

namespace dag {
template <class V>
class Graph {
 public:
  using Vertices = std::unordered_set<V>;
  using AdjacencyList = std::unordered_map<V, Vertices>;

 private:
  AdjacencyList next_;
  AdjacencyList prev_;

 public:
  Graph() = default;
  explicit Graph(size_t size);
  explicit Graph(const Vertices& vertices);
  explicit Graph(Vertices&& vertices);
  Graph(const Graph&) = default;
  Graph(Graph&&) = default;
  ~Graph() = default;

  auto getVertices() const -> const Vertices&;
  auto getNextVertices(const V& v) const -> const Vertices&;
  auto getPrevVertices(const V& v) const -> const Vertices&;
  auto getOutdegree(const V& v) const -> size_t;
  auto getIndegree(const V& v) const -> size_t;
  auto addVertex(const V& v) -> void;
  auto removeVertex(const V& v) -> void;
  auto addEdge(const V& v, const V& u) -> void;
  auto removeEdge(const V& v, const V& u) -> void;
  auto existEdge(const V& v, const V& u) const -> bool;
};
}

#include "impl/graph_impl.hpp"
