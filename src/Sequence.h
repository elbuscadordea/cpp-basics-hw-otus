//
// Created by elbus on 2026-11-03.
//
#pragma once
#include <cstddef>

namespace containers {
    /**
     * The default capacity of a sequence when it is created.
     */
    inline size_t SEQUENCE_INITIAL_CAPACITY = 5;
    /**
     * The coefficient to calculate the new capacity when a sequence is full.
     * Example: new_capacity = current_capacity * SEQUENCE_EXTENSION_COEF.
     */
    inline float CAPACITY_EXTENSION_COEF = 1.5;

    /**
     * @brief Interface class for sequential data structures.
     *
     * This interface provides a standard set of methods that all
     * sequential data structures must implement.
     */
    template<typename T>
    class ISequential {
    protected:
        ~ISequential() = default;

    public:

        /**
         * @brief Adds an element to the end of the sequence.
         *
         * @param value The element to add.
         */
        virtual void push_back(T value) = 0;

        /**
         * @brief Inserts an element at a specified position in the sequence.
         *
         * @param pos The position at which to insert the element.
         * @param value The element to insert.
         */
        virtual void insert(size_t pos, T value) = 0;

        /**
         * @brief Removes an element from the sequence at a specified position.
         *
         * @param pos The position of the element to remove.
         */
        virtual void erase(size_t pos) = 0;

        /**
         * @brief Returns the number of elements in the sequence.
         *
         * @return size_t The number of elements in the sequence.
         */
        virtual size_t size() const = 0;

        /**
         * @brief Retrieves an element at a specified position.
         *
         * @param index The position of the element to retrieve.
         * @return T The element at the specified position.
         */
        virtual T at(size_t index) const = 0;

        /**
         * @brief Gets a reference to an element at a specified position.
         *
         * @param pos The position of the element to get.
         * @return T& Reference to the element at the specified position.
         */
        virtual T& operator[](size_t pos) const = 0;
    };


    /**
     * @brief A template class representing a dynamic sequence of elements.
     *
     * This class implements an interface for a sequence, providing
     * methods to add, insert, remove, and access elements in the sequence.
     */
    template<typename T>
    class Sequence : public ISequential<T> {
    public:
        /**
         * @brief Constructs an empty sequence with a default capacity.
         */
        Sequence();

        /**
         * @brief Destructs the sequence and frees any allocated resources.
         */
        virtual ~Sequence();

        /**
         * @brief Adds an element to the end of the sequence.
         *
         * If the current capacity is not enough, it will be reallocated
         * with a new capacity calculated using the CAPACITY_EXTENSION_COEF.
         *
         * @param value The element to add.
         */
        void push_back(T value) override;

        /**
         * @brief Inserts an element at a specified position in the sequence.
         *
         * If the current capacity is not enough, it will be reallocated
         * with a new capacity calculated using the CAPACITY_EXTENSION_COEF.
         *
         * @param pos The position at which to insert the element.
         * @param value The element to insert.
         */
        void insert(size_t pos, T value) override;

        /**
         * @brief Removes an element from the sequence at a specified position.
         *
         * @param pos The position of the element to remove.
         */
        void erase(size_t pos) override;

        /**
         * @brief Retrieves an element at a specified position.
         *
         * @param pos The position of the element to retrieve.
         * @return T The element at the specified position.
         */
        T at(size_t pos) const override;

        /**
         * @brief Gets a reference to an element at a specified position.
         *
         * @param pos The position of the element to get.
         * @return T& Reference to the element at the specified position.
         */
        T& operator[](size_t pos) const override;

        /**
         * @brief Returns the number of elements in the sequence.
         *
         * @return size_t The number of elements in the sequence.
         */
        size_t size() const override;

    private:
        T *data_ = nullptr;         /**< Pointer to the array holding the sequence's elements. */
        std::size_t size_ = 0;      /**< Number of elements currently stored in the sequence. */
        std::size_t capacity_ = 0;  /**< Maximum number of elements that can be stored without reallocating memory. */

        /**
         * @brief Reallocates the internal array to increase its capacity.
         *
         * The new capacity is calculated by multiplying the current
         * capacity with CAPACITY_EXTENSION_COEF, then allocating a new
         * array and copying the existing elements to it.
         */
        void reallocate_memory();
    };


    // Implementation of the Sequence Class Members.
    template<typename T>
    Sequence<T>::Sequence() {
        capacity_ = SEQUENCE_INITIAL_CAPACITY;
        size_ = 0;
        data_ = new T[capacity_];
    }

    template<typename T>
    Sequence<T>::~Sequence() {
        delete[] data_;
        capacity_ = 0;
        size_ = 0;
    }

    template <typename T>
    void Sequence<T>::reallocate_memory() {
        // Recreate a new data_ in heap with considered capacity.
        const size_t new_capacity = capacity_ * 2;
        T* new_region = new T[new_capacity];
        capacity_ = new_capacity;
        for (size_t i = 0; i < size_; i++) {
            new_region[i] = data_[i];
        }
        delete[] data_;
        data_ = new_region;
    }

    template<typename T>
    void Sequence<T>::push_back(T value) {
        if (capacity_ <= size_) {
            reallocate_memory();
        }
        data_[size_] = value;
        size_++;
    }

    template<typename T>
    void Sequence<T>::insert(size_t pos, T value) {
        if (pos >= size_) {
            throw std::out_of_range("Sequence<T>::insert(size_t pos, T value): index out of range.");
        }

        if (size_ >= capacity_) {
            // Redefine new region of memory for data.
            reallocate_memory();
        }

        // Shift values to the right from pos.
        size_++;
        for (size_t i = size_ - 1; i > pos; i--) {
            data_[i] = data_[i - 1];
        }
        data_[pos] = value;
    }

    template<typename T>
    void Sequence<T>::erase(const size_t pos) {
        if (pos >= size_) {
            throw std::out_of_range("Sequence<T>::erase(size_t index): index out of range.");
        }


        if (pos < size_ - 2) {
            for (size_t i = pos; i < size_ - 1; i++) {
                data_[i] = data_[i + 1];
            }
        }
        size_--;
    }

    template<typename T>
    T Sequence<T>::at(size_t pos) const {
        if (pos >= size_) {
            throw std::out_of_range("Sequence<T>::at(size_t index): index out of range.");
        }
        return data_[pos];
    }

    template<typename T>
    T & Sequence<T>::operator[](size_t pos) const {
        return data_[pos];
    }

    template<typename T>
    size_t Sequence<T>::size() const {
        return size_;
    }
}


