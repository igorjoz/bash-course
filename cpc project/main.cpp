#include <iostream>
#include <fstream>

int main()
{
    // std::ofstream file("numbers.txt");

    int minNum = 1;
    int maxNum = 10;
    int step = 1;

    std::cin >> minNum >> maxNum >> step;

    // std::cerr << "minNum: " << minNum << "\n";
    // std::cerr << "maxNum: " << maxNum << "\n";
    // std::cerr << "step: " << step << "\n";

    for (int i = minNum; i <= maxNum; i += step) {
        // file << i << "\n";
        std::cout << i << "\n";
    }

    return 0;
}
