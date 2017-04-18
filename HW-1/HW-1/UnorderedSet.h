#pragma once

#include <vector> // for std::vector
#include <vcruntime_exception.h> // for std::bad_alloc
#include <utility> // for std::swap
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
        : public std::iterator<std::bidirectional_iterator_tag, value_type>
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
            if (!IsBeforeBegin()) {
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

        bool IsBeforeBegin() {
            return bucketIndex_ < 0;
        }

        bool IsEnd() {
            return bucketIndex_ > (buckets_.size() - 1);
        }

        bool IsBucketBegin() {
            return valueIndex_ == 0;
        }

    protected:
        buckets_type & buckets_;
        int bucketIndex_;
        int valueIndex_;
        value_type * ptr_;

        Iterator(buckets_type & buckets, bool isEnd)
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

        Iterator(buckets_type & buckets, int bucketIndex, bool isEnd)
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
        , maxLoadFactor_(1)
    {}

    // Copy constructor
    UnorderedSet(UnorderedSet& const other)
        : buckets_(buckets_type(other.buckets_))
        , hasher_(other.hasher_)
        , keyEqual_(other.keyEqual_)
        , maxLoadFactor_(other.maxLoadFactor_)
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
        , maxLoadFactor_(1)
    {
        Insert(first, last);
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
        , maxLoadFactor_(1)
    {
        Insert(initList);
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
        maxLoadFactor_ = other.maxLoadFactor_;
    }

    /* ITERATORS */

    // First iterator
    iterator Begin()
    {
        return iterator(buckets_, false);
    }

    const_iterator Begin() const
    {
        return const_iterator(buckets_, false);
    }

    const_iterator CBegin() const
    {
        return const_iterator(buckets_, false);
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
        return Size() == 0;
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
        buckets_.resize(MIN_BUCKETS_COUNT);
    }

    // Insert an element
    std::pair<iterator, bool> Insert(const value_type& value)
    {
        iterator it = Find(value);
        if (!it.IsEnd()) {
            return std::make_pair(it, false);
        }

        if (float(Size() + 1) / (float)BucketCount() >= MaxLoadFactor()) {
            Rehash(buckets_.size() * MIN_BUCKETS_COUNT);
        }
        buckets_[Bucket(value)].push_back(value);
        return std::make_pair(iterator(buckets_, &(buckets_[Bucket(value)].back())), true);
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
        iterator it = iterator(buckets_, Bucket(value), false);
        if (it.ptr_ != nullptr) {
            do {
                if (keyEqual_(*it, value)) {
                    return it;
                }
                ++it;
            } while (!it.IsBucketBegin());
        }
        return iterator(buckets_, true);
    }

    const_iterator Find(const value_type& value) const
    {
        const_iterator it = const_iterator(buckets_, Bucket(value), false);
        if (it.ptr_ != nullptr) {
            do {
                if (keyEqual_(*it, value)) {
                    return it;
                }
                ++it;
            } while (!it.IsBucketBegin());
        }
        return const_iterator(buckets_, true);
    }

    // Range of element with this value
    std::pair<iterator, iterator> EqualRange(const value_type& value)
    {
        iterator it = Find(value);
        return std::make_pair(it, it);
    }

    std::pair<const_iterator, const_iterator> EqualRange(const value_type& value) const
    {
        iterator it = Find(value);
        return std::make_pair(it, it);
    }

    /* BUCKET INTERFACE */

    // First iterator in bucket
    iterator Begin(size_type n)
    {
        return iterator(buckets_, n, false);
    }

    const_iterator Begin(size_type n) const
    {
        return const_iterator(buckets_, n, false);
    }

    const_iterator CBegin(size_type n) const
    {
        return const_iterator(buckets_, n, false);
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
        if (LoadFactor() > MaxLoadFactor()) {
            Rehash(buckets_.size() * MIN_BUCKETS_COUNT * ceil(LoadFactor() / MaxLoadFactor() / MIN_BUCKETS_COUNT));
        } */
    }

    // Sets the number of buckets to count and rehashes the container
    void Rehash(size_type count)
    {
        if (count < Size() / MaxLoadFactor()) {
            count = std::ceil(Size() / MaxLoadFactor());
        };
        size_type newCount = MIN_BUCKETS_COUNT;
        while (newCount < count) {
            newCount *= 2;
        }

        if (newCount == BucketCount()) {
            return;
        }

        buckets_type bucketsCopy(buckets_);

        buckets_.clear();
        buckets_.resize(newCount);
        for (iterator it(bucketsCopy, false); !it.IsEnd(); ++it) {
            Insert(*it);
        }
    }

    // Sets new capacity of the container
    void Reserve(size_type count)
    {
        Rehash(std::ceil(count / MaxLoadFactor()));
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

template< class Key,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>
> class std_unordered_set
    : public UnorderedSet<Key, Hash, KeyEqual>
{
public:
    iterator begin() { return Begin(); }
    const_iterator begin() const { return Begin(); }
    const_iterator cbegin() const { return CBegin(); }
    iterator end() { return End(); }
    const_iterator end() const { return End(); }
    const_iterator cend() const { return CEnd(); }
    bool empty() const { return Empty(); }
    size_type size() const { return Size(); }
    size_type max_size() const { return MaxSize(); }
    void clear() { Clear(); }
    std::pair<iterator, bool> insert(const value_type& value) { return Insert(value); }
    void insert(iterator first, iterator last) { Insert(first, last); }
    void insert(std::initializer_list<value_type> initList) { Insert(initList); }
    iterator erase(const_iterator position) { return Erase(position); }
    iterator erase(const_iterator first, const_iterator last) { return Erase(first, last); }
    size_type erase(const value_type& value) { return Erase(value); }
    void swap(UnorderedSet& other) { Swap(other); }
    size_type count(const value_type& value) const { return count(value); }
    iterator find(const value_type& value) { return Find(value); }
    const_iterator find(const value_type& value) const { return Find(value); }
    std::pair<iterator, iterator> equal_range(const value_type& value) { return EqualRange(value); }
    std::pair<const_iterator, const_iterator> equal_range(const value_type& value) const { return EqualRange(value); }
    iterator begin(size_type n) { return Begin(n); }
    const_iterator begin(size_type n) const { return Begin(n); }
    const_iterator cbegin(size_type n) const { return CBegin(n); }
    iterator end(size_type n) { return End(n); }
    const_iterator end(size_type n) const { return End(n); }
    const_iterator cend(size_type n) const { return CEnd(n); }
    size_type bucket_count() const { return BucketCount(); }
    size_type max_bucket_count() const { return MaxBucketCount(); }
    size_type bucket_size(size_type n) const { return BucketSize(n); }
    size_type bucket(const value_type& value) const { return Bucket(value); }
    float load_factor() const { return LoadFactor(); }
    float max_load_factor() const { return MaxLoadFactor(); }
    void max_load_factor(float ml) { MaxLoadFactor(ml); }
    void rehash(size_type count) { Rehash(count); }
    void reserve(size_type count) { Reserve(count); }
    hasher hash_function() const { return HashFunction(); }
    key_equal key_eq() const { return KeyEq(); }
};