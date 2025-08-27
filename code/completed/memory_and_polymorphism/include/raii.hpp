// ReSharper disable CppClangTidyCppcoreguidelinesMacroUsage
#pragma once
#ifndef RAII_HPP
#define RAII_HPP

#include <gsl/gsl>
#include <utility>

#ifndef SHOW_RAII_OPERATIONS
#define SHOW_RAII_OPERATIONS 0
#endif

namespace raii {

#if SHOW_RAII_OPERATIONS

inline void note(gsl::czstring msg) noexcept
{
    printf("%s", msg);
    printf("\n");
}

#else

consteval inline void note(gsl::czstring msg) noexcept {}

#endif

// We could just as well define this as taking a T*, but I wanted to show
// concepts :)
template <typename T>
requires std::is_pointer_v<T>
struct DefaultDeleter
{
    static void del(gsl::owner<T> ptr) noexcept
    {
        note("  -> ::raii::DefaultDeleter::del()");
        delete ptr;
    }
};

// A simple RAII container modeled somehow after std::unique_ptr<T> (but only
// for pointers and with built-in std::make_unique()).
template <typename T, template <typename> typename Deleter = DefaultDeleter>
class SimpleRaiiContainer
{
public:
    // Perfect forwarding of the constructor's arguments.
    template <typename... Ts>
    explicit SimpleRaiiContainer(Ts&&... args)
        : resource_{new T{std::forward<Ts>(args)...}}
    {
        note("::raii::SimpleRaiiContainer(...)");
    }

    // We apply the static casts from gsl::Owner<T*> to [const] T* to avoid
    // compiler warnings about not transferring ownership.
    T* get() { return static_cast<T*>(resource_); }
    [[nodiscard]] const T* get() const { return static_cast<const T*>(resource_); }

    // The copy constructor and assignment operator must be deleted, otherwise
    // the stored value would be deleted twice.
    SimpleRaiiContainer(const SimpleRaiiContainer& other) = delete;

    // We want to be able to move, so we define a move constructor that steals
    // the resources from other.
    SimpleRaiiContainer(SimpleRaiiContainer&& other) noexcept
    {
        note("::raii::SimpleRaiiContainer(&&)");
        steal_resources(std::move(other));
    }

    SimpleRaiiContainer& operator=(const SimpleRaiiContainer& other) = delete;

    // We again steal the resources from other, but in addition we delete the
    // resources we previously stored.
    SimpleRaiiContainer& operator=(SimpleRaiiContainer&& other) noexcept
    {
        note("::raii::SimpleRaiiContainer::operator=(&&)");
        this->~SimpleRaiiContainer();
        steal_resources(std::move(other));
        return *this;
    }

    ~SimpleRaiiContainer() noexcept
    {
        note("::raii::~SimpleRaiiContainer()");
        if (resource_) {
            Deleter<T*>::del(resource_);
        }
    }

private:
    gsl::owner<T*> resource_{};
    void steal_resources(SimpleRaiiContainer&& other) noexcept
    {
        note("  -> ::raii::SimpleRaiiContainer::steal_resources()");
        resource_ = other.resource_; // NOLINT(cppcoreguidelines-owning-memory)
        // It's important to put the other container in a state where it will no
        // longer try to delete the stolen resource.
        other.resource_ = nullptr;
    }
};

} // namespace raii

#endif // RAII_HPP