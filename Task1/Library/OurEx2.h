#pragma once
#include "Exercise.h"

namespace miit::algebra

{
    /**
     * @brief concrete realisation of task 2
     */
    class OurEx2 : public Exercise{
        public:
            using Exercise::Exercise;

            /**
             * @brief Task2 - delete elements with even first and last digit
             */
            void Task2() override;

        private:
            /**
             * @brief getting first digit of number
             * @param number
             * @return digit
             */
            int GetFirst_Digit(int number) const;

            /**
             * @brief getting last digit of number
             * @param number
             * @return digit
             */
            int Get_LastDigit(int number) const;

            /**
             * @brief even or not
             * @param digit
             * @return true if even, false if not
             */
            bool Is_Even_Digit(int digit) const;
    };
}
