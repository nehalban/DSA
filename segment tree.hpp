#pragma once

#include <algorithm>
#include <stdexcept>
#include <vector>

class SegTree {
private:
    std::vector<int> seg;
    int n = 0;

    static int lchild(int k) { return 2 * k + 1; }
    static int rchild(int k) { return 2 * k + 2; }
    static int parent(int k) { return (k - 1) / 2; }

    void build_helper(const std::vector<int>& arr, int index, int tl, int tr) {
        if (tl == tr) {
            seg[index] = arr[tl];
            return;
        }

        int mid = tl + (tr - tl) / 2;
        build_helper(arr, lchild(index), tl, mid);
        build_helper(arr, rchild(index), mid + 1, tr);
        seg[index] = std::max(seg[lchild(index)], seg[rchild(index)]);
    }

    int query_helper(int left, int right, int index, int tl, int tr) const {
        if (left == tl && right == tr) return seg[index];

        int mid = tl + (tr - tl) / 2;
        if (right <= mid) return query_helper(left, right, lchild(index), tl, mid);
        if (left > mid) return query_helper(left, right, rchild(index), mid + 1, tr);

        return std::max(
            query_helper(left, mid, lchild(index), tl, mid),
            query_helper(mid + 1, right, rchild(index), mid + 1, tr)
        );
    }

public:
    SegTree() = default;

    explicit SegTree(const std::vector<int>& arr) {
        build(arr);
    }

    void build(const std::vector<int>& arr) {
        n = static_cast<int>(arr.size());
        seg.assign(4 * std::max(1, n), 0);
        if (n > 0) build_helper(arr, 0, 0, n - 1);
    }

    int size() const {
        return n;
    }

    bool empty() const {
        return n == 0;
    }

    int query(int left, int right) const {
        if (n == 0) throw std::out_of_range("Segment tree is empty");
        if (left < 0 || right < left || right >= n) {
            throw std::out_of_range("Segment tree query range out of bounds");
        }
        return query_helper(left, right, 0, 0, n - 1);
    }

    void update(int index, int updated_val) {
        if (n == 0) throw std::out_of_range("Segment tree is empty");
        if (index < 0 || index >= n) {
            throw std::out_of_range("Segment tree update index out of bounds");
        }

        int i = 0;
        int left = 0;
        int right = n - 1;
        while (left != right) {
            int mid = left + (right - left) / 2;
            if (index > mid) {
                i = rchild(i);
                left = mid + 1;
            } else {
                i = lchild(i);
                right = mid;
            }
        }

        seg[i] = updated_val;
        while (i > 0) {
            i = parent(i);
            seg[i] = std::max(seg[lchild(i)], seg[rchild(i)]);
        }
    }
};
