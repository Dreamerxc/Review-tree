//
// Created by 谯保林 on 2021/6/21.
//

#ifndef MYTINYSTL_MAP_H
#define MYTINYSTL_MAP_H

#include "rb_tree.h"


namespace MyTinySTL
{
    template<typename Arg1, typename Arg2, typename Result>
    struct binary_function
    {
        /// @c first_argument_type is the type of the first argument
        typedef Arg1 	first_argument_type;

        /// @c second_argument_type is the type of the second argument
        typedef Arg2 	second_argument_type;

        /// @c result_type is the return type
        typedef Result 	result_type;
    };

    template <class Key, class T, class Compare = std::less<Key> >
    class map
    {
    public:
        typedef Key                      key_type;
        typedef T                        mapped_type;
        typedef std::pair<const Key, T>  value_type;
        typedef Compare                  key_compare;

        // 定义一个functor, 其作用是调用“元素比较函数”
        class value_compare : public binary_function<value_type, value_type, bool> {
            friend class map<Key, T, Compare>;
        private:
            Compare comp;
            value_compare(Compare c) : comp(c) {}

        public:
            bool operator()(const value_type& lhs, const value_type& rhs) const {
                return comp(lhs.first, rhs.first);
            }
        };
    private:
        typedef MyTinySTL::rb_tree<value_type, key_compare > base_type;
        base_type tree_;


    public:
        typedef typename base_type::tree_type              tree_type;
        typedef typename base_type::pointer                pointer;
        typedef typename base_type::const_pointer          const_pointer;
        typedef typename base_type::reference              reference;
        typedef typename base_type::const_reference        const_reference;
        typedef typename base_type::iterator               iterator;
        typedef typename base_type::const_iterator         const_iterator;
        typedef typename base_type::reverse_iterator       reverse_iterator;
        typedef typename base_type::const_reverse_iterator const_reverse_iterator;
        typedef typename base_type::size_type              size_type;
        typedef typename base_type::difference_type        difference_type;
        typedef typename base_type::allocator_type         allocator_type;

    public:
        map() = default;
        map(const map& rhs) : tree_(rhs.tree_) {}
        map(map&& rhs) : tree_(MyTinySTL::move(rhs.tree_)) {}

        template <class Iter>
        map(Iter first, Iter last) :tree_() {
            tree_.insert_unique(first, last);
        }

        map(std::initializer_list<value_type> ilist) : tree_() {
            tree_.insert_unique(ilist.begin(), ilist.end());
        }

        map& operator=(const map& rhs) {
            tree_ = rhs.tree_;
            return *this;
        }
        map& operator=(map&& rhs) {
            tree_ = MyTinySTL::move(rhs.tree_);
            return *this;
        }
        map& operator=(std::initializer_list<value_type> ilist) {
            tree_.clear();
            tree_.insert_unique(ilist.begin(), ilist.end());
            return *this;
        }

        key_compare            key_comp()      const { return tree_.key_comp(); }
        value_compare          value_comp()    const { return value_compare(tree_.key_comp()); }
        allocator_type         get_allocator() const { return tree_.get_allocator(); }
    public:
        iterator begin()
        { return tree_.begin(); }
        const_iterator begin() const
        { return tree_.begin(); }
        iterator end()
        { return tree_.end(); }
        const_iterator end() const
        { return tree_.end(); }

        reverse_iterator rbegin()
        { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const
        { return const_reverse_iterator(end()); }
        reverse_iterator rend()
        { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const
        { return const_reverse_iterator(begin()); }

        const_iterator         cbegin()
        { return begin(); }
        const_iterator         cend()    const
        { return end(); }
        const_reverse_iterator crbegin()
        { return rbegin(); }
        const_reverse_iterator crend()   const
        { return rend(); }

        bool empty() { return tree_.empty(); }
        size_type size() { return tree_.size(); }

        mapped_type& at(const key_type& key) {
            auto it = lower_bound(key);
            if (it == end() || key_comp()(it->first, key))
                throw std::out_of_range("No elems exits!");
            return it->second;
        }

        const mapped_type& at(const key_type& key) const{
            auto it = lower_bound(key);
            if (it == end() || key_comp()(it->first, key))
                throw std::out_of_range("No elems exits!");
            return it->second;
        }

        mapped_type& operator[](const key_type& key) {
            iterator it = lower_bound(key);
            if (it == end() || key_comp()(key, it->first)) {
                it = emplace_pos(it, key, key);
            }
            return it->second;
        }

        mapped_type& operator[](key_type&& key) {
            iterator it = lower_bound(key);
            if (it == end() || key_comp()(key, it->first)) {
                it = emplace_pos(it, MyTinySTL::move(key), T{});
            }
            return it->second;
        }

        template <class ...Args>
        std::pair<iterator, bool> emplace(Args&& ...args) {
            return tree_.emplace_unique(MyTinySTL::forward(args)...);
        }

        template <class ...Args>
        iterator emplace_pos(iterator pos, Args&& ...args) {
            return tree_.emplace_unique_at_pos(pos, MyTinySTL::forward<Args>(args)...);
        }

        std::pair<iterator, bool> insert(const value_type& value)
        {
            return tree_.insert_unique(value);
        }
        std::pair<iterator, bool> insert(value_type&& value)
        {
            return tree_.insert_unique(MyTinySTL::move(value));
        }

        iterator insert(iterator pos, const value_type& value)
        {
            return tree_.insert_unique(pos, value);
        }
        iterator insert(iterator pos, value_type&& value)
        {
            return tree_.insert_unique(pos, MyTinySTL::move(value));
        }

        template <class Iter>
        iterator insert(Iter first, Iter last) {
            tree_.insert_unique(first, last);
        }

        void erase(iterator pos) { return tree_.erase(pos); }
        size_type erase(const key_type& key)           { return tree_.erase_unique(key); }
        void      erase(iterator first, iterator last) { tree_.erase(first, last); }

        void      clear()                              { tree_.clear(); }

        iterator       find(const key_type& key)              { return tree_.find(key); }
        const_iterator find(const key_type& key)        const { return tree_.find(key); }

        iterator       lower_bound(const key_type& key)              { return tree_.lower_bound(key); }
        const_iterator lower_bound(const key_type& key)        const { return tree_.lower_bound(key); }

        iterator       upper_bound(const key_type& key)              { return tree_.upper_bound(key); }
        const_iterator upper_bound(const key_type& key)        const { return tree_.upper_bound(key); }

    public:
        friend bool operator==(const map& lhs, const map& rhs) { return lhs.tree_ == rhs.tree_; }
        friend bool operator< (const map& lhs, const map& rhs) { return lhs.tree_ <  rhs.tree_; }
    };

    template <class Key, class T, class Compare>
    bool operator==(const map<Key, T, Compare>& lhs, const map<Key, T, Compare>& rhs)
    {
        return lhs == rhs;
    }

    template <class Key, class T, class Compare>
    bool operator<(const map<Key, T, Compare>& lhs, const map<Key, T, Compare>& rhs)
    {
        return lhs < rhs;
    }

    template <class Key, class T, class Compare>
    bool operator!=(const map<Key, T, Compare>& lhs, const map<Key, T, Compare>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class Key, class T, class Compare>
    bool operator>(const map<Key, T, Compare>& lhs, const map<Key, T, Compare>& rhs)
    {
        return rhs < lhs;
    }

    template <class Key, class T, class Compare>
    bool operator<=(const map<Key, T, Compare>& lhs, const map<Key, T, Compare>& rhs)
    {
        return !(rhs < lhs);
    }

    template <class Key, class T, class Compare>
    bool operator>=(const map<Key, T, Compare>& lhs, const map<Key, T, Compare>& rhs)
    {
        return !(lhs < rhs);
    }

    template <class Key, class T, class Compare>
    void swap(map<Key, T, Compare>& lhs, map<Key, T, Compare>& rhs) noexcept
    {
        lhs.swap(rhs);
    }
}

#endif //MYTINYSTL_MAP_H
