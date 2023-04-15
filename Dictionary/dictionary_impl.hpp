#ifndef DICTIONARY_IMPL_HPP
#define DICTIONARY_IMPL_HPP

#include "dictionary.hpp"

template <typename Key, typename Value, typename Compare, typename Allocator>
dictionary<Key, Value, Compare, Allocator>::dictionary(Key const &key, Value const &value)
{
    m_data.first = key;
    m_data.second = value;
}

template <typename Key, typename Value, typename Compare, typename Allocator>
dictionary<Key, Value, Compare, Allocator>::dictionary(std::pair<Key, Value> const &data)
{
    m_data.first = data.first;
    m_data.second = data.second;
}

template <typename Key, typename Value, typename Compare, typename Allocator>
const Value &dictionary<Key, Value, Compare, Allocator>::get(Key const &) const {}

template <typename Key, typename Value, typename Compare, typename Allocator>
void dictionary<Key, Value, Compare, Allocator>::set(Key const &, Value const &) {}

template <typename Key, typename Value, typename Compare, typename Allocator>
bool dictionary<Key, Value, Compare, Allocator>::is_set(const Key &) const { return false; }

#endif // DICTIONARY_IMPL_HPP
