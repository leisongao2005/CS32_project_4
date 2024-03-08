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
    };
    
    std::vector<Node*> m_nodes {10};
    double m_max_load;
    int m_size;
    int m_numBuckets;
    
    size_t hashString(std::string s, bool rehash = false) const;
    
    double loadFactor() {
        return (double)m_size / (double)m_numBuckets;
    }
    
    void reallocate();
};

template <typename T>
size_t HashMap<T>::hashString(std::string s, bool rehash) const{
    size_t x = std::hash<std::string>()(s) % (m_numBuckets * (1 + rehash));
    // if rehashing, double buckets
    return x;
}

template <typename T>
HashMap<T>::HashMap(double max_load) {
    if (max_load <= 0)
        m_max_load = 0.75;
    // make sure max_load is correct
    
    m_max_load = max_load;
    m_size = 0;
    m_numBuckets = 10;
}

template <typename T>
int HashMap<T>::size() const {
    return m_size;
}

template <typename T>
void HashMap<T>::reallocate() {
    std::vector<Node*> temp_nodes {static_cast<size_t>(2*m_numBuckets)};
    
    for (int i = 0; i < m_numBuckets; i ++) { // iterate over original hashtable
        if (m_nodes.at(i) != nullptr) {
            Node* p = m_nodes.at(i);
            size_t hashKey = hashString(p->m_key, true); // rehash current item and store item in new hashtable
            if (temp_nodes.at(hashKey) == nullptr) { // when bucket is empty simply reassing
                temp_nodes.at(hashKey) = p;
            }
            else { // bucket is not empty, must first trace to end of linked list
                Node* p_temp = temp_nodes.at(hashKey);
                while (p_temp->next != nullptr) {
                    if (p_temp->m_key == p->m_key) {
                        p_temp->m_val = p->m_val; // reassigment if duplicate
                        return;
                    }
                    p_temp = p_temp->next;
                }
                p_temp->next = p;
            }
            
            Node* next_p = p->next; // store next value
            p->next = nullptr; // make sure no longer linked
            
            while (next_p != nullptr) { // must check entire linked list and insert all of those
                size_t hashKey = hashString(p->m_key, true); // rehash current item and store item in new hashtable
                if (temp_nodes.at(hashKey) == nullptr) { // when bucket is empty simply reassing
                    temp_nodes.at(hashKey) = p;
                }
                else { // bucket is not empty, must first trace to end of linked list
                    Node* p_temp = temp_nodes.at(hashKey);
                    while (p_temp->next != nullptr) {
                        if (p_temp->m_key == p->m_key) {
                            p_temp->m_val = p->m_val; // reassigment if duplicate
                            return;
                        }
                        p_temp = p_temp->next;
                    }
                    p_temp->next = p;
                }
                next_p = next_p->next;
            }
        }
    }
    m_nodes = temp_nodes; // vector assignment operator should free memory of old hashmap
    m_numBuckets *= 2;
}

template <typename T>
void HashMap<T>::insert(const std::string& key, const T& value) {
    if (loadFactor() > m_max_load) {
        reallocate();
    }
    size_t hashKey = hashString(key);
    if (m_nodes.at(hashKey) == nullptr) { // when bucket is empty, create new node
        Node* temp = new Node;
        temp->m_key = key;
        temp->m_val = value;
        temp->next = nullptr;
        m_nodes.at(hashKey) = temp;
        m_size ++;
    }
    else { // bucket is not empty, must first trace to end of linked list
        Node* p = m_nodes.at(hashKey);
        while (p->next != nullptr) {
            if (p->m_key == key) {
                p->m_val = value; // reassigment if duplicate
                return;
            }
            p = p->next;
        }
        Node* temp = new Node;
        temp->m_key = key;
        temp->m_val = value;
        temp->next = nullptr;
        p->next = temp;
        m_size ++;
    }
}

template <typename T>
T* HashMap<T>::find(const std::string& key) const {
    size_t hashKey = hashString(key);
    if (m_nodes.at(hashKey) == nullptr) {
        return nullptr;
    }
    else {
        Node* p = m_nodes.at(hashKey);
        if (p->m_key == key) {
            return &p->m_val; // passing by reference because pointer value return type
        }
        while (p->next != nullptr) {
            if (p->m_key == key) {
                return &p->m_val;
            }
            p = p->next;
        }
        return nullptr;
    }
}

template <typename T>
T& HashMap<T>::operator[](const std::string& key) {
    size_t hashKey = hashString(key);
    if (m_nodes.at(hashKey) == nullptr) {
        Node* temp = new Node;
        temp->m_key = key;
        temp->next = nullptr;
        m_nodes.at(hashKey) = temp;
        m_size ++;
        return temp->m_val;
    }
    else {
        Node* p = m_nodes.at(hashKey);
        if (p->m_key == key) {
            return p->m_val;
        }
        while (p->next != nullptr) {
            if (p->m_key == key) {
                return p->m_val;
            }
            p = p->next;
        }
        Node* temp = new Node;
        temp->m_key = key;
        temp->next = nullptr;
        p->next = temp;
        m_size ++;
        return temp->m_val;
    }
}

#endif /* geodb_h */
