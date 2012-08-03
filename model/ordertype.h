#ifndef MODEL_ORDERTYPE_H
#define MODEL_ORDERTYPE_H

#include <QString>
#include "baseitem.h"

namespace Model {

class OrderType : public BaseItem
{
public:

    // order type constants
    enum OrderTypes {
        CASH=1,
        CUPON,
        DISCOUNT,
        FREE
    };

    OrderType(int id);
    OrderType(int id, const QString arabicName, QString englishName);
};

}
#endif // MODEL_ORDERTYPE_H
