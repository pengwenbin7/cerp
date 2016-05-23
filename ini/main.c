#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <glib.h>

int main(int argc, char **argv)
{
  GKeyFile *key_file = g_key_file_new();
  GError *err = NULL;

  // load file
  if (!g_key_file_load_from_file(
          key_file,
          "test.ini",
          G_KEY_FILE_KEEP_COMMENTS,
          &err)) {
    printf("%s\n", err->message);
  }

  // read groups
  gchar **groups = g_key_file_get_groups(key_file, NULL);
  printf("%s\n", *groups);
  // get a value
  gchar *name = g_key_file_get_value(key_file,
                                     groups[0],
                                     "user",
                                     &err);
  printf("name: %s\n", name);

  // free memory
  g_strfreev(groups);
  
  return EXIT_SUCCESS;
}
