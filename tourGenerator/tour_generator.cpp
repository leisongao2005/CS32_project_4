//
//  tour_generator.cpp
//  tourGenerator
//
//  Created by Leison Gao on 3/9/24.
//

#include "tour_generator.h"
#include "geotools.h"

using namespace std;
string getDirection(double path_angle);


vector<TourCommand> TourGenerator::generate_tour(const Stops& stops) const {
    vector<TourCommand> commands;
    
    for (int i = 0; i != stops.size(); i ++) {
        string poi_name, poi_commentary;
        stops.get_poi_data(i, poi_name, poi_commentary);
//        cout << "Welcome to " << p1_name << endl;
//        cout << "this is where you " << p1_commentary << endl;
        TourCommand comm = TourCommand();
        comm.init_commentary(poi_name, poi_commentary);
        commands.push_back(comm);
        
        if (i != stops.size() - 1) { // if there are more poi to visit
            
            // generate path to next poi
            GeoPoint curr_poi;
            GeoPoint next_poi;
            string next_poi_name, next_poi_commentary;
            
            // getting locations of pois
            if (!stops.get_poi_data(i + 1, next_poi_name, next_poi_commentary) ||
                !m_db->get_poi_location(poi_name, curr_poi) ||
                !m_db->get_poi_location(next_poi_name, next_poi)) {
                commands.clear();
                return commands;
            }
            
            vector<GeoPoint> path = m_router->route(curr_poi, next_poi);
            
            // create proceed commands for points on path
            if (path.size() == 0) {
                commands.clear();
                return commands;
            }
            else if (path.size() == 1) { // add single proceed form path to next
//                TourCommand proceed = TourCommand();
//                proceed.init_proceed(getDirection(angle_of_line(*curr, *(curr + 1))),
//                                     m_db->get_street_name(*curr, *(curr + 1)),
//                                     distance_earth_miles(*curr, *(curr + 1)),
//                                     *curr, *(curr + 1));
//                commands.push_back(proceed);
            }
            
            for (vector<GeoPoint>::iterator p1 = path.begin(); p1 != path.end() - 1; p1 ++) {
                vector<GeoPoint>::iterator p2 = p1 + 1;
                vector<GeoPoint>::iterator p3 = p1 + 2;
                
                TourCommand proceed = TourCommand();
                proceed.init_proceed(getDirection(angle_of_line(*p1, *p2)),
                                     m_db->get_street_name(*p1, *p2),
                                     distance_earth_miles(*p1, *p2),
                                     *p1, *p2);
                commands.push_back(proceed);
                
                if (p3 < path.end()) { // if there is a next path to check for a turn
//                    GeoPoint* fol_poi;
//                    string fol_poi_name, fol_poi_commentary;
//                    stops.get_poi_data(i + 2, fol_poi_name, fol_poi_commentary);
//                    m_db->get_poi_location(fol_poi_name, *fol_poi);
                    
                    double turn_angle = angle_of_turn(*p1, *p2, *p3);
                    string first_road = m_db->get_street_name(*p1, *p2);
                    string second_road = m_db->get_street_name(*p2, *p3);
                    if (turn_angle != 0 && first_road != second_road) {
                        TourCommand turn;
                        string direction;
                        if (turn_angle < 180)
                            direction = "left";
                        else
                            direction = "right";
                        turn.init_turn(direction, m_db->get_street_name(*p2, *p3));
                        // need to check if came from a poi, then turn not required
                        commands.push_back(turn);
                         
                    }
                }
            }
        }
    }
    
    
    return commands;
}

string getDirection(double path_angle) {
    if (path_angle < 22.5)
        return "east";
    else if (path_angle < 67.5)
        return "northeast";
    else if (path_angle < 112.5)
        return "north";
    else if (path_angle < 157.5)
        return "northwest";
    else if (path_angle < 202.5)
        return "west";
    else if (path_angle < 247.5)
        return "southwest";
    else if (path_angle < 292.5)
        return "south";
    else if (path_angle < 337.5)
        return "southeast";
    else
        return "east";
}
