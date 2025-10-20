#pragma once
#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief concrete realisition of tasks
     */
    class OurEx : public Exercise
    {
    public:
        using Exercise::Exercise;
        
        /**
         * @brief Task1 - replacing of minimal by modul element 
         */
        void Task1() override;
        
        /**
         * @brief Task2- delete elements with even first and last digit
         */
        void Task2() override;
        
        /**
         * @brief Task3 - creating new array by rule
         * @param D array
         * @return new array A
         */
        Matrix<int> Task3(const Matrix<int>& D) override;
        
    private:
        /**
         * @brief getting first digit of number
         * @param number number
         * @return first digit
         */
        int get_first_digit(int number) const;
        
        /**
         * @brief getting last digit of number
         * @param number number
         * @return last digit
         */
        int get_last_digit(int number) const;
        
        /**
         * @brief even or not
         * @param digit digit
         * @return true if even, false if not
         */
        bool is_even_digit(int digit) const;
    };
}
