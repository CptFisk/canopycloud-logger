#include <cert.hpp>
#include <stdexcept>

namespace Interface {
X509Certificate::X509Certificate()
  : pkey(nullptr)
  , ctx(nullptr)
  , x509(nullptr) {
    OPENSSL_init_crypto(OPENSSL_INIT_LOAD_CONFIG, nullptr);
}

X509Certificate::~X509Certificate() {
    EVP_PKEY_free(pkey);
    EVP_PKEY_CTX_free(ctx);
    X509_free(x509);
}

auto
X509Certificate::generate(int keySize, int valid, const std::string& subject) -> void {
    if (!generateKey(keySize))
        throw std::runtime_error("Failed to generate key");
    if (!generateCertificate(valid, subject))
        throw std::runtime_error("Failed to generate certificate");
    if (!writeDER("client.der", "key.der"))
        throw std::runtime_error("Failed to write files");
}

auto
X509Certificate::generateKey(int keySize) -> bool {
    ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, nullptr);
    return (ctx && EVP_PKEY_keygen_init(ctx) > 0 && EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, keySize) > 0 && EVP_PKEY_keygen(ctx, &pkey) > 0);
}

auto
X509Certificate::generateCertificate(int valid, const std::string& subject) -> bool {
    x509 = X509_new();

    if (!x509)
        return false;
    ASN1_INTEGER_set(X509_get_serialNumber(x509), 1);
    X509_gmtime_adj(X509_get_notBefore(x509), 0);
    X509_gmtime_adj(X509_get_notAfter(x509), daysToSec(valid)); // Duration for 1 year
    X509_set_pubkey(x509, pkey);
    X509_NAME* name = X509_get_subject_name(x509);
    X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC, reinterpret_cast<const unsigned char*>(subject.c_str()), -1, -1, 0);
    X509_set_issuer_name(x509, name);
    // Sign certificate
    return X509_sign(x509, pkey, EVP_sha256()) > 0;
}

auto
X509Certificate::writeDER(const std::string& cert, const std::string& key) const -> bool {
    // Write certificate
    FILE* certFile = fopen(cert.c_str(), "wb");
    if (!certFile || i2d_X509_fp(certFile, x509) <= 0) {
        if (certFile)
            fclose(certFile);
        return false;
    }
    fclose(certFile);

    // Write key
    FILE* keyFile = fopen(key.c_str(), "wb");
    if (!keyFile || i2d_PrivateKey_fp(keyFile, pkey) <= 0) {
        if (keyFile)
            fclose(keyFile);
        return false;
    }
    fclose(keyFile);

    return true;
}

auto
X509Certificate::daysToSec(int days) -> long {
    constexpr auto secPerDay = 86400L; // 24 * 60 *60
    return static_cast<long>(secPerDay * days);
}
}
