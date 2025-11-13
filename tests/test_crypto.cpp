#include "../src/core/crypto.h"
#include <cassert>
#include <iostream>

void testCrypto() {
    std::string text = "hello world";
    std::string encrypted = Crypto::encrypt(text, "key");
    std::string decrypted = Crypto::decrypt(encrypted, "key");

    assert(decrypted == text);
    std::cout << "testCrypto passed.\n";
}

int main() {
    testCrypto();
    return 0;
}