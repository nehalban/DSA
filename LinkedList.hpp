/*Constructor from initializer_list<int> lets you initialize with array syntax:
SinglyLinkedList_wotail list = {1, 2, 3, 4};
*/

#include <iostream>
using namespace std;

//Why use tail function instead of pointer?
//With pointer, any manual mutation bypassing your class methods (like direct tail->next = new Node(...)) will break internal consistency.


struct SinglyLinkedList{
    // operations:
    // insertion at beginning : insert(data) or insert(data, false)
    // insertion at the end : insert(data, true)
    // insertion at given point : insert(data, index)
    // deletion at beginning: del() or del(false)
    // deletion at the end: del(true)
    // deletion at given point: del(index)
    // print entire list: print(separator)
    // reversal in place : reverse()
    // recursive function for reversal in place: recursive_reverse()
    // return reversed list: reversed()
    // length : len()
    // return tail : tail()
    // concatenation of two lists: concatenate(list, inplace)
    // copy of list: copy()
    // access elements at given index: operator[](index)
    // addition of two lists/ copy of concatenated list: operator+(addend)

    // empty the list, free up space: clear (called in destructor as well)

    //reverse between given indices: reverse(index_begin, index_end)
    //find - find first occurrence
    //contains - bool for find
    //remove - remove first occurrence of an element.
    struct Node {
        int data;
        Node* next;
        Node(Node* next = nullptr): data(0), next(next){
        }
        Node(int x=0, Node* next = nullptr): data(x), next(next){
        }
    };
    Node *head = nullptr;
	SinglyLinkedList() = default;
    SinglyLinkedList(std::initializer_list<int> values) {
		bool firstval = true;
		Node* current = nullptr;
        for (int x : values) {
            if (firstval) {
				head = new Node(x);
				current = head;
				firstval = false;
            }
            else {
                current->next = new Node(x);
                current = current->next;
            }
        }
	}
    Node* tail(){
        Node* temp= head;
        if(temp){
            while(temp->next) temp = temp->next;
        }
        return temp;
    }
    int len() const {
        int x=0;
        Node* temp = head;
        while(temp){
            x++;
            temp =temp->next;
        }
        return x;
    }
    Node* insert(int data_, bool at_end = false){
        if (at_end){
            if (!head){
                head = new Node(data_);
                return head;
            }
            else{
                Node* temp = new Node( data_ );
                tail()->next = temp;
                return temp;
            }
        }
        else{
            Node* temp = new Node(data_);
            temp->next = head;
            head = temp;
            return temp;
        }
    }
    Node* insert(int data_, int index){
        if (index==0) return insert(data_);
        else if (index<0){
            throw out_of_range("Index out of bounds: Negative index");
        }
        else{
            if (!head){
                throw out_of_range("Index out of bounds: Empty list");
                // return insert(data_, true);
                // uncomment this line to insert data in empty list when index is greater than 0.
            }
            else{
                Node* temp = head;
                for (int i=0; i<index-1; i++){
                    temp = temp->next;
                    if(!temp){
                        throw out_of_range("Index out of bounds");
                        // return insert(data_, true);
                        // uncomment this line to insert data at the end of list when index is greater than length of list.
                    }
                }
                Node* temp1 = new Node(data_);
                temp1->next = temp->next;
                temp->next= temp1;
                return temp1;
            }
        }
    }
    int del(bool at_end = false){
        if (head==nullptr){
            throw out_of_range("Empty List: Nothing to delete");
        }
        else if (head->next == nullptr){
            int data_ = head->data;
            delete head;
            head = nullptr;
            return data_;
        }
        if (at_end){
            Node* tail_ = tail();
            int data_=tail_->data;
            delete tail_;
            return data_;
        }
        else{
            Node* temp = head;
            head = head->next;
            int data_ = temp->data;
            delete temp;
            return data_;
        }
    }
    int del(int index){
        if(index==0) del(false);
        else if(index<0) {
            throw out_of_range("Index out of bounds: Negative index");
        }
        else{
            if (!head || !head->next){
                throw out_of_range("Index out of bounds");
            }
            else{
                Node* temp = head;
                for (int i = 0; i < index-1; i++){
                    temp = temp->next;
                    if(!temp->next){
                        throw out_of_range("Index out of bounds: Index greater than length of list");
                    }
                }
                Node* temp1 = temp->next->next;
                int data_ = temp->next->data;
                delete temp->next;
                temp->next = temp1;
                return data_;
            }
        }
    }
    void print(char separator = ',') const {
        if (!head){
            cout<<"Empty List"<<'\n';
            return;
        }
        else{
            const Node* temp = head;
            while(temp->next){
                cout<<temp->data<<separator;
                temp = temp->next;
            }
            cout<<temp->data<<'\n';
            return;
        }
    }
    void clear(){
        while(head){
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    int& operator[](const int& index) {
        if(index < 0) throw std::out_of_range("Index out of bounds: Negative index");
        if(!head) throw std::out_of_range("Index out of bounds: Empty List");
        Node* temp = head;
        for (int i = 0; i < index; i++){
            temp = temp->next;
            if(!temp) throw std::out_of_range("Index out of bounds: Index greater than length of List");
        }
        return temp->data;
    }
    SinglyLinkedList reversed() const {
        Node* temp = head;
        SinglyLinkedList list;
        while(temp){
            list.insert(temp->data);
            temp = temp->next;
        }
        return list;
    }
    void reverse(){
        if (!head || !(head->next)) return;
        Node* temp = head;
        Node* temp1 = temp->next;
        Node* temp2 = temp1->next;
        temp->next = nullptr;
        while(temp2){
            temp1->next = temp;
            temp = temp1;
            temp1 = temp2;
            temp2 = temp2->next;
        }
        temp1->next = temp;
        head = temp1;
    }
    void recursive_reverse(){
        if(!head->next || !head) return;
        Node* temp = head;
        head = head->next;
        recursive_reverse();
        temp->next->next = temp;
        temp->next = nullptr;
    }
    void concatenate(const SinglyLinkedList list, bool inplace = true){
        if (inplace) tail()->next = list.head;
        else tail()->next = list.copy().head;
    }
    SinglyLinkedList copy() const {
        SinglyLinkedList list;
        Node* temp = head;
        while(temp){
            list.insert(temp->data);
            temp = temp->next;
        }
        return list;
    }
    SinglyLinkedList operator+(const SinglyLinkedList & addend) const {
        SinglyLinkedList sum = copy();
        sum.concatenate(addend.copy());
        return sum;
    }
    SinglyLinkedList operator+(const int & addend) const {
        SinglyLinkedList sum = copy();
        sum.insert(addend, true);
        return sum;
	}
    Node* middle() const {
        if (!head) throw std::out_of_range("Empty List");
        Node* slow = head;
        Node* fast = head->next;
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
    Node* merge_sort(Node* start = nullptr) {
        if (!start) start = head;
        if (!start ||!start->next) return start;
        Node* mid = start;
        Node* temp = start->next;
        while(temp && temp->next) {
            mid = mid->next;
            temp = temp->next->next;
        }
        Node* start2 = mid->next;
        mid->next = nullptr;
        Node* start1 = merge_sort(start);
        start2 = merge_sort(start2);
        if (start1->data<start2->data) start = start1;
        else {
            start = start2;
            start2 = start1;
            start1 = start;
        }
        while(start2) {
            while (start1->next && start1->next->data<start2->data) {start1 = start1->next;}
            temp = start1->next;
            start1->next = start2;
            start2 = temp;
            start1 = start1->next;
        }
        return start;
    }
    protected:
    Node* floyd_node() const {
        Node* slow = head;
        Node* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                // Cycle detected
                return slow;
            }
        }
        return nullptr; // No cycle detected
    }
    public:
    bool has_loop() const {
		//uses Floyd's Cycle-Finding Algorithm
		return floyd_node()!=nullptr;
    }
    int loop_length() const {
        Node* meeting = floyd_node();
        Node* temp = meeting;
        if(meeting) {
            int ans=1;
            while (temp->next!=meeting) {
                ans++;
                temp = temp->next;
            }
            return ans;
        }
        else return 0;
	}
    Node* loop_head() {
        Node* temp = head;
        Node* temp1 = floyd_node();
        if (!temp1) return nullptr;
        while (temp!=temp1) {
            temp = temp->next;
            temp1 = temp1->next;
        }
        return temp;
    }

    ~SinglyLinkedList(){
        this->clear();
    }
};

struct SinglyLinkedList_t: public SinglyLinkedList{
    //Singly Linked List with tail pointer instead of tail function
    Node* tail = nullptr;
    const int& operator[](const int& index){
        if(index>=0){
            Node* temp = head;
            for (int i = 0; i < index; i++){
                temp = temp->next;
                if(!temp->next) break;
            }
            return temp->data;
        }
        else{
            //index<0
            return head->data;
        }
    }
};

struct DoublyLinkedList{
    struct Node{
        int data;
        Node* prev;
        Node* next;
        Node(): data(0), prev(nullptr), next(nullptr) {};
        Node(int data): data(data), prev(nullptr), next(nullptr) {};
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    int size = 0;
    int& operator[](int index){
        return address_at_index(index)->data;
    }
    Node* address_at_index(int index){
        if (!head) throw out_of_range("Index out of bounds: Empty List");
        else if (index>=size || index<-size) throw out_of_range("Index out of bounds: Absolute value greater than length of list");
        else if (index>=0){
            Node* temp= head;
            while(index--) temp = temp->next;
            return temp;
        }
        else{
            Node* temp= tail;
            index++;
            while(index++) temp = temp->prev;
            return temp;
        }
    }
    void print(char separator = ',') const{
        if(!head) cout<<"Empty List"<<'\n';
        else{
            Node* temp = head;
            for (int i = 0; i < size-1; i++)
            {
                cout<<temp->data<<separator;
                temp = temp->next;
            }
            cout<<temp->data<<'\n';
        }
    }
    Node* insert(int data_, bool at_end= false){
        size++;
        if(!head||!tail){
            head = new Node(data_);
            tail = head;
            return head;
        }
        else if (at_end){
            tail->next = new Node(data_);
            tail->next->prev = tail;
            tail= tail->next;
            return tail;
        }
        else{
            head->prev = new Node(data_);
            head->prev->next = head;
            head = head->prev;
            return head;
        }
    }
    Node* insert(int data_, int index){
        if(index==0 || index==-size-1) return insert(data_);
        else if(index==size||index==-1) return insert(data_, true);
        Node* temp;
        if(index>0) temp = address_at_index(index-1);
        else temp = address_at_index(index);
        temp->next->prev = new Node(data_);
        size++;
        temp->next->prev->prev = temp;
        temp->next->prev->next = temp->next;
        temp->next = temp->next->prev;
        return temp->next;
    }
    int del(bool at_end = false){
        if (head==tail){
            clear();
            size=0;
        }
        else if(at_end){
            int data = tail->data;
            tail = tail->prev;
            delete tail->next;
            size--;
            tail->next = nullptr;
            return data;
        }
        else{
            int data = head->data;
            head = head->next;
            delete head->prev;
            size--;
            head->prev = nullptr;
            return data;
        }
    }
    int del(int index){
        if (index==0||index==-size) return del();
        else if (index==size-1||index==-1) return del(true);
        Node* temp = address_at_index(index);
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        int data = temp->data;
        delete temp;
        size--;
        return data;
    }
    //reverse, add, copy, sort, find, contains, remove, initializer list
    void reverse();
    void clear(){
        if (head){
            while(head->next){
                head = head->next;
                delete head->prev;
            }
            delete head;
        }
        if (head!=tail && tail){
            while(tail->prev){
                tail = tail->prev;
                delete tail->next;
            }
            if(head!=tail) delete tail;
        }
        head=nullptr;
        tail=nullptr;
        size=0;
    }
    ~DoublyLinkedList(){
        clear();
    }
};

//circular linked list
template<typename T>
class CircularLinkedList {
public:
    CircularLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~CircularLinkedList() { clear(); }

    void insert(T data);
    void remove(T data);
    bool contains(T data);
    void clear();

private:
    struct Node {
        T data;
        Node* next;
        Node(T data) : data(data), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int size;
};
