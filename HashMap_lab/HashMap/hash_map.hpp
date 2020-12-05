#include <functional>
#include <memory>
#include <utility>
#include <type_traits>
#include <vector>
#include <limits>

namespace fefu
{
    template<typename T>
    class allocator {
    public:
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = typename std::add_lvalue_reference<T>::type;
        using const_reference = typename std::add_lvalue_reference<const T>::type;
        using value_type = T;

        allocator() noexcept = default;

        allocator(const allocator&) noexcept = default;

        template <class U>
        allocator(const allocator<U>&) noexcept {};

        ~allocator() = default;

        pointer allocate(size_type size = 1) {
            return static_cast<pointer>(::operator new(size * sizeof(value_type)));
        }

        void deallocate(pointer p, size_type n) noexcept {
            if (p != nullptr) {
                ::operator delete(p, n * sizeof(value_type));
            }
        }
    };

    template<typename ValueType>
    class hash_map_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = ValueType;
        using difference_type = std::ptrdiff_t;
        using reference = ValueType&;
        using pointer = ValueType*;

        hash_map_iterator() noexcept : ptr_value_(nullptr), used_(0) {}

        hash_map_iterator(const pointer& ptr_value, const std::vector<bool>& used) {
            ptr_value_ = ptr_value;
            used_ = used;
        }

        hash_map_iterator(const hash_map_iterator& other) noexcept {
            ptr_value_ = other.ptr_value_;
            used_ = other.used_;
        }

        reference operator*() const {
            return *(ptr_value_);
        }

        pointer operator->() const {
            return ptr_value_;
        }

        // prefix ++
        hash_map_iterator& operator++() { //TODO works not correct, make foreach to check where used[] is true
            ptr_value_++;

            return *this;
        }
        // postfix ++
        hash_map_iterator operator++(int) {
            return (*this)++;
        }

        friend bool operator==(const hash_map_iterator<ValueType>& lhs, const hash_map_iterator<ValueType>& rhs) {
            return lhs.ptr_value_ == rhs.ptr_value_;
        }

        friend bool operator!=(const hash_map_iterator<ValueType>& lhs, const hash_map_iterator<ValueType>& rhs) {
            return lhs.ptr_value_ != rhs.ptr_value_;
        }

    private:
        pointer ptr_value_;
        std::vector<bool> used_;
    };

    template<typename ValueType>
    class hash_map_const_iterator {
        // Shouldn't give non const references on value
    public:
        template<typename, typename, typename, typename, typename>
        friend class hash_map;

        using iterator_category = std::forward_iterator_tag;
        using value_type = ValueType;
        using difference_type = std::ptrdiff_t;
        using reference = const ValueType&;
        using pointer = const ValueType*;

        hash_map_const_iterator() noexcept : ptr_value_(nullptr), used_(0) {}

        hash_map_const_iterator(const pointer& ptr_value, const std::vector<bool>& used) {
            ptr_value_ = ptr_value;
            used_ = used;
        }

        hash_map_const_iterator(const hash_map_const_iterator& other) noexcept {
            ptr_value_ = other.ptr_value_;
            used_ = other.used_;
        }

        hash_map_const_iterator(const hash_map_iterator<ValueType>& other) noexcept {
            ptr_value_ = other.ptr_value_;
            used_ = other.used_;
        }

        reference operator*() const {
            return *ptr_value_;
        }

        pointer operator->() const {
            return ptr_value_;
        }

        // prefix ++
        hash_map_const_iterator& operator++() {
            ptr_value_++;

            return *this;
        }
        // postfix ++
        hash_map_const_iterator operator++(int) {
            return (*this)++;
        }

        friend bool operator==(const hash_map_const_iterator<ValueType>& lhs, const hash_map_const_iterator<ValueType>& rhs) {
            return lhs.ptr_value_ == rhs.ptr_value_;
        }
        friend bool operator!=(const hash_map_const_iterator<ValueType>& lhs, const hash_map_const_iterator<ValueType>& rhs) {
            return lhs.ptr_value_ != rhs.ptr_value_;
        }

    private:
        pointer ptr_value_;
        std::vector<bool> used_;
    };

    class PrimeNumberGenerator {
    public:
        explicit PrimeNumberGenerator(size_t start) {
            if (start == 1) {
                start++;
            }

            prime_number_ = start;
        }

        size_t GetNextPrime() {
            if (prime_number_ != 2 && prime_number_ % 2 == 0) {
                prime_number_++;
            }

            while (!IsPrime(prime_number_)) {
                prime_number_ += 2;
            }

            return prime_number_++;
        }

    private:
        size_t prime_number_;

        bool IsPrime(size_t number) {
            if (number % 2 == 0) {
                return number == 2;
            }

            size_t divisor = 3;

            while (divisor * divisor <= number && number % divisor != 0) {
                divisor += 2;
            }

            return divisor * divisor > number;
        }
    };

    template<typename K, typename T,
        typename Hash = std::hash<K>,
        typename Pred = std::equal_to<K>,
        typename Alloc = allocator<std::pair<const K, T>>>
        class hash_map
    {
    public:
        using key_type = K;
        using mapped_type = T;
        using hasher = Hash;
        using key_equal = Pred;
        using allocator_type = Alloc;
        using value_type = std::pair<const key_type, mapped_type>;
        using reference = value_type&;
        using const_reference = const value_type&;
        using iterator = hash_map_iterator<value_type>;
        using const_iterator = hash_map_const_iterator<value_type>;
        using size_type = std::size_t;

        /// Default constructor.
        hash_map() : max_load_factor_(0.5), size_(0), capacity_(0), ptr_begin_(nullptr), used_(0), prime_number_generator_(prime_num_) {};

        /**
         *  @brief  Default constructor creates no elements.
         *  @param n  Minimal initial number of buckets.
         */
        explicit hash_map(size_type n) : max_load_factor_(0.5),
            used_(n, false), size_(0),
            capacity_(n),
            ptr_begin_(allocator_.allocate(n)),
            prime_number_generator_(prime_num_) {}

        /**
         *  @brief  Builds an %hash_map from a range.
         *  @param  first  An input iterator.
         *  @param  last  An input iterator.
         *  @param  n  Minimal initial number of buckets.
         *
         *  Create an %hash_map consisting of copies of the elements from
         *  [first,last).  This is linear in N (where N is
         *  distance(first,last)).
         */
        template<typename InputIterator>
        hash_map(InputIterator first, InputIterator last, size_type n = 0) : hash_map(n) {
            insert(first, last);
        }

        /// Copy constructor.
        hash_map(const hash_map& other) {
            allocator_ = other.allocator_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            max_load_factor_ = other.max_load_factor_;
            ptr_begin_ = other.ptr_begin_;
            used_ = other.used_;
            hash_ = other.hash_;
            equal_ = other.equal_;
            prime_number_generator_ = other.prime_number_generator_;

            for (size_type i = 0; i != capacity_; i++) {
                if (used_[i]) {
                    new(ptr_begin_ + i) value_type(other.ptr_begin_[i]);
                }
            }

        }

        /// Move constructor.
        hash_map(hash_map&& other) : hash_map() {
            swap(other);
        }

        /**
         *  @brief Creates an %hash_map with no elements.
         *  @param a An allocator object.
         */
        explicit hash_map(const allocator_type& a) : allocator_(a), max_load_factor_(0.5), size_(0),
            capacity_(0), ptr_begin_(nullptr), used_(0),
            prime_number_generator_(prime_num_) {}

        /*
        *  @brief Copy constructor with allocator argument.
        * @param  uset  Input %hash_map to copy.
        * @param  a  An allocator object.
        */
        hash_map(const hash_map& umap,
            const allocator_type& a) : allocator_(a) {
            size_ = umap.size_;
            capacity_ = umap.capacity_;
            max_load_factor_ = umap.max_load_factor_;
            ptr_begin_ = allocator_.allocate(umap.capacity_);
            used_ = umap.used_;
            hash_ = umap.hash_;
            equal_ = umap.equal_;
            prime_number_generator_ = umap.prime_number_generator_;

            for (size_type i = 0; i != capacity_; i++) {
                if (used_[i]) {
                    new(ptr_begin_ + i) value_type(umap.ptr_begin_[i]);
                }
            }
        }

        /*
        *  @brief  Move constructor with allocator argument.
        *  @param  uset Input %hash_map to move.
        *  @param  a    An allocator object.
        */
        hash_map(hash_map&& umap,
            const allocator_type& a) : hash_map(allocator_) {
            swap(umap);
        }

        /**
         *  @brief  Builds an %hash_map from an initializer_list.
         *  @param  l  An initializer_list.
         *  @param n  Minimal initial number of buckets.
         *
         *  Create an %hash_map consisting of copies of the elements in the
         *  list. This is linear in N (where N is @a l.size()).
         */
        hash_map(std::initializer_list<value_type> l,
            size_type n = 0) : hash_map(n) {
            insert(l);
        }

        /// Copy assignment operator.
        hash_map& operator=(const hash_map& other) {
            *this = hash_map(other);
            return *this;
        }

        /// Move assignment operator.
        hash_map& operator=(hash_map&& other) {
            swap(other);
            return *this;
        }

        /**
         *  @brief  %hash_map list assignment operator.
         *  @param  l  An initializer_list.
         *
         *  This function fills an %hash_map with copies of the elements in
         *  the initializer list @a l.
         *
         *  Note that the assignment completely changes the %hash_map and
         *  that the resulting %hash_map's size is the same as the number
         *  of elements assigned.
         */
        hash_map& operator=(std::initializer_list<value_type> l) {
            *this = hash_map(l);
            return *this;
        }

        ///  Returns the allocator object used by the %hash_map.
        allocator_type get_allocator() const noexcept {
            return allocator_;
        }

        // size and capacity:

        ///  Returns true if the %hash_map is empty.
        bool empty() const noexcept {
            return size_ == 0;
        }

        ///  Returns the size of the %hash_map.
        size_type size() const noexcept {
            return size_;
        }

        ///  Returns the maximum size of the %hash_map.
        size_type max_size() const noexcept {
            return std::numeric_limits<size_type>::max();
        }

        // iterators.

        /**
         *  Returns a read/write iterator that points to the first element in the
         *  %hash_map.
         */
        iterator begin() noexcept {
            for (size_t i = 0; i != capacity_; i++) {
                if (used_[i]) {
                    return iterator(ptr_begin_ + i, used_);
                }
            }

            return iterator(ptr_begin_ + capacity_, used_);
        }

        //@{
        /**
         *  Returns a read-only (constant) iterator that points to the first
         *  element in the %hash_map.
         */
        const_iterator begin() const noexcept {
            return cbegin();
        }

        const_iterator cbegin() const noexcept {
            for (size_t i = 0; i != capacity_; i++) {
                if (used_[i]) {
                    return const_iterator(ptr_begin_ + i, used_);
                }
            }

            return cend();
        }

        /**
         *  Returns a read/write iterator that points one past the last element in
         *  the %hash_map.
         */
        iterator end() noexcept {
            return iterator(ptr_begin_ + capacity_, used_);
        }

        //@{
        /**
         *  Returns a read-only (constant) iterator that points one past the last
         *  element in the %hash_map.
         */
        const_iterator end() const noexcept {
            return cend();
        }

        const_iterator cend() const noexcept {
            return const_iterator(&ptr_begin_[capacity_], used_);
        }
        //@}

        // modifiers.

        /**
         *  @brief Attempts to build and insert a std::pair into the
         *  %hash_map.
         *
         *  @param args  Arguments used to generate a new pair instance (see
         *	        std::piecewise_contruct for passing arguments to each
        *	        part of the pair constructor).
        *
        *  @return  A pair, of which the first element is an iterator that points
        *           to the possibly inserted pair, and the second is a bool that
        *           is true if the pair was actually inserted.
        *
        *  This function attempts to build and insert a (key, value) %pair into
        *  the %hash_map.
        *  An %hash_map relies on unique keys and thus a %pair is only
        *  inserted if its first element (the key) is not already present in the
        *  %hash_map.
        *
        *  Insertion requires amortized constant time.
        */
        template<typename... _Args>
        std::pair<iterator, bool> emplace(_Args&&... args) {
            return insert(value_type(std::forward<_Args>(args)...));
        }

        /**
         *  @brief Attempts to build and insert a std::pair into the
         *  %hash_map.
         *
         *  @param k    Key to use for finding a possibly existing pair in
         *                the hash_map.
         *  @param args  Arguments used to generate the .second for a
         *                new pair instance.
         *
         *  @return  A pair, of which the first element is an iterator that points
         *           to the possibly inserted pair, and the second is a bool that
         *           is true if the pair was actually inserted.
         *
         *  This function attempts to build and insert a (key, value) %pair into
         *  the %hash_map.
         *  An %hash_map relies on unique keys and thus a %pair is only
         *  inserted if its first element (the key) is not already present in the
         *  %hash_map.
         *  If a %pair is not inserted, this function has no effect.
         *
         *  Insertion requires amortized constant time.
         */
        template <typename... _Args>
        std::pair<iterator, bool> try_emplace(const key_type& k, _Args&&... args) {
            return insert(value_type(std::piecewise_construct, std::forward_as_tuple(k), std::forward_as_tuple(std::forward<_Args>(args)...)));
        }

        // move-capable overload
        template <typename... _Args>
        std::pair<iterator, bool> try_emplace(key_type&& k, _Args&&... args) {
            return insert(value_type(std::piecewise_construct, std::forward_as_tuple(k), std::forward_as_tuple(std::forward<_Args>(args)...)));
        }

        //@{
        /**
         *  @brief Attempts to insert a std::pair into the %hash_map.
         *  @param x Pair to be inserted (see std::make_pair for easy
         *	     creation of pairs).
        *
        *  @return  A pair, of which the first element is an iterator that
        *           points to the possibly inserted pair, and the second is
        *           a bool that is true if the pair was actually inserted.
        *
        *  This function attempts to insert a (key, value) %pair into the
        *  %hash_map. An %hash_map relies on unique keys and thus a
        *  %pair is only inserted if its first element (the key) is not already
        *  present in the %hash_map.
        *
        *  Insertion requires amortized constant time.
        */
        std::pair<iterator, bool> insert(const value_type& x) {
            if (capacity_ == 0) {
                rehash(capacity_ + 2);
            }

            if (contains(x.first)) {
                return make_pair(find(x.first), false);
            }

            size_t hash_f = hash_first(x.first) % capacity_;
            size_t hash_s = hash_second(x.first) % capacity_;

            for (size_t i = 0; i != capacity_; i++) {
                if (!used_[hash_f]) {
                    used_[hash_f] = true;
                    size_++;
                    new (&ptr_begin_[hash_f]) value_type(x);
                    return std::make_pair(iterator(ptr_begin_ + hash_f, used_), true);
                }

                hash_f = (hash_f + i * hash_s) % capacity_;
            }

            rehash(capacity_ * 2);
            return std::make_pair(find(x.first), true);
        }

        std::pair<iterator, bool> insert(value_type&& x) {
            size_t hash_f = hash_first(x.first) % capacity_;
            size_t hash_s = hash_second(x.first) % capacity_;

            for (size_t i = 0; i != capacity_; i++) {
                if (!used_[hash_f]) {
                    used_[hash_f] = true;
                    size_++;
                    new (&ptr_begin_[hash_f]) value_type(x);
                    return std::make_pair(iterator(ptr_begin_ + hash_f, used_), true);
                }

                hash_f = (hash_f + i * hash_s) % capacity_;
            }

            rehash(capacity_ * 2);
            return std::make_pair(find(x.first), true);
        }

        //@}

        /**
         *  @brief A template function that attempts to insert a range of
         *  elements.
         *  @param  first  Iterator pointing to the start of the range to be
         *                   inserted.
         *  @param  last  Iterator pointing to the end of the range.
         *
         *  Complexity similar to that of the range constructor.
         */
        template<typename _InputIterator>
        void insert(_InputIterator first, _InputIterator last) {
            for (_InputIterator ptr_element = first; ptr_element != last; ptr_element++) {
                insert(*ptr_element);
            }
        }

        /**
         *  @brief Attempts to insert a list of elements into the %hash_map.
         *  @param  l  A std::initializer_list<value_type> of elements
         *               to be inserted.
         *
         *  Complexity similar to that of the range constructor.
         */
        void insert(std::initializer_list<value_type> l) {
            insert(l.begin(), l.end());
        }


        /**
         *  @brief Attempts to insert a std::pair into the %hash_map.
         *  @param k    Key to use for finding a possibly existing pair in
         *                the map.
         *  @param obj  Argument used to generate the .second for a pair
         *                instance.
         *
         *  @return  A pair, of which the first element is an iterator that
         *           points to the possibly inserted pair, and the second is
         *           a bool that is true if the pair was actually inserted.
         *
         *  This function attempts to insert a (key, value) %pair into the
         *  %hash_map. An %hash_map relies on unique keys and thus a
         *  %pair is only inserted if its first element (the key) is not already
         *  present in the %hash_map.
         *  If the %pair was already in the %hash_map, the .second of
         *  the %pair is assigned from obj.
         *
         *  Insertion requires amortized constant time.
         */
        template <typename _Obj>
        std::pair<iterator, bool> insert_or_assign(const key_type& k, _Obj&& obj) {
            if (!contains((k))) {
                return insert(std::make_pair(k, std::forward<_Obj>(obj)));
            }

            return std::make_pair(find(k), true);
        }

        // move-capable overload
        template <typename _Obj>
        std::pair<iterator, bool> insert_or_assign(key_type&& k, _Obj&& obj) {
            if (!contains((k))) {
                return insert(std::make_pair(k, std::forward<_Obj>(obj)));
            }

            return std::make_pair(find(k), true);
        }

        //@{
        /**
         *  @brief Erases an element from an %hash_map.
         *  @param  position  An iterator pointing to the element to be erased.
         *  @return An iterator pointing to the element immediately following
         *          @a position prior to the element being erased. If no such
         *          element exists, end() is returned.
         *
         *  This function erases an element, pointed to by the given iterator,
         *  from an %hash_map.
         *  Note that this function only erases the element, and that if the
         *  element is itself a pointer, the pointed-to memory is not touched in
         *  any way.  Managing the pointer is the user's responsibility.
         */
        iterator erase(const_iterator position) {
            auto pos = position.ptr_value_ - ptr_begin_;

            if (pos < capacity_ && used_[pos]) {
                used_[pos] = false;
                size_--;
                (ptr_begin_ + pos++)->~value_type();

                return iterator(ptr_begin_ + pos, pos);
            }

            return end();
        }

        // LWG 2059.
        iterator erase(iterator position) {
            auto pos = position.ptr_value_ - ptr_begin_;

            if (pos < capacity_ && used_[pos]) {
                used_[pos] = false;
                size_--;
                (ptr_begin_ + pos++)->~value_type();

                return iterator(ptr_begin_ + pos, pos);
            }

            return end();
        }
        //@}

        /**
         *  @brief Erases elements according to the provided key.
         *  @param  x  Key of element to be erased.
         *  @return  The number of elements erased.
         *
         *  This function erases all the elements located by the given key from
         *  an %hash_map. For an %hash_map the result of this function
         *  can only be 0 (not present) or 1 (present).
         *  Note that this function only erases the element, and that if the
         *  element is itself a pointer, the pointed-to memory is not touched in
         *  any way.  Managing the pointer is the user's responsibility.
         */
        size_type erase(const key_type& x) {
            if (contains(x)) {
                erase(find(x));
                return 1;
            }

            return 0;
        }

        /**
         *  @brief Erases a [first,last) range of elements from an
         *  %hash_map.
         *  @param  first  Iterator pointing to the start of the range to be
         *                  erased.
         *  @param last  Iterator pointing to the end of the range to
         *                be erased.
         *  @return The iterator @a last.
         *
         *  This function erases a sequence of elements from an %hash_map.
         *  Note that this function only erases the elements, and that if
         *  the element is itself a pointer, the pointed-to memory is not touched
         *  in any way.  Managing the pointer is the user's responsibility.
         */
        iterator erase(const_iterator first, const_iterator last) {
            for (const_iterator ptr_element = first; ptr_element != last; ptr_element++) {
                erase(*ptr_element);
            }

            return iterator(last.ptr_value_ - ptr_begin_, used_);
        }

        /**
         *  Erases all elements in an %hash_map.
         *  Note that this function only erases the elements, and that if the
         *  elements themselves are pointers, the pointed-to memory is not touched
         *  in any way.  Managing the pointer is the user's responsibility.
         */
        void clear() noexcept {
            if (size_ > 0) {
                erase(begin(), end());
                used_ = std::vector<bool>(capacity_, false);
                size_ = 0;
                prime_number_generator_ = PrimeNumberGenerator(2);
            }
        }

        /**
         *  @brief  Swaps data with another %hash_map.
         *  @param  x  An %hash_map of the same element and allocator
         *  types.
         *
         *  This exchanges the elements between two %hash_map in constant
         *  time.
         *  Note that the global std::swap() function is specialized such that
         *  std::swap(m1,m2) will feed to this function.
         */
        void swap(hash_map& x) {
            std::swap(size_, x.size_);
            std::swap(capacity_, x.capacity_);
            std::swap(max_load_factor_, x.max_load_factor_);
            std::swap(ptr_begin_, x.ptr_begin_);
            std::swap(used_, x.used_);
            std::swap(hash_, x.hash_);
            std::swap(equal_, x.equal_);
            std::swap(allocator_, x.allocator_);
            std::swap(prime_number_generator_, x.prime_number_generator_);
        }

        template<typename _H2, typename _P2>
        void merge(hash_map<K, T, _H2, _P2, Alloc>& source) {
            for (auto i = source.begin(); i != source.end(); i++) {
                insert(*i);
            }
        }

        template<typename _H2, typename _P2>
        void merge(hash_map<K, T, _H2, _P2, Alloc>&& source) {
            for (auto i = source.begin(); i != source.end(); i++) {
                insert(*i);
            }
        }

        // observers.

        ///  Returns the hash functor object with which the %hash_map was
        ///  constructed.
        Hash hash_function() const {
            return hash_;
        }

        ///  Returns the key comparison object with which the %hash_map was
        ///  constructed.
        Pred key_eq() const {
            return equal_;
        }

        // lookup.

        //@{
        /**
         *  @brief Tries to locate an element in an %hash_map.
         *  @param  x  Key to be located.
         *  @return  Iterator pointing to sought-after element, or end() if not
         *           found.
         *
         *  This function takes a key and tries to locate the element with which
         *  the key matches.  If successful the function returns an iterator
         *  pointing to the sought after element.  If unsuccessful it returns the
         *  past-the-end ( @c end() ) iterator.
         */
        iterator find(const key_type& x) {
            size_t hash_f = hash_first(x) % capacity_;
            size_t hash_s = hash_second(x) % capacity_;

            for (size_t i = 0; i != capacity_; i++) {
                if (used_[hash_f] && ptr_begin_[hash_f].first == x) {
                    return iterator(ptr_begin_ + hash_f, used_);
                }

                hash_f = (hash_f + i * hash_s) % capacity_;
            }

            return end(); //TODO
        }

        const_iterator find(const key_type& x) const {
            /*size_t hash_f = hash_first(x);
            size_t hash_s = hash_second(x);

            for (size_t i = 0; i != capacity_; i++) {
              if (used_[hash_f] && ptr_begin_[hash_f].first == x) {
                return const_iterator(ptr_begin_ + hash_f, used_);
              }

              hash_f = (hash_f + i * hash_s) % capacity_;
            }*/

            return cend();
        }
        //@}

        /**
         *  @brief  Finds the number of elements.
         *  @param  x  Key to count.
         *  @return  Number of elements with specified key.
         *
         *  This function only makes sense for %unordered_multimap; for
         *  %hash_map the result will either be 0 (not present) or 1
         *  (present).
         */
        size_type count(const key_type& x) const {
            return contains(x);
        }

        /**
         *  @brief  Finds whether an element with the given key exists.
         *  @param  x  Key of elements to be located.
         *  @return  True if there is any element with the specified key.
         */
        bool contains(const key_type& x) const {
            return find(x) != end();
        }

        //@{
        /**
         *  @brief  Subscript ( @c [] ) access to %hash_map data.
         *  @param  k  The key for which data should be retrieved.
         *  @return  A reference to the data of the (key,data) %pair.
         *
         *  Allows for easy lookup with the subscript ( @c [] )operator.  Returns
         *  data associated with the key specified in subscript.  If the key does
         *  not exist, a pair with that key is created using default values, which
         *  is then returned.
         *
         *  Lookup requires constant time.
         */
        mapped_type& operator[](const key_type& k);

        mapped_type& operator[](key_type&& k);
        //@}

        //@{
        /**
         *  @brief  Access to %hash_map data.
         *  @param  k  The key for which data should be retrieved.
         *  @return  A reference to the data whose key is equal to @a k, if
         *           such a data is present in the %hash_map.
         *  @throw  std::out_of_range  If no such data is present.
         */
        mapped_type& at(const key_type& k) {
            if (!contains(k)) {
                throw std::out_of_range("null reference exception: index is out of range");
            }

            return find(k)->second;
        }

        const mapped_type& at(const key_type& k) const {
            (*this).at(k);
        }
        //@}

        // bucket interface.

        /// Returns the number of buckets of the %hash_map.
        size_type bucket_count() const noexcept {
            return capacity_;
        }

        /*
        * @brief  Returns the bucket index of a given element.
        * @param  _K  A key instance.
        * @return  The key bucket index.
        */
        size_type bucket(const key_type& _K) const {
            if (!contains(_K)) {
                throw std::invalid_argument("key is not in the hash map");
            }

            return find(_K)->first;
        }

        // hash policy.

        /// Returns the average number of elements per bucket.
        float load_factor() const noexcept {
            return size_ == 0 ? 0 : static_cast<float>(static_cast<float>(size_) / capacity_);
        }

        /// Returns a positive number that the %hash_map tries to keep the
        /// load factor less than or equal to.
        float max_load_factor() const noexcept {
            return max_load_factor_;
        }

        /**
         *  @brief  Change the %hash_map maximum load factor.
         *  @param  z The new maximum load factor.
         */
        void max_load_factor(float z) {  //TODO maybe it is needed to throw exception when max_load_factor > 100%
            max_load_factor_ = z;
        }

        /**
         *  @brief  May rehash the %hash_map.
         *  @param  n The new number of buckets.
         *
         *  Rehash will occur only if the new number of buckets respect the
         *  %hash_map maximum load factor.
         */
        void rehash(size_type n) {
            *this = hash_map(begin(), end(), n);

            auto next_prime = prime_number_generator_.GetNextPrime();

            if (next_prime < capacity_) {
                prime_num_ = next_prime;
            }
        }

        /**
         *  @brief  Prepare the %hash_map for a specified number of
         *          elements.
         *  @param  n Number of elements required.
         *
         *  Same as rehash(ceil(n / max_load_factor())).
         */
        void reserve(size_type n) {
            rehash(ceil(n / max_load_factor()));
        }

        bool operator==(const hash_map& other) const {
            if (size_ != other.size_) {
                return false;
            }

            for (auto& element : other) {
                if (!contains(element.first)) {
                    return false;
                }
            }

            return true;
        }

    private:
        allocator_type allocator_;
        size_type size_;
        size_type capacity_;
        float max_load_factor_;
        value_type* ptr_begin_;
        std::vector<bool> used_;
        Hash hash_;
        key_equal equal_;
        size_t prime_num_ = 2;
        PrimeNumberGenerator prime_number_generator_;

        size_t hash_first(const key_type& key) {
            return hash_(key) % capacity_;
        }

        size_t hash_second(const key_type& key) {
            return prime_num_ - hash_(key) % prime_num_;
        }
    };

} // namespace fefu
