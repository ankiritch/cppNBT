#include <iostream>
#include <fstream>
#include <conio.h>
#include <list>

#include <nbt.h>


int main() {

    std::string path = "../data/data.dat";
    std::ios::openmode mode =std::ios::binary;



    nbt n(path, mode);

    std::list<nbt::NbtData> savedNbtData;

    nbt::NbtData myInt(nbt::NbtType::INT, "myInt", 10);
    nbt::NbtData myOtherInt(nbt::NbtType::INT, "myOtherInt", 20);

    nbt::NbtData myString(nbt::NbtType::STRING, "myString", "Hello World");

    nbt::NbtData myList(nbt::NbtType::LIST, "myList", std::list<nbt::NbtData>{myInt, myOtherInt}, nbt::NbtType::INT); //std::list<nbt::NbtData>{nbt::NbtData(nbt::NbtType::INT, "moreInt", 30)}, 

    nbt::NbtData myCompound(nbt::NbtType::COMPOUND, "myCompound", std::list<nbt::NbtData>{myString, myInt, myList});


    myInt.setPayload(20);

    // std::list<char> buffer = n.nbtToCharList(myCompound);

    // n.setBuffer(buffer);
    // n.writeNBT();

    std::list<int8_t> testBuffer{};
    n.pushData<int8_t>(25, testBuffer);

    getch();
    return 0;

}