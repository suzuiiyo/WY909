#include "dbormfactory.h"
DBOrm::Ptr DBOrmFactory::create(int type)
{
    DBOrm::Ptr ptr;
    if(type == TransientTaskConclusionRecordORM::Type)
        ptr = DBOrm::Ptr(new TransientTaskConclusionRecordORM());
    else if(type == TransientSwitchTaskConclusionRecordORM::Type)
        ptr = DBOrm::Ptr(new TransientSwitchTaskConclusionRecordORM());

    return ptr;
}
