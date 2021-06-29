//
// Created by 谯保林 on 2021/6/21.
//

#ifndef MYTINYSTL_SET_H
#define MYTINYSTL_SET_H

#endif //MYTINYSTL_SET_H
#include "rb_tree.h"

namespace MyTinySTL
{
    template <class Key, class Compare = std::less<Key>>
    class set
    {
    public:
        typedef Key       key_type;
        typedef Key       value_type;
        typedef Compare   key_compare;
        typedef Compare   value_compare;

    private:
        typedef MyTinySTL::rb_tree<value_type, key_compare > set_type;
        set_type tree_;


    public:
        typedef typename set_type::tree_type              tree_type;
        typedef typename set_type::pointer                pointer;
        typedef typename set_type::const_pointer          const_pointer;
        typedef typename set_type::reference              reference;
        typedef typename set_type::const_reference        const_reference;
        typedef typename set_type::iterator               iterator;
        typedef typename set_type::const_iterator         const_iterator;
        typedef typename set_type::reverse_iterator       reverse_iterator;
        typedef typename set_type::const_reverse_iterator const_reverse_iterator;
        typedef typename set_type::size_type              size_type;
        typedef typename set_type::difference_type        difference_type;
        typedef typename set_type::allocator_type         allocator_type;

    public:
        set() = default;
        set(const set& rhs) : tree_(rhs.tree_) {}
        set(set&& rhs) : tree_(MyTinySTL::move(rhs.tree_)) {}

        template <class Iter>
        set(Iter first, Iter last) :tree_() {
            tree_.insert_unique(first, last);
        }

        set(std::initializer_list<value_type> ilist) : tree_() {
            tree_.insert_unique(ilist.begin(), ilist.end());
        }

        set& operator=(const set& rhs) {
            tree_ = rhs.tree_;
            return *this;
        }

        set& operator=(set&& rhs) {
            tree_ = MyTinySTL::move(rhs.tree_);
            return *this;
        }

        set& operator=(std::initializer_list<value_type> ilist) {
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

        template <class ...Args>
        std::pair<iterator, bool> emplace(Args&& ...args) {
            return tree_.emplace_unique(MyTinySTL::forward<Args>(args)...);
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

    public:
        friend bool operator==(const set& lhs, const set& rhs) { return lhs.tree_ == rhs.tree_; }
        friend bool operator< (const set& lhs, const set& rhs) { return lhs.tree_ <  rhs.tree_; }
    };

    template <class Key, class Compare>
    bool operator==(const set<Key, Compare>& lhs, const set<Key, Compare>& rhs)
    {
        return lhs == rhs;
    }

    template <class Key, class Compare>
    bool operator<(const set<Key, Compare>& lhs, const set<Key, Compare>& rhs)
    {
        return lhs < rhs;
    }

    template <class Key, class Compare>
    bool operator!=(const set<Key, Compare>& lhs, const set<Key, Compare>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class Key, class Compare>
    bool operator>(const set<Key, Compare>& lhs, const set<Key, Compare>& rhs)
    {
        return rhs < lhs;
    }

    template <class Key, class Compare>
    bool operator<=(const set<Key, Compare>& lhs, const set<Key, Compare>& rhs)
    {
        return !(rhs < lhs);
    }

    template <class Key, class Compare>
    bool operator>=(const set<Key, Compare>& lhs, const set<Key, Compare>& rhs)
    {
        return !(lhs < rhs);
    }

    template <class Key, class Compare>
    void swap(set<Key, Compare>& lhs, set<Key, Compare>& rhs) noexcept
    {
        lhs.swap(rhs);
    }
}