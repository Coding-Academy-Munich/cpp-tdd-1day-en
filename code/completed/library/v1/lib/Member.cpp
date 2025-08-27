// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Member.h"
#include <memory>
#include <string>
#include <utility>

namespace library::v1 {

std::ostream& operator<<(std::ostream& os, const MemberType& type)
{
    os << type.ToString();
    return os;
}

unsigned int Member::nextId {1};

Member::Member(unsigned int id, std::unique_ptr<MemberType> type, std::string name,
    std::string address, std::chrono::year_month_day birthday,
    std::optional<std::string> occupation)
    : id {id}
    , name {std::move(name)}
    , address {std::move(address)}
    , birthday {birthday}
    , type {std::move(type)}
    , occupation {std::move(occupation)}
{
}

Member::Member(std::unique_ptr<MemberType> type, std::string name, std::string address,
    std::chrono::year_month_day birthday, std::optional<std::string> occupation)
    : Member(nextId++, std::move(type), std::move(name), std::move(address), birthday,
        std::move(occupation))
{
}

std::ostream& operator<<(std::ostream& os, const Member& member)
{
    os << "Member{id: " << member.GetId() << ", name: " << member.GetName()
       << ", address: \"" << member.GetAddress()
       << "\", birthday: " << member.GetBirthday()
       << ", occupation: " << member.GetOccupation().value_or("unknown")
       << ", type: " << *member.GetType() << "}";
    return os;
}

} // namespace library::v1