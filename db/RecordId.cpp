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

}
