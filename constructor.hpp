/**
 * @file constructor.hpp
 * @brief header of Constructor class
 */

#pragma once

#include "dag/graph.hpp"

namespace dep {
using dag::Graph;

template <class Node>
class Constructor {
 private:
  Graph<V> graph_;
  Vertices sources_;
  Vertices footprints_;

  auto _leaveFootprint(const V& v) const -> void;
  auto _existFootprint(const V& v) const -> bool;

 public:
  Constructor() = default;
  explicit Constructor(Graph&& graph);
  explicit Constructor(size_t size);
  template <class OrderedVertices>
  explicit Constructor(const Vertices& nodes);
  Constructor(const Constructor&) = default;
  Constructor(Constructor&&) = default;
  ~Constructor() = default;

  auto getGraph() const -> const Graph<V>&;
  auto addVertex(const V& v, const V& prev) -> bool;
  auto addVertex(const V& v) -> void;
  template <class OrderedVertices>
  auto addVertices(const OrderedVertices& vertices) -> void;
};
}

#include "impl/constructor_impl.hpp"