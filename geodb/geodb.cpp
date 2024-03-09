//
//  geodb.cpp
//  geodb
//
//  Created by Leison Gao on 3/6/24.
//

#include "geodb.h"
#include "HashMap.h"
#include "geotools.h"
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
//        cout << "reading place " << counter << endl;
        counter ++;
        istringstream nameString(line);
        string name;
        string name_part;
        string lat1, long1, lat2, long2;
        // get name first
        while (nameString >> name_part)
            name += name_part + " ";
        name = name.substr(0, name.size() - 1);
        
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
        
//        m_connectedPoints.insert(pair1);
//        m_connectedPoints.insert(pair2);
//        m_streets.insert(pair3);
        
        
//        cerr << "inserting points: " << endl;
//        cerr << "point 1: " << point1.to_string() << endl;
//        cerr << "point 2: " << point2.to_string() << endl << endl;
//        
        vector<GeoPoint> v1 = m_connectedPoints[point1.to_string()];
        v1.push_back(point2);
        vector<GeoPoint> v2 = m_connectedPoints[point2.to_string()];
        v2.push_back(point1);
        
        m_connectedPoints.insert(point1.to_string(), v1);
        m_connectedPoints.insert(point2.to_string(), v2);

        m_streets.insert(point1.to_string() + point2.to_string(), name);
//        m_streets.insert(point2.to_string() + point1.to_string(), name);
        
        // end debugging
        
        
        // checking for pois
        getline(infile, line);
        istringstream numPoiString(line);
        int numPois;
        
        numPoiString >> numPois;
        if (numPois != 0) { // case where pois must be iterated through
            
            // add midpoint to connected points and streets
            
            vector<GeoPoint> v1 = m_connectedPoints[midpoint(point1, point2).to_string()];
            v1.push_back(point1);
            v1.push_back(point2);
            
            vector<GeoPoint> v2 = m_connectedPoints[point1.to_string()];
            v2.push_back(midpoint(point1, point2));
            
            vector<GeoPoint> v3 = m_connectedPoints[point2.to_string()];
            v3.push_back(midpoint(point1, point2));
            
            m_connectedPoints.insert(midpoint(point1, point2).to_string(), v1);
            m_connectedPoints.insert(point1.to_string(), v2);
            m_connectedPoints.insert(point2.to_string(), v3);
            
            m_streets.insert(point1.to_string() + midpoint(point1, point2).to_string(), name);
            m_streets.insert(point2.to_string() + midpoint(point1, point2).to_string(), name);
//            m_streets.insert(midpoint(point1, point2).to_string() + point1.to_string(), "a path");
//            m_streets.insert(midpoint(point1, point2).to_string() + point2.to_string(), "a path");
            
            for (int i = 0; i < numPois; i ++) {
//                cout << "inserting poi" << endl;
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
                
                GeoPoint poi = GeoPoint(lat_val, long_val);
                
                vector<GeoPoint> v1 = m_connectedPoints[midpoint(point1, point2).to_string()];
                v1.push_back(poi);
                vector<GeoPoint> v2 = m_connectedPoints[poi.to_string()];
                v2.push_back(midpoint(point1, point2));
                
                m_connectedPoints.insert(midpoint(point1, point2).to_string(), v1);
                m_connectedPoints.insert(poi.to_string(), v2);
                
                m_streets.insert(poi.to_string() + midpoint(point1, point2).to_string(), "a path");
                // adding to hashmap
//                cerr << name << endl;
                
                // for debugging
//                pair<string, GeoPoint> pair1;
//                pair1.first = name;
//                pair1.second = GeoPoint(lat_val, long_val);
//                
//                cout << "inserting with " << pair1.second.to_string() << endl;
//                m_poiMap.insert(pair1);
                m_poiMap.insert(name, GeoPoint(lat_val, long_val));
                
                // end debugging
            }
        }
    }
    return true;
}

bool GeoDatabase::get_poi_location(const std::string& poi, GeoPoint& point) const {
    cout << m_poiMap.size() << endl;
    
    // for debugging
//    if (m_poiMap.find(poi) == m_poiMap.end())
//        return false;
//    else
//        return true;
    
    GeoPoint* p = m_poiMap.find(poi);
    if (p != nullptr) {
        point = *p;
        return true;
    }
    
    // end debugging
    return false;
}

std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const {
    vector<GeoPoint>* points = m_connectedPoints.find(pt.to_string());
    return *points;
}

std::string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const {
//    string s1 = *m_streets.find(pt1.to_string() + " ," + pt2.to_string());
//    string s2 = *m_streets.find(pt2.to_string() + " ," + pt1.to_string());
//    
//    if (s1 > s2)
//        return s1;
//    return s2;
    
    if (m_streets.find(pt1.to_string() + pt2.to_string()) != nullptr)
        return *m_streets.find(pt1.to_string() + pt2.to_string());
    else if (m_streets.find(pt2.to_string() + pt1.to_string()) != nullptr)
        return *m_streets.find(pt2.to_string() + pt1.to_string());
    else
        return "";
}
