#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <memory>

template <typename Key, typename Value, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<std::pair<Key, Value>>>
class dictionary
{
private:
    std::pair<Key, Value> m_data;

public:
    explicit dictionary() = default;
    explicit dictionary(Key const &, Value const &);
    explicit dictionary(std::pair<Key, Value> const &);
    explicit dictionary(dictionary const &) = default;
    explicit dictionary(dictionary &&) = default;
    dictionary &operator=(dictionary const &) = default;
    dictionary &operator=(dictionary &&) noexcept = default;
    virtual ~dictionary() = default;
    virtual const Value &get(Key const &) const;
    virtual void set(Key const &, Value const &);
    virtual bool is_set(const Key &) const;
};

template <typename Key>
class not_found_exception : public std::exception
{
public:
    virtual const Key &get_key() const noexcept = 0;
};

#endif // DICTIONARY_HPP
