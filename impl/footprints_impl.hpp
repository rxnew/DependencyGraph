namespace dep {
template <class T>
inline auto Footprints<T>::clear() -> void {
  this->footprints_.clear();
}

template <class T>
inline auto Footprints<T>::leave(const T& x) -> void {
  this->footprints_.insert(x);
}

template <class T>
inline auto Footprints<T>::exist(const T& x) const -> bool {
  return this->footprints_.cend() != this->footprints_.find(x);
}
}
