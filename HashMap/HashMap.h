//
//  geodb.h
//  project_4
//
//  Created by Leison Gao on 3/6/24.
//


#ifndef HASHMAP_H
#define HASHMAP_H

// ***** DO NOT TURN IN THIS FILE *****
//
// This file is an implementation of HashMap that has correct visible
// behavior.  If you cannot get your HashMap class to work well enough to
// make progress on the other classes that use HashMaps, you can use this
// one temporarily, switch your attention to implementing the other
// classes, and go back to working on *your* HashMap implementation later.
//
// DO NOT TURN IN THIS FILE AS YOUR IMPLEMENTATION -- it uses unordered_map,
// which the spec forbids.

#include <string>
#include <unordered_map>

template <class T>
class HashMap {
public:
    HashMap(double = 0.75) {}
    void insert(const std::string& key, const T& value) { m_map[key] = value;}
    int size() const { return m_map.size(); }
    T* find(const std::string& key) { const auto& hm = *this; return const_cast<T*>(hm.find(key)); }
    const T* find(const std::string& key) const { auto it = m_map.find(key); return it == m_map.end() ? nullptr : &it->second; }
    T& operator[](const std::string& key) { return m_map[key]; }
private:
    std::unordered_map<std::string, T> m_map;
};

#endif // HASHMAP_H

//
//
//#ifndef geodb_h
//#define geodb_h
//
//#include <iostream>
//#include <string>
//#include <vector>
//
//using namespace std;
//
//template <typename T>
//class HashMap
//{
//public:
//    HashMap(double max_load = 0.75); // constructor
//    ~HashMap(); // destructor; deletes all of the items in the hashmap
//    int size() const; // return the number of associations in the hashmap
//    // The insert method associates one item (key) with another (value).
//    // If no association currently exists with that key, this method inserts
//    // a new association into the hashmap with that key/value pair. If there is
//    // already an association with that key in the hashmap, then the item
//    // associated with that key is replaced by the second parameter (value).
//    // Thus, the hashmap must contain no duplicate keys.
//    void insert(const std::string& key, const T& value);
//    // If no association exists with the given key, return nullptr; otherwise,
//    // return a pointer to the value associated with that key. This pointer can be
//    // used to examine that value or modify it directly within the map.
//    T* find(const std::string& key) const;
//    // Defines the bracket operator for HashMap, so you can use your map like this:
//    // your_map["david"] = 2.99;
//    // If the key does not exist in the hashmap, this will create a new entry in
//    // the hashmap and map it to the default value of type T. Then it will return a
//    // reference to the newly created value in the map.
//    T& operator[](const std::string& key);
//    
//    HashMap(const HashMap&) = delete;
//    HashMap& operator=(const HashMap&) = delete;
//    
//private:
//    struct Node {
//        std::string m_key;
//        T m_val;
//        Node* next;
//        
//        Node() {}
//        Node(std::string key, T value, Node* next_node = nullptr) {
//            this->m_key = key;
//            this->m_val = value;
//            this->next = next_node;
//        }
//    };
//    
//    std::vector<Node*> m_map;
//    double m_max_load;
//    int m_size;
//    int m_numBuckets;
//    
//    size_t hashString(std::string s) const;
//    
//    double loadFactor() {
//        return (double)m_size / (double)m_numBuckets;
//    }
//    
//    void rehash();
//};
//
//template <typename T>
//HashMap<T>::~HashMap() {
//    for (int i = 0; i != m_map.size(); i ++) {
//        Node* p = m_map[i];
//        Node* np;
//        while (p != nullptr) {
//            np = p->next;
//            delete p;
//            p = np;
//        }
//    }
//}
//
//template <typename T>
//size_t HashMap<T>::hashString(std::string s) const{
//    size_t x = std::hash<std::string>()(s) % (m_numBuckets);
//    // if rehashing, double buckets
//    return x;
//}
//
//template <typename T>
//HashMap<T>::HashMap(double max_load) {
//    if (max_load <= 0)
//        m_max_load = 0.75;
//    // make sure max_load is correct
//    
//    m_map.resize(10);
//    m_max_load = max_load;
//    m_size = 0;
//    m_numBuckets = 10;
//}
//
//template <typename T>
//int HashMap<T>::size() const {
//    return m_size;
//}
//
//template <typename T>
//void HashMap<T>::rehash() {
////    std::cout << "rehash" << std::endl;
//    std::vector<Node*> old_map(m_map);
//    
//    m_map.clear();
//    m_map.resize(m_numBuckets * 2);
//    
//    m_size = 0;
//    m_numBuckets *= 2;
//    
//    for (int i = 0; i != old_map.size(); i ++) {
//        Node* p = old_map[i];
//        Node* next_p;
//        while (p != nullptr) {
//            // insert p into the new map
//            size_t hashKey = hashString(p->m_key);
//            Node* np = m_map[hashKey];
//            m_map[hashKey] = p;
//            m_size ++;
//            
//            // update p-> next position
//            next_p = p->next;
//            p->next = np;
//            p = next_p;
//        }
//    }
//}
//
//template <typename T>
//void HashMap<T>::insert(const std::string& key, const T& value) {
////    cout << "inserting value" << endl;
//    
//    size_t hashKey = hashString(key);
//    
//    Node* p = m_map[hashKey];
//    while (p != nullptr) { // checking if exists in map already
//        if (p->m_key == key) {
//            p->m_val = value;
//            return;
//        }
//        p = p->next;
//    }
//    
//    m_map[hashKey] = new Node(key, value, m_map[hashKey]);
//    m_size ++;
//    
//    if (loadFactor() > m_max_load) {
//        rehash();
//    }
//}
//
//template <typename T>
//T* HashMap<T>::find(const std::string& key) const {
//    size_t hashKey = hashString(key);
//    
//    Node* p = m_map[hashKey];
//    while (p != nullptr) { // checking if exists in map already
//        if (p->m_key == key) {
//            return &p->m_val;
//        }
//        p = p->next;
//    }
//    
//    return nullptr;
//}
//
//template <typename T>
//T& HashMap<T>::operator[](const std::string& key) {
//    size_t hashKey = hashString(key);
//    
//    
//    Node* p = m_map[hashKey];
//    while (p != nullptr) { // checking if exists in map already
//        if (p->m_key == key) {
//            return p->m_val;
//        }
//        p = p->next;
//    }
//    // creating default instance of value and inserting into array
//    T value = T();
//    m_map[hashKey] = new Node(key, value, m_map[hashKey]);
//    m_size ++;
//    
//    if (loadFactor() > m_max_load) {
//        rehash();
//    }
//    return m_map[hashKey]->m_val;
//}
//#endif /* geodb_h */
