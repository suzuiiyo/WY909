package JDBC;

import java.sql.*;

public class testPageDivSearch {
    public static void list(int start, int count) {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }

        String basePort = "jdbc:mysql://localhost:3306/";
        String dataBaseName = "how2java";
        String tail = "?CharacterEncoding=UTF-8";
        String userName = "root";
        String userPw = "root";

        try (Connection c = DriverManager.getConnection(basePort + dataBaseName + tail, userName, userPw);
             Statement s = c.createStatement();) {
            String sql = "select * from hero limit " + start + "," + count;
            boolean isQUery = s.execute(sql);
            if(isQUery){
                ResultSet rs = s.getResultSet();
                while (rs.next()){
                    int id = rs.getInt("id");
                    String name = rs.getString(2);
                    float hp = rs.getFloat("hp");
                    int damage = rs.getInt(4);
                    System.out.printf("%d\t%s\t%f\t%d%n", id, name, hp, damage);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        list(10, 5);
    }
}
