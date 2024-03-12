//
//  tour_generator.hpp
//  tourGenerator
//
//  Created by Leison Gao on 3/9/24.
//

#ifndef tour_generator_hpp
#define tour_generator_hpp

#include "base_classes.h"
#include <stdio.h>
class TourGenerator: public TourGeneratorBase
{
public:
    TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router): TourGeneratorBase(), m_db(&geodb), m_router(&router) {}
    virtual ~TourGenerator();
    virtual std::vector<TourCommand> generate_tour(const Stops& stops) const;
private:
    const GeoDatabaseBase* m_db;
    const RouterBase* m_router;
};
#endif /* tour_generator_hpp */
