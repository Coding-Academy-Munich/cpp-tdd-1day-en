// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "DeleteMe.h"

namespace library_sk {

std::ostream& operator<<(std::ostream& os, const DeleteMe& location)
{
    os << "DeleteMe";
    return os;
}

bool DeleteMe::operator==(const DeleteMe& rhs) const { return this == &rhs; }

} // namespace library_sk