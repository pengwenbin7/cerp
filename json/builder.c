#include <stdio.h>
#include <stdlib.h>
#include <glib-object.h>
#include <json-glib/json-glib.h>

int main(int argc, char *argv[])
{
  JsonBuilder *builder = json_builder_new ();

  json_builder_begin_object (builder);

  json_builder_set_member_name (builder, "string");
  json_builder_add_string_value (builder, "你好，中国");

  json_builder_set_member_name (builder, "size");
  json_builder_begin_array (builder);
  json_builder_add_int_value (builder, 652);
  json_builder_add_int_value (builder, 242);
  json_builder_end_array (builder);

  json_builder_end_object (builder);

  JsonGenerator *gen = json_generator_new ();
  JsonNode * root = json_builder_get_root (builder);
  json_generator_set_root (gen, root);
  gchar *str = json_generator_to_data (gen, NULL);

  json_node_free (root);
  g_object_unref (gen);
  g_object_unref (builder);

  printf("%s\n", str);

  return 0;
}
