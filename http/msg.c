#include <stdio.h>
#include <libsoup/soup.h>
#include <gio/gio.h>
#include <string.h>

void headers_foreach_func(const char *name,
			  const char *value,
			  void *data);

int main(int argc, char **argv)
{
    SoupSession *session = soup_session_new();
    SoupMessage *msg;
    SoupMessageHeaders *head;
    guint status;
    char buf[1024];
    char *formdata = soup_form_encode("key1", "hello", "key2", "你好", "me", "xl", NULL);
    msg = soup_message_new("GET", "http://127.0.0.1");
    soup_message_set_request (msg, "application/x-www-form-urlencoded",
	    SOUP_MEMORY_COPY, formdata, strlen (formdata));

    status = soup_session_send_message(session, msg);
    head = msg->response_headers;
    soup_message_headers_foreach(head,
				 headers_foreach_func,
				 NULL);
    printf("%u\n", status);
    return 0;
}

void headers_foreach_func(const char *name,
			  const char *value,
			  void *data) 
{
  printf("%s: %s\n", name, value);
}
