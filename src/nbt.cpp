
#include <nbt.h>

#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <typeinfo>
#include <any>

void logToConsole(std::string m1, std::string m2="") {
    std::cout <<"[NBT]: "<< m1 + " " + m2 << std::endl;
}

nbt::NbtData::NbtData(NbtType typeArg, std::string nameArg, NbtPayloadTypes valueArg, NbtType listTypeArg) {
    type = typeArg;
    name = nameArg;
    payload = valueArg;
    payloadPtr = &payload;

    if (type == NbtType::LIST) {
        listType = listTypeArg;
    }

    if (!isCorrectType()) {
        throw std::runtime_error("Invalid type");
    }

    setTag();
}

nbt::NbtData::NbtData(NbtType typeArg, std::string nameArg, NbtPayloadTypes *valueArg, NbtType listTypeArg) {
    type = typeArg;
    name = nameArg;
    payloadPtr = valueArg;

    if (type == NbtType::LIST) {
        listType = listTypeArg;
    }

    if (!isCorrectType()) {
        throw std::runtime_error("Invalid type");
    }

    setTag();
}

nbt::NbtData::NbtData(NbtType typeArg, std::string nameArg, std::list<NbtData> valueArg, std::list<NbtData*> valuePtrArg, NbtType listTypeArg) {
    type = typeArg;
    name = nameArg;
    payload = valueArg;
    payloadPtr = nullptr;

    //Push all pointers to payload to list
    for (NbtData element : std::get<std::list<NbtData>>(payload)) {
        payloadPtrList.push_back(&element);
    }
    //Push all pointers to outside to list
    for (NbtData* element : valuePtrArg) {
        payloadPtrList.push_back(element);
    }

    if (type == NbtType::LIST) {
        listType = listTypeArg;
    }

    if (!isCorrectType()) {
        throw std::runtime_error("Invalid type");
    }
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

bool nbt::NbtData::intToCorrectType() {
    NbtPayloadTypes* currentPayloadPtr;
    std::list<int8_t> tempByteArray;
    std::list<int64_t> tempLongArray;
    try {
            switch (type) {
                case NbtType::BYTE:
                    setPayload(static_cast<int8_t>(std::get<int>(getPayload())));
                    return true;
                    break;
                case NbtType::SHORT:
                    setPayload(static_cast<int16_t>(std::get<int>(getPayload())));
                    return true;
                    break;
                case NbtType::INT:
                    setPayload(static_cast<int32_t>(std::get<int>(getPayload())));
                    return true;
                    break;
                case NbtType::LONG:
                    setPayload(static_cast<int64_t>(std::get<int>(getPayload())));
                    return true;
                    break;
                case NbtType::FLOAT:
                    setPayload(static_cast<float>(std::get<int>(getPayload())));
                    return true;
                    break;
                case NbtType::DOUBLE:
                    setPayload(static_cast<double>(std::get<int>(getPayload())));
                    return true;
                    break;
                case NbtType::BYTE_ARRAY:
                    currentPayloadPtr = getPayloadPtr();
                    for (int element : std::get<std::list<int>>(*currentPayloadPtr)) {
                        tempByteArray.push_back(static_cast<int8_t>(element));
                    }
                    *currentPayloadPtr = tempByteArray;
                    return true;
                    break;
                case NbtType::LONG_ARRAY:
                    currentPayloadPtr = getPayloadPtr();
                    for (int element : std::get<std::list<int>>(*currentPayloadPtr))  {
                        tempLongArray.push_back(static_cast<int64_t>(element));
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
    std::list<NbtData*> currentPayloadPtrList;
    if (type == NbtType::LIST) {
        try {
            currentPayloadPtrList = payloadPtrList;
        }
        catch (...) {
            logToConsole("Failed to get payloadPtrList");
            return false;
        }
    }

    switch (type) {
        case NbtType::BYTE:
            if (std::holds_alternative<int8_t>(getPayload())) {
                return true;
            }
            break;
        case NbtType::SHORT:
            if (std::holds_alternative<int16_t>(getPayload())) {
                return true;
            }
            break;
        case NbtType::INT:
            if (std::holds_alternative<int32_t>(getPayload())) {
                return true;
            }
            break;
        case NbtType::LONG:
            if (std::holds_alternative<int64_t>(getPayload())) {
                return true;
            }
            break;
        case NbtType::FLOAT:
            if (std::holds_alternative<float>(getPayload())) {
                return true;
            }
            break;
        case NbtType::DOUBLE:
            if (std::holds_alternative<double>(getPayload())) {
                return true;
            }
            break;
        case NbtType::BYTE_ARRAY:
            if (std::holds_alternative<std::list<int8_t>>(getPayload())) {
                return true;
            }
            break;
        case NbtType::STRING:
            if (std::holds_alternative<std::string>(getPayload())) {
                return true;
            }
            break;
        case NbtType::LIST:
            for (NbtData* elementPtr : currentPayloadPtrList) {
                NbtData element = *elementPtr;
                if (listType != element.type) {
                    throw std::runtime_error("List contains invalid type");
                }
                if ((!element.isCorrectType())) {
                        logToConsole(std::string(element.name) + " element in list conversion failed.");
                        return false;
                }

                *elementPtr = element;
            }
            return true;
            break;
        case NbtType::COMPOUND:
            if (std::holds_alternative<std::list<NbtData>>(getPayload())) {
                return true;
            }
            break;
        case NbtType::INT_ARRAY:
            if (std::holds_alternative<std::list<int32_t>>(getPayload())) {
                return true;
            }
            break;
        case NbtType::LONG_ARRAY:
            if (std::holds_alternative<std::list<int64_t>>(getPayload())) {
                return true;
            }
            break;
        default:
            return false;
            break;
    }
    if (intToCorrectType()) { //if not list try converting
        logToConsole(name, "type converted.");
        return true;
    }
    else {
        logToConsole(name, "conversion failed.");
        return false;
    }
};

bool nbt::NbtData::setPayload(NbtPayloadTypes newPayload) {
    NbtPayloadTypes oldPayload{payload};
    NbtPayloadTypes* oldPayloadPtr{payloadPtr};

    //set local, point to it
    payload = newPayload;
    payloadPtr = &payload;

    if (!isCorrectType()) {
        payload = oldPayload;
        payloadPtr = oldPayloadPtr;
        logToConsole(name , "attempted to set invalid type.");
    }

    return true;
}

bool nbt::NbtData::setPayload(NbtPayloadTypes *newPayload) {
    NbtPayloadTypes* oldPayloadPtr{payloadPtr};

    //point to original
    payloadPtr = newPayload;

    if (!isCorrectType()) {
        payloadPtr = oldPayloadPtr;
        logToConsole(name, "attempted to set invalid type.");
    }

    return true;
}

nbt::NbtPayloadTypes nbt::NbtData::getPayload() {
    if (type != NbtType::LIST) {
        return *payloadPtr;        
    } else {
        logToConsole("Unable to get payload from list, returning nullptr");
        return nullptr;
    }
}

nbt::NbtPayloadTypes* nbt::NbtData::getPayloadPtr() {

    if (type != NbtType::LIST) {
        return payloadPtr;
    } else {
        logToConsole(name, ": use getListPayloadPtr to get payload from list");
        return nullptr;
    }
}

std::list<nbt::NbtData*> nbt::NbtData::getPayloadPtrList() {
    return payloadPtrList;
}

std::list<nbt::NbtData*>* nbt::NbtData::getPayloadPtrListPtr() {
    return &payloadPtrList;
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

