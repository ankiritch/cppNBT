
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

void nbt::setBuffer(std::list<char> newBuffer) {
    buffer = newBuffer;
}