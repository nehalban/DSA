#pragma once

#include <functional>
#include <stdexcept>
#include <utility>
#include <vector>
#include <algorithm>

template<typename K, typename V>
struct HashMap {
    int N;
    std::vector<std::vector<std::pair<K, V>>> HashTable;

private:
    int elements = 0;

    int bucket_index(const K& key) const {
        return static_cast<int>(std::hash<K>{}(key) % N);
    }

    void rehash_if_needed() {
        if (N == 0 || elements <= N * 2) return;

        std::vector<std::vector<std::pair<K, V>>> old_table = std::move(HashTable);
        N *= 2;
        HashTable.assign(N, {});
        elements = 0;
        for (const auto& bucket : old_table) {
            for (const auto& entry : bucket) {
                insert(entry.first, entry.second);
            }
        }
    }

public:
    explicit HashMap(int n = 10) : N(std::max(1, n)), HashTable(N) {}

    int hash(const K& key) const {
        return bucket_index(key);
    }

    int size() const {
        return elements;
    }

    bool empty() const {
        return elements == 0;
    }

    bool contains(const K& key) const {
        const auto& bucket = HashTable[bucket_index(key)];
        for (const auto& entry : bucket) {
            if (entry.first == key) return true;
        }
        return false;
    }

    V* find(const K& key) {
        auto& bucket = HashTable[bucket_index(key)];
        for (auto& entry : bucket) {
            if (entry.first == key) return &entry.second;
        }
        return nullptr;
    }

    const V* find(const K& key) const {
        const auto& bucket = HashTable[bucket_index(key)];
        for (const auto& entry : bucket) {
            if (entry.first == key) return &entry.second;
        }
        return nullptr;
    }

    V& get(const K& key) {
        V* value = find(key);
        if (!value) throw std::out_of_range("Key not found");
        return *value;
    }

    const V& get(const K& key) const {
        const V* value = find(key);
        if (!value) throw std::out_of_range("Key not found");
        return *value;
    }

    void insert(const K& key, const V& value) {
        auto& bucket = HashTable[bucket_index(key)];
        for (auto& entry : bucket) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }

        bucket.push_back({key, value});
        ++elements;
        rehash_if_needed();
    }

    bool erase(const K& key) {
        auto& bucket = HashTable[bucket_index(key)];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                --elements;
                return true;
            }
        }
        return false;
    }

    V& operator[](const K& key) {
        V* value = find(key);
        if (value) return *value;

        insert(key, V{});
        return *find(key);
    }
};

template<typename K, typename V>
using HashSet = HashMap<K, V>;
