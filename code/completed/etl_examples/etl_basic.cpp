#include <iostream>
#include <string>
#include "etl/vector.h"

int main()
{
    etl::vector<int, 5>{1, 2, 3, 4, 5};
    std::string sep{};
    std::cout << "ETL vector: [";
    for (auto i : etl::vector<int, 5>{1, 2, 3, 4, 5})
    {
        std::cout << sep << i;
        sep = ", ";
    }
    std::cout << "]\n";
}
