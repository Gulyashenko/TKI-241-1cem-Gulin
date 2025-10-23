#include "OurEx3.h"

namespace miit::algebra
{
    /**
     * @brief Task3 - creating new array by rule
     * @param D array
     * @return new array A
     */
    Matrix<int> OurEx3::Task3(const Matrix<int>& D) {
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
}
