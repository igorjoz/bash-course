#include <iostream>
#include <fstream>

int main()
{
    // std::ofstream file("numbers.txt");

    int minNum = 1;
    int maxNum = 10;
    int step = 1;

    std::cin >> minNum >> maxNum >> step;

    if (step == 2) {
        minNum += 10;
        maxNum -= 10;
    }

    for (int i = minNum; i <= maxNum; i += step) {
        std::cout << i << "\n";
    }

    return 0;
}
