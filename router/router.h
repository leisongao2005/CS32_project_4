//
//  router.hpp
//  router
//
//  Created by Leison Gao on 3/9/24.
//

#ifndef router_hpp
#define router_hpp

#include <stdio.h>
#include "base_classes.h"

class Router: public RouterBase
{
public:
    Router(const GeoDatabaseBase& geo_db): RouterBase(), m_data(&geo_db) {}
    virtual ~Router() {}
    virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const;
    
private:
    const GeoDatabaseBase* m_data;
    
};
#endif /* router_hpp */
