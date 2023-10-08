#include <db/HeapPage.h>
#include <cmath>

using namespace db;

HeapPageIterator::HeapPageIterator(int i, const HeapPage *page) {
    this->slot = i;
    this->page = page;
    while (slot < page->numSlots && !page->isSlotUsed(slot)) {
        slot++;
    }
}

bool HeapPageIterator::operator!=(const HeapPageIterator &other) const {
    return slot != other.slot || page != other.page;
}

HeapPageIterator &HeapPageIterator::operator++() {
    do {
        slot++;
    } while (slot < page->numSlots && !page->isSlotUsed(slot));
    return *this;
}

Tuple &HeapPageIterator::operator*() const {
    return page->tuples[slot];
}

HeapPage::HeapPage(const HeapPageId &id, uint8_t *data) : pid(id) {
    this->td = Database::getCatalog().getTupleDesc(id.getTableId());
    this->numSlots = getNumTuples();

    // Allocate and read the header slots of this page
    size_t header_size = getHeaderSize();
    header = new uint8_t[header_size];
    memcpy(header, data, header_size);
    size_t offset = header_size;

    tuples = new Tuple[numSlots];
    //std::cout << numSlots << std::endl;
    for (int slot = 0; slot < numSlots; slot++) {
        if (isSlotUsed(slot)) {
            //std::cout << slot << std::endl;//COUT REACH EVERY SLOT
            readTuple(tuples + slot, data + offset, slot);
        }
        offset += td.getSize();
    }
}

int HeapPage::getNumTuples() {
    // TODO pa1.4: implement
    //floor((BufferPool.getPageSize()*8) / (tuple size * 8 + 1))
    int pgSize =Database::getBufferPool().getPageSize();
    int tpSize = (int)Database::getCatalog().getTupleDesc(pid.getTableId()).getSize();
    return floor((pgSize * 8) / (tpSize * 8 +1));
}

int HeapPage::getHeaderSize() {
    // TODO pa1.4: implement
    //header bytes = page size - tuples per page * tuple size
    return Database::getBufferPool().getPageSize() - (getNumTuples()*((int)Database::getCatalog().getTupleDesc(pid.getTableId()).getSize()));

}

PageId &HeapPage::getId() {
    // TODO pa1.4: implement
    return pid;
}

void HeapPage::readTuple(Tuple *t, uint8_t *data, int slotId) {
    new(t) Tuple(td, new RecordId(&pid, slotId));
    int i = 0;
    for (const auto &item: td) {
        Types::Type type = item.fieldType;
        const Field *f = Types::parse(data, type);
        data += Types::getLen(type);
        t->setField(i, f);
        i++;
    }
}

void *HeapPage::getPageData() {
    auto *data = createEmptyPageData();
    size_t header_size = getHeaderSize();

    // Create the header of the page
    memcpy(data, header, header_size);
    size_t offset = header_size;
    // Create the tuples
    for (int i = 0; i < numSlots; i++) {
        const Tuple &tuple = tuples[i];
        // Empty slot
        if (!isSlotUsed(i)) {
            memset(data + offset, 0, td.getSize());
            offset += td.getSize();
        } else {
            // Non-empty slot
            for (int j = 0; j < td.numFields(); j++) {
                const Field &f = tuple.getField(j);
                f.serialize(data + offset);
                offset += Types::getLen(f.getType());
            }
        }
    }

    return data;
}

uint8_t *HeapPage::createEmptyPageData() {
    int len = Database::getBufferPool().getPageSize();
    return new uint8_t[len]{}; // all 0
}


int HeapPage::getNumEmptySlots() const {
    // TODO pa1.4: implement
    int NumEmptySlots = 0;
    for(int i = 0; i < this->numSlots; i++){
        if(!isSlotUsed(i)){
            NumEmptySlots ++;
        }
    }
    return NumEmptySlots;
}

bool HeapPage::isSlotUsed(int i) const {
    // TODO pa1.4: implement
    return (header[i / 8] & (1 << (i % 8))) != 0;
}

HeapPageIterator HeapPage::begin() const {
    // TODO pa1.4: implement
    HeapPageIterator begin_itr = HeapPageIterator(0,this);
    return begin_itr;
}

HeapPageIterator HeapPage::end() const {
    // TODO pa1.4: implement
    HeapPageIterator end_itr = HeapPageIterator(numSlots, this);
    return end_itr;
}
