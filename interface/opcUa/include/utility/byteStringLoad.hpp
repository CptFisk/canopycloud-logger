#pragma once
#include <open62541/types.h>
#include <string>

namespace Interface {
/**
 * @brief Load a file and return it as a UA_ByteString, the wrapper clears memory at end of scope
 */
class ByteStringLoad {
  public:
    ByteStringLoad();                                 ///< Default constructor
    explicit ByteStringLoad(const std::string& path); ///< Constructor that loads a file
    ~ByteStringLoad();

    /**
     * @brief Fill with data
     * @return True if file was loaded
     */
    auto set(const std::string& path) -> bool;
    [[nodiscard]] UA_ByteString& getValue();

    // Overloaders
    ByteStringLoad(const ByteStringLoad&)            = delete;
    ByteStringLoad& operator=(const ByteStringLoad&) = delete;
    ByteStringLoad(ByteStringLoad&& other) noexcept;
    ByteStringLoad& operator=(ByteStringLoad&& other) noexcept;

  private:
    UA_ByteString value;
};

}