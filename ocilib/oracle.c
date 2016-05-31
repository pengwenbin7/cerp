#include "oracle.h"

// connect oracle database
// exampel: char *db = "192.168.188.112:1521/XE"
OCI_Connection *oci_conn(const char *db, const char *user, const char *pass)
{
  if (!OCI_Initialize(NULL, NULL, OCI_ENV_DEFAULT)) {
    fprintf(stderr, "Connect Error");
    exit(EXIT_FAILURE)-;
  }

  return OCI_ConnectionCreate(db, user, pass, OCI_SESSION_DEFAULT);
}

// query database result save in *result as json string
char *oci_sql_query(OCI_Statement *st, const char *sql, char *result)
{
  OCI_Resultset *rs;
  OCI_ExecuteStmt(st, sql);
  rs = OCI_GetResultset(st);
  rs2json(rs, result);
  return result;
}

void rs2json(OCI_Resultset *rs, char *json_str)
{
  unsigned int column, row, i;
  column = OCI_GetColumnCount(rs);

  // json builder initial
  JsonBuilder *builder = json_builder_new();
  json_builder_begin_object(builder);
  json_builder_set_member_name(builder, "column");
  json_builder_add_int_value(builder, column);
  json_builder_set_member_name(builder, "columns");
  json_builder_begin_array(builder);
  
  for (i = 1; i <= column; i++) {
    OCI_Column *col = OCI_GetColumn(rs, i);
    json_builder_add_string_value(builder, OCI_ColumnGetName(col));
  }
  json_builder_end_array(builder);
  
  json_builder_set_member_name(builder, "rows");
  json_builder_begin_array(builder);
  while (OCI_FetchNext(rs)) {
    json_builder_begin_array(builder);
    for (i = 1; i <= column; i++) {
      json_builder_add_string_value(builder, OCI_GetString(rs, i));
    }
    json_builder_end_array(builder);
  }
  json_builder_end_array(builder);
  
  row = OCI_GetRowCount(rs);
  json_builder_set_member_name(builder, "row");
  json_builder_add_int_value(builder, row);
  json_builder_end_object(builder);

  // generate json string
  JsonGenerator *gen = json_generator_new();
  JsonNode *root = json_builder_get_root(builder);
  json_generator_set_root(gen, root);
  strcpy(json_str, json_generator_to_data(gen, NULL));
  json_str[LEN] = '\0';
  json_node_free(root);
  g_object_unref(gen);
  g_object_unref(builder);
}
