#ifndef STATIC_BUFFER_HPP
#define STATIC_BUFFER_HPP

#include <stddef.h>
#include "buffer.hpp"
#include <initializer_list>

template <typename T, size_t TMaxSize>
class static_buffer : public buffer<T> {
public:
    static_buffer() :
        buffer<T>(_bufferData, TMaxSize)
    {
    }
    static_buffer(std::initializer_list<T> list) :
    	static_buffer()
    {
    	buffer<T>::append(list.begin(), list.end());
    }
    static_buffer& operator=(const buffer<T>& other) {
        buffer<T>::operator =(other);
        return *this;
    }
private:
    T _bufferData[TMaxSize];
};


#endif // STATIC_BUFFER_HPP
