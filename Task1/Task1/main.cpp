#include <iostream>
#include <memory>
#include <string>
#include "../Library/Matrix.h"
#include "../Library/Exercise.h"
#include "../Library/OurEx1.h"
#include "../Library/OurEx2.h"
#include "../Library/OurEx3.h"
#include "../Library/RandomGenerator.h"
#include "../Library/ConstantGenerator.h"
#include "../Library/IStreamGenerator.h"

namespace miit::algebra
{
    /**
     * @brief Enum for choosing array filling method
     */
    enum class FillMethod
    {
        RANDOM,
        CONSTANT,
        FROM_INPUT
    };

    /**
     * @brief Enum for choosing which task to execute
     */
    enum class TaskChoice
    {
        TASK1,
        TASK2,
        TASK3
    };
    
    /**
     * @brief Input size of array
     * @return size of array
     */
    size_t Input_size(void);

    /**
     * @brief input value
     * @param message message
     * @return value
     */
    double Input(const char* message);

    int main(void)
    {
        using namespace miit::algebra;

            size_t size = Input_size();
            int fill_choice;
            std::cout << "Choose fill method:" << RANDOM << " - random," << CONSTANT
              << " - constant," << FROM_INPUT << " - from input";
            std::cin >> fill_choice;

            FillMethod fill_method;
            switch (fill_choice){
              case RANDOM: FillMethod = FillMethod::RANDOM; break;
              case CONSTANT: FillMethod = FillMethod::CONSTANT; break;
              case FROM_INPUT: FillMethod = FillMethod::FROM_INPUT; break;
              default: return 1;
            }

            int task_choice;
            std::cout << "Choose task" << TASK1 << " - task 1," << TASK2 << " - task 2," << TASK3 << " - task 3";
            std::cin >> task_choice;
            
            TaskChoice task;
            switch (task_choice){
              case TASK1: TaskChoice = TaskChoice::TASK1; break;
              case TASK2: TaskChoice = TaskChoice::TASK2; break;
              case TASK3: TaskChoice = TaskChoice::TASK3; break;
              default: return 1;
            }
            
            std::unique_ptr<Generator> generator;
            switch (fill_method){
              case FillMethod::RANDOM:
                int min, max;
                std::cout << "Input min value";
                std::cin >> min;
                std::cout << "Input max value";
                std::cin >> max;
                if (min > max)
                {
                    std::cout << "Input error" << std::endl;
                    throw;
                }
                generator = std::make_unique<RandomGenerator>(min, max); break;
              case FillMethod::CONSTANT: 
                int value;
                std::cout << "Input value";
                std::cin >> value;
                generator = std::make_unique<ConstantGenerator>(value); break;
              case FillMethod::FROM_INPUT: generator = std::make_unique<IStreamGenerator>(std::cin); break;
              default: return 1;
            }

            std::unique_ptr<Exercise> exercise;
            switch (task){
                case TaskChoice::TASK1: 
                    exercise = std::make_unique<OurEx1>(size, std::move(generator)); 
                    break;
                case TaskChoice::TASK2: 
                    exercise = std::make_unique<OurEx2>(size, std::move(generator)); 
                    break;
                case TaskChoice::TASK3: 
                    exercise = std::make_unique<OurEx3>(size, std::move(generator)); 
                    break;
                default: return 1;
            }

            exercise->fill_matrix();
            std::cout << "Original array: " << exercise->get_matrix().to_string() << std::endl;
            
            exercise->Task();
            
            std::cout << "Result array: " << exercise->get_matrix().to_string() << std::endl;

            return 0;
    }

    size_t Input_size(void) {
        int size = Input("Input array size");
        if (size <= 0)
        {
            std::cout << "Input error" << std::endl;
            throw;
        }
        if (size == 0){
          std::cout << "Array size must be more than 0" << std::endl;
          throw;
        }
        return (size_t)size;
    }

    double Input(const char* message) {
        double input;
        if (message != nullptr)
        {
            std::cout << message << std::endl;
        }
        std::cin >> input;
        if (std::cin.fail())
        {
            std::cout << "Incorrect input" << std::endl;
            throw;
        }
        return input;
    }
}
