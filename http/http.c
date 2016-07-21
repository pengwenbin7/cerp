#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http.h"

Response *res;
char buf[1024];
GHashTable *hashTable;

// test function
int main(int argc, char *argv[])
{
  char *url = "http://127.0.0.1/rec.php?key=hello";
  Response *res = getResponse(url, FALSE);
  printf("%s", res->body);
  hash_table_showall(res->headers);
  return 0;
}

/**
 * get response from url
 * ignoreHeaders: if ignore heasers from message body
 */
Response *getResponse(const char *url, gboolean ignoreHeaders)
{
  Response *res = (Response *) malloc(sizeof(Response));
  SoupSession *session = soup_session_new();
  SoupMessage *msg = soup_message_new("GET", url);
  res->status = soup_session_send_message(session, msg);
  res->body = msg->response_body->data;
  res->method = msg->method;
  res->length = msg->response_body->length;
  if (ignoreHeaders) {
    res->headers = NULL;
  } else {
    res->headers = headersHash(msg->response_headers);
  }
  // free msg
  msg = NULL;
  return res;
}

GHashTable *headersHash(SoupMessageHeaders *headers)
{
  GHashTable *hashTable = g_hash_table_new(g_str_hash, g_str_equal);
  soup_message_headers_foreach(headers,
			       headers_foreach_hash,
			       (void*) hashTable);
  return hashTable;
}

SoupMessage *getMessage(const char *url)
{
  SoupSession *session = soup_session_new();
  SoupMessage *msg = soup_message_new("GET", url);
  soup_session_send_message(session, msg);
  return msg;
}

// iterator headers k-v pair, print and insert into hash table
void headers_foreach_hash(const char *name,
			  const char *value,
			  void *data) 
{
  g_hash_table_insert((GHashTable *) data, (gpointer) name, (gpointer) value);
}

// show hash table k-v pair
void hash_table_showall(GHashTable *hashTable)
{
  g_hash_table_foreach(hashTable,
		       hash_table_show_func,
		       NULL);
}

void hash_table_show_func(gpointer key, gpointer value, gpointer data)
{
  printf("%s: %s\n", (char *) key, (char *) value);
}
