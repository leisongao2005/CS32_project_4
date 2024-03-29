//
//  geodbTest.cpp
//  geodb
//
//  Created by Leison Gao on 3/6/24.
//

#include <stdio.h>
#include "geodb.h"
using namespace std;


int main() {
//     get poi location testing
    GeoDatabase g;
    g.load("mapdatatest.txt"); // assume this works to avoid error checking
//    // mapdata.txt should have 646 poi?
//    GeoPoint p;
//    if (g.get_poi_location("20th Century Fox Studios Galaxy Way", p))
//        cout << "The PoI is at " << p.sLatitude << ", " << p.sLongitude << endl;
//    else
//        cout << "PoI not found!\n";
    
//     get connected points testing
//    GeoDatabase g;
//    g.load("mapdata.txt"); // assume this works to avoid error checking
    
//    std::vector<GeoPoint> pts = g.get_connected_points(GeoPoint("34.0600768", "-118.4467216"));
//    cout << pts.size() << endl;
//    if (pts.empty())
//        cout << "There are no points connected to your specified point\n";
//    else {
//        for (const auto &p: pts)
//            cout << p.sLatitude << ", " << p.sLongitude << endl;
//    }
//    
    GeoPoint p1("34.0602175", "-118.4464952");
    GeoPoint p2("34.0600768", "-118.4467216");
    cout << g.get_street_name(p1, p2) << endl; // writes "Glenmere Way"
    cout << g.get_street_name(p2, p1) << endl; // writes "Glenmere Way" // writes "a path"
}

/*
 inserting points:
 point 1: 34.0732851,-118.4931016
 point 2: 34.0736122,-118.4927669

 this is v1 before inserting
 this is v1 after inserting
 34.0736122, -118.4927669
 this is v2 before inserting
 this is v2 after inserting
 34.0732851, -118.4931016
 
 inserting points:
 point 1: 34.0736122,-118.4927669
 point 2: 34.0739890,-118.4931789

 this is v1 before inserting
 34.0731714, -118.4921918
 this is v1 after inserting
 34.0731714, -118.4921918
 34.0739890, -118.4931789
 this is v2 before inserting
 this is v2 after inserting
 34.0736122, -118.4927669
 */
