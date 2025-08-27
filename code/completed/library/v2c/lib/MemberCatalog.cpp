// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "MemberCatalog.h"

namespace library::v2c {

void MemberCatalog::Add(unsigned int id, std::unique_ptr<MemberType> type,
    std::string name, std::string address, std::chrono::year_month_day birthday,
    std::optional<std::string> occupation)
{
    Add(std::make_unique<Member>(id, std::move(type), std::move(name),
        std::move(address), birthday, std::move(occupation)));
}

} // namespace library::v2c