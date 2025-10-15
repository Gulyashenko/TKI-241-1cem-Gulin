#include <iostream>
#include <memory>

class Mass{
    private:
        std::unique_ptr<int[]> pointer;
        int size;
    public:
        Mass();
        Mass(int size);
        Mass(const Mass& other);
        ~Mass();
        
        void manualInput();
        void randomInput();
        void print();

        int getSize();
        int getElement(int index);
        void setElement(int index, int value);
};
