#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

void say(void);
int main(int argc, char **argv)
{
  GHashTable *table = g_hash_table_new(g_str_hash, g_str_equal);
  // save string
  g_hash_table_insert(table, "a", "China");
  // save utf-8 string
  g_hash_table_insert(table, "c", "中国");
  // save function
  g_hash_table_insert(table, "s", say);
  // get string
  char *c = g_hash_table_lookup(table, "c");
  printf("%s\n", c);

  // get function
  void (*s)(void) = g_hash_table_lookup(table, "s");
  printf("%p\n", s);
  printf("%p\n", say);
  // run function
  s(void);

  struct method_table {
    char *name;
    void (*mp)(void);
  } mt;

  mt.name = "say";
  mt.mp = say;
  
  (mt.mp)();
  return 0;
}

void say(void)
{
  printf("say");
}
