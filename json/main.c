#include <stdio.h>
#include <stdlib.h>
#include <glib-object.h>
#include <json-glib/json-glib.h>

int main(int argc, char *argv[])
{
  JsonParser *parser;
  JsonNode *root;
  JsonObject *obj;
  JsonReader *reader;
  GError *error;
  
  g_type_init();

  parser = json_parser_new();

  error = NULL;
  json_parser_load_from_file(parser, argv[1], &error);
  if (error) {
      g_print("Unable to parse demo.json: %s\n", error->message);
      g_error_free(error);
      g_object_unref(parser);
      return EXIT_FAILURE;
  }

  root = json_parser_get_root(parser);
  reader = json_reader_new(root);
  gint count = json_reader_count_members(reader);
  
  g_print("MEMBERS: %d\n", count);
  if (json_reader_read_member(reader, "arr")) {
    //printf("c: %s\n", json_reader_get_string_value(reader));
    JsonNode *node = json_reader_get_value();
    
    // after reading the value, should be reposition the cursor
    json_reader_end_member(reader);
  }

  /* manipulate the object tree and then exit */
  g_object_unref(parser);

  return EXIT_SUCCESS;
}
