// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef STARTER_KITS_library_DATA_BOOKDATA_H
#define STARTER_KITS_library_DATA_BOOKDATA_H

#include <string>
#include <vector>

namespace library::data {

struct BookData {
    std::string name;
    std::vector<std::string> authors;
    std::string isbn;
};

extern std::vector<BookData> bookData;

} // namespace library::data

#endif // STARTER_KITS_library_DATA_BOOKDATA_H
