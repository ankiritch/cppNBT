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


        void bufferNbtData(std::list<NBT_DATATYPES> nbtData);
        void writeNBT();
        std::list<char> nbtDataToBinaryArray(NBT_DATATYPES nbtData);

        struct BYTE {
            std::string name;
            uint8_t payload;
            const char TAG{0x01};

            std::string getName() {
                return name;
            }
            uint8_t getPayload() {
                return payload;
            }
            const char getTag() {
                return TAG;
            }
        };


        struct SHORT {
            std::string name;
            int16_t payload;
            const char TAG{0x02};

            std::string getName() {
                return name;
            }
            int16_t getPayload() {
                return payload;
            }
            const char getTag() {
                return TAG;
            }
        };

        struct INT {
            std::string name;
            int32_t payload;
            const char TAG{0x03};

            std::string getName() {
                return name;
            }
            int32_t getPayload() {
                return payload;
            }
            const char getTag() {
                return TAG;
            }
        };

        struct LONG {
            std::string name;
            int64_t payload;
            const char TAG{0x04};

            std::string getName() {
                return name;
            }
            int64_t getPayload() {
                return payload;
            }
            const char getTag() {
                return TAG;
            }
        };

        struct FLOAT {
            std::string name;
            float payload;
            const char TAG{0x05};

            std::string getName() {
                return name;
            }
            float getPayload() {
                return payload;
            }
            const char getTag() {
                return TAG;
            }
        };

        struct DOUBLE {
            std::string name;
            double payload;
            const char TAG{0x06};

            std::string getName() {
                return name;
            }
            double getPayload() {
                return payload;
            }
            const char getTag() {
                return TAG;
            }
        };

        struct BYTE_ARRAY {
            std::string name;
            std::list<uint8_t> payload;
            const char TAG{0x07};

            std::string getName() {
                return name;
            }
            std::list<uint8_t> getPayload() {
                return payload;
            }
            const char getTag() {
                return TAG;
            }
        };

        struct STRING {
            std::string name;
            std::string payload;
            const char TAG{0x08};

            std::string getName() {
                return name;
            }
            std::string getPayload() {
                return payload;
            }
            const char getTag() {
                return TAG;
            }
        };

        struct LIST {
            std::string name;
            char datatypeTag;
            std::list<NBT_DATATYPES> payload;
            const char TAG{0x09};

            std::string getName() {
                return name;
            }
            std::list<NBT_DATATYPES> getPayload() {
                return payload;
            }
            const char getTag() {
                return TAG;
            }
        };

        struct COMPOUND {
            std::string name;
            std::list<NBT_DATATYPES> payload;
            const char TAG{0x0a};

            std::string getName() {
                return name;
            }
            std::list<NBT_DATATYPES> getPayload() {
                return payload;
            }
            const char getTag() {
                return TAG;
            }
        };

        struct INT_ARRAY {
            std::string name;
            std::list<int32_t> payload;
            const char TAG{0x0b};

            std::string getName() {
                return name;
            }
            std::list<int32_t> getPayload() {
                return payload;
            }
            const char getTag() {
                return TAG;
            }
        };

        struct LONG_ARRAY {
            std::string name;
            std::list<int64_t> payload;
            const char TAG{0x0c};

            std::string getName() {
                return name;
            }
            std::list<int64_t> getPayload() {
                return payload;
            }
            const char getTag() {
                return TAG;
            }
        };

    private:
        std::ofstream outfile;
        std::list<NBT_DATATYPES> nbt_data;
        std::list<char> buffer;
};

#endif