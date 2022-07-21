#ifndef DBORMFACTORY_H
#define DBORMFACTORY_H
#include "dborm.h"
class DBOrmFactory
{
public:
    static DBOrm::Ptr create(int type);
};
#endif // DBORMFACTORY_H
