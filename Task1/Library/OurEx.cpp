#include "OurEx.h"
#include <cmath>
#include <memory>

namespace miit::algebra
{
    void OurEx::Task1()
    {
        if (matrix->get_size() == 0) return;
        
        int min_abs_positive = -1;
        size_t min_index = 0;
        
        for (size_t i = 0; i < matrix->get_size(); ++i)
        {
            int current = (*matrix)[i];
            if (current > 0)
            {
                if (min_abs_positive == -1 || std::abs(current) < std::abs(min_abs_positive))
                {
                    min_abs_positive = current;
                    min_index = i;
                }
            }
        }
        
        if (min_abs_positive != -1)
        {
            (*matrix)[min_index] = 0;
        }
    }

    void OurEx::Task2()
    {
        if (matrix->get_size() == 0) return;
        
        auto temp = std::make_unique<int[]>(matrix->get_size());
        size_t new_size = 0;
        
        for (size_t i = 0; i < matrix->get_size(); ++i)
        {
            int number = (*matrix)[i];
            int first_digit = get_first_digit(number);
            int last_digit = get_last_digit(number);
            
            if (!(is_even_digit(first_digit) && is_even_digit(last_digit)))
            {
                temp[new_size++] = number;
            }
        }
        
        auto new_matrix = std::make_unique<Matrix<int>>(new_size);
        for (size_t i = 0; i < new_size; ++i)
        {
            (*new_matrix)[i] = temp[i];
        }
        
        matrix = std::move(new_matrix);
    }

    Matrix<int> OurEx::Task3(const Matrix<int>& D)
    {
        size_t size = D.get_size();
        Matrix<int> A(size);
        
        for (size_t i = 0; i < size; ++i)
        {
            if (i >= 2 && i < 12)
            {
                A[i] = -D[i] * D[i];
            }
            else
            {
                A[i] = D[i] - 1;
            }
        }
        
        return A;
    }

    int OurEx::get_first_digit(int number) const
    {
        number = std::abs(number);
        while (number >= 10)
        {
            number /= 10;
        }
        return number;
    }

    int OurEx::get_last_digit(int number) const
    {
        return std::abs(number) % 10;
    }

    bool OurEx::is_even_digit(int digit) const
    {
        return digit % 2 == 0;
    }
}
