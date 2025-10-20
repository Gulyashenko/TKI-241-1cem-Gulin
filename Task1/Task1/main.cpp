#include <iostream>
#include <memory>
#include "../Library/OurEx.h"

using namespace miit::algebra;

int main()
{
    try
    {
        size_t size;
        int choice;
        
        std::cout << "Введите размер массива: ";
        std::cin >> size;
        
        std::cout << "Выберите способ заполнения:\n";
        std::cout << "1 - случайные числа\n";
        std::cout << "2 - ввод с клавиатуры\n";
        std::cin >> choice;
        
        std::unique_ptr<Generator> generator;
        
        if (choice == 1)
        {
            int min, max;
            std::cout << "Введите минимальное значение: ";
            std::cin >> min;
            std::cout << "Введите максимальное значение: ";
            std::cin >> max;
            generator = std::make_unique<RandomGenerator>(min, max);
        }
        else
        {
            generator = std::make_unique<IStreamGenerator>();
        }
        
        // Создание объекта для выполнения заданий
        OurEx exercise(size, std::move(generator));
        
        // Заполнение массива
        exercise.fill_matrix();
        
        std::cout << "\nИсходный массив: " << exercise.get_matrix().to_string() << std::endl;
        
        // Выполнение задания 1
        Matrix<int> original = exercise.get_matrix(); // Сохраняем копию для Task3
        exercise.Task1();
        std::cout << "После задания 1: " << exercise.get_matrix().to_string() << std::endl;
        
        // Выполнение задания 2
        exercise.Task2();
        std::cout << "После задания 2: " << exercise.get_matrix().to_string() << std::endl;
        
        // Выполнение задания 3
        Matrix<int> result = exercise.Task3(original);
        std::cout << "Результат задания 3: " << result.to_string() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    
    return 0;
}
