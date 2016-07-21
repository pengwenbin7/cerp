#include <fcgi_stdio.h>
#include <stdlib.h>

int main(void)
{
  
  while(FCGI_Accept() >= 0) {
    char *query = getenv("QUERY_STRING");
    char *root = getenv("DOCUMENT_ROOT");
    char *script = getenv("SCRIPT_NAME");
    char *request = getenv("REQUEST_URI");
    printf("Content-type: text/html\r\nStatus: 200 OK\r\n\r\n");
    printf("<pre>");
    printf("query:%s\ndoc_root:%s\nscript:%s\nrequest_uri:%s", query, root, script, request);
  }

  return 0;
}
