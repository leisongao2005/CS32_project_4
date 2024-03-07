//
//  geodb.h
//  project_4
//
//  Created by Leison Gao on 3/6/24.
//

#ifndef geodb_h
#define geodb_h

#include <string>
#include <vector>

template <typename T>
class HashMap
{
public:
    HashMap(double max_load = 0.75); // constructor
    ~HashMap(); // destructor; deletes all of the items in the hashmap
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
private:
    struct Node {
        std::string m_akey;
        Node* m_next
    }
    vector<
};
#endif /* geodb_h */
