/**
 * @file footprints.hpp
 * @brief header of Footprints class
 */

#pragma once

#include "graph.hpp"

namespace dep {
using graph::DirectedGraph;

template <class V>
class Footprints {
 protected:
  using Graph = graph::DirectedGraph<V>;
  using Vertices = Graph::Vertices;

  mutable Vertices footprints_;

  auto _clearFootprints() const -> void;
  auto _leaveFootprint(const V& v) const -> void;
  auto _existFootprint(const V& v) const -> bool;

  Footprints() = delete;
  virtual ~Footprints() = default;
};
}

#include "impl/footprints_impl.hpp"
