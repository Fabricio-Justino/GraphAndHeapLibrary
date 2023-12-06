//
// Created by Fabricio on 02/12/2023.
//

#ifndef GRAPHALGORITHM_MAXPRIORITYQUEUE_HPP
#define GRAPHALGORITHM_MAXPRIORITYQUEUE_HPP

#include "Heap.hpp"

template <class T>
class MaxPriorityQueue : public Heap<T>{
protected:
    void sink(int parentIndex) override;
    void swim(int childIndex) override;

public:
    MaxPriorityQueue() = default;
};

template<class T>
void MaxPriorityQueue<T>::swim(int childIndex) {
    if (childIndex == 0) return;

    std::vector<T> &heap = this->heap;
    int PARENT_POS = childIndex / 2;
    PARENT_POS -= (childIndex % 2 == 0) ? 1 : 0;

    while (this->heap[childIndex] > heap[PARENT_POS] && childIndex != 0){
        this->exchange(childIndex, PARENT_POS);
        childIndex = PARENT_POS;
        PARENT_POS = childIndex / 2;
        PARENT_POS -= (childIndex % 2 == 0) ? 1 : 0;
    }

}

template<class T>
void MaxPriorityQueue<T>::sink(int parentIndex) {
    int LEFT = std::min(parentIndex * 2 + 1, (int) this->size - 1);
    int RIGHT = std::min(2 * (parentIndex + 1), (int) this->size - 1);

    std::vector<T> &heap = this->heap;

    while (heap[parentIndex] < heap[LEFT] || heap[parentIndex] < heap[RIGHT]) {
        const int GRATTER_OF = (heap[LEFT] >= heap[RIGHT]) ? LEFT : RIGHT;

        this->exchange(parentIndex, GRATTER_OF);
        parentIndex = GRATTER_OF;
        LEFT = std::min(parentIndex * 2 + 1, (int) this->size - 1);
        RIGHT = std::min(2 * (parentIndex + 1), (int) this->size - 1);
    }

}

#endif //GRAPHALGORITHM_MAXPRIORITYQUEUE_HPP
