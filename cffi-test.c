#include <stdio.h>
#include <string.h>

#define CSIZE (50)

extern int crypto_stream_xor(
        unsigned char *out,
        const unsigned char *in,
        unsigned long long inlen,
        const unsigned char *n,
        const unsigned char *k
);


int main(
    int argc,
    const char *argv[]
) {
    unsigned char key[32];
    unsigned char nonce[8];
    unsigned char toencrypt[CSIZE];
    unsigned char output[CSIZE];

    memset(key, 0, 32);
    memset(nonce, 0, 8);
    memset(toencrypt, 0, CSIZE);    
    crypto_stream_xor(output, toencrypt, CSIZE, nonce, key);
    for (int i = 0; i < CSIZE; i++) {
        printf("%02x ", output[i]);
    }
    printf("\n");
    return 0;
}

