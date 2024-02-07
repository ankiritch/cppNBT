#ifndef NBT_H
#define NBT_H

#include <iostream>
#include <fstream>
#include <list>
#include <variant>
#include <cstdint>
#include <memory>

class nbt {
    public:
        //Tags
        const char TAG_End{0x00};
        const char TAG_Byte{0x01};
        const char TAG_Short{0x02};
        const char TAG_char{0x03};
        const char TAG_Long{0x04};
        const char TAG_Float{0x05};
        const char TAG_Double{0x06};
        const char TAG_Byte_Array{0x07};
        const char TAG_String{0x08};
        const char TAG_List{0x09};
        const char TAG_Compound{0x0a};
        const char TAG_char_Array{0x0b};
        const char TAG_Long_Array{0x0c}; 
        

        nbt(std::string path, std::ios::openmode mode);
        
        void writeNBT();
        void setBuffer(std::list<char> newBuffer);

        //All possible data types, contain name, payload, and tag (LIST: datatypeTag)
        //use vector later to store data
        struct BYTE {
            std::string name;
            uint8_t payload;
            const char TAG{0x01};
        };

        struct SHORT {
            std::string name;
            int16_t payload;
            const char TAG{0x02};
        };

        struct INT {
            std::string name;
            int32_t payload;
            const char TAG{0x03};
        };

        struct LONG {
            std::string name;
            int64_t payload;
            const char TAG{0x04};
        };

        struct FLOAT {
            std::string name;
            float payload;
            const char TAG{0x05};
        };

        struct DOUBLE {
            std::string name;
            double payload;
            const char TAG{0x06};
        };

        struct BYTE_ARRAY {
            std::string name;
            std::list<uint8_t> payload;
            const char TAG{0x07};
        };

        struct STRING {
            std::string name;
            std::string payload;
            const char TAG{0x08};
        };

        //Forward declaration to use in NBT_DATATYPES
        struct LIST;
        struct COMPOUND;
        struct INT_ARRAY;
        struct LONG_ARRAY;

        using NBT_DATATYPES = std::variant<BYTE, SHORT, INT, LONG, FLOAT, DOUBLE, BYTE_ARRAY, STRING, LIST, COMPOUND, INT_ARRAY, LONG_ARRAY>;

        struct LIST {
            std::string name;
            char datatypeTag;
            std::list<NBT_DATATYPES> payload;
            const char TAG{0x09};
        };

        struct COMPOUND {
            std::string name;
            std::list<NBT_DATATYPES> payload;
            const char TAG{0x0a};
        };

        struct INT_ARRAY {
            std::string name;
            std::list<nbt::INT> payload;
        };

        struct LONG_ARRAY {
            std::string name;
            std::list<nbt::LONG> payload;
        };

    private:
        std::ofstream outfile;
        std::list<char> buffer;
};

#endif