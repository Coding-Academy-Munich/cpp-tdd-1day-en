// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_LIBRARY_V2C_LIB_LIBRARY_H
#define COMPLETED_LIBRARY_V2C_LIB_LIBRARY_H

#include "Book.h"
#include "BookCatalog.h"
#include "Catalog.h"
#include "Member.h"
#include "MemberCatalog.h"
#include <functional>
#include <vector>

namespace library::v2c {

class Library {
public:
    explicit Library(BookCatalog books = {}, MemberCatalog members = {});

    [[nodiscard]] const BookCatalog& GetBooks() const { return books; }
    [[nodiscard]] BookCatalog& GetBooks() { return books; }

    [[nodiscard]] const MemberCatalog& GetMembers() const { return members; }
    [[nodiscard]] MemberCatalog& GetMembers() { return members; }

private:
    BookCatalog books;
    MemberCatalog members;
};

} // namespace library::v2c

#endif // COMPLETED_LIBRARY_V2C_LIB_LIBRARY_H
