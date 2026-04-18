#include <iostream>
#include <fstream>
#include <climits>
#include "Cache.h"

Entry::Entry() 
{
    valid = false;
    tag = 0;
    ref = 0;
}

Entry::~Entry() {}

void Entry::set_tag(int _tag) { tag = _tag; }
int Entry::get_tag() { return tag; }

void Entry::set_valid(bool _valid) { valid = _valid; }
bool Entry::get_valid() { return valid; }

void Entry::set_ref(int _ref) { ref = _ref; }
int Entry::get_ref() { return ref; }


Cache::Cache(int entries, int associativity) 
{
    assoc = associativity;
    num_entries = entries;
    num_sets = num_entries / assoc;
    global_counter = 0;

    this->entries = new Entry*[num_sets];
    for (int i = 0; i < num_sets; i++) 
    {
        this->entries[i] = new Entry[assoc];
    }
}

Cache::~Cache() {
    for (int i = 0; i < num_sets; i++) 
    {
        delete[] entries[i];
    }
    delete[] entries;
}

int Cache::get_index(unsigned long addr) 
{
    return addr % num_sets;
}

int Cache::get_tag(unsigned long addr) 
{
    return addr / num_sets;
}

bool Cache::hit(unsigned long addr) 
{
    int index = get_index(addr);
    int tag = get_tag(addr);

    for (int i = 0; i < assoc; i++) 
    {
        if (entries[index][i].get_valid() &&
            entries[index][i].get_tag() == tag) 
            {
            return true;
        }
    }
    return false;
}

void Cache::update(unsigned long addr) {
    int index = get_index(addr);
    int tag = get_tag(addr);

    global_counter++;

    //empty slot first
    for (int i = 0; i < assoc; i++) {
        if (!entries[index][i].get_valid()) {
            entries[index][i].set_valid(true);
            entries[index][i].set_tag(tag);
            entries[index][i].set_ref(global_counter);
            return;
        }
    }

    //FIFO replacement
    int min_ref = INT_MAX;
    int replace_idx = 0;

    for (int i = 0; i < assoc; i++) 
    {
        if (entries[index][i].get_ref() < min_ref)
        {
            min_ref = entries[index][i].get_ref();
            replace_idx = i;
        }
    }

    entries[index][replace_idx].set_tag(tag);
    entries[index][replace_idx].set_ref(global_counter);
}