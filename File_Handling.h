#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include "Laptop.h"
#include<fstream>
#include<iostream>

#define MAX_LAPTOPS 100

using namespace std;

// Save laptops to a structured .txt file using outFile
inline void saveLaptopsToFile(Laptop laptops[], int size, const string& filename) 
{
    ofstream outFile(filename); // Use 'outFile' as per convention

    if (!outFile) 
    {
        cerr << "   Failed to open file for saving.\n";
        return;
    }

    for (int i = 0; i < size; ++i) 
    {
        // Writing each record in structured format: name|brand|price
        outFile << laptops[i].name << "|" << laptops[i].brand << "|" << laptops[i].price << "\n";
    }

    outFile.close();
}

// Loading laptops from a .txt file using inFile and parse each record
inline int loadLaptopsFromFile(Laptop laptops[], const string& filename) 
{
    ifstream inFile(filename); // Use 'inFile' as per convention

    if (!inFile) 
    {
        cerr << "   Failed to open file for loading.\n";
        return 0;
    }

    int count = 0;
    string line;

    while (getline(inFile, line) && count < MAX_LAPTOPS) 
    {
        // Simulate file pointer tracking like in presentation
        streampos position = inFile.tellg(); // Position after reading this line

        // Parse line format: name|brand|price
        size_t pos1 = line.find('|');
        size_t pos2 = line.rfind('|');

        if (pos1 == string::npos || pos2 == string::npos || pos1 == pos2)
            continue;

        string name = line.substr(0, pos1);
        string brand = line.substr(pos1 + 1, pos2 - pos1 - 1);
        double price = stod(line.substr(pos2 + 1));

        laptops[count++] = Laptop(name, brand, price);
    }

    inFile.close();
    return count;
}

#endif // FILEHANDLING_H
