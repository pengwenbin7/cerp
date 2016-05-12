#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <string.h>

int main(int argc, char **argv)
{
  MYSQL *mysql = mysql_init(NULL);
  const char *host = "127.0.0.1";
  const char *user = "root";
  const char *passwd = "root";
  const char *db = "test";
  unsigned int port = 3306;
  const char *unix_socket = "/tmp/mysql.sock";
  unsigned long clientflag = 0;
  if (mysql_real_connect(
			 mysql,
			 host,
			 user,
			 passwd,
			 db,
			 port,
			 unix_socket,
			 clientflag
			 )) {
    printf("CONN OK!\n");
  } else {
    printf("ERROR: %s\n", mysql_error(mysql));
  }

  const char *query = "CREATE TABLE odbct (id int, name varchar(20))";
  if (mysql_real_query(mysql, query, strlen(query))) {
  	printf("%s\n", mysql_error(mysql));
  }

  return 0;
}
  
