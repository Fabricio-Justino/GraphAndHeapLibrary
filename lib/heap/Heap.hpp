//
// Created by Fabricio on 02/12/2023.
//

#ifndef GRAPHALGORITHM_HEAP_HPP
#define GRAPHALGORITHM_HEAP_HPP

#include <iostream>
#include <vector>

template <class T>
class Heap {
protected:
    std::vector<T> heap;
    size_t size;
    Heap() : size(0){}

    /**
     * @brief Swaps the current element with its child at the left or right, only if the child has higher priority.
     *
     * This method is responsible for moving the current element down the heap (sinking) if the child has a higher priority.
     *
     * @param childIndex The index of the next element to be swapped if its parent.
     *
     * @note The time complexity of this operation is O(log n), where n is the number of elements in the heap.
     */
    virtual void sink(int childIndex) = 0;

    /**
    * @brief Swaps the current element with its parent, only if the parent has higher priority.
    *
    * This method is responsible for moving the current element up the heap (swimming) if the parent has a higher priority.
    *
    * @param parentIndex The index of the parent element to be swapped with the current element.
    *
    * @note The time complexity of this operation is O(log n), where n is the number of elements in the heap.
    */
    virtual void swim(int parentIndex) = 0;



    /**
     * @brief Swap the value of v1 and v2
     *
     * @param v1 The index for the first value in heap vector
     * @param v2 The index for the second value in heap vector
     */
    void exchange(int v1, int v2);

public:
    /**
      * @brief Adds an element to the priority queue of the heap.
      *
      * This method inserts an element in the order of its priority in the heap.
      *
      * @note The time complexity of this operation is O(log n), where n is the number of elements in the heap.
      * @param value The data to be added to the heap.
      */
    void add(const T &value);

    /**
      * @brief Checks if the heap is empty.
      *
      * @return True if there is at least one element in the heap, false otherwise.
      */
    bool isEmpty();

    /**
      * @brief Gets the number of elements stored in the heap.
      *
      * This method returns the current count of elements in the heap.
      *
      * @return The number of elements stored in the heap.
      */
    size_t getSize();

    /**
     * @brief Retrieves and removes the element with the highest priority.
     *
     * This method returns a reference to the element with the highest priority in the heap.
     * The element is also removed from the heap.
     *
     * @note The time complexity of this operation is O(log n), where n is the number of elements in the heap.
     * @return A read/write reference to the element with the highest priority.
     */
    T& pool();

    /**
     * @brief Retrieves, without removing, the element with the highest priority.
     *
     * This method returns a read-only reference to the element with the highest priority in the heap.
     * The element remains in the heap.
     *
     * @return Read-only reference to the element with the highest priority.
     */
    const T& peek() const;

    /**
     * @brief Erases all elements in the heap.
     *
     * This method removes all elements from the heap, resulting in an empty heap.
     */
    void clear();


    friend std::ostream &operator<<(std::ostream &os, const Heap &heaps) {
        os << "{";

        for (int i = 0; i < heaps.size; i++)
            os << heaps.heap[i] << ((i != heaps.size-1) ? ", " : "");
        os << "}" << std::endl;

        return os;
    }
};

template<class T>
size_t Heap<T>::getSize() {
    return this->size;
}

template<class T>
void Heap<T>::clear() {
    this->heap.clear();
    this->size = 0;
}

template<class T>
const T& Heap<T>::peek() const {
    if (this->size == 0) throw std::exception();
    return heap[0];
}

template<class T>
void Heap<T>::exchange(int v1, int v2) {
    T aux = heap[v1];
    heap[v1] = heap[v2];
    heap[v2] = aux;
}

template<class T>
T& Heap<T>::pool() {
    if (this->size <= 0) throw std::exception();

    this->exchange(0, size - 1);

    T &result = *(this->heap.end() - 1);

    heap.erase((this->heap.end() - 1));
    size--;
    if (this->size > 1) sink(0);
    return result;
}

template<class T>
bool Heap<T>::isEmpty() {
    return size <= 0;
}

template<class T>
void Heap<T>::add(const T &value) {
    heap.push_back(value);
    if (++size > 1) swim(size - 1);
}

#endif //GRAPHALGORITHM_HEAP_HPP
