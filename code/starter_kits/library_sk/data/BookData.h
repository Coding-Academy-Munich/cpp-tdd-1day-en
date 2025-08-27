#pragma once
#ifndef STARTER_KITS_LIBRARY_SK_DATA_BOOKDATA_H
#define STARTER_KITS_LIBRARY_SK_DATA_BOOKDATA_H

#include <string>
#include <vector>

namespace library_sk::data {

struct BookData {
    std::string name;
    std::vector<std::string> authors;
    std::string isbn;
};

extern std::vector<BookData> bookData;

} // namespace library_sk::data

#endif // STARTER_KITS_LIBRARY_SK_DATA_BOOKDATA_H
