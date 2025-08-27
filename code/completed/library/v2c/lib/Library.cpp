// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Library.h"

namespace library::v2c {

Library::Library(BookCatalog books, MemberCatalog members)
    : books {std::move(books)}
    , members {std::move(members)}
{
}

} // namespace library::v2c