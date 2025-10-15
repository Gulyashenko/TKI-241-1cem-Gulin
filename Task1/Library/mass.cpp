#include "mass.h"
#include <random>
#include <ctime>

Mass::Mass(){
    size = 0;
    pointer = nullptr;
}

Mass::Mass(int size){
    this->size = size;
    pointer = std::make_unique<int[]>(size);

    for (int i = 0; i < size; i++){
        pointer[i] = 0;
    }
}

Mass::~Mass(){
    pointer = nullptr;
}

void Mass::manualInput(){
    if (size == 0){
        std::cout << "Print size: ";
        std::cin >> size;
        pointer = std::make_unique<int[]>(size);
    }
    for (int i = 0; i < size; i++){
        std::cin >> pointer[i];
    }
}

void Mass::randomInput(){
    if (size == 0){
        std::cout << "Print size: ";
        std::cin >> size;
        pointer = std::make_unique<int[]>(size);
    }

    srand(time(nullptr));
    for (int i = 0; i < size; i++){
        pointer[i] = rand() % 100;
    }
}

void Mass::print(){
    for (int i = 0; i < size; i++){
        std::cout << pointer[i] << ", ";
    }
    std::cout << std::endl;
}

Mass::Mass(const Mass& other) : size (other.size){
    pointer = std::make_unique<int[]>(size);
    for (int i = 0; i < size; i++){
        pointer[i] = other.pointer[i];
    }    
}

int Mass::getSize(){
    return size;
}

int Mass::getElement(int index){
    return pointer[index];
}

void Mass::setElement(int index, int value){
    pointer[index] = value;
}
