//
// Created by Fabricio on 02/12/2023.
//

#ifndef GRAPHALGORITHM_PAIRHEAP_HPP
#define GRAPHALGORITHM_PAIRHEAP_HPP

#include "MinPriorityQueue.hpp"
#include "MaxPriorityQueue.hpp"

/**
 * An heap that associates two elements.
 *
 * @tparam T    The data to be stored in the heap.
 * @tparam CMP  The value used to compare two elements.
 */
template <class T, class CMP = int>
class PairHeap {
private:
    class Pair {
    public:
        CMP comp;
        T data;
        Pair(T data, CMP comp): data(data), comp(comp){}
        Pair() = default;

        /**
         * @brief Comparison operators for Pair objects.
         */
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
    /**
     * @brief Default constructor for PairHeap.
     */
    explicit PairHeap(): heap(nullptr){}

    /**
     * @brief Destructor for PairHeap.
     */
    ~PairHeap() {
        if (heap != nullptr)
            delete heap;
    }

    /**
     * @brief Adds a new element with a given weight to the PairHeap.
     *
     * @param data The data element to be added.
     * @param weight The weight (priority) associated with the data.
     */
    void add(T data, CMP weight);

    /**
     * @brief Gets the number of elements stored in the PairHeap.
     *
     * @return The number of elements stored in the PairHeap.
     */
    size_t size() const;

    /**
     * @brief Checks if the PairHeap is empty.
     *
     * @return True if there is at least one element in the PairHeap, false otherwise.
     */
    bool isEmpty() const ;

    /**
     * @brief Clears all elements from the PairHeap.
     */
    void clear();

    /**
     * @brief Retrieves and removes the element with the highest priority.
     *
     * @return A read/write reference to the data element with the highest priority.
     */
    T& pool();

    /**
     * @brief Retrieves, without removing, the element with the highest priority.
     *
     * @return A read-only reference to the data element with the highest priority.
     */
    const T& peek();

    /**
     * @brief Creates a PairHeap configured as a minimum heap.
     *
     * @param pairHeap The PairHeap instance to be configured.
     * @return A reference to the configured PairHeap.
     */
    static PairHeap<T, CMP> &minPairHeap(PairHeap<T, CMP> &pairHeap);

    /**
     * @brief Creates a PairHeap configured as a maximum heap.
     *
     * @param pairHeap The PairHeap instance to be configured.
     * @return A reference to the configured PairHeap.
     */
    static PairHeap<T, CMP> &maxPairHeap(PairHeap<T, CMP> &pairHeap);

    /**
     * @brief Retrieves the weight (priority) of the element with the highest priority.
     *
     * @return The weight (priority) of the element with the highest priority.
     */
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
size_t PairHeap<T, COMP_VALUE>::size() const{
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
const T& PairHeap<T, COMP_VALUE>::peek() {
    return this->heap->peek().data;
}

template<class T, class COMP_VALUE>
bool PairHeap<T, COMP_VALUE>::isEmpty() const{
    return this->heap->isEmpty();
}

template<class T, class COMP_VALUE>
T& PairHeap<T, COMP_VALUE>::pool() {
    return this->heap->pool().data;
}

template<class T, class COMP_VALUE>
void PairHeap<T, COMP_VALUE>::add(T data, COMP_VALUE weight) {
    Pair p(data, weight);
    this->heap->add(p);
}

#endif //GRAPHALGORITHM_PAIRHEAP_HPP
