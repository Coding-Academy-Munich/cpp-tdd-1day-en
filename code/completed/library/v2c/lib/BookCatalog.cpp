// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "BookCatalog.h"

namespace library::v2c {

void BookCatalog::Add(BookInfo& info)
{
    Add(std::make_unique<Book>(info.shared_from_this()));
}

} // namespace library::v2c