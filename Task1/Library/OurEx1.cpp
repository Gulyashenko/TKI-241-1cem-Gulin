#include "OurEx1.h"
#include <cmath>
#include <memory>

namespace miit::algebra
{
    void OurEx1::Task1()
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
}
