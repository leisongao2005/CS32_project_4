//
//  geodb.h
//  project_4
//
//  Created by Leison Gao on 3/6/24.
//

#ifndef geodb_h
#define geodb_h

#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
class HashMap
{
public:
    HashMap(double max_load = 0.75); // constructor
    ~HashMap() {}; // destructor; deletes all of the items in the hashmap
    int size() const; // return the number of associations in the hashmap
    // The insert method associates one item (key) with another (value).
    // If no association currently exists with that key, this method inserts
    // a new association into the hashmap with that key/value pair. If there is
    // already an association with that key in the hashmap, then the item
    // associated with that key is replaced by the second parameter (value).
    // Thus, the hashmap must contain no duplicate keys.
    void insert(const std::string& key, const T& value);
    // If no association exists with the given key, return nullptr; otherwise,
    // return a pointer to the value associated with that key. This pointer can be
    // used to examine that value or modify it directly within the map.
    T* find(const std::string& key) const;
    // Defines the bracket operator for HashMap, so you can use your map like this:
    // your_map["david"] = 2.99;
    // If the key does not exist in the hashmap, this will create a new entry in
    // the hashmap and map it to the default value of type T. Then it will return a
    // reference to the newly created value in the map.
    T& operator[](const std::string& key);
    
    HashMap(const HashMap&) = delete;
    HashMap& operator=(const HashMap&) = delete;
    
private:
    struct Node {
        std::string m_key;
        T m_val;
        Node* next;
        
        Node(std::string key, T value, Node* next_node = nullptr) {
            this->m_key = key;
            this->m_val = value;
            this->next = next_node;
        }
    };
    
    std::vector<Node*> m_map;
    double m_max_load;
    int m_size;
    int m_numBuckets;
    
    size_t hashString(std::string s) const;
    
    double loadFactor() {
        return (double)m_size / (double)m_numBuckets;
    }
    
    void rehash();
//    bool insertHelper(const std::string& key, const T& value, std::vector<Node*>& table, int hashSize);
    
};


template <typename T>
size_t HashMap<T>::hashString(std::string s) const{
    size_t x = std::hash<std::string>()(s) % (m_numBuckets);
    // if rehashing, double buckets
    return x;
}

template <typename T>
HashMap<T>::HashMap(double max_load) {
    if (max_load <= 0)
        m_max_load = 0.75;
    // make sure max_load is correct
    
    m_map.resize(10);
    m_max_load = max_load;
    m_size = 0;
    m_numBuckets = 10;
}

template <typename T>
int HashMap<T>::size() const {
    return m_size;
}

template <typename T>
void HashMap<T>::rehash() {
//    std::cout << "rehash" << std::endl;
    std::vector<Node*> old_map(m_map);
    
    m_map.clear();
    m_map.resize(m_numBuckets * 2);
    
    m_size = 0;
    m_numBuckets *= 2;
    
    for (int i = 0; i != old_map.size(); i ++) {
        Node* p = old_map[i];
        while (p != nullptr) {
            insert(p->m_key, p->m_val);
            p = p->next;
        }
    }
    
//    std::vector<Node*> old_nodes(m_nodes);
//    m_nodes.clear();
//    m_nodes.resize(2*m_numBuckets);
//    
//    for (int i = 0; i < m_numBuckets; i ++) { // iterate over original hashtable
//        if (old_nodes.at(i) != nullptr) {
//            cout << "rehashing value " << endl;
//            Node* p = old_nodes.at(i);
//            
//            size_t hashKey = hashString(p->m_key, 2*m_numBuckets);
//            Node* next_p = p->next;
//            Node* temp_p = m_nodes.at(hashKey);
//            if (temp_p == nullptr) { // when bucket is empty, link node
//                temp_p = p;
//                p->next = nullptr; // unlink rest
//            }
//            else { // bucket is not empty, must first trace to end of linked list
//                while (temp_p->next != nullptr)
//                    temp_p = temp_p->next;
//                temp_p = p;
//                p->next = nullptr; // unlink rest
//            }
//            
//            p = next_p;
//            while (p != nullptr) { // must check entire linked list and insert all of those
//                hashKey = hashString(p->m_key, 2*m_numBuckets);
//                temp_p = m_nodes.at(hashKey);
//                if (temp_p == nullptr) { // when bucket is empty, link node
//                    temp_p = p;
//                    p->next = nullptr; // unlink rest
//                }
//                else { // bucket is not empty, must first trace to end of linked list
//                    while (temp_p->next != nullptr)
//                        temp_p = temp_p->next;
//                    temp_p = p;
//                    p->next = nullptr; // unlink rest
//                }
//                p = p->next;
//            }
//        }
//    }
//    m_nodes = temp_nodes; // vector assignment operator should free memory of old hashmap
//    m_numBuckets *= 2;
}

template <typename T>
void HashMap<T>::insert(const std::string& key, const T& value) {
//    cout << "inserting value" << endl;
    
    size_t hashKey = hashString(key);
    
    Node* p = m_map[hashKey];
    while (p != nullptr) { // checking if exists in map already
        if (p->m_key == key) {
            p->m_val = value;
            return;
        }
        p = p->next;
    }
    
    m_map[hashKey] = new Node(key, value, m_map[hashKey]);
    m_size ++;
    
    if (loadFactor() > m_max_load) {
        rehash();
    }
//    size_t hashKey = hashString(key, m_numBuckets);
//    if (m_nodes.at(hashKey) == nullptr) { // when bucket is empty, create new node
//        Node* temp = new Node;
//        temp->m_key = key;
//        temp->m_val = value;
//        temp->next = nullptr;
//        m_nodes.at(hashKey) = temp;
//        m_size ++;
//    }
//    else { // bucket is not empty, must first trace to end of linked list
//        Node* p = m_nodes.at(hashKey);
//        while (p->next != nullptr) {
//            if (p->m_key == key) {
//                p->m_val = value; // reassigment if duplicate
//                return;
//            }
//            p = p->next;
//        }
//        Node* temp = new Node;
//        temp->m_key = key;
//        temp->m_val = value;
//        temp->next = nullptr;
//        p->next = temp;
//        m_size ++;
//    }
//    cout << "current load factor: " << loadFactor() << endl;
//    if (loadFactor() > m_max_load) {
//        rehash();
//    }
////    if (insertHelper(key, value, m_nodes, m_numBuckets))
////        m_size ++;
}

template <typename T>
T* HashMap<T>::find(const std::string& key) const {
    size_t hashKey = hashString(key);
    
    Node* p = m_map[hashKey];
    while (p != nullptr) { // checking if exists in map already
        if (p->m_key == key) {
            return &p->m_val;
        }
        p = p->next;
    }
    
    return nullptr;
}

template <typename T>
T& HashMap<T>::operator[](const std::string& key) {
    size_t hashKey = hashString(key);
    
    Node* p = m_map[hashKey];
    while (p != nullptr) { // checking if exists in map already
        if (p->m_key == key) {
            return p->m_val;
        }
        p = p->next;
    }
    // creating default instance of value and inserting into array
    T* value = new T();
    m_map[hashKey] = new Node(key, *value, m_map[hashKey]);
    m_size ++;
    
    if (loadFactor() > m_max_load) {
        rehash();
    }
    return *value;
}
#endif /* geodb_h */
