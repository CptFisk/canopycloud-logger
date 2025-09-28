#pragma once
#include <open62541/types.h>

namespace Interface {
/**
 * @brief Load a file and return it as a UA_ByteString, the wrapper clears memory at end of scope
 */
class ByteStringLoader {
  public:
    ByteStringLoader();                                 ///< Default constructor
    explicit ByteStringLoader(const std::string& path); ///< Constructor that loads a file
    ~ByteStringLoader();

    [[nodiscard]] auto getValue() -> UA_ByteString;

    // Overloaders
    ByteStringLoader(const ByteStringLoader&)            = delete;
    ByteStringLoader& operator=(const ByteStringLoader&) = delete;
    ByteStringLoader(ByteStringLoader&& other) noexcept;
    ByteStringLoader& operator=(ByteStringLoader&& other) noexcept;

  private:
    UA_ByteString value;
};

}