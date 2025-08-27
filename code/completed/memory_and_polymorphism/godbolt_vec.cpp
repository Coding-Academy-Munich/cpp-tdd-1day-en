#include <vector>

std::vector<int> returnVectorByRef(const std::vector<int>& v) {
    return v;
}

std::vector<int> returnVectorByValue(std::vector<int> v) {
    return v;
}


std::vector<int> returnLocalVector() {
    return std::vector<int>{500};
}


std::vector<int> returnVector(std::vector<int> v) {
    std::vector<int> v1{v};
    std::vector<int> v2{v1};
    return v2;
}

std::vector<int> returnVectorRvalueRef(std::vector<int> v) {
    std::vector<int> v1{std::move(v)};
    std::vector<int> v2{std::move(v1)};
    return v2;
}
