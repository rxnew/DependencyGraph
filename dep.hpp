#pragma once

#include "constructor.hpp"
#include "manager.hpp"

namespace dep {
// Please specialize the following function
// This function returns 'true', if 'u' depends on 'v'.
template <class V>
auto isDependent(const V& v, const V& u) -> bool;
}