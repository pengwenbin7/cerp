package com.infortechn;

import java.io.*;
import java.util.Map;
import javax.servlet.*;
import javax.servlet.http.*;

import com.google.gson.*;
import oracle.jdbc.OracleResultSet;
import oracle.jdbc.OracleStatement;
import oracle.jdbc.driver.OracleConnection;
import oracle.jdbc.pool.OracleDataSource;

import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.util.Properties;

public class Api extends HttpServlet {

    public void doGet(HttpServletRequest request, HttpServletResponse response)
	throws IOException, ServletException {
	response.setCharacterEncoding("UTF-8");
	response.setContentType("application/json");
	String table = request.getParameter("table");
	if (table == null) {
	    table = "tblgem";
	}

	PrintWriter out = response.getWriter();
	
	Map<String, String> map = System.getenv();
	out.print("pwd: " + map.get("PWD"));
    
	OracleDataSource ods = null;
	OracleConnection conn = null;
	OracleStatement st = null;
	OracleResultSet result = null;
    
	try {
	    ods = new OracleDataSource();
	    ods.setURL("jdbc:oracle:thin:@//192.168.188.112:1521/XE");
	    ods.setUser("admin");
	    ods.setPassword("admin");

	    conn = (OracleConnection) ods.getConnection();
	    st = (OracleStatement) conn.createStatement();
	    String sql = "select trim(img01), trim(ima02), trim(img02), trim(img03), trim(img04), img10 from tblimg, tblima where img01 = ima01";
	    result = (OracleResultSet) st.executeQuery(sql);
	    String json = rs2json(result);
	    out.println(json);
	} catch (Exception e) {
	    out.println(e.getMessage());
	} finally {
	    /*
	      if (result != null) result.close();
	      if (st != null) st.close();
	      if (conn != null) conn.close();
	    */
	}
    }

    private static String rs2json(OracleResultSet rs) throws SQLException {
	Gson gson = new GsonBuilder().create();
	JsonObject jsonObject = new JsonObject();

	ResultSetMetaData md = rs.getMetaData();
	int column = md.getColumnCount();

	jsonObject.addProperty("column", column);
	JsonArray columns = new JsonArray();
	for (int i = 1; i <= column; i++) {
	    columns.add(md.getColumnName(i));
	}
	jsonObject.add("columns", columns);

	int row = 0;
	JsonArray rows = new JsonArray();
	while (rs.next()) {
	    JsonArray aRow = new JsonArray();
	    for (int i = 1; i <= column; i++) {
		aRow.add(rs.getString(i));
	    }
	    rows.add(aRow);
	    row++;
	}
	jsonObject.addProperty("row", row);
	jsonObject.add("rows", rows);

	return gson.toJson(jsonObject);
    }
}
