#include <stdio.h>
#include "oracle.h"

int main(int argc, char **argv)
{
  OCI_Connection *cn = oci_conn("192.168.188.112:1521/XE", "admin", "admin");
  OCI_Statement *st = OCI_StatementCreate(cn);
  char data[LEN];
  oci_sql_query(st, "select * from t01", data);
  printf("%s\n", data);

  return 0;
}
