#include <stdio.h>
#include <string.h>

#include "crypto_core_salsa20.h"

int main(
    int argc,
    const char *argv[]
) {
    unsigned char sigma[crypto_core_salsa20_CONSTBYTES] = "expand 32-byte k";
    unsigned char key[crypto_core_salsa20_KEYBYTES];
    unsigned char input[crypto_core_salsa20_INPUTBYTES];
    unsigned char output[crypto_core_salsa20_OUTPUTBYTES];

    memset(key, 0, crypto_core_salsa20_KEYBYTES);
    memset(input, 0, crypto_core_salsa20_INPUTBYTES);
    key[0] = 0x80;
    crypto_core_salsa20(output, input, key, sigma);
    for (int i = 0; i < crypto_core_salsa20_OUTPUTBYTES; i++) {
        printf("%02x ", output[i]);
    }
    printf("\n");
    return 0;
}
