/**
 * @file constructor.hpp
 * @brief header of Constructor class
 */

#pragma once

#include <memory>

#include "footprints.hpp"

namespace dep {
template <class V>
class Constructor {
 private: 
  using Graph = graph::DirectedGraph<V>;
  using Vertices = typename Graph::Vertices;

  std::unique_ptr<Graph> graph_;
  Vertices sources_;
  mutable Footprints<V> footprints_;

 public:
  Constructor();
  explicit Constructor(std::unique_ptr<Graph>&& graph);
  explicit Constructor(Graph*&& graph);
  explicit Constructor(size_t size);
  template <class OrderedVertices>
  explicit Constructor(const OrderedVertices& nodes);
  Constructor(Constructor&&) noexcept = default;
  ~Constructor() = default;

  auto operator=(Constructor&&) -> Constructor& = default;

  auto getGraph() const -> const Graph&;
  auto moveGraph() -> std::unique_ptr<Graph>;
  auto addVertex(const V& v, const V& pos) -> bool;
  auto addVertex(const V& v) -> void;
  template <class OrderedVertices>
  auto addVertices(const OrderedVertices& vertices) -> void;
};
}

#include "impl/constructor_impl.hpp"
