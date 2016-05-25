#include <stdlib.h>
#include <string.h>
#include <ocilib.h>

void sql_query(const char *sql, char *result);
int sql_exec(const char *sql);

// query database result save in *result as json string
void sql_query(OCI_Statement st, const char *sql, char *result)
{
  OCI_resultset *rs;
  OCI_ExecuteStmt(st, sql);
  rs = OCI_GetResultset(st);
  int colcount = OCI_GetColumnCount(rs);
  
  while (OCI_FetchNext(rs)) {

  }
