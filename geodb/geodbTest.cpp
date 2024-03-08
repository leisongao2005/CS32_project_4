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
    GeoDatabase g;
    g.load("mapdata.txt"); // assume this works to avoid error checking
    GeoPoint p;
    if (g.get_poi_location("Diddy Riese", p))
        cout << "The PoI is at " << p.sLatitude << ", " << p.sLongitude << endl;
    else
        cout << "PoI not found!\n";
}
