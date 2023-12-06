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
    virtual void sink(int childIndex) = 0;
    virtual void swim(int childIndex) = 0;
    void exchange(int v1, int v2);

public:
    void add(const T &value);
    bool isEmpty();
    size_t getSize();
    T pool();
    T peek();
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
T Heap<T>::peek() {
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
T Heap<T>::pool() {
    if (this->size <= 0) throw std::exception();

    this->exchange(0, size - 1);

    T result = *(this->heap.end() - 1);

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
