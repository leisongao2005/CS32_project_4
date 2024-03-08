//
//  geodb.cpp
//  geodb
//
//  Created by Leison Gao on 3/6/24.
//

#include "geodb.h"
#include "HashMap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

bool GeoDatabase::load(const std::string& map_data_file) {
    ifstream infile(map_data_file);    // infile is a name of our choosing
    if (!infile)                // Did opening the file fail?
    {
        cerr << "Error: Cannot open data.txt!" << endl;
        return false;
    }
    string line;
      // getline returns infile; the while tests its success/failure state
    int counter = 0;
    while (getline(infile, line))
    {
        cout << "reading place " << counter << endl;
        counter ++;
        istringstream nameString(line);
        string name;
        string lat1, long1, lat2, long2;
        // get name first
        nameString >> name;
        getline(infile, line);
        istringstream coordString(line);
        // getting coordinates
        coordString >> lat1 >> long1 >> lat2 >> long2;
        
        // storing street information
        GeoPoint point1 = GeoPoint(lat1, long1);
        GeoPoint point2 = GeoPoint(lat2, long2);
        
        // for debugging
//        pair<string, GeoPoint> pair1;
//        pair1.first = point1.to_string();
//        pair1.second = point2;
//        pair<string, GeoPoint> pair2;
//        pair2.first = point2.to_string();
//        pair2.second = point1;
//        pair<string, string> pair3;
//        pair3.first = point1.to_string() + point2.to_string();
//        pair3.second = name;
//        
//        m_connectedPoints.insert(pair1);
//        m_connectedPoints.insert(pair2);
//        m_streets.insert(pair3);
        
//        m_connectedPoints.insert(point1.to_string(), point2);
//        m_connectedPoints.insert(point2.to_string(), point1);
//
//        m_streets.insert(point1.to_string() + point2.to_string(), name);
        
        // end debugging
        
        
        // checking for pois
        getline(infile, line);
        istringstream numPoiString(line);
        int numPois;
        
        numPoiString >> numPois;
        if (numPois != 0) { // case where pois must be iterated through
            cout << "inserting poi" << endl;
            for (int i = 0; i < numPois; i ++) {
                getline(infile, line);
                istringstream poiString(line);
                string poiName;
                string name;
                
                string lat_val, long_val;
                bool end = false;
                
                while((poiString >> poiName) && !end) {
                    for (size_t j = 0; j != poiName.size(); j ++) {
                        if (poiName.at(j) == '|') {
                            lat_val = poiName.substr(j + 1);
                            poiName = poiName.substr(0, j);
                            end = true;
                            poiString >> long_val;
                            break;
                        }
                    }
                    name += poiName + " ";
                }
                name = name.substr(0, name.size() - 1); // removing extra space
                // adding to hashmap
                cerr << name << endl;
                
                // for debugging
                pair<string, GeoPoint> pair1;
                pair1.first = name;
                pair1.second = GeoPoint(lat_val, long_val);
                
                cout << "inserting with " << pair1.second.to_string() << endl;
                m_poiMap.insert(pair1);
//                m_poiMap.insert(name, GeoPoint(lat_val, long_val));
                
                // end debugging
            }
        }
    }
    return true;
}

bool GeoDatabase::get_poi_location(const std::string& poi, GeoPoint& point) const {
    cout << m_poiMap.size() << endl;
    
    // for debugging
    if (m_poiMap.find(poi) == m_poiMap.end())
        return false;
    else
        return true;
//    if (p != nullptr) {
//        point = *p;
//        return true;
//    }
    
//    GeoPoint* p = m_poiMap.find(poi);
//    if (p != nullptr) {
//        point = *p;
//        return true;
//    }
//    
    // end debugging
    return false;
}

std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const {
    vector<GeoPoint> points;
    return points;
}

std::string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const {
    return "";
}