
#include <nbt.h>

#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <typeinfo>

nbt::nbt(std::string path, std::ios::openmode mode) {
    outfile.open(path, mode);
}

void nbt::writeNBT(std::list<char> buffer) {
    for (char c : buffer) {
        outfile << c;
    }
}






using nbtVector = std::vector<std::variant<std::string, char, nbt::NBT_SINGLE_PAYLOAD_DATATYPES, nbt::NBT_MULTI_PAYLOAD_DATATYPES>>;

template <typename T>
struct nbtVisitor {
    nbtVector toReturn;

    nbtVector operator()(T nbtData) {
        std::visit([&](const auto& data) {
            toReturn.push_back(data.TAG);
            toReturn.push_back(data.name);
            toReturn.push_back(data.payload);

            if constexpr (std::is_same_v<decltype(data), nbt::LIST>) {
                toReturn.push_back(data.datatypeTag);
            }
        }, nbtData);
        return toReturn;
    }
};

void nbt::pushNumber(auto payload, std::list<char> &buffer) {
    for (int i = (sizeof(payload)-1); i >= 0; i--) {
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wconversion"
        buffer.push_back((payload >> 8*i) & 0xFF);
        #pragma GCC diagnostic pop
    }

    return;
}

std::list<char> nbt::nbtDataToWritableArray(NBT_DATATYPES nbtData) {
    std::list<char> buffer;

    //get nbt data as easily accessible vector
    nbtVector data = std::visit(nbtVisitor<decltype(nbtData)>{}, nbtData);
    
    
    //Compound, list, ... -> Call recursively, insert returned buffer arrays nbtInto buffer and create header
    //Other -> Return buffer

    char currentTag{std::get<char>(data[0])};
    std::string name = std::get<std::string>(data[1]);

    if ((currentTag <= 6 || currentTag == 8) && currentTag != 0) {
        //return header + payload as binary

        //Pushheader
        buffer.push_back(currentTag);
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wconversion"
        pushNumber((int16_t)name.size(), buffer); //name length size should be 2B
        #pragma GCC diagnostic pop
        for (char c : name) {
            buffer.push_back(c);
        }

        //Push payload     

        NBT_SINGLE_PAYLOAD_DATATYPES payload = std::get<NBT_SINGLE_PAYLOAD_DATATYPES>(data[2]);

        switch (currentTag) { //1: Byte, 2: Short, 3: Int, 4: Long, 5: Float, 6: Double, 8: String
            case 1: {
                int8_t typePayload = std::get<int8_t>(payload);
                pushNumber(typePayload, buffer);
                break;
            }
            case 2: {
                int16_t typePayload = std::get<int16_t>(payload);
                pushNumber(typePayload, buffer);
                break;
            }
            case 3: {
                int32_t typePayload = std::get<int32_t>(payload);
                pushNumber(typePayload, buffer);
                break;
            }
            case 4: {
                int64_t typePayload = std::get<int64_t>(payload);
                pushNumber(typePayload, buffer);
                break;
            }
            case 5: {
                float typePayload = std::get<float>(payload);
                pushNumber(static_cast<int32_t>(typePayload), buffer);
                break;
            }
            case 6: {
                double typePayload = std::get<double>(payload);
                pushNumber(static_cast<int64_t>(typePayload), buffer);
                break;
            }
            case 8: {
                std::string typePayload = std::get<std::string>(payload);
                for (char c : typePayload) {
                    buffer.push_back(c);
                }
                break;
            }
        }


    } else {
        //this header + call on each direct child
    }

    return buffer;
}

void nbt::bufferNbtData(std::list<NBT_DATATYPES> nbtData) {
    for (NBT_DATATYPES n : nbtData) {
        
    }
}

void nbt::setBuffer(std::list<char> newBuffer) {
    buffer = newBuffer;
}

