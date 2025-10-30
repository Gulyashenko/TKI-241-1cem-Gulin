#include <iostream>
#include <memory>
#include <string>
#include "Matrix.h"
#include "Exercise.h"
#include "OurEx1.h"
#include "OurEx2.h"
#include "OurEx3.h"
#include "RandomGenerator.h"
#include "ConstantGenerator.h"
#include "IStreamGenerator.h"

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
              case 1: FillMethod = FillMethod::RANDOM; break;
              case 2: FillMethod = FillMethod::CONSTANT; break;
              case 3: FillMethod = FillMethod::FROM_INPUT; break;
              default: return 1;
            }

            int task_choice;
            std::cout << "Choose task" << TASK1 << " - task 1," << TASK2 << " - task 2," << TASK3 << " - task 3";
            std::cin >> task_choice;
            
            TaskChoice task;
            switch (task_choice){
              case 1: TaskChoice = TaskChoice::TASK1; break;
              case 2: TaskChoice = TaskChoice::TASK2; break;
              case 3: TaskChoice = TaskChoice::TASK3; break;
              default: return 1;
            }
            
            std::unique_ptr<Generator> generator;
            switch (fill_method){
              case FillMethod::RANDOM: generator = std::make_unique<RandomGenerator>(-10, 10); break;
              case FillMethod::CONSTANT: generator = std::make_unique<ConstantGenerator>(0); break;
              case FillMethod::FROM_INPUT: generator = std::make_unique<IStreamGenerator>(std::cin); break;
              default: return 1;
            }

            Exercise exercise(size, std::move(generator));
            switch (task){
              case TaskChoice::TASK1: exercise.Task1(); break;
              case TaskChoice::TASK2: exercise.Task2(); break;
              case TaskChoice::TASK3: exercise.Task3(); break;
              default: return 1;
            }

            std::cout << exercise.get_matrix().to_string() << std::endl;


            
        return 0;
    }

    size_t Input_size(void) {
        int size = Input("Input array size");
        if (Input <= 0)
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
    
