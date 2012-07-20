#include "order.h"

namespace Model {
    Order::Order(int aItemDetaildId) {
        this->itemDetailId = aItemDetaildId;
        this->quantity = 1;
        this->computeCash();
    }

    Order::Order(int aItemDetailId, int aQuantity, QStringList aComponentsIds, QStringList aAdditionalsIds) {
        this->itemDetailId = aItemDetailId;
        this->quantity = aQuantity;
        this->componentsIds = aComponentsIds;
        this->additionalsIds = aAdditionalsIds;
        this->computeCash();
    }

    void Order::computeCash() {
        this->cash = 0;
    }
}