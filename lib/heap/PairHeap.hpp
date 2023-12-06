//
// Created by Fabricio on 02/12/2023.
//

#ifndef GRAPHALGORITHM_PAIRHEAP_HPP
#define GRAPHALGORITHM_PAIRHEAP_HPP

#include "MinPriorityQueue.hpp"
#include "MaxPriorityQueue.hpp"

template <class T, class CMP = int>
class PairHeap {
private:
    class Pair {
    public:
        CMP comp;
        T data;
        Pair(T data, CMP comp): data(data), comp(comp){}
        Pair() = default;


        bool operator==(const Pair &other) const {
            return comp == other.comp;
        }

        bool operator<(const Pair &rhs) const {
            return comp < rhs.comp;
        }

        bool operator>(const Pair &rhs) const {
            return rhs < *this;
        }

        bool operator<=(const Pair &rhs) const {
            return !(rhs < *this);
        }

        bool operator>=(const Pair &rhs) const {
            return !(*this < rhs);
        }


    };
    Heap<PairHeap::Pair> *heap;

public:
    explicit PairHeap(): heap(nullptr){}
    ~PairHeap() {
        if (heap != nullptr)
            delete heap;
    }
    void add(T data, CMP weight);
    size_t size();
    bool isEmpty();
    void clear();
    T pool();
    T peek();
    static PairHeap<T, CMP> &minPairHeap(PairHeap<T, CMP> &pairHeap);
    static PairHeap<T, CMP> &maxPairHeap(PairHeap<T, CMP> &pairHeap);
    CMP peekWeight() const;
};

template<class T, class CMP>
CMP PairHeap<T, CMP>::peekWeight() const {
    return this->heap->peek().comp;
}

template<class T, class COMP_VALUE>
void PairHeap<T, COMP_VALUE>::clear() {
    this->heap->clear();
}

template<class T, class COMP_VALUE>
size_t PairHeap<T, COMP_VALUE>::size() {
    return this->heap->getSize();
}

template<class T, class COMP_VALUE>
PairHeap<T, COMP_VALUE> &PairHeap<T, COMP_VALUE>::maxPairHeap(PairHeap<T, COMP_VALUE> &pairHeap) {
    pairHeap.heap = new MaxPriorityQueue<Pair>;
    return pairHeap;
}

template<class T, class COMP_VALUE>
PairHeap<T, COMP_VALUE> &PairHeap<T, COMP_VALUE>::minPairHeap(PairHeap<T, COMP_VALUE> &pairHeap) {
    pairHeap.heap = new MinPriorityQueue<Pair>;
    return pairHeap;
}

template<class T, class COMP_VALUE>
T PairHeap<T, COMP_VALUE>::peek() {
    return this->heap->peek();
}

template<class T, class COMP_VALUE>
bool PairHeap<T, COMP_VALUE>::isEmpty() {
    return this->heap->isEmpty();
}

template<class T, class COMP_VALUE>
T PairHeap<T, COMP_VALUE>::pool() {
    return this->heap->pool().data;
}

template<class T, class COMP_VALUE>
void PairHeap<T, COMP_VALUE>::add(T data, COMP_VALUE weight) {
    Pair p(data, weight);
    this->heap->add(p);
}

#endif //GRAPHALGORITHM_PAIRHEAP_HPP
