#include <iostream>
#include <fstream>
#include <conio.h>
#include <list>

#include <nbt.h>


int main() {

    std::string path = "../data/data.dat";
    std::ios::openmode mode =std::ios::binary;



    nbt n(path, mode);

    nbt::NbtData myInt(nbt::NbtType::LONG, "myInt", 10);
    nbt::NbtData myOtherInt(nbt::NbtType::LONG, "myOtherInt", 20);

    nbt::NbtData myString(nbt::NbtType::STRING, "myString", "Hello World");

    nbt::NbtData myList(nbt::NbtType::LIST, "myList", std::list<nbt::NbtData>{myInt, myOtherInt}, nbt::NbtType::LONG);



    getch();
    return 0;

}