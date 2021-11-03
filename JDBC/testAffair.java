package JDBC;

import java.sql.*;

public class testAffair {
    public static void main(String[] args) {
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
        }catch (ClassNotFoundException e){
            e.printStackTrace();
        }

        String baseName = "jdbc:mysql://localhost:3306/";
        String dataBaseName = "how2java";
        String tail = "?characterEncoding=UTF-8";
        String userName = "root";
        String userPw = "root";

        try(Connection c = DriverManager.getConnection(baseName+dataBaseName+tail, userName, userPw);
        Statement s = c.createStatement();){

            c.setAutoCommit(false);

            String sql1 = "update hero set hp = hp + 1 where id = 22";
            s.execute(sql1);

            String sql2 = "updata hero set hp = hp -1 where id = 22";
            s.execute(sql2);

            c.commit();
        }catch (SQLException e){
            e.printStackTrace();
        }
    }
}
