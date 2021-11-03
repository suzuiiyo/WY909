package JDBC;

import java.sql.*;

public class testAutoIncrease {
    public static void main(String[] args) {
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
        }catch (ClassNotFoundException e){
            e.printStackTrace();
        }

        String basePort = "jdbc:mysql://localhost:3306/";
        String databaseName = "how2java";
        String tail = "?characterEncoding=UTF-8";
        String userName = "root";
        String userPw = "root";

        String sql = "insert into hero values(null, ?, ?, ?)";
        try(Connection c = DriverManager.getConnection(basePort+databaseName+tail, userName, userPw);
            PreparedStatement ps = c.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS);){
            ps.setString(1, "gaigai");
            ps.setFloat(2, 797);
            ps.setInt(3, 100);

            ps.execute();

            ResultSet rs = ps.getGeneratedKeys();
            if(rs.next()){
                int id = rs.getInt(1);
                System.out.println(id);
            }

        }catch (SQLException e){
            e.printStackTrace();
        }
    }
}
