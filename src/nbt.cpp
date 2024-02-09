
#include <nbt.h>

#include <iostream>
#include <string>



nbt::nbt(std::string path, std::ios::openmode mode) {
    outfile.open(path, mode);
}

void nbt::writeNBT() {  
    for (char c : buffer) {
        outfile << c;
    }
}

std::list<char> nbt::nbtDataToBinaryArray(NBT_DATATYPES nbtData) {
    std::list<char> buffer;
    
    //Compound, list, ... -> Call recursively, insert returned buffer arrays into buffer and create header
    //Other -> Return buffer array


    return buffer;
}

void nbt::bufferNbtData(std::list<NBT_DATATYPES> nbtData) {
    for (NBT_DATATYPES n : nbtData) {
        
    }
}