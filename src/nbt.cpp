
#include <nbt.h>

#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <typeinfo>
#include <any>

nbt::NbtData::NbtData(NbtType typeArg, std::string nameArg, NbtPayloadTypes valueArg, NbtType listTypeArg) {
    type = typeArg;
    name = nameArg;
    payload = valueArg;

    if (type == NbtType::LIST) {
        listType = listTypeArg;
    }

    if (!isCorrectType()) {
        throw std::runtime_error("Invalid type");
    }

    setTag();
}

void nbt::NbtData::setTag() {
    switch (type) {
        case NbtType::BYTE:
            tag = TAG_Byte;
            break;
        case NbtType::SHORT:
            tag = TAG_Short;
            break;
        case NbtType::INT:
            tag = TAG_Int;
            break;
        case NbtType::LONG:
            tag = TAG_Long;
            break;
        case NbtType::FLOAT:
            tag = TAG_Float;
            break;
        case NbtType::DOUBLE:
            tag = TAG_Double;
            break;
        case NbtType::BYTE_ARRAY:
            tag = TAG_Byte_Array;
            break;
        case NbtType::STRING:
            tag = TAG_String;
            break;
        case NbtType::LIST:
            tag = TAG_List;
            break;
        case NbtType::COMPOUND:
            tag = TAG_Compound;
            break;
        case NbtType::INT_ARRAY:
            tag = TAG_Int_Array;
            break;
        case NbtType::LONG_ARRAY:
            tag = TAG_Long_Array;
            break;

        case NbtType::NONE:
            break;

    }
}

bool nbt::NbtData::convertToCorrectType() {
    try {
            switch (type) {
                case NbtType::BYTE:
                    payload = static_cast<int8_t>(std::get<int>(payload));
                    return true;
                    break;
                case NbtType::SHORT:
                    payload = static_cast<int16_t>(std::get<int>(payload));
                    return true;
                    break;
                case NbtType::INT:
                    payload = static_cast<int32_t>(std::get<int>(payload));
                    return true;
                    break;
                case NbtType::LONG:
                    payload = static_cast<int64_t>(std::get<int>(payload));
                    return true;
                    break;
                case NbtType::FLOAT:
                    payload = static_cast<float>(std::get<int>(payload));
                    return true;
                    break;
                case NbtType::DOUBLE:
                    payload = static_cast<double>(std::get<int>(payload));
                    return true;
                    break;
                case NbtType::BYTE_ARRAY:
                    for (auto &element : std::get<std::list<int>>(payload))  {
                        element = static_cast<int8_t>(element);
                    }
                    return true;
                    break;
                case NbtType::LONG_ARRAY:
                    for (auto &element : std::get<std::list<int>>(payload))  {
                        element = static_cast<int64_t>(element);
                    }
                    return true;
                    break;
                default:
                    return false; //string, list, compound, int_array do not have directly convertible payload
                    break;
            }
        }
        catch (...) {
            return false;
        }
}


bool nbt::NbtData::isCorrectType() {
    switch (type) {
        case NbtType::BYTE:
            if (std::holds_alternative<int8_t>(payload)) {
                return true;
            }
            break;
        case NbtType::SHORT:
            if (std::holds_alternative<int16_t>(payload)) {
                return true;
            }
            break;
        case NbtType::INT:
            if (std::holds_alternative<int32_t>(payload)) {
                return true;
            }
            break;
        case NbtType::LONG:
            if (std::holds_alternative<int64_t>(payload)) {
                return true;
            }
            break;
        case NbtType::FLOAT:
            if (std::holds_alternative<float>(payload)) {
                return true;
            }
            break;
        case NbtType::DOUBLE:
            if (std::holds_alternative<double>(payload)) {
                return true;
            }
            break;
        case NbtType::BYTE_ARRAY:
            if (std::holds_alternative<std::list<int8_t>>(payload)) {
                return true;
            }
            break;
        case NbtType::STRING:
            if (std::holds_alternative<std::string>(payload)) {
                return true;
            }
            break;
        case NbtType::LIST:
        //check if all NbtData is of correct type, if not convert, if not convertable return false
            if (std::holds_alternative<std::list<NbtData>>(payload)) { 
                for (NbtData &element : std::get<std::list<NbtData>>(payload)) {
                    if (listType != element.type) {
                        throw std::runtime_error("List contains invalid type");
                    }
                    if ((!element.isCorrectType())) {
                        if (!element.convertToCorrectType()) {
                            return false;
                        }
                    }
                }
                return true;
            }
            break;
        case NbtType::COMPOUND:
            if (std::holds_alternative<std::list<NbtData>>(payload)) {
                return true;
            }
            break;
        case NbtType::INT_ARRAY:
            if (std::holds_alternative<std::list<int32_t>>(payload)) {
                return true;
            }
            break;
        case NbtType::LONG_ARRAY:
            if (std::holds_alternative<std::list<int64_t>>(payload)) {
                return true;
            }
            break;
        default:
            return false;
            break;
    }
    if (convertToCorrectType()) { //if not list try converting
        std::cout << name << " type converted.\n";
        return true;
    }
    else {
        std:: cout << name << " conversion failed.\n";
        return false;
    }
};

bool nbt::NbtData::setPayload(NbtPayloadTypes newPayload) {
    payload = newPayload;
    return true;
}

nbt::nbt(std::string path, std::ios::openmode mode) {
    outfile.open(path, mode);
}

void nbt::writeNBT(std::list<char> buffer) {
    for (char c : buffer) {
        outfile << c;
    }
}

void nbt::pushNumber(auto payload, std::list<char> &buffer) {
    for (int i = (sizeof(payload)-1); i >= 0; i--) {
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wconversion"
        buffer.push_back((payload >> 8*i) & 0xFF);
        #pragma GCC diagnostic pop
    }

    return;
}

void nbt::setBuffer(std::list<char> newBuffer) {
    buffer = newBuffer;
}
