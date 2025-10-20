#include "Exercise.h"

namespace miit::algebra
{
    Exercise::Exercise(size_t size, std::unique_ptr<Generator> gen)
        : matrix(std::make_unique<Matrix<int>>(size))
        , generator(std::move(gen))
    {
    }

    void Exercise::fill_matrix()
    {
        matrix->fill(*generator);
    }

    const Matrix<int>& Exercise::get_matrix() const
    {
        return *matrix;
    }
}
