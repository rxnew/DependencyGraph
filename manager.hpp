/**
 * @file manager.hpp
 * @brief header of Manager class
 */

#pragma once

#include <memory>

#include "footprints.hpp"

namespace dep {
template <class V>
class Manager {
 private:
  using Graph = graph::DirectedGraph<V>;
  using Vertices = typename Graph::Vertices;

  std::shared_ptr<Graph> graph_;
  Vertices active_;
  Vertices checked_;
  mutable Footprints<V> footprints_;

  template <template <class...> class T>
  auto _countDependentVertices(const T<V>& vertices) const -> int;

 public:
  explicit Manager(const std::shared_ptr<Graph>& graph);
  Manager(const Manager& other);
  Manager(Manager&& other) noexcept;
  ~Manager() = default;

  auto operator=(const Manager& other) -> Manager&;
  auto operator=(Manager&& other) -> Manager&;

  auto getActiveVertices() const -> const Vertices&;
  auto isChecked(const V& v) const -> bool;
  auto isCompleted() const -> bool;
  auto canActivate(const V& v) const -> bool;
  auto check(const V& v) -> void;
  template <template <class...> class T>
  auto check(const T<V>& vertices) -> void;
  auto clear() -> void;
  auto countDependentVertices(const V& v) const -> int;
  template <template <class...> class T>
  auto countDependentVertices(const T<V>& vertices) const -> int;
  auto createCriticalPathList() const -> std::unordered_map<V, int>;
};
}

#include "impl/manager_impl.hpp"
