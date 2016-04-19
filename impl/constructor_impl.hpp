namespace dep {
template <class V>
inline Constructor<V>::Constructor(Graph&& graph)
  : graph_(std::move(graph)), source_(this->graph_.getSourceVertices()) {
}

template <class V>
inline Constructor<V>::Constructor(size_t size) : graph_(size) {
}

template <class V>
template <class OrderedVertices>
Constructor<V>::Constructor(const OrderedVertices& vertices)
  : graph_(vertices.size()) {
  this->addVertices(vertices);
}

template <class V>
inline auto Constructor<V>::getGraph() const -> const Graph& {
  return this->graph_;
}

template <class V>
auto Constructor<V>::addVertex(const V& v, const V& prev) -> bool {
  if(this->_existFootprint(v)) return false;
  this->_leaveFootprint(v);
  bool add_flg = false;
  for(const auto& next : this->graph_.getNextVertices(v)) {
    add_flg |= this->addVertex(next);
  }
  if(add_flg) return true;
  if(!dep::isDependent(prev, v)) return false;
  this->graph_.addEdge(prev, v);
  return true;
}

template <class V>
auto Constructor<V>::addVertex(const V& v) -> void {
  this->graph_.addVertex(v);
  this->_clearFootprints();
  if(this->sources_.empty()) {
    this->sources_.insert(v);
    return;
  }
  for(const auto& source : this->sources_) {
    this->addVertex(v, source);
  }
  if(!this->graph_.getInDegree(v)) this->sources_.insert(v);
}

template <class V>
template <class OrderedVertices>
auto Constructor<V>::addVertices(const OrderedVertices& vertices) -> void {
  for(const auto& v : vertices) {
    this->addVertex(v);
  }
}
}
