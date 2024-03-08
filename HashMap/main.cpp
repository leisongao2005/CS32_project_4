//
//  main.cpp
//  Hashmap
//
//  Created by Leison Gao on 3/6/24.
//

#include <iostream>
#include "HashMap.h"

using namespace std;
void foo()
{
    // Define a hashmap that maps strings to doubles and has a maximum
    // load factor of 0.3. It will initially have 10 buckets when empty.
    HashMap<double> nameToGPA(0.3);
    // Add new items to the hashmap. Inserting the third item will cause
    // the hashmap to increase the number of buckets (since the maximum
    // load factor is 0.3), forcing a rehash of all items.
    nameToGPA.insert("1", 3.5); // Carey has a 3.5 GPA
    nameToGPA.insert("2", 2.99); // David needs to up his game
    cout << nameToGPA.size() << endl;
    nameToGPA.insert("3", 3.5);
    
    double* g1 = nameToGPA.find("1");
    if (g1 != nullptr)
        cout << "found" << endl;
    else
        cout << "not found" << endl;
    cout << "load factor = 0.3, next should reallocate" << endl;
    nameToGPA.insert("4", 3.5);
    nameToGPA.insert("5", 3.5);
    nameToGPA.insert("6", 3.5);
    nameToGPA.insert("7", 3.5);
    
    g1 = nameToGPA.find("1");
    if (g1 != nullptr)
        cout << "found" << endl;
    else
        cout << "not found" << endl;
    cout << "load factor = 0.3, next should reallocate" << endl;
    nameToGPA.insert("8", 3.5);
    nameToGPA.insert("9", 3.5);
    
    g1 = nameToGPA.find("2");
    if (g1 != nullptr)
        cout << "found" << endl;
    else
        cout << "not found" << endl;
    cout << nameToGPA.size() << endl;
    
    // you can also use brackets like C++'s unordered_map!
    nameToGPA["Annie"] = 3.85; // Adds Annie, who has the highest GPA of all
    nameToGPA.insert("Annie", 3.85);
    double* davidsGPA = nameToGPA.find("David");
    if (davidsGPA != nullptr) {
        *davidsGPA = 3.1; // after a re-grade of David's exam, update 2.99 -> 3.1
        cout << "updated david gpa" << endl;
    }
//    cout << nameToGPA.find("David") << endl;
    nameToGPA.insert("Carey", 4.0); // Carey deserves a 4.0
    // sees if linda is in the map; if not, creates a new entry for linda in map
    std::cout << nameToGPA["Linda"] << endl; // prints zero
}

int main() {
//    foo();
    HashMap<vector<int>> a(.4);
    for (int i = 0; i < 8; i ++) {
        vector<int> v;
        v.push_back(i);
        a.insert(to_string(i), v);
        cout << "inserted, size now: " << a.size() << endl;
    }
    for (int i = 0; i < 8; i ++) {
        vector<int>* v = a.find(to_string(i));
        if (v != nullptr) {
            cout << to_string(i) << " v exists" << endl;
        }
    }
//    vector<int> v1 = a["1"];
//    for(const auto &p: v1) {
//        cout << p << endl;
//    }
//    v1.push_back(2);
////    a.insert("1", v1);
//    a["1"] = v1;
//    for(const auto &p: v1) {
//        cout << p << endl;
//    }
}
