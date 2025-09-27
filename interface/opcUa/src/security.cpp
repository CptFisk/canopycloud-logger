#include <security.hpp>

namespace Interface {

auto getSecurityConfig(const Security& sec) -> SecurityConfig{
    switch(static_cast<int>(sec)) {
        case None:
            return {"http://opcfoundation.org/UA/SecurityPolicy#None", UA_MESSAGESECURITYMODE_NONE};
        case Basic128Rsa15Sign:
            return {"http://opcfoundation.org/UA/SecurityPolicy#Basic128Rsa15", UA_MESSAGESECURITYMODE_SIGN};
        case Basic256Rsa15SignEncrypt:
            return {"http://opcfoundation.org/UA/SecurityPolicy#Basic256Rsa15", UA_MESSAGESECURITYMODE_SIGNANDENCRYPT};
        case Basic256Sign:
            return {"http://opcfoundation.org/UA/SecurityPolicy#Basic256", UA_MESSAGESECURITYMODE_SIGN};
        case Basic256SignEncrypt:
            return {"http://opcfoundation.org/UA/SecurityPolicy#Basic256", UA_MESSAGESECURITYMODE_SIGNANDENCRYPT};
        case Basic256Sha256Sign:
            return {"http://opcfoundation.org/UA/SecurityPolicy#Basic256Sha256", UA_MESSAGESECURITYMODE_SIGN};
        case Basic256Sha256SignEncrypt:
            return {"http://opcfoundation.org/UA/SecurityPolicy#Basic256Sha256", UA_MESSAGESECURITYMODE_SIGNANDENCRYPT};
        case Aes128Sha256RsaOaepSign:
            return {"http://opcfoundation.org/UA/SecurityPolicy#Aes128_Sha256_RsaOaep", UA_MESSAGESECURITYMODE_SIGN};
        case Aes128Sha256RsaOaepSignEncrypt:
            return {"http://opcfoundation.org/UA/SecurityPolicy#Aes128_Sha256_RsaOaep", UA_MESSAGESECURITYMODE_SIGNANDENCRYPT};
        case Aes256Sha256RsaPssSign:
            return {"http://opcfoundation.org/UA/SecurityPolicy#Aes256_Sha256_RsaPss", UA_MESSAGESECURITYMODE_SIGN};
        case Aes256Sha256RsaPssSignEncrypt:
            return {"http://opcfoundation.org/UA/SecurityPolicy#Aes256_Sha256_RsaPss", UA_MESSAGESECURITYMODE_SIGNANDENCRYPT};
        default:
            return {"", UA_MESSAGESECURITYMODE_INVALID};
    }
}

}