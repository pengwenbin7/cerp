#include <stdlib.h>
#include <string.h>
#include <ocilib.h>
#include <stddef.h>
#include <glib.h>
#include <json-glib/json-glib.h>

#define oci_sql_exec(st, sql) OCI_ExecuteStmt(st, sql)
// json data limit 2M
#define LEN 2097152

OCI_Connection *oci_conn(const char *db, const char *user, const char *pass);
char *oci_sql_query(OCI_Statement *st, const char *sql, char *result);
void rs2json(OCI_Resultset *rs, char *json_str);
