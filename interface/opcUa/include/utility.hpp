#include <open62541/types.h>
#include <fstream>
#include <vector>
#include <string>

class ByteStringWrapper {
public:
    UA_ByteString value;

    ByteStringWrapper() {
        value.data = nullptr;
        value.length = 0;
    }

    explicit ByteStringWrapper(const std::string& path) {
        std::ifstream file(path, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            value.data = nullptr;
            value.length = 0;
            return;
        }

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<uint8_t> buffer(size);
        if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
            value.data = nullptr;
            value.length = 0;
            return;
        }

        value.length = static_cast<UA_Int32>(size);
        value.data = static_cast<UA_Byte*>(UA_malloc(size));
        if (value.data)
            std::copy(buffer.begin(), buffer.end(), value.data);
    }

    // Prevent copying
    ByteStringWrapper(const ByteStringWrapper&) = delete;
    ByteStringWrapper& operator=(const ByteStringWrapper&) = delete;

    // Allow moving
    ByteStringWrapper(ByteStringWrapper&& other) noexcept {
        value = other.value;
        other.value.data = nullptr;
        other.value.length = 0;
    }

    ByteStringWrapper& operator=(ByteStringWrapper&& other) noexcept {
        if (this != &other) {
            UA_ByteString_clear(&value);
            value = other.value;
            other.value.data = nullptr;
            other.value.length = 0;
        }
        return *this;
    }

    ~ByteStringWrapper() {
        UA_ByteString_clear(&value);
    }
};