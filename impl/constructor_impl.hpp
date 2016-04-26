namespace dep {
template <class V>
inline Constructor<V>::Constructor()
  : graph_(new Graph()) {
}

template <class V>
inline Constructor<V>::Constructor(std::unique_ptr<Graph>&& graph)
  : graph_(std::move(graph)), sources_(this->graph_->getSourceVertices()) {
}

template <class V>
inline Constructor<V>::Constructor(Graph*&& graph)
  : graph_(std::move(graph)), sources_(this->graph_->getSourceVertices()) {
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
  return *this->graph_;
}

template <class V>
inline auto Constructor<V>::moveGraph() -> std::unique_ptr<Graph> {
  return std::move(this->graph_);
}

template <class V>
auto Constructor<V>::addVertex(const V& v, const V& pos) -> bool {
  if(this->footprints_.exist(pos)) return false;
  this->footprints_.leave(pos);
  bool add_flg = false;
  for(const auto& next : this->graph_->getNextVertices(pos)) {
    add_flg |= this->addVertex(v, next);
  }
  if(add_flg) return true;
  if(!dep::isDependent(pos, v)) return false;
  this->graph_->addEdge(pos, v);
  return true;
}

template <class V>
auto Constructor<V>::addVertex(const V& v) -> void {
  this->graph_->addVertex(v);
  this->footprints_.clear();
  if(this->sources_.empty()) {
    this->sources_.insert(v);
    return;
  }
  for(const auto& source : this->sources_) {
    this->addVertex(v, source);
  }
  if(!this->graph_->getIndegree(v)) this->sources_.insert(v);
}

template <class V>
template <class OrderedVertices>
auto Constructor<V>::addVertices(const OrderedVertices& vertices) -> void {
  for(const auto& v : vertices) {
    this->addVertex(v);
  }
}
}
