#ifndef INC_RINGBUFFER_HPP_
#define INC_RINGBUFFER_HPP_

#include "stddef.h"
#include <stdbool.h>

template<size_t TMaxSize, typename T>
class RingBuffer {
private:
  static_assert(TMaxSize % 2 == 0, "Size must be a power of 2");
  T _data[TMaxSize];
  size_t _readIndex {0};
  size_t _writeIndex {0};

  size_t mask(size_t index) const {
	  return index & (TMaxSize - 1);
  }
public:
  RingBuffer() {
	  clear();
  }
  inline bool write(const T& value) {
    if(full())
      return false;
    _data[mask(_writeIndex++)] = value;
    return true;
  }

  inline bool write(const T* data, size_t length) {
	  for(size_t i = 0; i < length; ++i) {
		  if(!write(data[i]))
			  return false;
	  }
	  return true;
  }

  inline bool read(T& value) {
    if(empty())
      return false;
    value = _data[mask(_readIndex++)];
    return true;
  }

  inline bool empty() const {
    return size() == 0;
  }

  inline bool full() const {
    return size() == TMaxSize;
  }

  inline size_t size() const {
    return _writeIndex - _readIndex;
  }

  inline void clear() {
    _readIndex = _writeIndex;
  }

  constexpr size_t max_size() {
	  return TMaxSize;
  }
};

#endif /* INC_RINGBUFFER_HPP_ */
