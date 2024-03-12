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
        string name, commentary;
        stops.get_poi_data(i, name, commentary);
        
        TourCommand comm = TourCommand();
        comm.init_commentary(name, commentary);
        commands.push_back(comm);
        
        if (i != stops.size() - 1) { // if there are more poi to visit
            GeoPoint poi_start, poi_end;
            string next_poi_name;
            stops.get_poi_data(i + 1, next_poi_name, commentary);
            m_db->get_poi_location(name, poi_start);
            m_db->get_poi_location(next_poi_name, poi_end);
            vector<GeoPoint> path = m_router->route(poi_start, poi_end);
            
            vector<GeoPoint>::iterator prev = path.begin();
            for (vector<GeoPoint>::iterator curr = path.begin() + 1; curr != path.end(); curr ++) {
                TourCommand proceed = TourCommand();
                proceed.init_proceed(getDirection(angle_of_line(*prev, *curr)),
                                     m_db->get_street_name(*prev, *curr),
                                     distance_earth_miles(*prev, *curr),
                                     *prev, *curr);
                commands.push_back(proceed);
                if (curr + 1 != path.end()) { // if there is a next path to check for a turn
                    vector<GeoPoint>::iterator next = curr + 1;
                    string p3_name;
                    GeoPoint p3;
                    stops.get_poi_data(i + 2, p3_name, commentary);
                    m_db->get_poi_location(p3_name, p3);
                    
                    double turn_angle = angle_of_turn(poi_start, poi_end, p3);
                    if (turn_angle != 0) {
                        TourCommand turn;
                        string direction;
                        if (turn_angle < 180)
                            direction = "left";
                        else
                            direction = "right";
                        turn.init_turn(direction, m_db->get_street_name(poi_end, p3));
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
