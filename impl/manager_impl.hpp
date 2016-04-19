namespace dep {
template <class V>
Manager<V>::Manager(const Graph& graph)
  : graph_(graph),
    active_(graph.getSourceVertices()),
    checked_(graph.getSize()) {
}

template <class V>
template <template <class...> class T>
auto Manager<V>::_countDependentVertices(const T<V>& vertices) const -> int {
  int count = 0;
  for(const auto& v : vertices) {
    if(this->_existFootprint(v)) continue;
    this->_leaveFootprint(v);
    const auto& next = this->graph_.getNextVertices(v);
    count += this->_countDependentVertices(next) + next.size();
  }
  return count;
}

template <class V>
inline auto Manager<V>::getActiveVertices() const -> const Vertices& {
  return this->active_;
}

template <class V>
inline auto Manager<V>::isChecked(const V& v) const -> bool {
  return this->checked_.cend() != this->checked_.find(v);
}

template <class V>
inline auto Manager<V>::isCompleted() const -> bool {
  return this->active_.empty();
}

template <class V>
auto Manager<V>::canActivate(const V& v) -> bool {
  for(const auto& prev : this->graph_.getPrevVertices(v)) {
    if(!this->isChecked(prev)) return false;
  }
  return true;
}

template <class V>
auto Manager<V>::check(const V& v) -> void {
  this->checked_.insert(v);
  this->active_.erase(v);
  for(const auto& next : this->graph_.getNextVertices(v)) {
    if(this->canActivate(v)) this->active_.insert(next);
  }
}

template <class V>
template <template <class...> class T>
auto Manager<V>::check(const T<V>& vertices) -> void {
  for(const auto& v : vertices) {
    this->check(v);
  }
}

template <class V>
inline auto Manager<V>::countDependentVertices(const V& v) const -> int {
  return this->_countDependentVertices(this->graph_.getNextVertices(v));
}

template <class V>
template <template <class...> class T>
inline auto Manager<V>::countDependentVertices(const T<V>& vertices) const
  -> int {
  this->_clearFootprints();
  return this->_countDependentVertices(vertices);
}

template <class V>
auto Manager<V>::createCriticalPathList() const -> std::unordered_map<V, int> {
  std::unordered_map<V, int> critical_path;
  std::function<void(const V&)> update;
  for(const auto& sink : this->graph_.getSinkVertices()) {
    (update = [&](const V& v) {
      for(const auto& prev : this->graph_.getPrevVertices(v)) {
        if(critical_path[v] + 1 <= critical_path[prev]) continue;
        critical_path[prev] = critical_path[v] + 1;
        update(prev);
      }
    })(sink);
  }
  return std::move(critical_path);
}
}
