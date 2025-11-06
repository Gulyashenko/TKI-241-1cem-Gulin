#pragma once
#include "Generator.h"
#include <iostream>

namespace miit::algebra
{
    /**
     * @brief Class input stream generator
     */
    class IStreamGenerator : public Generator
    {
    private:
        std::istream& in;
    public:
        /**
         * @brief constructor
         * @param in - input stream
         */
        IStreamGenerator(std::istream& in = std::cin){}

        /**
         * @brief Reading value from stream
         * @return readed value
         */
        int generate() override;
    };
}
