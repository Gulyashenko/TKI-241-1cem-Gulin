#pragma once
#include "Matrix.h"
#include "Generator.h"
#include <memory>

namespace miit::algebra
{
    /**
     * @brief Абстрактный класс для выполнения заданий
     */
    class Exercise
    {
    protected:
        std::unique_ptr<Matrix<int>> matrix;
        std::unique_ptr<Generator> generator;
        
    public:
        /**
         * @brief Constructor
         * @param size - size of array
         * @param gen - generator of array
         */
        Exercise(size_t size, std::unique_ptr<Generator> gen);
        
        /**
         * @brief virtual distructor
         */
        virtual ~Exercise() = default;
        
        /**
         * @brief filling array
         */
        void fill_matrix();
        
        /**
         * @brief getting array
         * @return array
         */
        const Matrix<int>& get_matrix() const;
        
        /**
         * @brief Task1 - replace minimal by modul element
         */
        virtual void Task1() = 0;
        
        /**
         * @brief Task2 - delite elements with even first and last digit
         */
        virtual void Task2() = 0;
        
        /**
         * @brief Задание 3 - creating new array by rule
         * @param D array
         * @return new array A
         */
        virtual Matrix<int> Task3(const Matrix<int>& D) = 0;
    };
}
