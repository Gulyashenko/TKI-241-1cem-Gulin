#pragma once
#include "Generator.h"

nemespase miit::algebra{
  /**
   * @brief Class constant Generator
   */ 
  class ConstantGenerator : public generator{
    private:
      double vavue;
    public:
      /**
       * @brief constructor
       */
      ConstantGenerator(double value);

      int generate() override;
  };
}
