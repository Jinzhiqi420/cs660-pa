#include <db/RecordId.h>
#include <stdexcept>

using namespace db;

//
// RecordId
//

// TODO pa1.4: implement
RecordId::RecordId(const PageId *pid, int tupleno) {
    this->pid = pid;
    this->tupleno = tupleno;
}

bool RecordId::operator==(const RecordId &other) const {
    // TODO pa1.4: implement
    return (this->pid == other.getPageId()) && (this->tupleno == other.getTupleno());
}

const PageId *RecordId::getPageId() const {
    // TODO pa1.4: implement
    return pid;
}

int RecordId::getTupleno() const {
    // TODO pa1.4: implement
    return tupleno;
}

//
// RecordId hash function
//

std::size_t std::hash<RecordId>::operator()(const RecordId &r) const {
    // TODO pa1.4: implement
    std::size_t hash_val;
    hash_val = std::hash<int>()(r.getTupleno())
            + std::hash<int>()(r.getPageId()->getTableId())
              + std::hash<int>()(r.getPageId()->pageNumber());
    return hash_val;

}
