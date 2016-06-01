CLASSPATH = ~/bin/apache-tomcat-8.0.35/lib/servlet-api.jar:./lib/gson-2.6.2.jar:./lib/ojdbc6.jar:.
SOURCEPATH = ./src
api:
	javac -classpath $(CLASSPATH) -sourcepath $(SOURCEPATH) -d classes/ src/Api.java
hello:
	javac -classpath ~/bin/apache-tomcat-8.0.35/lib/servlet-api.jar:./lib/gson-2.6.2.jar:./lib/ojdbc6.jar:. -sourcepath src -d classes/ src/Hello.java

