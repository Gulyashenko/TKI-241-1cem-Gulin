#include "OurEx3.h"

namespace miit::algebra
{
    OurEx3::OurEx3(size_t size, std::unique_ptr<Generator> gen) : Exercise(size, gen)
    {
    }
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
