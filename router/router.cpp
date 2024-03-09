//
//  router.cpp
//  router
//
//  Created by Leison Gao on 3/9/24.
//

#include "router.h"
#include "geotools.h"
#include <map>
using namespace std;

vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const {
    vector<GeoPoint> points;
    if (pt1.to_string() == pt2.to_string()) {
        points.push_back(pt1);
        return points;
    }
    
    // hashmaps used for O(1) retrieval
    unordered_map<string, GeoPoint> came_from;
    unordered_map<string, double> cost_so_far;
    // red-black tree used for O(logN) search
    map<double, GeoPoint> next_points;
    next_points[0] = pt1;

    came_from[pt1.to_string()] = pt1;
    cost_so_far[pt1.to_string()] = 0;
  
    while (!next_points.empty()) {
        GeoPoint current = next_points.begin()->second;

        if (current.to_string() == pt2.to_string()) {
            break;
        }
        
        vector<GeoPoint> neighbors = m_data->get_connected_points(current);
        
        // add cost for every new point
        for (vector<GeoPoint>::iterator it = neighbors.begin(); it != neighbors.end(); it ++) {
            double new_cost = cost_so_far[current.to_string()] + distance_earth_km(current, *it);
            
            // update cost to lower value if faster route
            if (cost_so_far.find(it->to_string()) == cost_so_far.end() ||
                new_cost < cost_so_far[it->to_string()]) {
                cost_so_far[it->to_string()] = new_cost;
                // uses distance to end as priority in search
                next_points[distance_earth_km(*it, pt2)] = *it;
                came_from[it->to_string()] = current;
            }
        }
    }
    
    // find end point and return vector
    vector<GeoPoint> path;
    // if end point wasn't accessible then it isn't in came_from map
    if (came_from.find(pt2.to_string()) == came_from.end())
        return path;
    
    GeoPoint next = pt2;
    
    while (next.to_string() == pt1.to_string()) {
        path.push_back(next);
        next = came_from[next.to_string()];
    }
    path.push_back(pt1);
    return path;
    return points;
}
