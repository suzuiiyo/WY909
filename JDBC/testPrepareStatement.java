package JDBC;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class testPrepareStatement {
    public static void main(String[] args) {
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
        }catch (ClassNotFoundException e){
            e.printStackTrace();
        }

        String sql = "insert into hero values(null, ?, ?, ?)";
        try(Connection c = DriverManager.getConnection("jdbc:mysql://localhost:3306/how2java?characterEncoding=Utf-8", "root", "root");
            PreparedStatement ps = c.prepareStatement(sql);){
            ps.setString(1, "TIMOO");
            ps.setFloat(2, 313.0f);
            ps.setInt(3, 50);
            ps.executeUpdate();
        }catch (SQLException e){
            e.printStackTrace();
        }
    }
}
