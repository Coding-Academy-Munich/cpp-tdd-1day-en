// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef STARTER_KITS_LIBRARY_SK_LIB_DELETEME_H
#define STARTER_KITS_LIBRARY_SK_LIB_DELETEME_H

#include "BookData.h"
#include <ostream>
#include <string>

namespace library_sk {

class DeleteMe {
public:
    bool operator==(const DeleteMe& rhs) const;
};

std::ostream& operator<<(std::ostream& os, const DeleteMe& location);

} // library_sk

#endif // STARTER_KITS_LIBRARY_SK_LIB_DELETEME_H
