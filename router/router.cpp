//
//  router.cpp
//  router
//
//  Created by Leison Gao on 3/9/24.
//

#include "router.h"
#include "geotools.h"
#include "base_classes.h"
#include <map>
#include <unordered_map>
#include <algorithm>
using namespace std;

//
//vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const {
//    vector<GeoPoint> path;
//    if (pt1.to_string() == pt2.to_string()) {
//        path.push_back(pt1);
//        return path;
//    }
//
//    queue<GeoPoint> points;
//    points.push(pt1);
//    unordered_map<GeoPoint*, bool> visited;
//    unordered_map<GeoPoint*, double> dist;
//    unordered_map<const GeoPoint*, GeoPoint*> cameFrom;
//    
//    while (!points.empty()) {
//        GeoPoint* curr = &points.front();
//        if (curr->to_string() == pt2.to_string())
//            break; // found exit
//        
//        vector<GeoPoint> adj = m_data->get_connected_points(points.front());
//        for (int i = 0; i != adj.size(); i ++) {
////            GeoPoint* neighbor = new GeoPoint(adj[i]);
//            GeoPoint* neighbor = &adj[i];
//            if (!visited[neighbor]) {
//                visited[neighbor] = true;
//                dist[neighbor] = dist[curr] + distance_earth_miles(*neighbor, *curr);
//                cameFrom[neighbor] = curr;
//                points.push(*neighbor);
//            }
//            else if (dist[curr] + distance_earth_miles(*neighbor, *curr) < dist[neighbor]){
//                // if path is shorter update
//                dist[neighbor] = dist[curr] + distance_earth_miles(*neighbor, *curr);
//                cameFrom[neighbor] = curr;
//                points.push(*neighbor);
//            }
//        }
//        points.pop();
//    }
//    const GeoPoint* next = &pt2;
//    for (unordered_map<const GeoPoint*, GeoPoint*>::iterator it = cameFrom.begin();
//         it != cameFrom.end(); it ++)
//        cout << it->first->to_string() << endl;
//    if (cameFrom.find(next) == cameFrom.end()) {
//        cout << "not in path" << endl;
//        return path;
//    }
//    
//    while (next->to_string() != pt1.to_string()) {
//        path.push_back(*next);
//        next = cameFrom[next];
//    }
//    path.push_back(pt1);
//    cout << "looking for path with size: " << path.size() << endl;
//    return path;
//}



//class Node {
//public:
//    Node(double weight, const GeoPoint pt): m_weight(weight), m_pt(pt) {};
//    double getWeight() const {return m_weight;}
//    GeoPoint& getPoint() const {return m_pt;}
//    bool operator<(const Node &rhs) const {return m_weight < rhs.m_weight;}
//private:
//    double m_weight;
//    GeoPoint m_pt;
//};
//
//struct LessThanByWeight {
//    bool operator()(Node const & lhs, Node const & rhs) {
//        return lhs.getWeight() < rhs.getWeight();
//    }
//};
//
//vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const {
//    vector<GeoPoint> points;
//    if (pt1.to_string() == pt2.to_string()) {
//        points.push_back(pt1);
//        return points;
//    }
////    priority_queue<Node, std::vector<Node>, LessThanByWeight> openSet;
//    multimap<double, GeoPoint> openSet;
//    map<GeoPoint, GeoPoint> cameFrom;
//    unordered_map<GeoPoint, double> gscore;  // distance from beginning
//    // make sure to check if value exists in map before inserting
//    gscore[pt1] = 0;
//    unordered_map<GeoPoint, double> fscore; // distance from end
//    fscore[pt1] = distance_earth_miles(pt1, pt2); // using distance as heuristic
//    
//    while (!openSet.empty()) {
//        GeoPoint current = openSet.begin()->second;
//        
//        if (current.to_string() == pt2.to_string()) {
//            break; // finished
//        }
//        
//        openSet.erase(openSet.begin()); // removes current point from openSet
//        
//        vector<GeoPoint> adj = m_data->get_connected_points(current);
//        for (int i = 0; i != adj.size(); i ++) {
//            double newscore = gscore[current] + distance_earth_miles(current, adj[i]);
//            GeoPoint neighbor = adj[i];
//            if (gscore.find(neighbor) == gscore.end()) { // value doesn't exist, must initialize
//                gscore[neighbor] = newscore;
//            }
//            else if (newscore < gscore[neighbor]) {
//                cameFrom[neighbor] = current;
//                gscore[neighbor] = newscore;
//                fscore[neighbor] = newscore + distance_earth_miles(neighbor, pt2);
//                // check if neighbor is in openset, if not add them
//                bool inset = false;
//                for (multimap<double, GeoPoint>::iterator it = openSet.begin();
//                     it != openSet.end(); it ++) {
//                    if (it->second.to_string() == neighbor.to_string())
//                        inset = true;
//                }
//                if (!inset) {
//                    openSet.insert({fscore[neighbor], neighbor});
//                }
//            }
//        }
//    }
//    // find end point and return vector
//    vector<GeoPoint> path;
//    // if end point wasn't accessible then it isn't in came_from map
//    if (cameFrom.find(pt2) == cameFrom.end())
//        return path;
//
//    GeoPoint next = pt2;
//
//    while (next.to_string() != pt1.to_string()) {
//        path.push_back(next);
//        next = cameFrom[next];
//    }
//    path.push_back(pt1);
//    return path;
//    return points;
//}


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
        next_points.erase(next_points.begin());

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
    
    while (next.to_string() != pt1.to_string()) {
        path.push_back(next);
        next = came_from[next.to_string()];
    }
    path.push_back(pt1);
    reverse(path.begin(), path.end());
    return path;
    return points;
}
