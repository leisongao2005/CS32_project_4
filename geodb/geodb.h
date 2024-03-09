//
//  geodb.hpp
//  geodb
//
//  Created by Leison Gao on 3/6/24.
//

#ifndef geodb_hpp
#define geodb_hpp

#include <stdio.h>
#include "base_classes.h"
#include "HashMap.h"

// only for debugging
#include <unordered_map>

class GeoDatabase: public GeoDatabaseBase
{
public:
    GeoDatabase(): GeoDatabaseBase() {}
    virtual ~GeoDatabase() {}
    virtual bool load(const std::string& map_data_file);
    virtual bool get_poi_location(const std::string& poi,
                                  GeoPoint& point) const;
    virtual std::vector<GeoPoint> get_connected_points(const GeoPoint& pt) const;
    virtual std::string get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const;
private:
    HashMap<GeoPoint> m_poiMap; // point of contact
    HashMap<std::vector<GeoPoint>> m_connectedPoints; // other points
    HashMap<std::string> m_streets; // hash with two coordinates together, key is street name

    
//    std::unordered_map<std::string, GeoPoint> m_poiMap; // point of contact
//    std::unordered_map<std::string, GeoPoint> m_connectedPoints; // other points
//    std::unordered_map<std::string, std::string> m_streets; // hash with two coordinates together, key is street name
};

/* 
 get_poi_location => O(1) on name
 get_connected_points => O(1) on points
 get_street_name => O(1) on points
 
 two hashtables? one for poi name and one for coordinates
 
 */
#endif /* geodb_hpp */
