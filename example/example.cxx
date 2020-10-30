#include <chrono>
#include <iostream>
#include <string>

#include <MBL.h>

// functions for MBL
void inner_function_mbl(MBL::MBL& mbl, int size)
{
    MBL::Measure m1{mbl, "inner function mbl (size: " + std::to_string(size) + ")"};
    std::unique_ptr<int[]> data {new int[size]};
    for (int i = 0; i < size; i++) {
        data[i] = 0;
    }
}

void outer_function_mbl(MBL::MBL& mbl)
{
    MBL::Measure m1{mbl, "outer function mbl"};
    for (int i = 1; i <= 1024*1024; i<<=1) {
        inner_function_mbl(mbl, i);
    }
}

// functions for chrono
void inner_function_chrono(std::chrono::time_point<std::chrono::steady_clock> time_zero, int size)
{
    auto start = std::chrono::steady_clock::now();
    std::cout << "        inner function chrono (size: " << size << ") [start: " << std::chrono::duration<float, std::micro>(start - time_zero).count() << "]" << std::endl;
    std::unique_ptr<int[]> data {new int[size]};
    for (int i = 0; i < size; i++) {
        data[i] = 0;
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << "        inner function chrono (size: " << size << ") [end: " << std::chrono::duration<float, std::micro>(end - time_zero).count() << "][elapsed time: " << std::chrono::duration<float, std::micro>(end - start).count() << "]" << std::endl;
}

void outer_function_chrono(std::chrono::time_point<std::chrono::steady_clock> time_zero)
{
    auto start = std::chrono::steady_clock::now();
    std::cout << "    outer function chrono [start: " << std::chrono::duration<float, std::micro>(start - time_zero).count() << "]" << std::endl;
    for (int i = 1; i <= 1024*1024; i<<=1) {
        inner_function_chrono(time_zero, i);
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << "    outer function chrono [end: " << std::chrono::duration<float, std::micro>(end - time_zero).count() << "][elapsed time: " << std::chrono::duration<float, std::micro>(end - start).count() << "]" << std::endl;
    
}

int main()
{
    // MBL
    {
        MBL::MBL mbl("result.json", MBL::Time_unit::microseconds);
        MBL::Measure m1{mbl, "main"};
        outer_function_mbl(mbl);
    }

    {
        // chrono
        auto time_zero = std::chrono::steady_clock::now();
        auto start = std::chrono::steady_clock::now();
        std::cout << "main [start: " << std::chrono::duration<float, std::micro>(start - time_zero).count() << "]" << std::endl;
        outer_function_chrono(time_zero);
        auto end = std::chrono::steady_clock::now();
        std::cout << "main [end: " << std::chrono::duration<float, std::micro>(end - time_zero).count() << "][elapsed time: " << std::chrono::duration<float, std::micro>(end - start).count() << "]" << std::endl;
    }

}