#include "Exercise.h"

namespace miit::algebra
{
    class OurEx3 : public Exercise
    {
        public:
            using Exercise::Exercise;
            /**
             * @brief constructor
             */
            OurEx3(size_t size, std::unique_ptr<Generator> gen);

            /**
             * @brief Task3 - creating new array by rule
             * @param D array
             * @return new array A
             */
            void Task() override;
    };
}
