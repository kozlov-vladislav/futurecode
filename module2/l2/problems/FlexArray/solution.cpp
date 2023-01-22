#include <iostream>
#include <vector>

template<typename T>
struct FlexArray {
    std::vector<T> vec;
    FlexArray() = default;
    FlexArray(size_t size);
    T& at(size_t index);
    const T& at(size_t index) const;
    size_t Size() const;
    FlexArray& operator += (const FlexArray& another);
    FlexArray& operator *= (size_t number);
};

template<typename T>
FlexArray<T>::FlexArray(size_t size) : vec(size) {};

template<typename T>
T& FlexArray<T>::at(size_t index) {
    return vec[index];
}

template<typename T>
const T& FlexArray<T>::at(size_t index) const {
    return vec[index];
}

template<typename T>
size_t FlexArray<T>::Size() const {
    return vec.size();
}

template<typename T>
FlexArray<T>& FlexArray<T>::operator+=(const FlexArray<T> &another) {
    for (size_t i = 0, n = another.Size(); i < n; ++i) {
        vec.push_back(another.vec[i]);
    }
    return *this;
}

template<typename T>
FlexArray<T>& FlexArray<T>::operator*=(size_t number) {
    if (number <= 1) {
        return *this;
    }
    auto copy = *this;
    for (size_t i = 1; i < number; ++i) {
        *this += copy;
    }
    return *this;
}

template<typename T>
FlexArray<T> operator+(const FlexArray<T>& left, const FlexArray<T>& right) {
    auto res = left;
    res += right;
    return res;
}

template<typename T>
FlexArray<T> operator*(const FlexArray<T>& left, size_t size) {
    auto res = left;
    res *= size;
    return res;
}

template<typename T>
FlexArray<T> operator*(size_t size, const FlexArray<T>& right) {
    return right * size;
}