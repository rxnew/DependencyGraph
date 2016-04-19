#pragma once

#include <cassert>

namespace dag {
template <class V>
auto Graph<V>::_initAdjacencyList() -> void {
  for(const auto& v : this->vertices_) {
    this->out_.emplace(v, Vertices());
  }
}

template <class V>
inline Graph<V>::Graph(size_t size)
  : vertices_(size), next_(size), prev_(size) {
}

template <class V>
inline Graph<V>::Graph(const Vertices& vertices)
  : vertices_(vertices), next_(vertices.size()), prev_(vertices.size()) {
  this->_initAdjacencyList();
}

template <class V>
inline Graph<V>::Graph(Vertices&& vertices)
  : vertices_(std::move(vertices)),
    next_(vertices.size()),
    prev_(vertices.size()) {
  this->_initAdjacencyList();
}

template <class V>
inline auto Graph<V>::getVertices() const -> const Vertices& {
  return this->vertices_;
}

template <class V>
auto Graph<V>::getSourceVertices() const -> Vertices {
  Vertices source_vertices;
  for(const auto& v : this->vertices_) {
    if(!this->getIndegree(v)) source_vertices.insert(v);
  }
  return std::move(source_vertices);
}

template <class V>
auto Graph<V>::getSinkVertices() const -> Vertices {
  Vertices sink_vertices;
  for(const auto& v : this->vertices_) {
    if(!this->getOutdegree(v)) sink_vertices.insert(v);
  }
  return std::move(sink_vertices);
}

template <class V>
inline auto Graph<V>::getNextVertices(const V& v) const -> const Vertices& {
  auto pos = this->next_.find(v);
  assert(pos != this->next_.cend());
  return pos->second;
}

template <class V>
inline auto Graph<V>::getPrevVertices(const V& v) const -> const Vertices& {
  auto pos = this->prev_.find(v);
  assert(pos != this->prev_.cend());
  return pos->second;
}

template <class V>
inline auto Graph<V>::getInVertices(const V& v) const -> const Vertices& {
  auto pos = this->prev_.find(v);
  assert(pos != this->prev_.cend());
  return pos->second;
}

template <class V>
inline auto Graph<V>::getOutdegree(const V& v) const -> size_t {
  return this->getNextVertices(v).size();
}

template <class V>
inline auto Graph<V>::getIndegree(const V& v) const -> size_t {
  return this->getPrevVertices(v).size();
}

template <class V>
inline auto Graph<V>::getSize() const -> size_t {
  return this->vertices.size();
}

template <class V>
inline auto Graph<V>::addVertex(const V& v) -> void {
  this->vertices_.insert(v);
  this->next_.emplace(v, Vertices());
  this->prev_.emplace(v, Vertices());
}

template <class V>
auto Graph<V>::removeVertex(const V& v) -> void {
  this->vertices_.erase(v);
  for(const auto& u : this->next_[v]) {
    this->next_[u].erase(v);
  }
  this->next_.erase(v);
}

template <class V>
inline auto Graph<V>::addEdge(const V& v, const V& u) -> void {
  this->next_[v].insert(u);
  this->prev_[u].insert(v);
}

template <class V>
inline auto Graph<V>::removeEdge(const V& v, const V& u) -> void {
  this->next_[v].erase(u);
  this->prev_[u].erase(v);
}

template <class V>
inline auto Graph<V>::existEdge(const V& v, const V& u) const -> bool {
  return this->next_[v].count(u);
}
}
