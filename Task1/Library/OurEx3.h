#include "Exercise.h"

namespace miit::algebra
{
    class OurEx3 : public Exercise
    {
        public:
            using Exercise::Exercise;
            /**
             * @brief Task3 - creating new array by rule
             * @param D array
             * @return new array A
             */
            void Task() override;
    };
}
