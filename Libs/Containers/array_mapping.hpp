#ifndef ARRAY_MAPPING_HPP
#define ARRAY_MAPPING_HPP

#include <stddef.h>
#include <cstdint>


#ifndef arraysize
   #define arraysize(a) (sizeof(a) / sizeof(a[0]))
#endif

template <typename T>
class array_mapping
{
public:
    using value_type = T;
    using iterator = T*;
    using const_iterator = const T*;

    constexpr array_mapping(T* data, uint32_t size) :
        _data(data),
        _size(size)
    {}

    array_mapping(const array_mapping<T>& other) :
    	_data(other._data),
		_size(other._size)
    {}

    T* begin() {
        return _data;
    }

    const T* begin() const {
        return _data;
    }

    T* end() {
        return _data + _size;
    }

    const T* end() const {
        return _data + _size;
    }

    T& front() {
        return *_data;
    }

    const T& front() const {
        return *_data;
    }

    T& back() {
        return _data[_size - 1];
    }

    const T& back() const {
        return _data[_size - 1];
    }

    T& operator[](uint32_t index) {
        return _data[index];
    }

    const T& operator[](uint32_t index) const {
        return _data[index];
    }

    uint32_t size() const {
        return _size;
    }

    T* data() {
        return _data;
    }

    const T* data() const {
        return _data;
    }

private:
    T* _data;
    uint32_t _size;
};

#endif // ARRAY_MAPPING_HPP
