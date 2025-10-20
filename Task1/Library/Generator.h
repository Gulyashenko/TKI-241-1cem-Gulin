#pragma once

namespace miit::algebra
{
    /**
     * @brief Abstract class generator
     */
    class Generator 
    {
        public:
            /**
             * @brief virtual distructor
             */
            virtual ~Generator() = default;

            /**
             * @brief Generating value
             * @return generated value
             */
            virtual int generate() = 0;
    };
}
