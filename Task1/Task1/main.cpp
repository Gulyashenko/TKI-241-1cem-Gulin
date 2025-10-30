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
     * @brief Function to create generator based on fill method
     */
    std::unique_ptr<Generator> create_generator(FillMethod method)
    {
        switch (method)
        {
        case FillMethod::RANDOM:
            return std::make_unique<RandomGenerator>(-100, 100);
        case FillMethod::CONSTANT:
            return std::make_unique<ConstantGenerator>(5.0);
        case FillMethod::FROM_INPUT:
            return std::make_unique<IStreamGenerator>(std::cin);
        default:
            std::cout << "Inwalid chooise of fill method" << std::endl;
            
        }
    }

    /**
     * @brief Function to create exercise based on task choice
     */
    std::unique_ptr<Exercise> create_exercise(TaskChoice task, size_t size, std::unique_ptr<Generator> generator)
    {
        switch (task)
        {
        case TaskChoice::TASK1:
            return std::make_unique<OurEx1>(size, std::move(generator));
        case TaskChoice::TASK2:
            return std::make_unique<OurEx2>(size, std::move(generator));
        case TaskChoice::TASK3:
            return std::make_unique<OurEx3>(size, std::move(generator));
        default:
            std::cout << "Inwalid chooise of task" << std::endl;
        }
    }

    size_t Input_size(void);
    double Input(const char* message);

    int main(void)
    {
        using namespace miit::algebra;

            size_t size = Input_size();

            if (size == 0)
            {
                std::cout << "Array size must be greater than 0" << std::endl;
                return 1;
            }

            int fill_choice;
            std::cout << "Choose fill method (1-3): ";
            std::cin >> fill_choice;

            FillMethod fill_method;


            int task_choice;
            std::cout << "Choose task (1-3): ";
            std::cin >> task_choice;

            TaskChoice task;
          

            auto generator = create_generator(fill_method);
            auto exercise = create_exercise(task, size, std::move(generator));

            // Fill matrix
            if (fill_method == FillMethod::FROM_INPUT)
            {
                std::cout << "Enter " << size << " integer values:" << std::endl;
            }

            exercise->fill_matrix();

            // Display original array
            std::cout << "\nOriginal array: " << exercise->get_matrix().to_string() << std::endl;

            // Execute task
            exercise->Task();

            // Display result
            std::cout << "Result array: " << exercise->get_matrix().to_string() << std::endl;

        return 0;
    }

    size_t Input_size(void) {
        int size = Input("Input array size");
        if (Input <= 0)
        {
            std::cout << "Input error" << std::endl;
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
    