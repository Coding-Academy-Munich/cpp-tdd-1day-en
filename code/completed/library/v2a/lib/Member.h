// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_LIBRARY_V2A_LIB_MEMBER_H
#define COMPLETED_LIBRARY_V2A_LIB_MEMBER_H

#include <chrono>
#include <memory>
#include <string>

namespace library::v2a {
class MemberType {
public:
    MemberType() = default;
    MemberType(const MemberType&) = delete;
    MemberType(MemberType&&) = delete;
    MemberType& operator=(const MemberType&) = delete;
    MemberType& operator=(MemberType&&) = delete;
    virtual ~MemberType() = default;

    virtual std::string ToString() const = 0;
};

std::ostream& operator<<(std::ostream& os, const MemberType& type);

class RegularMemberType : public MemberType {
public:
    std::string ToString() const override { return "regular member"; }
};

class Member {
public:
    Member(unsigned int id, std::unique_ptr<MemberType> type, std::string name,
        std::string address, std::chrono::year_month_day birthday,
        std::optional<std::string> occupation = {});

    Member(std::unique_ptr<MemberType> type, std::string name, std::string address,
        std::chrono::year_month_day birthday,
        std::optional<std::string> occupation = {});

    auto operator<=>(const Member&) const = default;

    static unsigned int GetNextId() { return nextId; }
    [[nodiscard]] unsigned int GetId() const { return id; }
    [[nodiscard]] const std::string& GetName() const { return name; }
    [[nodiscard]] const std::string& GetAddress() const { return address; }
    [[nodiscard]] const std::chrono::year_month_day& GetBirthday() const
    {
        return birthday;
    }
    [[nodiscard]] const std::optional<std::string>& GetOccupation() const
    {
        return occupation;
    }
    [[nodiscard]] const std::unique_ptr<MemberType>& GetType() const { return type; }

private:
    static unsigned int nextId;
    unsigned int id {nextId++};
    std::unique_ptr<MemberType> type;
    std::string name;
    std::string address;
    std::chrono::year_month_day birthday;
    std::optional<std::string> occupation;
};

std::ostream& operator<<(std::ostream& os, const Member& member);

} // namespace library::v2a
#endif // COMPLETED_LIBRARY_V2A_LIB_MEMBER_H
