#include <stdio.h>
#include <openssl/md5.h>
#include <string.h>

/**
 * digest md5
 */
void MDPrint(unsigned char digest[16]);
int main(int argc, char *argv[])
{
    unsigned char md5[16];
    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, (void *) argv[1], strlen(argv[1]));
    MD5_Final(md5, &ctx);
    MDPrint(md5);

    return 0;
}

void MDPrint(unsigned char digest[16])
{
    int i;
    for (i = 0; i < 16; i++) {
	printf("%02x", digest[i]);
    }
}
