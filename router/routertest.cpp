//
//  main.cpp
//  router
//
//  Created by Leison Gao on 3/9/24.
//

#include <iostream>
#include "router.h"
#include "base_classes.h"
#include "geodb.h"

using namespace std;

int main() {
    GeoPoint p1("34.0547000", "-118.4794734");
    GeoPoint p2("34.0544590", "-118.4801137");
    
    GeoDatabase g;
    g.load("mapdatatest.txt"); // assume this works to avoid error checking
    
    Router r(g);
}
