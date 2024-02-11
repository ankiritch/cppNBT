#ifndef NBT_H
#define NBT_H

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <variant>
#include <cstdint>
#include <memory>

class nbt {
    public:
        //Tags
        const char TAG_End{0x00};
        const char TAG_Byte{0x01};
        const char TAG_Short{0x02};
        const char TAG_Int{0x03};
        const char TAG_Long{0x04};
        const char TAG_Float{0x05};
        const char TAG_Double{0x06};
        const char TAG_Byte_Array{0x07};
        const char TAG_String{0x08};
        const char TAG_List{0x09};
        const char TAG_Compound{0x0a};
        const char TAG_Int_Array{0x0b};
        const char TAG_Long_Array{0x0c}; 
        

        nbt(std::string path, std::ios::openmode mode);
        void writeNBT(std::list<char> buffer);
        void setBuffer(std::list<char> newBuffer);



        //All possible data types, contain name, payload, and tag (lists: datatypeTag)
        //use vector later to store data

        //Forward declaration to use in NBT_DATATYPES
        struct BYTE;
        struct SHORT;
        struct INT;
        struct LONG;
        struct FLOAT;
        struct DOUBLE;
        struct BYTE_ARRAY;
        struct STRING;
        struct LIST;
        struct COMPOUND;
        struct INT_ARRAY;
        struct LONG_ARRAY;

        using NBT_DATATYPES = std::variant<BYTE, SHORT, INT, LONG, FLOAT, DOUBLE, BYTE_ARRAY, STRING, LIST, COMPOUND, INT_ARRAY, LONG_ARRAY>;
        using NBT_SINGLE_PAYLOAD_DATATYPES = std::variant<int8_t, int16_t, int32_t, int64_t, float, double, std::string>;
        using NBT_MULTI_PAYLOAD_DATATYPES = std::variant<std::list<int8_t>, std::list<int32_t>, std::list<int64_t>, std::list<std::string>, std::list<NBT_DATATYPES>>;
        using NBT_PAYLOAD_DATATYPES = std::variant<int8_t, int16_t, int32_t, int64_t, float, double, std::list<int8_t>, std::list<int32_t>, std::list<int64_t>, std::string, std::list<NBT_DATATYPES>>;


        void bufferNbtData(std::list<NBT_DATATYPES> nbtData);
        std::list<char> nbtDataToWritableArray(NBT_DATATYPES nbtData);

        struct BYTE {
            std::string name;
            int8_t payload;
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
            std::list<int8_t> payload;
            const char TAG{0x07};
        };

        struct STRING {
            std::string name;
            std::string payload;
            const char TAG{0x08};
        };

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
            std::list<int32_t> payload;
            const char TAG{0x0b};
        };

        struct LONG_ARRAY {
            std::string name;
            std::list<int64_t> payload;
            const char TAG{0x0c};
        };
    
    private:
        std::ofstream outfile;
        std::list<NBT_DATATYPES> nbt_data;
        std::list<char> buffer;

        void pushNumber(auto payload, std::list<char> &buffer);
};

#endif