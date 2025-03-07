#include <db/HeapPageId.h>
#include <iostream>

using namespace db;

//
// HeapPageId
//

// TODO pa1.4: implement
HeapPageId::HeapPageId(int tableId, int pgNo) {
    this->tableId = tableId;
    this->pgNo = pgNo;
}

int HeapPageId::getTableId() const {
    // TODO pa1.4: implement
    return tableId;
}

int HeapPageId::pageNumber() const {
    // TODO pa1.4: implement
    return pgNo;
}

bool HeapPageId::operator==(const PageId &other) const {
    if (const auto *otherPageId = dynamic_cast<const HeapPageId *>(&other)) {
        // TODO pa1.4: implement
        return (this->tableId == other.getTableId()) && (this->pgNo == other.pageNumber());
    }
    return false;
}
