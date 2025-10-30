#include "ConstantGenerator.h"

namespace miit::algebra{
  ConstantGenerator::ConstantGenerator(double value) : value(value){}

  int ConstantGenerator::generate(){return value;}
}
