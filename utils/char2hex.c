#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *char2hex(const char *str);
int main(int argc, char *argv[])
{
    printf("%s\n", char2hex(argv[1]));

    return 0;
}

/**
 * convert char array to hex string
 */
char *char2hex(const char *str)
{
    unsigned int len = strlen(str), i;
    char *hex = malloc(len * 2);
    for (i = 0; i < len; i++) {
	sprintf(hex + (i * 2), "%02x", str[i]);
    }

    return hex;
}
