/**
 * ocilib simple code
 * @author pengwenbin7@126.com
 * @filename main.c
 * @compile gcc main.c -locilib -o main
 */
#include <stdio.h>
#include <stdlib.h>
#include <ocilib.h>

int main(int argc, char **argv)
{
  OCI_Connection *cn;
  OCI_Statement  *st;
  OCI_Resultset *rs;

  // init env
  if (!OCI_Initialize(NULL, NULL, OCI_ENV_DEFAULT)) {
    fprintf(stderr, "connect error");
    return EXIT_FAILURE;
  }

  // connect oracle xe
  const char *db = "192.168.1.101:1521/XE",
    *user = "admin",
    *pass = "admin";
  const int mode = OCI_SESSION_DEFAULT;
  cn = OCI_ConnectionCreate(db, user, pass, mode);

  // get OCI_Statement object
  st = OCI_StatementCreate(cn);

  // execute sql statement
  OCI_ExecuteStmt(st,
		  "create table t01 (id int, name varchar(20))"
		  );
  OCI_ExecuteStmt(st,
		  "insert into t01 values (1, 'xl')"
		  );
  OCI_ExecuteStmt(st,
		  "insert into t01 values (2, 'haha')"
		  );
  OCI_ExecuteStmt(st,
		  "insert into t01 values (3, 'gogo')"
		  );
  OCI_ExecuteStmt(st,
		  "update t01 set name = 'xxxxx' where id = 2"
		  );
  OCI_ExecuteStmt(st,
		  "delete from t01 where id = 3"
		  );
  OCI_ExecuteStmt(st,
		  "select * from t01"
		  );
		  
  // get result
  rs = OCI_GetResultset(st);
  unsigned int row = OCI_GetRowCount(rs),
    column = OCI_GetColumnCount(rs);
  printf("resultset size: %u x %u\n", row, column);
  while (OCI_FetchNext(rs)) {
    printf("%d\t%s\n", OCI_GetInt(rs, 1), OCI_GetString(rs, 2));
  }

  // commit update
  OCI_Commit(cn);
  // clean up
  OCI_Cleanup();
  return EXIT_SUCCESS;
}
