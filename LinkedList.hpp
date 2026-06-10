#pragma once

#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <utility>

struct SinglyLinkedList {
    struct Node {
        int data;
        Node* next;

        Node(Node* next = nullptr) : data(0), next(next) {}
        Node(int x, Node* next = nullptr) : data(x), next(next) {}
    };

    Node* head = nullptr;

    SinglyLinkedList() = default;

    SinglyLinkedList(std::initializer_list<int> values) {
        for (int x : values) insert(x, true);
    }

    SinglyLinkedList(const SinglyLinkedList& other) {
        Node* temp = other.head;
        while (temp) {
            insert(temp->data, true);
            temp = temp->next;
        }
    }

    SinglyLinkedList& operator=(const SinglyLinkedList& other) {
        if (this == &other) return *this;
        clear();
        Node* temp = other.head;
        while (temp) {
            insert(temp->data, true);
            temp = temp->next;
        }
        return *this;
    }

    SinglyLinkedList(SinglyLinkedList&& other) noexcept : head(other.head) {
        other.head = nullptr;
    }

    SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept {
        if (this == &other) return *this;
        clear();
        head = other.head;
        other.head = nullptr;
        return *this;
    }

    Node* tail() const {
        Node* temp = head;
        while (temp && temp->next) temp = temp->next;
        return temp;
    }

    int len() const {
        int x = 0;
        Node* temp = head;
        while (temp) {
            ++x;
            temp = temp->next;
        }
        return x;
    }

    Node* insert(int data_, bool at_end = false) {
        Node* temp = new Node(data_);
        if (at_end) {
            if (!head) head = temp;
            else tail()->next = temp;
            return temp;
        }

        temp->next = head;
        head = temp;
        return temp;
    }

    Node* insert(int data_, int index) {
        if (index == 0) return insert(data_);
        if (index < 0) throw std::out_of_range("Index out of bounds: Negative index");
        if (!head) throw std::out_of_range("Index out of bounds: Empty list");

        Node* temp = head;
        for (int i = 0; i < index - 1; ++i) {
            temp = temp->next;
            if (!temp) throw std::out_of_range("Index out of bounds");
        }

        Node* added = new Node(data_, temp->next);
        temp->next = added;
        return added;
    }

    int del(bool at_end = false) {
        if (!head) throw std::out_of_range("Empty List: Nothing to delete");

        if (!head->next) {
            int data_ = head->data;
            delete head;
            head = nullptr;
            return data_;
        }

        if (at_end) {
            Node* prev = head;
            while (prev->next->next) prev = prev->next;
            int data_ = prev->next->data;
            delete prev->next;
            prev->next = nullptr;
            return data_;
        }

        Node* temp = head;
        head = head->next;
        int data_ = temp->data;
        delete temp;
        return data_;
    }

    int del(int index) {
        if (index == 0) return del(false);
        if (index < 0) throw std::out_of_range("Index out of bounds: Negative index");
        if (!head || !head->next) throw std::out_of_range("Index out of bounds");

        Node* temp = head;
        for (int i = 0; i < index - 1; ++i) {
            if (!temp->next) throw std::out_of_range("Index out of bounds");
            temp = temp->next;
        }
        if (!temp->next) throw std::out_of_range("Index out of bounds");

        Node* victim = temp->next;
        int data_ = victim->data;
        temp->next = victim->next;
        delete victim;
        return data_;
    }

    void print(char separator = ',') const {
        if (!head) {
            std::cout << "Empty List" << '\n';
            return;
        }

        const Node* temp = head;
        while (temp->next) {
            std::cout << temp->data << separator;
            temp = temp->next;
        }
        std::cout << temp->data << '\n';
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    int& operator[](const int& index) {
        if (index < 0) throw std::out_of_range("Index out of bounds: Negative index");
        if (!head) throw std::out_of_range("Index out of bounds: Empty List");

        Node* temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
            if (!temp) throw std::out_of_range("Index out of bounds");
        }
        return temp->data;
    }

    const int& operator[](const int& index) const {
        if (index < 0) throw std::out_of_range("Index out of bounds: Negative index");
        if (!head) throw std::out_of_range("Index out of bounds: Empty List");

        Node* temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
            if (!temp) throw std::out_of_range("Index out of bounds");
        }
        return temp->data;
    }

    SinglyLinkedList reversed() const {
        SinglyLinkedList list;
        Node* temp = head;
        while (temp) {
            list.insert(temp->data);
            temp = temp->next;
        }
        return list;
    }

    void reverse() {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    void recursive_reverse() {
        head = recursive_reverse_helper(head);
    }

    void concatenate(const SinglyLinkedList& list, bool inplace = true) {
        (void)inplace;
        Node* temp = list.head;
        while (temp) {
            insert(temp->data, true);
            temp = temp->next;
        }
    }

    SinglyLinkedList copy() const {
        return SinglyLinkedList(*this);
    }

    SinglyLinkedList operator+(const SinglyLinkedList& addend) const {
        SinglyLinkedList sum = copy();
        sum.concatenate(addend);
        return sum;
    }

    SinglyLinkedList operator+(const int& addend) const {
        SinglyLinkedList sum = copy();
        sum.insert(addend, true);
        return sum;
    }

    Node* middle() const {
        if (!head) throw std::out_of_range("Empty List");
        Node* slow = head;
        Node* fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    Node* merge_sort(Node* start = nullptr) {
        bool sorting_whole_list = start == nullptr;
        if (!start) start = head;
        Node* sorted = merge_sort_impl(start);
        if (sorting_whole_list) head = sorted;
        return sorted;
    }

    Node* find(int value) const {
        Node* temp = head;
        while (temp) {
            if (temp->data == value) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    bool contains(int value) const {
        return find(value) != nullptr;
    }

    bool remove(int value) {
        if (!head) return false;
        if (head->data == value) {
            del(false);
            return true;
        }

        Node* prev = head;
        while (prev->next && prev->next->data != value) prev = prev->next;
        if (!prev->next) return false;

        Node* victim = prev->next;
        prev->next = victim->next;
        delete victim;
        return true;
    }

    void reverse(int index_begin, int index_end) {
        if (index_begin < 0 || index_end < index_begin) {
            throw std::out_of_range("Invalid reverse range");
        }
        if (index_begin == index_end) return;

        Node dummy(0, head);
        Node* before = &dummy;
        for (int i = 0; i < index_begin; ++i) {
            before = before->next;
            if (!before) throw std::out_of_range("Reverse range out of bounds");
        }

        Node* range_tail = before->next;
        if (!range_tail) throw std::out_of_range("Reverse range out of bounds");
        Node* curr = range_tail->next;
        for (int i = index_begin; i < index_end; ++i) {
            if (!curr) throw std::out_of_range("Reverse range out of bounds");
            range_tail->next = curr->next;
            curr->next = before->next;
            before->next = curr;
            curr = range_tail->next;
        }
        head = dummy.next;
    }

protected:
    Node* floyd_node() const {
        Node* slow = head;
        Node* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return slow;
        }
        return nullptr;
    }

public:
    bool has_loop() const {
        return floyd_node() != nullptr;
    }

    int loop_length() const {
        Node* meeting = floyd_node();
        if (!meeting) return 0;

        int ans = 1;
        Node* temp = meeting->next;
        while (temp != meeting) {
            ++ans;
            temp = temp->next;
        }
        return ans;
    }

    Node* loop_head() const {
        Node* temp = head;
        Node* temp1 = floyd_node();
        if (!temp1) return nullptr;
        while (temp != temp1) {
            temp = temp->next;
            temp1 = temp1->next;
        }
        return temp;
    }

    ~SinglyLinkedList() {
        clear();
    }

private:
    Node* recursive_reverse_helper(Node* node) {
        if (!node || !node->next) return node;
        Node* new_head = recursive_reverse_helper(node->next);
        node->next->next = node;
        node->next = nullptr;
        return new_head;
    }

    static Node* merge(Node* a, Node* b) {
        Node dummy;
        Node* tail = &dummy;
        while (a && b) {
            if (a->data <= b->data) {
                tail->next = a;
                a = a->next;
            } else {
                tail->next = b;
                b = b->next;
            }
            tail = tail->next;
        }
        tail->next = a ? a : b;
        return dummy.next;
    }

    Node* merge_sort_impl(Node* start) {
        if (!start || !start->next) return start;

        Node* slow = start;
        Node* fast = start->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        Node* second = slow->next;
        slow->next = nullptr;
        return merge(merge_sort_impl(start), merge_sort_impl(second));
    }
};

struct SinglyLinkedList_t : public SinglyLinkedList {
    Node* tail = nullptr;

    Node* insert(int data_, bool at_end = false) {
        Node* added = SinglyLinkedList::insert(data_, at_end);
        tail = SinglyLinkedList::tail();
        return added;
    }

    int del(bool at_end = false) {
        int value = SinglyLinkedList::del(at_end);
        tail = SinglyLinkedList::tail();
        return value;
    }

    const int& operator[](const int& index) const {
        return SinglyLinkedList::operator[](index);
    }
};

struct DoublyLinkedList {
    struct Node {
        int data;
        Node* prev;
        Node* next;

        Node() : data(0), prev(nullptr), next(nullptr) {}
        explicit Node(int data) : data(data), prev(nullptr), next(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    int size = 0;

    DoublyLinkedList() = default;

    DoublyLinkedList(std::initializer_list<int> values) {
        for (int x : values) insert(x, true);
    }

    int& operator[](int index) {
        return address_at_index(index)->data;
    }

    Node* address_at_index(int index) const {
        if (!head) throw std::out_of_range("Index out of bounds: Empty List");
        if (index >= size || index < -size) {
            throw std::out_of_range("Index out of bounds: Absolute value greater than length of list");
        }

        if (index < 0) index = size + index;
        if (index <= size / 2) {
            Node* temp = head;
            while (index--) temp = temp->next;
            return temp;
        }

        Node* temp = tail;
        int from_tail = size - 1 - index;
        while (from_tail--) temp = temp->prev;
        return temp;
    }

    void print(char separator = ',') const {
        if (!head) {
            std::cout << "Empty List" << '\n';
            return;
        }

        Node* temp = head;
        while (temp->next) {
            std::cout << temp->data << separator;
            temp = temp->next;
        }
        std::cout << temp->data << '\n';
    }

    Node* insert(int data_, bool at_end = false) {
        Node* node = new Node(data_);
        ++size;
        if (!head) {
            head = tail = node;
            return node;
        }

        if (at_end) {
            node->prev = tail;
            tail->next = node;
            tail = node;
            return node;
        }

        node->next = head;
        head->prev = node;
        head = node;
        return node;
    }

    Node* insert(int data_, int index) {
        if (index == 0 || index == -size - 1) return insert(data_);
        if (index == size || index == -1) return insert(data_, true);

        if (index < 0) index = size + index + 1;
        if (index < 0 || index > size) throw std::out_of_range("Index out of bounds");

        Node* next_node = address_at_index(index);
        Node* prev_node = next_node->prev;
        Node* node = new Node(data_);
        node->prev = prev_node;
        node->next = next_node;
        prev_node->next = node;
        next_node->prev = node;
        ++size;
        return node;
    }

    int del(bool at_end = false) {
        if (!head) throw std::out_of_range("Empty List: Nothing to delete");

        Node* victim = at_end ? tail : head;
        int data = victim->data;

        if (head == tail) {
            head = tail = nullptr;
        } else if (at_end) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }

        delete victim;
        --size;
        return data;
    }

    int del(int index) {
        if (index == 0 || index == -size) return del();
        if (index == size - 1 || index == -1) return del(true);

        Node* temp = address_at_index(index);
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        int data = temp->data;
        delete temp;
        --size;
        return data;
    }

    void reverse() {
        Node* curr = head;
        while (curr) {
            std::swap(curr->next, curr->prev);
            curr = curr->prev;
        }
        std::swap(head, tail);
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

    ~DoublyLinkedList() {
        clear();
    }
};

template<typename T>
class CircularLinkedList {
public:
    CircularLinkedList() = default;
    ~CircularLinkedList() { clear(); }

    void insert(T data) {
        Node* node = new Node(data);
        if (!head) {
            head = tail = node;
            node->next = node;
        } else {
            node->next = head;
            tail->next = node;
            tail = node;
        }
        ++size;
    }

    bool remove(T data) {
        if (!head) return false;

        Node* curr = head;
        Node* prev = tail;
        for (int i = 0; i < size; ++i) {
            if (curr->data == data) {
                if (size == 1) {
                    head = tail = nullptr;
                } else {
                    prev->next = curr->next;
                    if (curr == head) head = curr->next;
                    if (curr == tail) tail = prev;
                }
                delete curr;
                --size;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }

    bool contains(T data) const {
        Node* curr = head;
        for (int i = 0; i < size; ++i) {
            if (curr->data == data) return true;
            curr = curr->next;
        }
        return false;
    }

    int len() const {
        return size;
    }

    bool empty() const {
        return size == 0;
    }

    void clear() {
        while (size > 0) {
            remove(head->data);
        }
    }

private:
    struct Node {
        T data;
        Node* next;

        explicit Node(T data) : data(data), next(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    int size = 0;
};
