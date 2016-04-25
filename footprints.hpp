/**
 * @file footprints.hpp
 * @brief header of Footprints class
 */

#pragma once

#include <unordered_set>

namespace dep {
template <class T>
class Footprints {
 private:
  std::unordered_set<T> footprints_;

 public:
  Footprints() = default;
  Footprints(const Footprints&) = default;
  Footprints(Footprints&&) noexcept = default;
  ~Footprints() = default;

  auto operator=(const Footprints&) -> Footprints& = default;
  auto operator=(Footprints&&) -> Footprints& = default;

  auto clear() -> void;
  auto leave(const T& x) -> void;
  auto exist(const T& x) const -> bool;
};
}

#include "impl/footprints_impl.hpp"
