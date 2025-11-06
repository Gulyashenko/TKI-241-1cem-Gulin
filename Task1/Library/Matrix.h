#pragma once
#include <memory>
#include <string>
#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Шаблонный класс одномерного массива
     */
    template<typename T>
    class Matrix
    {
    private:
        std::unique_ptr<T[]> data;
        size_t size;
        
    public:
        /**
         * @brief constructors
         */
        Matrix();
        Matrix(size_t size);
        Matrix(const Matrix& other);
        Matrix(Matrix&& other) noexcept;
        
        /**
         * @brief destructor
         */
        ~Matrix() = default;
        
        /**
         * @brief operators
         */
        Matrix& operator=(const Matrix& other);
        Matrix& operator=(Matrix&& other) noexcept;
        
        /**
         * @brief function for getting size
         */
        size_t get_size() const;
        /**
         * @brief function for getting element
         * @param index
         */
        T& operator[](size_t index);
        /**
         * @brief function for getting element
         * @param index
         */
        const T& operator[](size_t index) const;
        
        /**
         * @brief shift operators
         */
        Matrix operator<<(int shift) const;
        Matrix operator>>(int shift) const;
        
        /**
         * @brief filling array
         */
        void fill(Generator& generator);
        
        /**
         * @brief converting to string
         */
        std::string to_string() const;
    };
}
