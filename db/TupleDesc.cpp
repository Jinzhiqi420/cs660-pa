#include <db/TupleDesc.h>
#include <vector>
#include <iostream>

using namespace db;

//
// TDItem
//

bool TDItem::operator==(const TDItem &other) const {
    // TODO pa1.1: implement (Y)
    return this->to_string() == other.to_string();
}

std::size_t std::hash<TDItem>::operator()(const TDItem &r) const {
    // TODO pa1.1: implement ???????????
    std::size_t hashValue = 0;
    return hashValue;
}

//
// TupleDesc
//

// TODO pa1.1: implement
TupleDesc::TupleDesc(const std::vector<Types::Type> &types) {
    this->types = types;
    this->names = std::vector<std::string>(types.size(), "");
    for(int i = 0; i < types.size(); i++){
        this->items.push_back(TDItem(types[i],names[i]));
    }
}

// TODO pa1.1: implement
TupleDesc::TupleDesc(const std::vector<Types::Type> &types, const std::vector<std::string> &names) {
    this->types = types;
    this->names = names;
    for(int i = 0; i < types.size(); i++){
        this->items.push_back(TDItem(types[i],names[i]));
    }
}

size_t TupleDesc::numFields() const {
    // TODO pa1.1: implement
    //return types.size();
    return items.size();
}

std::string TupleDesc::getFieldName(size_t i) const {
    // TODO pa1.1: implement
    return names[i];
}

Types::Type TupleDesc::getFieldType(size_t i) const {
    // TODO pa1.1: implement
    return types[i];
}

int TupleDesc::fieldNameToIndex(const std::string &fieldName) const {
    // TODO pa1.1: implement
    for(int i = 0; i < names.size(); i++){
        if(names[i] == fieldName){
            return i;
        }
    }
    throw std::invalid_argument("Name Cannot be Found.");
}

size_t TupleDesc::getSize() const {
    // TODO pa1.1: implement
    size_t total_size = 0;
    for(int i = 0; i < types.size(); i++){
        total_size += getLen(types[i]);
    }
    return total_size;
}

TupleDesc TupleDesc::merge(const TupleDesc &td1, const TupleDesc &td2) {
    // TODO pa1.1: implement
    std::vector<Types::Type> new_types;
    std::vector<std::string> new_names;
    for(int i = 0; i < td1.numFields(); i++){
        new_types.push_back(td1.getFieldType(i));
        new_names.push_back(td1.getFieldName(i));
    }
    for(int j = 0; j < td2.numFields(); j++){
        new_types.push_back(td2.getFieldType(j));
        new_names.push_back(td2.getFieldName(j));
    }
    return TupleDesc(new_types, new_names);

}

std::string TupleDesc::to_string() const {
    // TODO pa1.1: implement
    std::string td_str;
    for(int i = 0; i < items.size(); i++){
        td_str += items[i].to_string() + "; ";
    }
    return td_str;
}

bool TupleDesc::operator==(const TupleDesc &other) const {
    // TODO pa1.1: implement
    if((this->numFields() != other.numFields()) || (this->names.size() != other.names.size())){
        return false;
    }
    for(int i = 0; i < other.numFields(); i++){
        if(this->getFieldType(i) != other.getFieldType(i)){
            return false;
        }
    }
    return true;
}

TupleDesc::iterator TupleDesc::begin() const {
    return items.begin();
}

TupleDesc::iterator TupleDesc::end() const {
    // TODO pa1.1: implement
    return items.end();
}

std::size_t std::hash<db::TupleDesc>::operator()(const db::TupleDesc &td) const {
    // TODO pa1.1: implement
    std::size_t hashValue = 0;
    return hashValue;
}
