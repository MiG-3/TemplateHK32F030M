#ifndef BUFFER_MAPPING_HPP
#define BUFFER_MAPPING_HPP

#include <stddef.h>
#include <iterator>
#include <string.h>
#include <algorithm>
#include <Libs/Utils/DebugAssert.h>

template <typename T>
class buffer
{
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    using value_type = T;

    buffer() :
        _array(nullptr),
        _maxSize(0),
        _size(0)
    {
    }

    buffer(T* array, size_t maxSize, size_t size = 0) :
      _array(array),
      _maxSize(maxSize),
      _size(size)
    {
        DEBUG_ASSERT(_array != nullptr);
        DEBUG_ASSERT(_maxSize != 0);
        DEBUG_ASSERT(_size <= _maxSize);
    }

    buffer(buffer& other) :
        _array(other._array),
        _maxSize(other._maxSize),
        _size(other._size)
    {
        DEBUG_ASSERT(_array != nullptr);
        DEBUG_ASSERT(_maxSize != 0);
        DEBUG_ASSERT(_size <= _maxSize);
    }

    buffer(buffer&& src) :
    	_array(src._array),
		_maxSize(src._maxSize),
		_size(src._size)
    {
        src._array = 0;
        src._maxSize = 0;
        src._size = 0;
    }

    buffer<T>& operator = (const buffer& other) {
    	_array = other._array;
		_maxSize = other._maxSize;
		_size = other._size;
		return *this;
    }

    bool operator == (const buffer<T>& other) const {
        if(size() != other.size()) {
            return false;
        }
        for(size_t cnt = 0; cnt < size(); ++cnt) {
            if((*this)[cnt] != other[cnt]) {
                return false;
            }
        }
        return true;
    }

    T& operator [] (size_t index) {
        check_index(index);
        return _array[index];
    }

    const T& operator [] (size_t index) const {
        check_index(index);
        return _array[index];
    }

    T& front() {
        return _array[first_element_index()];
    }

    const T& front() const {
        return _array[first_element_index()];
    }

    T& back() {
        return _array[last_element_index()];
    }

    const T& back() const {
        return _array[last_element_index()];
    }

    T* data() {
        return _array;
    }

    const T* data() const {
        return _array;
    }


    iterator begin() {
        return _array;
    }

    const_iterator begin() const {
        return _array;
    }

    iterator end() {
        return _array + _size;
    }

    const_iterator end() const {
        return _array + _size;
    }

    std::reverse_iterator<iterator> rbegin() {
        return std::reverse_iterator<iterator>(end());
    }

    std::reverse_iterator<const_iterator> rbegin() const {
        return std::reverse_iterator<const_iterator>(end());
    }

    std::reverse_iterator<iterator> rend() {
        return std::reverse_iterator<iterator>(begin());
    }

    std::reverse_iterator<const_iterator> rend() const {
        return std::reverse_iterator<const_iterator>(begin());
    }

    size_t size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }

    bool full() const {
        return _size == _maxSize;
    }

    size_t max_size() const {
        return _maxSize;
    }

    size_t capacity() const {
        return max_size();
    }

    size_t free_space() const {
        return _maxSize - _size;
    }

    void clear() {
        _size = 0;
    }

    iterator insert(const_iterator pos, const T& value) {
        const T* valuePtr = &value;
        return insert(pos, valuePtr, valuePtr + 1);
    }

    template<typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last) {
        check_iterator(pos);
        iterator insertPos = const_cast<iterator>(pos);
        size_t insertedNumber = std::distance<InputIterator>(first, last);
        size_t relocatedNumber = std::distance<const_iterator>(pos, end());
        increase_size(insertedNumber);
        move(insertPos, insertPos + insertedNumber, relocatedNumber);
        for(InputIterator it = first; it != last; ++it) {
            *(insertPos++) = *it;
        }
        return const_cast<iterator>(pos);
    }

    iterator erase(iterator pos) {
        return erase(pos, pos + 1);
    }

    iterator erase(iterator first, iterator last) {
        check_iterator_is_dereferenceable(first);
        check_iterator(last);
        size_t count = std::distance(first, last);
        if(count == 0) {
            return first;
        }
        size_t relocatedSize = std::distance(last, end());
        decrease_size(count);
        move(last, first, relocatedSize);
        return const_cast<iterator>(first);
    }

    void push_back(const T& value) {
        increment_size();
        _array[last_element_index()] = value;
    }

    void pop_back() {
        assert_that_no_empty();
        _size--;
    }

    template<typename InputIterator>
    void append(InputIterator first, InputIterator last) {
    	insert(end(), first, last);
    }

    void resize(size_t count, const T& value = T()) {
        if(count > _size) {
            extend(count, value);
        } else {
            truncate(count);
        }
    }

protected:
    size_t first_element_index() const {
        assert_that_no_empty();
        return 0;
    }

    size_t last_element_index() const {
        assert_that_no_empty();
        return _size - 1;
    }

    void assert_that_no_empty() const {
        DEBUG_ASSERT(_size != 0);
    }

    void assert_that_can_increase_size(size_t increment) const {
        DEBUG_ASSERT(_maxSize - _size >= increment);
    }

    void assert_that_can_decrease_size(size_t decrement) const {
        DEBUG_ASSERT(_size >= decrement);
    }

    void check_index(size_t index) const {
        DEBUG_ASSERT(index < _size);
    }

    void check_iterator(const_iterator it) const {
        DEBUG_ASSERT((it >= begin()) && (it <= end()));
    }

    void check_iterator_is_dereferenceable(iterator it) const {
        DEBUG_ASSERT((it >= begin() && (it < end())));
    }

    void increment_size() {
        DEBUG_ASSERT(_size < _maxSize);
        ++_size;
    }

    void increase_size(size_t increment) {
        assert_that_can_increase_size(increment);
        _size += increment;
    }

    void decrease_size(size_t decrement) {
        assert_that_can_decrease_size(decrement);
        _size -= decrement;
    }

    void extend(size_t count, const T& value) {
        while(_size < count) {
            push_back(value);
        }
    }

    void truncate(size_t count) {
        _size = count;
    }

    void move(const T* src, T* dst, size_t count) {
        // Note: �� ���� memmove ��� ������ �������, ���� ���������� � ������� �������������.
        memmove(dst, src, count * sizeof(T));
    }


    T* _array;
    size_t _maxSize;
    size_t _size;
};


#endif // BUFFER_MAPPING_HPP
