package dao;

import java.awt.event.ContainerListener;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

/**
 * @author yanGw
 */
public class DbUtil{
    String drive = "com.mysql.cj.jdbc.Driver";
    String url = "jdbc:mysql://localhost:3306/";
    String database = "cart";
    String factor = "?characterEncoding=UTF-8&serverTimezone=UTC";
    String user = "root";
    String password = "admin";

    public Connection getConn(){
        Connection conn = null;
        try{
            Class.forName(drive);
            conn = DriverManager.getConnection(url + database + factor, user, password);
        }catch (ClassNotFoundException | SQLException e){
            e.printStackTrace();
        }
        return conn;
    }

    public static void getClose(Connection conn) throws SQLException {
        if(null != conn){
            conn.close();
        }
    }
}
