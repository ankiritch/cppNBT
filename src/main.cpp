#include <iostream>
#include <fstream>
#include <conio.h>
#include <list>

#include <nbt.h>


int main() {

    std::string path = "../data/data.dat";
    std::ios::openmode mode =std::ios::binary;



    nbt n(path, mode);

    nbt::NbtData myInt(nbt::NbtType::INT, "myInt", 10);
    nbt::NbtData myString(nbt::NbtType::STRING, "myString", "Hello World");

    nbt::NbtData myCompound(nbt::NbtType::COMPOUND, "myCompound", std::list<nbt::NbtData>{myInt, myString});


    getch();
    return 0;

}