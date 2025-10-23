#pragma once
#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief concrete realisition of task1
     */
    class OurEx1 : public Exercise
    {
    public:
        using Exercise::Exercise;
        
        /**
         * @brief Task1 - replacing of minimal by modul element 
         */
        void Task1() override;
        };
}
