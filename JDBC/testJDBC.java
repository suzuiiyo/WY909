package JDBC;

import java.sql.*;

public class testJDBC {
    public static void main(String[] args) {
        String sql = "select * from user where name = 'dashen' and password = 'thisispassword'";
        execute(sql);
    }

    public static void execute(String sql){
          try{
              Class.forName("com.mysql.cj.jdbc.Driver");
          }catch (ClassNotFoundException e){
              e.printStackTrace();
          }

          try(Connection c = DriverManager.getConnection("jdbc:mysql://localhost:3306/how2java?characterEncoding=utf-8", "root", "root");
          Statement s = c.createStatement();){
              ResultSet rs = s.executeQuery(sql);
              if(rs.next()) {
                  System.out.println("account secret is correct");
              }
              else {
                  System.out.println("account secret is error");
              }
          }catch (SQLException e){
              e.printStackTrace();
          }
    }
}
