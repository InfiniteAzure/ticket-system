#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>

#include <climits>
#include <cstddef>

namespace sjtu {
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
    template<typename T>
    class vector {
    public:
        T *start;
        int used_size;
        int allocated_size;
        /**
         * TODO
         * a type for actions of the elements of a vector, and you should write
         *   a class named const_iterator with same interfaces.
         */
        /**
         * you can see RandomAccessIterator at CppReference for help.
         */
        class const_iterator;

        class iterator {
            // The following code is written for the C++ type_traits library.
            // Type traits is a C++ feature for describing certain properties of a type.
            // For instance, for an iterator, iterator::value_type is the type that the
            // iterator points to.
            // STL algorithms and containers may use these type_traits (e.g. the following
            // typedef) to work properly. In particular, without the following code,
            // @code{std::sort(iter, iter1);} would not compile.
            // See these websites for more information:
            // https://en.cppreference.com/w/cpp/header/type_traits
            // About value_type: https://blog.csdn.net/u014299153/article/details/72419713
            // About iterator_category: https://en.cppreference.com/w/cpp/iterator
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T *;
            using reference = T &;
            using iterator_category = std::output_iterator_tag;

        private:
            /**
             * TODO add data members
             *   just add whatever you want.
             */

        public:

            vector* father;
            int position;

            iterator(vector *a, int pos) {
                father = a;
                position = pos;
            }

            /**
             * return a new iterator which pointer n-next elements
             * as well as operator-
             */
            iterator operator+(const int &n) const {
                //TODO
                iterator ans(father, position + n);
                return ans;
            }

            iterator operator-(const int &n) const {
                //TODO
                iterator ans(father, position - n);
                return ans;
            }

            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const iterator &rhs) const {
                if (father != rhs.starter) {
                    throw (invalid_iterator());
                }
                return position - rhs.position;
            }

            iterator &operator+=(const int &n) {
                position += n;
                return *this;
                //TODO
            }

            iterator &operator-=(const int &n) {
                position -= n;
                return *this;
                //TODO
            }

            /**
             * TODO iter++
             */
            iterator operator++(int) {
                iterator ans(*this);
                ans.position++;
                return ans;
            }

            /**
             * TODO ++iter
             */
            iterator &operator++() {
                position++;
                return *this;
            }

            /**
             * TODO iter--
             */
            iterator operator--(int) {
                iterator ans(*this);
                ans.position--;
                return ans;
            }

            /**
             * TODO --iter
             */
            iterator &operator--() {
                position--;
                return *this;
            }

            /**
             * TODO *it
             */
            T &operator*() const {
                return father->start[position];
            }

            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator &rhs) const {
                return (father == rhs.father && position == rhs.position);
            }

            bool operator==(const const_iterator &rhs) const {
                return (father == rhs.father && position == rhs.position);
            }

            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return !(*this == rhs);
            }

            bool operator!=(const const_iterator &rhs) const {
                return !(*this == rhs);
            }
        };

        /**
         * TODO
         * has same function as iterator, just for a const object.
         */
        class const_iterator {
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T *;
            using reference = T &;
            using iterator_category = std::output_iterator_tag;


        private:
            /*TODO*/


        public:
            const vector *father;
            int position;

            const_iterator(const vector *a, int pos) {
                father = a;
                position = pos;
            }

            /**
             * return a new iterator which pointer n-next elements
             * as well as operator-
             */
            const_iterator operator+(const int &n) const {
                //TODO
                iterator ans(father, position + n);
                return ans;
            }

            const_iterator operator-(const int &n) const {
                //TODO
                iterator ans(father, position - n);
                return ans;
            }

            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const const_iterator &rhs) const {
                if (father != rhs.father) {
                    throw (invalid_iterator());
                }
                return position - rhs.position;
            }

            const_iterator &operator+=(const int &n) {
                position += n;
                return *this;
                //TODO
            }

            const_iterator &operator-=(const int &n) {
                position -= n;
                return *this;
                //TODO
            }

            /**
             * TODO iter++
             */
            const_iterator operator++(int) {
                iterator ans(*this);
                ans.position++;
                return ans;
            }

            /**
             * TODO ++iter
             */
            const_iterator &operator++() {
                position++;
                return *this;
            }

            /**
             * TODO iter--
             */
            const_iterator operator--(int) {
                iterator ans(*this);
                ans.position--;
                return ans;
            }

            /**
             * TODO --iter
             */
            const_iterator &operator--() {
                position--;
                return *this;
            }

            /**
             * TODO *it
             */
            T &operator*() const {
                return father->start[position];
            }

            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator &rhs) const {
                return (father == rhs.father && position == rhs.position);
            }

            bool operator==(const const_iterator &rhs) const {
                return (father == rhs.father && position == rhs.position);
            }

            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return !(*this == rhs);
            }

            bool operator!=(const const_iterator &rhs) const {
                return !(*this == rhs);
            }

        };


        /**
         * TODO Constructs
         * At least two: default constructor, copy constructor
         */
        vector() {
            start = (T *) malloc(100 * sizeof(T));
            allocated_size = 100;
            used_size = 0;
        }

        vector(const vector &other) {
            start = (T *) malloc(other.allocated_size * sizeof(T));
            for (int i = 0; i < other.used_size; ++i) {
                new(start + i) T(other.start[i]);
            }
            allocated_size = other.allocated_size;
            used_size = other.used_size;
        }

        /**
         * TODO Destructor
         */
        ~vector() {
            for (int i = 0; i < used_size; ++i) {
                start[i].~T();
            }
            free(start);
        }

        /**
         * TODO Assignment operator
         */
        vector &operator=(const vector &other) {
            if (other.start == start) {
                return *this;
            }
            for (int i = 0; i < used_size; ++i) {
                start[i].~T();
            }
            free(start);
            start = (T *) malloc(other.allocated_size * sizeof(T));
            for (int i = 0; i < used_size; ++i) {
                new(start + i) T(other.start[i]);
            }
            allocated_size = other.allocated_size;
            used_size = other.used_size;
            return *this;
        }

        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         */
        T &at(const size_t &pos) {
            if (pos < 0 || pos >= used_size) {
                throw (index_out_of_bound());
            }
            return (start[pos]);
        }

        const T &at(const size_t &pos) const {
            if (pos >= used_size || pos < 0) {
                throw (index_out_of_bound());
            }
            return start[pos];
        }

        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         * !!! Pay attentions
         *   In STL this operator does not check the boundary but I want you to do.
         */
        T &operator[](const size_t &pos) {
            return this->at(pos);
        }

        const T &operator[](const size_t &pos) const {
            return this->at(pos);
        }

        /**
         * access the first element.
         * throw container_is_empty if size == 0
         */
        const T &front() const {
            if (used_size == 0) {
                throw (container_is_empty());
            }
            return this->at(0);
        }

        /**
         * access the last element.
         * throw container_is_empty if size == 0
         */
        const T &back() const {
            if (used_size == 0) {
                throw (container_is_empty());
            }
            return this->at(used_size - 1);
        }

        /**
         * returns an iterator to the beginning.
         */
        iterator begin() {
            iterator ans(this, 0);
            return ans;
        }

        const_iterator cbegin() const {
            const_iterator ans(this, 0);
            return ans;
        }

        /**
         * returns an iterator to the end.
         */
        iterator end() {
            iterator ans(this, used_size);
            return ans;
        }

        const_iterator cend() const {
            const_iterator ans(this, used_size);
            return ans;
        }

        /**
         * checks whether the container is empty
         */
        bool empty() const {
            return (used_size == 0);
        }

        /**
         * returns the number of elements
         */
        size_t size() const {
            return used_size;
        }

        /**
         * clears the contents
         */
        void clear() {
            for (int i = 0; i < used_size; ++i) {
                start[i].~T();
            }
            used_size = 0;
        }

        void double_space() {
            T *del = start;
            start = (T *) malloc(allocated_size * 2 * sizeof(T));
            allocated_size *= 2;
            for (int i = 0; i < used_size; ++i) {
                new(start + i) T(del[i]);
            }
            for(int i = 0;i < used_size;++i) {
                del[i].~T();
            }
            free(del);
        }

        /**
         * inserts value before pos
         * returns an iterator pointing to the inserted value.
         */
        iterator insert(iterator pos, const T &value) {
            if (used_size == allocated_size) {
                double_space();
            }
            for (int i = used_size; i > pos.position; --i) {
                start[i] = start[i - 1];
            }
            start[pos.position] = value;
            iterator ans(this, pos.position);
            used_size++;
            return ans;
        }

        /**
         * inserts value at index ind.
         * after inserting, this->at(ind) == value
         * returns an iterator pointing to the inserted value.
         * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
         */
        iterator insert(const size_t &ind, const T &value) {
            if (ind > used_size) {
                throw (index_out_of_bound());
            }
            if (used_size == allocated_size) {
                double_space();
            }
            for (int i = used_size; i != ind; --i) {
                start[i] = start[i - 1];
            }
            start[ind] = value;
            used_size++;
            iterator ans(this, ind);
            return ans;
        }

        /**
         * removes the element at pos.
         * return an iterator pointing to the following element.
         * If the iterator pos refers the last element, the end() iterator is returned.
         */
        iterator erase(iterator pos) {
            start[pos.position].~T();
            for (int i = pos.position; i < used_size - 1; ++i) {
                start[i] = start[i + 1];
            }
            used_size--;
            iterator ans(this, pos.position);
            return ans;
        }

        /**
         * removes the element with index ind.
         * return an iterator pointing to the following element.
         * throw index_out_of_bound if ind >= size
         */
        iterator erase(const size_t &ind) {
            if (ind >= used_size) {
                throw (index_out_of_bound());
            }
            start[ind].~T();
            for (int i = ind; i < used_size; ++i) {
                start[i] = start[i + 1];
            }
            iterator ans(start, ind);
            return ans;
        }

        /**
         * adds an element to the end.
         */
        void push_back(const T &value) {
            if (used_size == allocated_size) {
                double_space();
            }
            new(start + used_size) T(value);
            used_size++;
        }

        /**
         * remove the last element from the end.
         * throw container_is_empty if size() == 0
         */
        void pop_back() {
            if (used_size == 0) {
                throw (container_is_empty());
            }
            start[used_size - 1].~T();
            used_size--;
        }
    };
}

#endif
