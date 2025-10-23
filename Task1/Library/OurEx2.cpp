#include "OurEx2.h"
#include <cmath>
#include <memory>

namespace miit::algebra{
    void OurEx2::Task2(){
        if (matrix->get_size() == 0) return;

        auto temp = std::make_unique<int[]>(matrix->get_size());
        size_t new_size = 0;

        for (size_t i=0; i < matrix->get_size(); i++){
            int number = (*matrix)[i];
            int first_digit = GetFirst_Digit(number);
            int last_digit = Get_LastDigit(number);

            if(!(Is_Even_Digit(first_digit) && Is_Even_Digit(last_digit))){
                temp[new_size++] = number;
            }
        }
        auto new_matrix = std::make_unique<Matrix<int>>(new_size);
        for (size_t i=0; i< new_size; ++i){
            (*new_matrix)[i]=temp[i];
        }
        matrix = std::move(new_matrix);
    }

    int OurEx2::Get_LastDigit(int number) const{
        return std::abs(number)%10;
    }

    int OurEx2::GetFirst_Digit(int number) const{
        number = std::abs(number);
        while (number>= 10){
            number /= 10;
        }
        return number;
    }

    bool OurEx2::Is_Even_Digit(int digit) const {
        return digit%2==0;
    }
}
