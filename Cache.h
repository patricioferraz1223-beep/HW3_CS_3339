#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <fstream>

class Entry {
public:
    Entry();
    ~Entry();

    void set_tag(int _tag);
    int get_tag();

    void set_valid(bool _valid);
    bool get_valid();

    void set_ref(int _ref);
    int get_ref();

private:
    bool valid;
    unsigned tag;
    int ref;
};

class Cache {
public:
    Cache(int entries, int associativity);
    ~Cache();

    int get_index(unsigned long addr);
    int get_tag(unsigned long addr);

    bool hit(unsigned long addr);
    void update(unsigned long addr);

private:
    int assoc;
    unsigned num_entries;
    int num_sets;

    Entry **entries;
    int global_counter;
};

#endif