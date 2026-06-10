#pragma once

#include <algorithm>
#include <functional>
#include <stdexcept>
#include <vector>

struct Heap {
    int size = 0;
    std::vector<int> pq;
    bool (*comp)(int, int) = min_comp;

    static bool min_comp(int a, int b) {
        return a < b;
    }

    static bool max_comp(int a, int b) {
        return a > b;
    }

    Heap(bool (*comparison)(int, int) = min_comp) : comp(comparison) {}

    Heap(const std::vector<int>& values, bool (*comparison)(int, int) = min_comp)
        : size(static_cast<int>(values.size())), pq(values), comp(comparison) {
        buildheap();
    }

    bool empty() const {
        return size == 0;
    }

    int len() const {
        return size;
    }

    int top() const {
        if (empty()) throw std::out_of_range("Heap is empty");
        return pq[0];
    }

    void heapify_up(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (comp(pq[p], pq[i])) break;
            std::swap(pq[p], pq[i]);
            i = p;
        }
    }

    void heapify_down(int i) {
        while (2 * i + 1 < size) {
            int best = 2 * i + 1;
            int right = 2 * i + 2;
            if (right < size && comp(pq[right], pq[best])) best = right;

            if (comp(pq[i], pq[best])) break;
            std::swap(pq[i], pq[best]);
            i = best;
        }
    }

    void buildheap() {
        size = static_cast<int>(pq.size());
        for (int i = size / 2 - 1; i >= 0; --i) {
            heapify_down(i);
        }
    }

    void push(int value) {
        pq.push_back(value);
        size = static_cast<int>(pq.size());
        heapify_up(size - 1);
    }

    int pop() {
        if (empty()) throw std::out_of_range("Heap is empty");

        int value = pq[0];
        pq[0] = pq.back();
        pq.pop_back();
        size = static_cast<int>(pq.size());
        if (!empty()) heapify_down(0);
        return value;
    }
};
