#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <ocilib.h>

int main(int argc, char **argv)
{
  OCI_Connection *cn;
  OCI_Statement  *st;
  OCI_Resultset *rs;
  int res = 0;
  if (!OCI_Initialize(NULL, NULL, OCI_ENV_DEFAULT)) {
    return EXIT_FAILURE;
  }
  cn = OCI_ConnectionCreate("192.168.188.112:1521/XE", "admin", "admin", OCI_SESSION_DEFAULT);
  //printf("Server major version: %i\n", OCI_GetServerMajorVersion(cn));
  st = OCI_StatementCreate(cn);
  //OCI_ExecuteStmt(st, "insert into t00 values (3, 'ogjoa')");
  //OCI_ExecuteStmt(st, "update t00 set name = 'qtt' where id = 2");
  OCI_ExecuteStmt(st, "select * from t00");
  rs = OCI_GetResultset(st);

  while (OCI_FetchNext(rs)) {
    printf("%i\t%s\n", OCI_GetInt(rs, 1), OCI_GetString(rs, 2));
  }

  OCI_Commit(cn);
  OCI_Cleanup();
  return EXIT_SUCCESS;
}
