package com.infortechn;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import oracle.jdbc.pool.OracleDataSource;

import java.io.FileReader;
import java.io.IOException;
import java.sql.*;
import java.util.Properties;

/**
 * Created by xl on 16-6-1.
 */
class Utils {

    private static Connection conn;
    private static Statement st;

    public static Properties loadSettings(String file) throws IOException {
        Properties p = new Properties();
        p.load(new FileReader(file));
        return p;
    }

    public static Connection getConn(Properties p) throws SQLException, IOException {
        OracleDataSource ds = new OracleDataSource();
        String host = p.getProperty("host"),
                port = p.getProperty("port"),
                instance = p.getProperty("instance"),
                user = p.getProperty("user"),
                password = p.getProperty("password");
        ds.setURL("jdbc:oracle:thin:@//" + host + ":" + port + "/" + instance);
        ds.setUser(user);
        ds.setPassword(password);

        conn = ds.getConnection();
        return conn;
    }

    public static Statement getStatement(Connection cn) throws IOException, SQLException {
        st = cn.createStatement();
        return st;
    }

    public static String rs2json(ResultSet rs) throws SQLException {
        Gson gson = new GsonBuilder().create();
        JsonObject json = new JsonObject();

        ResultSetMetaData md = rs.getMetaData();
        int column = md.getColumnCount();
        json.addProperty("column", column);
        JsonArray columns = new JsonArray();
        for (int i = 0; i < column; i++) {
            columns.add(md.getColumnName(i + 1));
        }
        json.add("columns", columns);

        int row = 0;
        JsonArray rows = new JsonArray();
        while (rs.next()) {
            JsonArray aRow = new JsonArray();
            for (int i = 0; i < column; i++) {
                aRow.add(rs.getString(i + 1));
            }
            rows.add(aRow);
            row++;
        }

        json.addProperty("row", row);
        json.add("rows", rows);

        return gson.toJson(json);
    }
}
