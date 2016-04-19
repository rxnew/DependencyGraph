namespace dep {
template <class V>
inline auto Footprints<V>::_clearFootprints() const -> void {
  this->footprints_.clear();
}

template <class V>
inline auto Footprints<V>::_leaveFootprint(const V& v) const -> void {
  this->footprints_.insert(v);
}

template <class V>
inline auto Footprints<V>::_existFootprint(const V& v) const -> bool {
  return this->footprints_.cend() != this->footprints_.find(v);
}
}
