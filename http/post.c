#include <stdio.h>
#include <libsoup/soup.h>
#include <gio/gio.h>
#include <string.h>

int main(int argc, char **argv)
{
    SoupSession *session = soup_session_new();
    SoupMessage *msg;
    SoupMessageBody *body;
    GInputStream *in;
    guint status;
    char buf[1024];
    char *formdata = soup_form_encode("key1", "hello", "key2", "你好", "me", "xl", NULL);
    printf("form: %s\n", formdata);

    msg = soup_message_new("POST", "http://127.0.0.1/rec.php");
    soup_message_set_request (msg, "application/x-www-form-urlencoded",
	    SOUP_MEMORY_COPY, formdata, strlen (formdata));
    /*
    in = soup_session_send(session, msg, NULL, NULL);
    g_input_stream_read(in, buf, 1024, NULL, NULL);
    */
    status = soup_session_send_message(session, msg);
    body = msg->response_body;

    if(status == 200) {
    	printf("%s", body->data);
    } else {
	printf("%d", status);
    }
    return 0;
}
