#include <libsoup/soup.h>
#include <gio/gio.h>
#include <glib.h>


#define BUF 2048
typedef struct Response Response;

struct Response {
  const char *method;
  guint status;
  GHashTable *headers;
  const char *body;
  goffset length;
};

void headers_foreach_hash(const char *name,
			  const char *value,
			  void *data);
void parseResponse(SoupMessage *msg, Response *res);
SoupMessage *getMessage(const char *url);
Response *getResponse(const char *url, gboolean ignoreHeaders);
GHashTable *headersHash(SoupMessageHeaders *headers);
void hash_table_showall(GHashTable *hashTable);
void hash_table_show_func(gpointer key, gpointer value, gpointer data);
