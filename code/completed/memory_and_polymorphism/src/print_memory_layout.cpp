#include "print_memory_layout.hpp"

void print_content_addresses(const std::string& name, const std::vector<int>& v)
{
    for (int i = 0; i < v.size(); ++i) {
        print_address(name + "[" + std::to_string(i) + "]: ", &v[i]);
    }
}

void print_memory_layout()
{
    int i{17};
    int ai[3] = {1, 2, 3};
    int* pi = new int;
    *pi = 21;
    std::vector<int> vi{1, 2, 3, 4, 5, 6};
    int ii{0};
    std::vector<int> wi{vi};

    print_address("i:   ", &i);
    print_address("ai:  ", &ai);
    print_address("pi:  ", &pi);
    print_address("vi:  ", &vi);
    print_address("wi:  ", &wi);
    print_address("wi:  ", &wi);

    std::cout << std::endl;
    print_address("*pi:   ", pi);

    std::cout << std::endl;
    print_content_addresses("vi", vi);

    std::cout << std::endl;
    print_content_addresses("wi", wi);

    std::vector<int> ui{std::move(wi)};

    std::cout << std::endl;
    print_address("wi:  ", &wi);
    print_address("ui:  ", &ui);

    std::cout << std::endl;
    print_content_addresses("ui", ui);

    std::cout << std::endl;
    print_dist(" i to ai: ", &i, &ai);
    print_dist("ai to pi: ", &ai, &pi);
    print_dist("pi to vi: ", &pi, &vi);
    print_dist("vi to ii: ", &vi, &ii);
}
