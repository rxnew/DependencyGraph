/**
 * @file constructor.hpp
 * @brief header of Constructor class
 */

#pragma once

#include "footprints.hpp"

namespace dep {
template <class V>
class Constructor : Footprints<V> {
 private:
  using Super = Footprints<V>;
  using Graph = typename Super::Graph;
  using Vertices = typename Super::Vertices;

  Graph graph_;
  Vertices sources_;

 public:
  Constructor() = default;
  explicit Constructor(Graph&& graph);
  explicit Constructor(size_t size);
  template <class OrderedVertices>
  explicit Constructor(const OrderedVertices& nodes);
  Constructor(const Constructor&) = default;
  Constructor(Constructor&&) noexcept = default;
  ~Constructor() = default;

  auto operator=(const Constructor&) -> Constructor& = default;
  auto operator=(Constructor&&) -> Constructor& = default;

  auto getGraph() const -> const Graph&;
  auto addVertex(const V& v, const V& prev) -> bool;
  auto addVertex(const V& v) -> void;
  template <class OrderedVertices>
  auto addVertices(const OrderedVertices& vertices) -> void;
};
}

#include "impl/constructor_impl.hpp"
