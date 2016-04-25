#pragma once

namespace dep {
template <class V>
using Graph = graph::DirectedGraph<V>;

// Please specialize the following function
// This function returns 'true', if 'u' depends on 'v'.
template <class V>
auto isDependent(const V& v, const V& u) -> bool;
}

#include "constructor.hpp"
#include "manager.hpp"
