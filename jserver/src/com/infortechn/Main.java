package com.infortechn;

import com.google.gson.*;
import oracle.jdbc.OracleResultSet;
import oracle.jdbc.OracleStatement;
import oracle.jdbc.driver.OracleConnection;
import oracle.jdbc.pool.OracleDataSource;

import java.sql.ResultSetMetaData;
import java.sql.SQLException;

public class Main {

    public static void main(String[] args) throws SQLException {
        OracleDataSource ods = null;
        OracleConnection conn = null;
        OracleStatement st = null;
        OracleResultSet result = null;

        ods = new OracleDataSource();
        ods.setURL("jdbc:oracle:thin:@//192.168.1.107:1521/XE");
        ods.setUser("system");
        ods.setPassword("tiger");

        conn = (OracleConnection) ods.getConnection();
        try {
            st = (OracleStatement) conn.createStatement();
            //st.executeUpdate("update t00 set name = '猴子' where id = 3");
            result = (OracleResultSet) st.executeQuery("select * from t00");
            String json = rs2json(result);
            System.out.println(json);
            /*
            ResultSetMetaData mdata =result.getMetaData();
            int columns = mdata.getColumnCount();
            for (int i = 1; i <= columns; i++) {
                System.out.print(mdata.getColumnName(i) + "\t");
            }
            System.out.println();
            while (result.next()) {
                for (int i = 1; i <= columns; i++) {
                    System.out.print(result.getString(i) + "\t");
                }
                System.out.println();
            }
            */
        } finally {
            if (result != null) result.close();
            if (st != null) st.close();
            if (conn != null) conn.close();
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