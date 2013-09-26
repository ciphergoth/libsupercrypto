#include <stdio.h>
#include <string.h>

#define CRYPTO_OUTPUTBYTES 64
#define CRYPTO_INPUTBYTES 16
#define CRYPTO_KEYBYTES 32
#define CRYPTO_CONSTBYTES 16

extern int crypto_core_salsa20_ref(
        unsigned char *out,
  const unsigned char *in,
  const unsigned char *k,
  const unsigned char *c
);


int main(
    int argc,
    const char *argv[]
) {
    unsigned char sigma[CRYPTO_CONSTBYTES] = "expand 32-byte k";
    unsigned char key[CRYPTO_KEYBYTES];
    unsigned char input[CRYPTO_INPUTBYTES];
    unsigned char output[CRYPTO_OUTPUTBYTES];

    memset(key, 0, CRYPTO_KEYBYTES);
    memset(input, 0, CRYPTO_INPUTBYTES);
    key[0] = 0x80;
    crypto_core_salsa20(output, input, key, sigma);
    for (int i = 0; i < CRYPTO_OUTPUTBYTES; i++) {
        printf("%02x ", output[i]);
    }
    printf("\n");
    return 0;
}
