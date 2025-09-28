#pragma once
#include <openssl/x509.h>
#include <string>

namespace Interface {
class X509Certificate {
  public:
    X509Certificate();
    ~X509Certificate();

    auto generate(int keySize, int valid, const std::string& subject) -> void;

  private:
    std::string subjectCN;

    EVP_PKEY*     pkey;
    EVP_PKEY_CTX* ctx;
    X509*         x509;

    /**
     * @param keySize Size of the key
     * @return True if key was generated successfully
     */
    [[nodiscard]] auto generateKey(int keySize) -> bool;

    /**
     *
     * @param valid Number of days the certificate is valid
     * @param subject
     * @return True if the certificate was generated successfully
     */
    auto generateCertificate(int valid, const std::string& subject) -> bool;

    [[nodiscard]] auto writeDER(const std::string& cert, const std::string& key) const -> bool;

    /**
     * @param days Number of days to be converted
     * @return The number of seconds as a long
     */
    [[nodiscard]] static auto daysToSec(int days) -> long;
};
}
