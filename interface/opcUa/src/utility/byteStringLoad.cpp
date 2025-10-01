#include <fstream>
#include <utility/byteStringLoad.hpp>
#include <vector>

namespace Interface {

ByteStringLoad::ByteStringLoad()
  : value{} {}

ByteStringLoad::ByteStringLoad(const std::string& path)
  : value{} {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        value.data   = nullptr;
        value.length = 0;
        return;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
        value.data   = nullptr;
        value.length = 0;
        return;
    }

    value.length = static_cast<UA_Int32>(size);
    value.data   = static_cast<UA_Byte*>(UA_malloc(size));
    if (value.data)
        std::copy(buffer.begin(), buffer.end(), value.data);
}

ByteStringLoad::~ByteStringLoad() {
    UA_ByteString_clear(&value);
}

auto
ByteStringLoad::set(const std::string& path) -> bool {
    if (!value.data || value.length == 0)
        return false;

    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        value.data   = nullptr;
        value.length = 0;
        return false;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
        value.data   = nullptr;
        value.length = 0;
        return false;
    }

    value.length = static_cast<UA_Int32>(size);
    value.data   = static_cast<UA_Byte*>(UA_malloc(size));
    if (value.data)
        std::copy(buffer.begin(), buffer.end(), value.data);
    return true;
}


UA_ByteString&
ByteStringLoad::getValue() {
    return value;
}

ByteStringLoad::ByteStringLoad(ByteStringLoad&& other) noexcept
  : value{} {
    value              = other.value;
    other.value.data   = nullptr;
    other.value.length = 0;
}

ByteStringLoad&
ByteStringLoad::operator=(ByteStringLoad&& other) noexcept {
    if (this != &other) {
        UA_ByteString_clear(&value);
        value              = other.value;
        other.value.data   = nullptr;
        other.value.length = 0;
    }
    return *this;
}

}