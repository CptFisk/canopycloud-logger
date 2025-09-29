#include <cstring>
#include <utility/byteStringClone.hpp>

namespace Interface {

ByteStringClone::ByteStringClone()
  : value{} {};

ByteStringClone::ByteStringClone(const UA_ByteString& source)
  : value{} {
    value.length = source.length;
    value.data   = static_cast<UA_Byte*>(malloc(value.length * sizeof(UA_ByteString)));
    if (value.data && source.data) {
        std::memcpy(value.data, source.data, value.length);
    }
}

ByteStringClone::~ByteStringClone() {
    UA_ByteString_clear(&value);
}

auto
ByteStringClone::set(const UA_ByteString& source) -> void {
    if (!value.data && value.length == 0) {
        value.length = source.length;
        value.data   = static_cast<UA_Byte*>(malloc(value.length * sizeof(UA_ByteString)));
        if (value.data && source.data) {
            std::memcpy(value.data, source.data, value.length);
        }
    }
}

UA_ByteString&
ByteStringClone::getValue() {
    return value;
}

ByteStringClone::ByteStringClone(ByteStringClone&& other) noexcept
  : value{} {
    value              = other.value;
    other.value.length = 0;
    other.value.data   = nullptr;
}

ByteStringClone&
ByteStringClone::operator=(ByteStringClone&& other) noexcept {
    if (this != &other) {
        UA_ByteString_clear(&value);
        value              = other.value;
        other.value.length = 0;
        other.value.data   = nullptr;
    }
    return *this;
}

}