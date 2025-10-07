#include <vector>

template<typename K, typename V>
struct HashSet{
    int N;
    std::vector<std::vector<std::pair<K,V>>> HashTable;
public:
    HashMap(int n=10): N(n), HashTable(n, std::vector<std::pair<K,V>>){
    };
    int hash(int key){
        return key%N;
    }
    int hash(char key){
        return ((int)key)%N;
    }




    void insert(K key, V value){

    };
private:
    struct Node {
        K key;
        V value;
    };
    Node* table[10];
    int hash(K key);
};
