#include <db/Catalog.h>
#include <db/TupleDesc.h>
#include <stdexcept>
#include <iostream>

using namespace db;

void Catalog::addTable(DbFile *file, const std::string &name, const std::string &pkeyField) {
    // TODO pa1.2: implement
    if(name.empty()){
        throw std::invalid_argument("Name Cannot Be Null.");
    }
    for(auto itr = tables.begin(); itr != tables.end(); itr ++){
        if(itr->first == name){
            tables.erase(name);
            break;
        }
        if(itr->second.file->getId() == file->getId()){
            tables.erase(itr->first);
            break;
        }

    }
    //if(tables.find(name) != tables.end()){}
    tables.emplace(name, Table(file, name, pkeyField));
}

int Catalog::getTableId(const std::string &name) const {
    // TODO pa1.2: implement
    auto itr = tables.find(name);
    if(itr == tables.end()){
        throw std::invalid_argument("Invalid Table Name.");
    }
    return itr->second.file->getId();
}

const TupleDesc &Catalog::getTupleDesc(int tableid) const {
    // TODO pa1.2: implement
    for(auto itr = tables.begin(); itr != tables.end(); itr++){
        if(itr->second.file->getId() == tableid){
            return itr->second.file->getTupleDesc();
        }
    }
    throw std::invalid_argument("Invalid Table ID.");
}

DbFile *Catalog::getDatabaseFile(int tableid) const {
    // TODO pa1.2: implement
    for(auto itr = tables.begin(); itr != tables.end(); itr++){
        if(itr->second.file->getId() == tableid){
            return itr->second.file;
        }
    }
    throw std::invalid_argument("Invalid Table ID.");
}

std::string Catalog::getPrimaryKey(int tableid) const {
    // TODO pa1.2: implement
    for(auto itr = tables.begin(); itr != tables.end(); itr++){
        if(itr->second.file->getId() == tableid){
            return itr->second.pkeyField;
        }
    }
    throw std::invalid_argument("Invalid Table ID.");
}

std::string Catalog::getTableName(int id) const {
    // TODO pa1.2: implement
    for(auto itr = tables.begin(); itr != tables.end(); itr++){
        if(itr->second.file->getId() == id){
            return itr->second.name;
        }
    }
    throw std::invalid_argument("Invalid Table ID.");
}

void Catalog::clear() {
    // TODO pa1.2: implement
    tables.clear();
}
