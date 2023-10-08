#include <db/Tuple.h>
#include <db/Field.h>
#include <iostream>

using namespace db;

//
// Tuple
//

// TODO pa1.1: implement
Tuple::Tuple(const TupleDesc &td, RecordId *rid): td(&td){
    if (td.numFields() < 1) {
        throw std::invalid_argument("TupleDesc must have at least one field.");
    }
    this->rid = rid;
    this->contents = std::vector<const Field*>(td.numFields(), nullptr);
}

const TupleDesc &Tuple::getTupleDesc() const {
    // TODO pa1.1: implement
    return *td;
}

const RecordId *Tuple::getRecordId() const {
    // TODO pa1.1: implement
    return rid;
}

void Tuple::setRecordId(const RecordId *id) {
    // TODO pa1.1: implement
    this->rid = id;
}

const Field &Tuple::getField(int i) const {
    // TODO pa1.1: implement
    const Field* f = contents[i];
    if(contents[i] == nullptr){
        std::cout << "POINTER IS NULL"<< std::endl;
    }
    return *f;
}

void Tuple::setField(int i, const Field *f) {
    // TODO pa1.1: implement
    if (i < 0 || i >= td->numFields()) {
        throw std::invalid_argument("Index Out Of Range.");
    }
    this->contents[i] = f;
}

Tuple::iterator Tuple::begin() const {
    // TODO pa1.1: implement
    return contents.begin();
}

Tuple::iterator Tuple::end() const {
    // TODO pa1.1: implement
    return contents.end();
}

std::string Tuple::to_string() const {
    // TODO pa1.1: implement
    if(contents.empty()){
        return "EMPTY TUPLE.";
    }
    std::string tp_str = "";
    for(int i = 0; i < contents.size(); i++){
        const Field *f = contents[i];
        if(f == nullptr){
            tp_str += "NULL; ";
        }else{
            tp_str += f->to_string() + "; ";
        }
    }
    return tp_str;
}
