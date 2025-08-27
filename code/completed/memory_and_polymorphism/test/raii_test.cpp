// ReSharper disable CppClangTidyCppcoreguidelinesAvoidNonConstGlobalVariables
// ReSharper disable CppClangTidyCppcoreguidelinesProTypeReinterpretCast
// ReSharper disable CppClangTidyHicppInvalidAccessMoved
// ReSharper disable CppClangTidyBugproneUseAfterMove
#include "raii.hpp"

#include <catch2/catch_test_macros.hpp>

template <typename T>
uintptr_t to_uintptr_t(T* ptr) noexcept
{
    return reinterpret_cast<uintptr_t>(ptr);
}

template <typename T>
requires std::is_pointer_v<T>
struct TestDeleter
{
    static void del(gsl::owner<T> ptr) noexcept
    {
        // We could just ignore any exceptions thrown by push_back and just let
        // the program abort...
        try {
            deleted_addresses.push_back(to_uintptr_t(ptr));
        }
        catch (...) {
            printf("TestDeleter caught an exception!");
        }
        delete ptr;
    }
    static std::vector<std::uintptr_t> deleted_addresses;
};

// clang-format off
template <typename T>
requires std::is_pointer_v<T>
std::vector<std::uintptr_t>
TestDeleter<T>::deleted_addresses{};
// clang-format on

TEST_CASE("SimpleRaiiContainer is no larger than necessary.")
{
    CHECK(sizeof(raii::SimpleRaiiContainer<int>) == sizeof(int*));
}

TEST_CASE("Results of std::forward for non-const types.")
{
    int i{};
    CHECK(std::is_same_v<decltype(std::forward<int>(static_cast<int&&>(i))), int&&>);
    CHECK(std::is_same_v<decltype(std::forward<int>(static_cast<int&>(i))), int&&>);
    CHECK(std::is_same_v<decltype(std::forward<int>(static_cast<int>(i))), int&&>);
    CHECK(std::is_same_v<decltype(std::forward<int&>(static_cast<int&&>(i))), int&>);
    CHECK(std::is_same_v<decltype(std::forward<int&>(static_cast<int&>(i))), int&>);
    CHECK(std::is_same_v<decltype(std::forward<int&>(static_cast<int>(i))), int&>);
    CHECK(std::is_same_v<decltype(std::forward<int&&>(static_cast<int&&>(i))), int&&>);
    CHECK(std::is_same_v<decltype(std::forward<int&&>(static_cast<int&>(i))), int&&>);
    CHECK(std::is_same_v<decltype(std::forward<int&&>(static_cast<int>(i))), int&&>);
}

template <typename T>
decltype(auto) perfect_forward(T&& arg)
{
    return std::forward<T>(arg);
}

TEST_CASE("Test perfect forwarding for non-const types.")
{
    int i{0};
    CHECK(std::is_same_v<decltype(perfect_forward(1)), int&&>);
    CHECK(std::is_same_v<decltype(perfect_forward(i)), int&>);
    CHECK(std::is_same_v<decltype(perfect_forward(static_cast<int&>(i))), int&>);
    CHECK(std::is_same_v<decltype(perfect_forward(static_cast<int&&>(i))), int&&>);
}

TEST_CASE("Test perfect forwarding for const types.")
{
    const int i{0};
    CHECK(std::is_same_v<decltype(perfect_forward(i)), const int&>);
    CHECK(std::is_same_v<
          decltype(perfect_forward(static_cast<const int&>(i))), const int&>);
    CHECK(std::is_same_v<
          decltype(perfect_forward(static_cast<const int&&>(i))), const int&&>);
}

TEST_CASE("SimpleRaiiContainer deletes its member.")
{
    TestDeleter<int*>::deleted_addresses = {};
    {
        raii::SimpleRaiiContainer<int, TestDeleter> container{2};
        CHECK(TestDeleter<int*>::deleted_addresses.empty());
    }
    CHECK_FALSE(TestDeleter<int*>::deleted_addresses.empty());
}

TEST_CASE("SimpleRaiiContainer can be move-constructed.")
{
    TestDeleter<int*>::deleted_addresses = {};
    {
        raii::SimpleRaiiContainer<int, TestDeleter> c1{42};
        const auto c1_value_address{reinterpret_cast<std::uintptr_t>(c1.get())};
        auto c2{std::move(c1)};
        // Nothing was deleted by the move
        CHECK(TestDeleter<int*>::deleted_addresses.empty());
        CHECK(c1.get() == nullptr); // NOLINT(bugprone-use-after-move)
        CHECK(reinterpret_cast<std::uintptr_t>(c2.get()) == c1_value_address);
    }
}

TEST_CASE("SimpleRaiiContainer can be moveed.")
{
    TestDeleter<int*>::deleted_addresses = {};
    {
        uintptr_t c1_value_address{};
        uintptr_t c2_value_address{};
        {
            raii::SimpleRaiiContainer<int, TestDeleter> c1{42};
            // Save the address of the value stored in c1 so that we can check
            // that it gets deleted at the correct time.
            c1_value_address = reinterpret_cast<uintptr_t>(c1.get());

            raii::SimpleRaiiContainer<int, TestDeleter> c2{};
            // Same for c2.
            c2_value_address = reinterpret_cast<uintptr_t>(c2.get());

            c2 = std::move(c1);
            // The old value of c2 was deleted by the move...
            REQUIRE(TestDeleter<int*>::deleted_addresses.size() == 1);
            CHECK(TestDeleter<int*>::deleted_addresses[0] == c2_value_address);
            // ... and c1 was brought into a state where it no longer deletes a
            // vale when it goes out of scope...
            CHECK(c1.get() == nullptr);
            //... and c2 now points to the value.
            CHECK(to_uintptr_t(c2.get()) == c1_value_address);
        }
        // c1 goes out of scope here, so its value should be deleted as well.
        REQUIRE(TestDeleter<int*>::deleted_addresses.size() == 2);
        CHECK(TestDeleter<int*>::deleted_addresses[0] == c2_value_address);
        CHECK(TestDeleter<int*>::deleted_addresses[1] == c1_value_address);
    }
}

struct CannotCopy
{
    explicit CannotCopy(int val) : val{val} {}
    CannotCopy(const CannotCopy& other) = delete;
    CannotCopy(CannotCopy&& other) noexcept = default;
    CannotCopy& operator=(const CannotCopy& other) = delete;
    CannotCopy& operator=(CannotCopy&& other) noexcept = default;
    ~CannotCopy() = default;
    int val;
};

struct CanNeitherMoveNorCopy
{
    int& val_ref;
};

TEST_CASE("SimpleRaiiContainer forwands its constructor args.")
{
    using Type = CannotCopy;
    TestDeleter<Type*>::deleted_addresses = {};
    int j{1};
    {
        raii::SimpleRaiiContainer<Type, TestDeleter> container{CannotCopy{1}};
        CHECK(TestDeleter<Type*>::deleted_addresses.empty());
    }
    CHECK_FALSE(TestDeleter<Type*>::deleted_addresses.empty());
}

TEST_CASE("SimpleRaiiContainer forwands its constructor args (2).")
{
    using Type = CanNeitherMoveNorCopy;
    TestDeleter<Type*>::deleted_addresses = {};
    int j{1};
    {
        auto elt{CanNeitherMoveNorCopy{j}};
        raii::SimpleRaiiContainer<Type, TestDeleter> container{elt};
        CHECK(TestDeleter<Type*>::deleted_addresses.empty());
    }
    CHECK_FALSE(TestDeleter<Type*>::deleted_addresses.empty());
}

TEST_CASE("SimpleRaiiContainer forwands its constructor args (3).")
{
    using Type = CanNeitherMoveNorCopy;
    TestDeleter<Type*>::deleted_addresses = {};
    int j{1};
    {
        raii::SimpleRaiiContainer<Type, TestDeleter> container{
            CanNeitherMoveNorCopy{j}};
        CHECK(TestDeleter<Type*>::deleted_addresses.empty());
    }
    CHECK_FALSE(TestDeleter<Type*>::deleted_addresses.empty());
}

TEST_CASE("SimpleRaiiContainer::get() works.")
{
    using Type = std::pair<CannotCopy, CanNeitherMoveNorCopy>;
    int j{23};
    raii::SimpleRaiiContainer<Type> container{3, j};
    CHECK(container.get()->first.val == 3);
    CHECK(container.get()->second.val_ref == 23);
}

TEST_CASE("SimpleRaiiContainer::get() returns mutable values.")
{
    using Type = std::pair<CannotCopy, CanNeitherMoveNorCopy>;
    int j{23};
    raii::SimpleRaiiContainer<Type> container{3, j};
    REQUIRE(container.get()->first.val == 3);
    CHECK_NOTHROW(container.get()->first.val = 100);
    CHECK(container.get()->first.val == 100);
}

TEST_CASE("SimpleRaiiContainer::get() const works.")
{
    using Type = std::pair<CannotCopy, CanNeitherMoveNorCopy>;
    int j{234};
    const raii::SimpleRaiiContainer<Type> container{4, j};
    CHECK(container.get()->first.val == 4);
    CHECK(container.get()->second.val_ref == 234);
    // Compiler error!
    // container.get()->first.val = 10;
}
