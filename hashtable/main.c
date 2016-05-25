#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

void say(void);
void showkv(char *key, char *value, char *data);
int main(int argc, char **argv)
{
  GHashTable *table = g_hash_table_new(g_str_hash, g_str_equal);
  // save string
  g_hash_table_insert(table, "a", "China");
  // save utf-8 string
  g_hash_table_insert(table, "c", "中国");
  // save function
  g_hash_table_insert(table, "s", say);
  g_hash_table_add(table, "nk");
    
  // get size
  guint size = g_hash_table_size(table);
  printf("size: %u\n", size);
  // get string
  char *c = g_hash_table_lookup(table, "c");
  printf("%s\n", c);
  // get key without value
  char *value = g_hash_table_lookup(table, "nk");
  printf("NK: %s\n", value);
  // get function
  void (*s)(void) = g_hash_table_lookup(table, "s");
  printf("%p\n", s);
  printf("%p\n", say);
  // run function
  s();
  
  // foreach operation
  printf("foreach op:\n");
  g_hash_table_foreach(table, showkv, NULL);
      
  /*
  struct method_table {
    char *name;
    void (*mp)(void);
  } mt;

  mt.name = "say";
  mt.mp = say;
  
  (mt.mp)();
  */
  return 0;
}

void say(void)
{
  printf("say\n");
}

void showkv(char *key, char *value, char *data)
{
  printf("%s => %s\n", key, value);
}
