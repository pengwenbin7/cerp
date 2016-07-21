#include <stdio.h>
#include <libsoup/soup.h>
#include <gio/gio.h>
#include <string.h>

#define BUF 2048

int main(int argc, char **argv)
{
    SoupSession *session = soup_session_new();
    SoupMessage *msg;
    SoupMessageBody *body;
    GInputStream *in;
    guint status;
    char buf[BUF];
    char url[BUF];

    char *formdata = soup_form_encode("key1", "hello", "key2", "你好", "me", "xl", NULL);
    sprintf(url, "http://127.0.0.1/rec.php?%s", formdata);
    msg = soup_message_new("GET", url);
    status = soup_session_send_message(session, msg);
    body = msg->response_body;

    printf("%u\n", status);
    printf("%s", body->data);
    return 0;
}
