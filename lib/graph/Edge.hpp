#ifndef GRAPHALGORITHM_EDGE_HPP
#define GRAPHALGORITHM_EDGE_HPP

#include <functional>
#include <string>

template <class T>
class Edge {
    T from;
    T to;
    double weight{};

public:
    Edge() = default;
    Edge(const T &from, const T &to, double weight = 1);

    T getFrom() const;
    T getTo() const;
    double getWeight() const;

    bool operator<(const Edge<T>& rhs) const;
    bool operator>(const Edge<T>& rhs) const;
    bool operator<=(const Edge<T>& rhs) const;
    bool operator>=(const Edge<T>& rhs) const;
    bool operator==(const Edge<T>& rhs) const;
    bool operator!=(const Edge<T>& rhs) const;

};

namespace std {
    template <class T>
    struct hash<Edge<T>> {
    size_t operator()(const Edge<T>& edge) const {
        size_t hashFrom = std::hash<T>()(edge.getFrom());
        size_t hashTo = std::hash<T>()(edge.getTo());
        return hashFrom ^ hashTo;
    }
};
}  // namespace std

template <class T>
Edge<T>::Edge(const T &from, const T &to, double weight) : from(from), to(to), weight(weight) {}

template <class T>
T Edge<T>::getFrom() const {
    return from;
}

template <class T>
T Edge<T>::getTo() const {
    return to;
}

template <class T>
double Edge<T>::getWeight() const {
    return weight;
}

template <class T>
bool Edge<T>::operator<(const Edge<T>& rhs) const {
    return weight < rhs.weight;
}

template <class T>
bool Edge<T>::operator>(const Edge<T>& rhs) const {
    return weight > rhs.weight;
}

template <class T>
bool Edge<T>::operator<=(const Edge<T>& rhs) const {
    return *this < rhs || *this == rhs;
}

template <class T>
bool Edge<T>::operator>=(const Edge<T>& rhs) const {
    return *this > rhs || *this == rhs;
}

template <class T>
bool Edge<T>::operator==(const Edge<T>& rhs) const {
    return from == rhs.from && to == rhs.to;
}

template <class T>
bool Edge<T>::operator!=(const Edge<T>& rhs) const {
    return !(rhs == *this);
}

#endif  // GRAPHALGORITHM_EDGE_HPP

