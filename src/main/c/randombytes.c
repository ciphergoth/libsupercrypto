#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#include "randombytes.h"
#include "randombytes_init.h"

static int dev_urandom = -1;

int randombytes_init()
{
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0)
        return -1;
    dev_urandom = fd;
    return 0;
}

void randombytes(
    unsigned char *destination,
    unsigned long long len
) {
    if (dev_urandom == -1) {
        fprintf(stderr, "Random bytes library not initialized, exiting\n");
        exit(-1);
    }
    while (len > 0) {
        ssize_t count = read(dev_urandom, destination,
            len < SSIZE_MAX ? len : SSIZE_MAX);
        destination += count;
        len -= count;
    }
}
