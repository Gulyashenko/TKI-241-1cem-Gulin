#include "OurEx3.h"

namespace miit::algebra
{
    /**
     * @brief Task3 - creating new array by rule
     * @param D array
     * @return new array A
     */
    void OurEx3::Task() {
        size_t size = matrix->get_size();
        
        for (size_t i = 0; i < size; ++i)
        {
            if (i >= 2 && i < 12)
            {
                (*matrix)[i] = -(*matrix)[i] * (*matrix)[i];
            }
            else
            {
                (*matrix)[i] = (*matrix)[i] - 1;
            }
        }
    }
}
