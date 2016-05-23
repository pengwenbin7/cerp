#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <libxml/parser.h>

int main(int argc, char **argv)
{
  xmlDocPtr doc;
  doc = xmlReadFile(argv[1], "UTF-8", XML_PARSE_NOCDATA);

  return 0;
}
