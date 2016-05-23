#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <string.h>
#include <glib-object.h>
#include <json-glib/json-glib.h>
#include <ctype.h>

int main(int argc, char **argv)
{
  // mysql initial
  MYSQL *mysql = mysql_init(NULL);
  MYSQL_RES *res;
  MYSQL_ROW row;
  MYSQL_FIELD *fields;
  const char *host = "127.0.0.1";
  const char *user = "root";
  const char *passwd = "root";
  const char *db = "test";
  unsigned int port = 3306;
  const char *unix_socket = "/tmp/mysql.sock";
  unsigned long clientflag = 0;
  unsigned int field_count;
  
  int i;

  // json builder initial
  JsonBuilder *builder = json_builder_new();

  
  // connect mysql
  if (!mysql_real_connect(
			 mysql,
			 host,
			 user,
			 passwd,
			 db,
			 port,
			 unix_socket,
			 clientflag
			 )) {
  	printf("%s\n", mysql_error(mysql));
  }

  char *create = "CREATE TABLE IF NOT EXISTS odbct (id int, name varchar(20))";
  if (!mysql_real_query(mysql, create, strlen(create))) {
  	printf("%s\n", mysql_error(mysql));
  }

  char *sql = "set names utf8";
  mysql_real_query(mysql, sql, strlen(sql));
  char *select = "SELECT * FROM odbct";
  mysql_real_query(mysql, select, strlen(select));
  res = mysql_store_result(mysql);
  int rows = (int) mysql_num_rows(res);

  // add rows
  json_builder_begin_object(builder);
  json_builder_set_member_name(builder, "count");
  json_builder_add_int_value(builder, rows);

  field_count = mysql_field_count(mysql);
  json_builder_set_member_name(builder, "fields");
  json_builder_begin_array(builder);
  fields = mysql_fetch_fields(res);
  for (i = 0; i < field_count; i++) {
    json_builder_add_string_value(builder, fields[i].name);
  }
  json_builder_end_array(builder);
  
  json_builder_set_member_name(builder, "rows");
  json_builder_begin_array(builder);
  while (row = mysql_fetch_row(res)) {
    json_builder_begin_array(builder);
    for (i = 0; i < field_count; i++) {
      json_builder_add_string_value(builder, row[i]);
    }
    json_builder_end_array(builder);
  }
  json_builder_end_array(builder);

  json_builder_end_object(builder);

  // generate json string
  JsonGenerator *gen = json_generator_new();
  JsonNode *root = json_builder_get_root(builder);
  json_generator_set_root(gen, root);
  gchar *str = json_generator_to_data(gen, NULL);
  
  mysql_free_result(res);
  mysql_close(mysql);
  json_node_free (root);
  g_object_unref (gen);
  g_object_unref (builder);

  printf("%s\n", str);
  
  return 0;
}
  
