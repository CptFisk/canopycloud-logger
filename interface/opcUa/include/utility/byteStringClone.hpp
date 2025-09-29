#pragma once
#include <open62541/types.h>

namespace Interface {

class ByteStringClone {
  public:
    ByteStringClone();
    explicit ByteStringClone(const UA_ByteString& source);

    ~ByteStringClone();

    // Overloaders
    ByteStringClone(const ByteStringClone&)            = delete;
    ByteStringClone& operator=(const ByteStringClone&) = delete;
    ByteStringClone(ByteStringClone&& other) noexcept;
    ByteStringClone& operator=(ByteStringClone&& other) noexcept;

    auto set(const UA_ByteString& source) -> void;
    UA_ByteString& getValue();


  private:
    UA_ByteString value;
};

}