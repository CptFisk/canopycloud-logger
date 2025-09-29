#include <fstream>
#include <utility/byteStringLoader.hpp>
#include <vector>

namespace Interface {

ByteStringLoader::ByteStringLoader()
  : value{} {}

ByteStringLoader::ByteStringLoader(const std::string& path)
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

ByteStringLoader::~ByteStringLoader() {
    UA_ByteString_clear(&value);
}

auto
ByteStringLoader::getValue() const -> UA_ByteString {
    return value;
}

ByteStringLoader::ByteStringLoader(ByteStringLoader&& other) noexcept
  : value{} {
    value              = other.value;
    other.value.data   = nullptr;
    other.value.length = 0;
}

ByteStringLoader&
ByteStringLoader::operator=(ByteStringLoader&& other) noexcept {
    if (this != &other) {
        UA_ByteString_clear(&value);
        value              = other.value;
        other.value.data   = nullptr;
        other.value.length = 0;
    }
    return *this;
}

}