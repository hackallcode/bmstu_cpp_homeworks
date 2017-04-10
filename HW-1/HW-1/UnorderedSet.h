#pragma once

#include <vector> // for std::vector
#include <list> // for std::list
#include <vcruntime_exception.h> // for std::bad_array_new_length
#include <utility> // for std::swap
#include <xutility> // for std::copy
#include <cmath> // for ceil()

#define MIN_BUCKETS_COUNT 8

template< class Key,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key> >
    class UnorderedSet
{
public:
    // Typedefs
    using key_type = Key;
    using value_type = Key;
    using reference = value_type&;
    using const_reference = value_type& const;
    using size_type = size_t;
    using hasher = Hash;
    using key_equal = KeyEqual;
    using bucket_type = std::vector<value_type>;
    using buckets_type = std::vector<bucket_type>;

    // Iterators
    class Iterator
        : public std::iterator<std::random_access_iterator_tag, value_type>
    {
    public:
        Iterator() = default;
        Iterator& operator=(const Iterator& other) {
            buckets_ = other.buckets_;
            bucketIndex_ = other.bucketIndex_;
            valueIndex_ = other.valueIndex_;
            ptr_ = other.ptr_;
            return *this;
        }

        value_type& operator*() const
        {
            return *ptr_;
        }

        value_type* operator->() const
        {
            return ptr_;
        }

        bool operator!=(const Iterator& other)
        {
            return ptr_ != other.ptr_;
        }

        bool operator<(const Iterator& other)
        {
            return ptr_ < other.ptr_;
        }

        bool operator==(const Iterator& other)
        {
            return !(*this != other);
        }

        Iterator& operator++()
        {
            if (!IsEnd()) {
                if (valueIndex_ < buckets_[bucketIndex_].size() - 1) {
                    ++valueIndex_;
                }
                else {
                    valueIndex_ = 0;
                    for (++bucketIndex_; bucketIndex_ < buckets_.size(); ++bucketIndex_) {
                        if (buckets_[bucketIndex_].size() != 0) {
                            break;
                        }
                    }
                }
                ptr_ = (bucketIndex_ < buckets_.size()) ? &buckets_[bucketIndex_][valueIndex_] : nullptr;
            }
            return *this;
        }

        Iterator& operator--()
        {
            if (!IsBegin()) {
                if (valueIndex_ > 0) {
                    --valueIndex_;
                }
                else {
                    valueIndex_ = 0;
                    for (--bucketIndex_; bucketIndex_ > -1; --bucketIndex_) {
                        if (buckets_[bucketIndex_].size() != 0) {
                            valueIndex_ = buckets_[bucketIndex_].size() - 1;
                            break;
                        }
                    }
                }
                ptr_ = (bucketIndex_ > -1) ? &buckets_[bucketIndex_][valueIndex_] : nullptr;
            }
            return *this;
        }

        bool IsBegin() {
            return bucketIndex_ < 0;
        }

        bool IsEnd() {
            return bucketIndex_ > (buckets_.size() - 1);
        }

    private:
        buckets_type & buckets_;
        int bucketIndex_;
        int valueIndex_;
        value_type * ptr_;

        Iterator(buckets_type & buckets, bool isEnd = false)
            : buckets_(buckets)
        {
            if (isEnd) {
                bucketIndex_ = buckets_.size();
            }
            else {
                for (bucketIndex_ = 0; bucketIndex_ < buckets_.size(); ++bucketIndex_) {
                    for (valueIndex_ = 0; valueIndex_ < buckets_[bucketIndex_].size(); ++valueIndex_) {
                        ptr_ = &buckets_[bucketIndex_][valueIndex_];
                        return;
                    }
                }
            }

            valueIndex_ = 0;
            ptr_ = nullptr;
        }

        Iterator(buckets_type & buckets, int bucketIndex, bool isEnd = false)
            : buckets_(buckets)
            , bucketIndex_(bucketIndex)
        {
            if (isEnd) {
                valueIndex_ = buckets_[bucketIndex_].size();
            }
            else {
                for (valueIndex_ = 0; valueIndex_ < buckets_[bucketIndex_].size(); ++valueIndex_) {
                    ptr_ = &buckets_[bucketIndex_][valueIndex_];
                    return;
                }
            }

            ptr_ = nullptr;
        }

        Iterator(buckets_type & buckets, value_type * ptr)
            : buckets_(buckets)
            , ptr_(ptr)
        {
            for (bucketIndex_ = 0; bucketIndex_ < buckets_.size(); ++bucketIndex_) {
                for (valueIndex_ = 0; valueIndex_ < buckets_[bucketIndex_].size(); ++valueIndex_) {
                    if (&buckets_[bucketIndex_][valueIndex_] == ptr_) {
                        return;
                    }
                }
            }

            valueIndex_ = 0;
            ptr_ = nullptr;
        }

        friend class UnorderedSet<Key, Hash, KeyEqual>;
    };
    using iterator = Iterator;
    using const_iterator = Iterator const;

    // Default constructor
    explicit UnorderedSet(
        size_type bucket_count = MIN_BUCKETS_COUNT,
        const hasher& hash = hasher(),
        const key_equal& equal = key_equal()
    ) throw(std::bad_alloc)
        : buckets_(buckets_type(bucket_count))
        , hasher_(hash)
        , keyEqual_(equal)
    {}

    // Copy constructor
    UnorderedSet(UnorderedSet& const other)
        : buckets_(buckets_type(other.buckets_))
        , hasher_(other.hasher_)
        , keyEqual_(other.keyEqual_)
    {}

    // Constructor from [first, last)
    template< class InputIt >
    UnorderedSet(
        InputIt first,
        InputIt last,
        size_type bucket_count = MIN_BUCKETS_COUNT,
        const hasher& hash = hasher(),
        const key_equal& equal = key_equal()
    ) throw(std::bad_alloc)
        : buckets_(buckets_type(bucket_count))
        , hasher_(hash)
        , keyEqual_(equal)
    {
        buckets_.insert(buckets_.end(), first, last);
    }

    // Constructor from std::initializer_list
    UnorderedSet(
        std::initializer_list<value_type> initList,
        size_type bucket_count = MIN_BUCKETS_COUNT,
        const hasher& hash = hasher(),
        const key_equal& equal = key_equal()
    ) throw(std::bad_alloc)
        : buckets_(buckets_type(bucket_count))
        , hasher_(other.hasher_)
        , keyEqual_(other.keyEqual_)
    {
        buckets_.insert(buckets.end(), initList);
    }

    // Destructor
    ~UnorderedSet()
    {}

    // Operator =
    UnorderedSet& operator=(UnorderedSet& const other)
    {
        if (this == &other) {
            return *this;
        }
        buckets_ = other.buckets_;
        hasher_ = other.hasher_;
        keyEqual_ = other.keyEqual_;
    }

    /* ITERATORS */

    // First iterator
    iterator Begin()
    {
        return iterator(buckets_);
    }

    const_iterator Begin() const
    {
        return const_iterator(buckets_);
    }

    const_iterator CBegin() const
    {
        return const_iterator(buckets_);
    }

    // Iterator after last
    iterator End()
    {
        return iterator(buckets_, true);
    }

    const_iterator End() const
    {
        return const_iterator(buckets_, true);
    }

    const_iterator CEnd() const
    {
        return const_iterator(buckets_, true);
    }

    /* CAPACITY */

    // Is empty or no
    bool Empty() const
    {
        return buckets_.empty();
    }

    // Number of elements
    size_type Size() const
    {
        size_type result = 0;
        for (bucket_type bucket : buckets_) {
            result += bucket.size();
        }
        return result;
    }

    // Maximum size of container
    size_type MaxSize() const
    {
        return buckets_type().max_size() * bucket_type().max_size();
    }

    /* MODIFIERS */

    // Delete all elements
    void Clear()
    {
        for (bucket_type& bucket : buckets_) {
            bucket.clear();
        }
    }

    // Insert an element
    std::pair<iterator, bool> Insert(const value_type& value)
    {
        iterator it = Find(value);
        if (!it.IsEnd()) {
            return std::pair<iterator, bool>(it, false);
        }

        if (float(Size() + 1) / (float)BucketCount() >= MaxLoadFactor()) {
            Rehash(buckets_.size() * 8);
        }
        buckets_[Bucket(value)].push_back(value);
        return std::pair<iterator, bool>(iterator(buckets_, &(buckets_[Bucket(value)].back())), true);
    }

    // Insert elements from [first, last)
    void Insert(iterator first, iterator last)
    {
        for (iterator it = first; it != last; ++it) {
            Insert(*it);
        }
    }

    // Insert from std::initializer_list
    void Insert(std::initializer_list<value_type> initList)
    {
        for (value_type& value : initList) {
            Insert(value);
        }
    }

    // Remove an element at position
    iterator Erase(const_iterator position)
    {
        // Iterator before deleted
        iterator result = position;
        --result;

        bucket_type& bucket = buckets_[position.bucketIndex_];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (keyEqual_(*it, *position)) {
                bucket.erase(it);
                break;
            }
        }
        return ++result;
    }

    // Remove elements in [first; last)
    iterator Erase(const_iterator first, const_iterator last)
    {
        iterator result;
        for (iterator it = first; it != last; ++it) {
            result = Erase(it);
        }
        return result;
    }

    // Remeve all elements with this value
    size_type Erase(const value_type& value)
    {
        for (bucket_type& bucket : buckets_) {
            for (auto it = bucket.begin(); it != bucket.end(); ++it) {
                if (keyEqual_(*it, value)) {
                    bucket.erase(it);
                    return 1;
                }
            }
        }
        return 0;
    }

    // Swap containers
    void Swap(UnorderedSet& other)
    {
        std::swap(buckets_, other.buckets_);
        std::swap(hasher_, other.hasher_);
        std::swap(keyEqual_, other.keyEqual_);
    }

    /* LOOKUP */

    // Number of elements with this value
    size_type Count(const value_type& value) const
    {
        for (const_iterator it(buckets_); !it.IsEnd(); ++it) {
            if (keyEqual_(*it, value)) {
                return 1;
            }
        }
        return 0;
    }

    // Element with this value
    iterator Find(const value_type& value)
    {
        for (iterator it(buckets_); !it.IsEnd(); ++it) {
            if (keyEqual_(*it, value)) {
                return it;
            }
        }
        return iterator(buckets_, true);
    }

    const_iterator Find(const value_type& value) const
    {
        for (const_iterator it(buckets_); !it.IsEnd(); ++it) {
            if (keyEqual_(*it, value)) {
                return it;
            }
        }
        return const_iterator(buckets_, true);
    }

    // Range of element with this value
    std::pair<iterator, iterator> EqualRange(const value_type& value)
    {
        for (iterator it(buckets_); !it.IsEnd(); ++it) {
            if (keyEqual_(*it, value)) {
                return std::pair<iterator, iterator>(it, it);
            }
        }
        iterator it = iterator(buckets_, true);
        return std::pair<iterator, iterator>(it, it);
    }

    std::pair<const_iterator, const_iterator> EqualRange(const value_type& value) const
    {
        for (const_iterator it(buckets_); !it.IsEnd(); ++it) {
            if (keyEqual_(*it, value)) {
                return std::pair<const_iterator, const_iterator>(it, it);
            }
        }
        const_iterator it = const_iterator(buckets_, true);
        return std::pair<const_iterator, const_iterator>(it, it);
    }

    /* BUCKET INTERFACE */

    // First iterator in bucket
    iterator Begin(size_type n)
    {
        return iterator(buckets_, n);
    }

    const_iterator Begin(size_type n) const
    {
        return const_iterator(buckets_, n);
    }

    const_iterator CBegin(size_type n) const
    {
        return const_iterator(buckets_, n);
    }

    // Iterator after last
    iterator End(size_type n)
    {
        return iterator(buckets_, n, true);
    }

    const_iterator End(size_type n) const
    {
        return const_iterator(buckets_, n, true);
    }

    const_iterator CEnd(size_type n) const
    {
        return const_iterator(buckets_, n, true);
    }

    // Number of buckets in container
    size_type BucketCount() const
    {
        return buckets_.size();
    }

    // Maximum bucket count
    size_type MaxBucketCount() const
    {
        return buckets_type().max_size();
    }

    // Number of elements in bucket
    size_type BucketSize(size_type n) const
    {
        return buckets_[n].size();
    }

    // Bucket index with this value
    size_type Bucket(const value_type& value) const
    {
        return hasher_(value) % BucketCount();
    }

    /* HASH POLICY */

    // Average number of elements in bucket
    float LoadFactor() const
    {
        return ((float)Size() / (float)BucketCount());
    }

    // Maximum number of elements in bucket
    float MaxLoadFactor() const
    {
        return maxLoadFactor_;
    }

    // Set maximum number of elements in bucket
    void MaxLoadFactor(float ml)
    {
        maxLoadFactor_ = ml;
        /* Rehash, if LoadFactor more than MaxLoadFactor
        if (LoadFactor() > maxLoadFactor_) {
            Rehash(buckets_.size() * 8 * ceil(LoadFactor() / maxLoadFactor_ / 8));
        } */
    }

    // Sets the number of buckets to count and rehashes the container
    void Rehash(size_type count)
    {
        buckets_type bucketsCopy(buckets_);

        buckets_.clear();
        buckets_.resize(count);
        for (iterator it(bucketsCopy); !it.IsEnd(); ++it) {
            Insert(*it);
        }
    }

    // Sets new capacity of the container
    void Reserve(size_type count)
    {
        buckets_.reserve(count);
    }

    /* OBSERVERS */

    // Current hash function
    hasher HashFunction() const
    {
        return hasher_;
    }

    // Key equal function
    key_equal KeyEq() const
    {
        return keyEqual_;
    }

protected:
    buckets_type buckets_;
    hasher hasher_;
    key_equal keyEqual_;
    float maxLoadFactor_;
};

// Operator ==
template< class Key, class Hash, class KeyEqual >
bool operator==(UnorderedSet<Key, Hash, KeyEqual>& lhs, UnorderedSet<Key, Hash, KeyEqual>& rhs)
{
    if (lhs.Size() != rhs.Size()) {
        return false;
    }

    auto lit = lhs.Begin();
    auto rit = rhs.Begin();
    while (true) {
        if (lit.IsEnd() || rit.IsEnd()) {
            break;
        }
        if (*lit != *rit) {
            return false;
        }
        ++lit;
        ++rit;
    }
    return true;
}

// Operator !=
template< class Key, class Hash, class KeyEqual >
bool operator!=(UnorderedSet<Key, Hash, KeyEqual>& lhs, UnorderedSet<Key, Hash, KeyEqual>& rhs)
{
    return !(lhs == rhs);
}

// std::swap
template< class Key, class Hash, class KeyEqual >
void swap(UnorderedSet<Key, Hash, KeyEqual>& lhs, UnorderedSet<Key, Hash, KeyEqual>& rhs)
{
    lhs.swap(rhs);
}