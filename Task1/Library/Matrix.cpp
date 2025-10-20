#include "Matrix.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>

namespace miit::algebra
{
    template<typename T>
    Matrix<T>::Matrix() : data(nullptr), size(0) {}

    template<typename T>
    Matrix<T>::Matrix(size_t size) : size(size)
    {
        data = std::make_unique<T[]>(size);
    }

    template<typename T>
    Matrix<T>::Matrix(const Matrix& other) : size(other.size)
    {
        data = std::make_unique<T[]>(size);
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = other.data[i];
        }
    }

    template<typename T>
    Matrix<T>::Matrix(Matrix&& other) noexcept 
        : data(std::move(other.data)), size(other.size)
    {
        other.size = 0;
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator=(const Matrix& other)
    {
        if (this != &other)
        {
            size = other.size;
            data = std::make_unique<T[]>(size);
            for (size_t i = 0; i < size; ++i)
            {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept
    {
        if (this != &other)
        {
            data = std::move(other.data);
            size = other.size;
            other.size = 0;
        }
        return *this;
    }

    template<typename T>
    size_t Matrix<T>::get_size() const
    {
        return size;
    }

    template<typename T>
    T& Matrix<T>::operator[](size_t index)
    {
        if (index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    template<typename T>
    const T& Matrix<T>::operator[](size_t index) const
    {
        if (index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    template<typename T>
    Matrix<T> Matrix<T>::operator<<(int shift) const
    {
        Matrix result(size);
        shift = shift % static_cast<int>(size);
        if (shift < 0) shift += size;
        
        for (size_t i = 0; i < size; ++i)
        {
            result[(i + shift) % size] = data[i];
        }
        return result;
    }

    template<typename T>
    Matrix<T> Matrix<T>::operator>>(int shift) const
    {
        return *this << (-shift);
    }

    template<typename T>
    void Matrix<T>::fill(Generator& generator)
    {
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = static_cast<T>(generator.generate());
        }
    }

    template<typename T>
    void Matrix<T>::fill_zeros()
    {
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = T{};
        }
    }

    template<typename T>
    void Matrix<T>::fill_const(const T& value)
    {
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = value;
        }
    }

    template<typename T>
    std::string Matrix<T>::to_string() const
    {
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < size; ++i)
        {
            oss << data[i];
            if (i < size - 1) oss << ", ";
        }
        oss << "]";
        return oss.str();
    }

    template class Matrix<int>;
}
