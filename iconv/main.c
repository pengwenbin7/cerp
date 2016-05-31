#include <stdio.h>
#include <stddef.h>
#include <iconv.h>

int main(int argc, char **argv)
{
  iconv_t cd = iconv_open("GBK", "UTF-8");
  FILE *file = fopen("iconv.txt", "r");
  char ori[2 * 1024 * 1024];
  char out[1024];
  size_t *size = 1024;
  fgets(ori, 1024, file);
  printf("%s\n", ori);
  iconv(cd, &ori, size, &out, size);
  printf("%s\n", out);

  return 0;
}
