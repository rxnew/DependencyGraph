/**
 * @file manager.hpp
 * @brief header of Manager class
 */

#pragma once

#include "footprints.hpp"

namespace dep {
template <class V>
class Manager : Footprints<V> {
 private:
  using Graph = dag::Graph<V>;
  using Vertices = Graph::Vertices;

  const Graph& graph_;
  Vertices active_;
  Vertices checked_;

  template <template <class...> class T>
  auto _countDependentVertices(const T<V>& vertices) const -> int;

 public:
  explicit Manager(const Graph& graph);
  Manager(const Manager&) = default;
  Manager(Manager&&) noexcept = default;
  ~Manager() = default;

  auto getActiveVertices() const -> const Vertices&;
  auto isChecked(const V& v) const -> bool;
  auto isCompleted() const -> bool;
  auto canActivate() const -> bool;
  auto check(const V& v) -> void;
  template <template <class...> class T>
  auto check(const T<V>& vertices) -> void;
  auto countDependentVertices(const V& v) -> int;
  template <template <class...> class T>
  auto countDependentVertices(const T<V>& vertices) const -> int;
  auto createCriticalPathMap() const -> std::unordered_map<V, int>;
};
}

#include "impl/manager_impl.hpp"
