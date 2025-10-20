#pragma once
#include "Generator.h"
#include <random>

namespace miit::algebra
{
    /**
     * @brief Class random generator
     */
    class RandomGenerator : public Generator
    {
    private:
        std::uniform_int_distribution<int> distribution;
        std::mt19937 generator;

    public:
        /**
         * brief constructor
         * @param min - minimal value
         * @param max - maximum value
         */
        RandomGenerator(const int min, const int max);

        /**
         * @brief Generating value
         * @return generated value
         */
        int generate() override;
    };
}
