#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Cache.h"

using namespace std;

//Forward declaration
class Cache;

int main(int argc, char* argv[]) 
{
    if (argc < 4) 
    {
        cout << "Usage:\n";
        cout << "./cache_sim num_entries associativity input_file\n";
        return 0;
    }

    int num_entries = atoi(argv[1]);
    int associativity = atoi(argv[2]);
    string input_filename = argv[3];

    ifstream input(input_filename);
    if (!input.is_open()) 
    {
        cerr << "Error opening input file.\n";
        return 1;
    }

    ofstream output("cache_sim_output");

    //Create cache
    Cache cache(num_entries, associativity);

    unsigned long addr;

    while (input >> addr) 
    {
        if (cache.hit(addr)) 
        {
            output << addr << " : HIT" << endl;
        }
        else 
        {
            output << addr << " : MISS" << endl;
            cache.update(addr);
        }
    }

    input.close();
    output.close();

    return 0;
}