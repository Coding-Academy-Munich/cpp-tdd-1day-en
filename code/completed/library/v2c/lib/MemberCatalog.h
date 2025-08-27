// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_LIBRARY_V2C_LIB_MEMBERCATALOG_H
#define COMPLETED_LIBRARY_V2C_LIB_MEMBERCATALOG_H

#include "Catalog.h"
#include "Member.h"

namespace library::v2c {

class MemberCatalog : public Catalog<Member> {
public:
    using Catalog<Member>::Add;
    void Add(unsigned int id, std::unique_ptr<MemberType> type, std::string name,
        std::string address, std::chrono::year_month_day birthday,
        std::optional<std::string> occupation = {});

    [[nodiscard]] Member* FindById(unsigned int id)
    {
        return Find([&id](const Member& member) { return member.GetId() == id; });
    }
    [[nodiscard]] Member* FindByName(const std::string& name)
    {
        return Find([&name](const Member& member) { return member.GetName() == name; });
    }
    [[nodiscard]] Member* FindByAddress(const std::string& address)
    {
        return Find([&address](const Member& member) {
            return member.GetAddress() == address;
        });
    }
    [[nodiscard]] Member* FindByBirthday(const std::chrono::year_month_day& birthday)
    {
        return Find([&birthday](const Member& member) {
            return member.GetBirthday() == birthday;
        });
    }
    [[nodiscard]] Member* FindByOccupation(const std::string& occupation)
    {
        return Find([&occupation](const Member& member) {
            return member.GetOccupation() == occupation;
        });
    }
};

} // namespace library::v2c

#endif // COMPLETED_LIBRARY_V2C_LIB_MEMBERCATALOG_H
