#ifndef NOX_OPTIONAL_HPP_
#define NOX_OPTIONAL_HPP_

#include <type_traits>
#include <utility>

namespace nox {

struct Nullopt {};

/**
 * A type-safe optional without exceptions.
 */
template <typename T>
class Optional {
public:
    using value_type = T;

    /**
     * Default constructor.
     *
     * Creates an empty instance.
     */
    constexpr Optional() noexcept : m_has_value{false} {}

    /**
     * Empty constructor.
     *
     * Creates an empty instance.
     */
    constexpr explicit Optional(Nullopt) noexcept : m_has_value{false} {}

    /**
     * Value constructor.
     *
     * Creates an instance containing the value. The value is moved into the internal storage.
     *
     * @param val the initial value
     */
    constexpr explicit Optional(value_type v) : m_has_value{true} { value() = std::move(v); }

    /**
     * Argument forwarding constructor.
     *
     * Creates an instance constructed from the given arguments.
     */
    template <typename... Args>
    constexpr Optional(Args&&... args) : m_has_value{true} {
      value() = T{args...};
    }

    /**
     * Returns the contained value or a default value.
     *
     * @param default_value the default value to be returned if the instance is empty
     * @returns the contained value or the passed in default value
     */
    template <typename U>
    constexpr value_type value_or(U&& default_value) const& {
        return m_has_value ? value() : static_cast<T>(std::forward<U>(default_value));
    }

    template <typename U>
    constexpr value_type value_or(U&& default_value) && {
        return m_has_value ? std::move(value()) : static_cast<T>(std::forward<U>(default_value));
    }

    /**
     * Incokes the given function with the contained value if the instance is not empty.
     *
     * @param f the function to invoke
     * @returns the result of the function (if any)
     */
    template <typename Func>
    decltype(auto) apply(Func&& f) {
        if (m_has_value) f(value());
    }

    /**
     * Invokes the first given function with the contained value if the instance is not empty,
     * otherwise the second function will be called.
     *
     * @param on_present the function to be invoked if a value is present
     * @param on_empty the function to be invoked if no value is present
     * @returns the result of either of the functions (if any)
     */
    template <typename PresentFunc, typename EmptyFunc>
    decltype(auto) apply(PresentFunc&& on_present, EmptyFunc&& on_empty) {
        return m_has_value ? on_present(value()) : on_empty();
    }

private:
    value_type& value() { return *reinterpret_cast<value_type*>(&m_storage); }

    value_type const& value() const { return *reinterpret_cast<value_type const*>(&m_storage); }

    using Storage = typename std::aligned_storage<sizeof(value_type), alignof(value_type)>::type;

    Storage m_storage;
    bool m_has_value;
};

}  // namespace nox

#endif  // NOX_OPTIONAL_HPP_
