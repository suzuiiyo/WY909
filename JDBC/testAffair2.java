package JDBC;

import java.sql.*;
import java.util.Scanner;

public class testAffair2 {
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

        try(Connection c = DriverManager.getConnection(basePort+databaseName+tail, userName, userPw);
        Statement st4Query = c.createStatement();
        Statement st4Delete = c.createStatement();
        Scanner s = new Scanner(System.in)){
            c.setAutoCommit(false);

            ResultSet rs = st4Query.executeQuery("select id from hero order by id asc limit 0, 10");
            while(rs.next()){
                int id = rs.getInt(1);
                System.out.println("try to delete id =" + id + " 's data");
                st4Delete.execute("delete from hero where id = " + id);
            }

            while(true){
                System.out.println("are you sure to delete these data(Y/N)");

                String str = s.next();
                if("Y".equals(str)){
                    c.commit();
                    System.out.println("commit delete");
                    break;
                }else if("N".equals(str)){
                    System.out.println("give up to delete");
                    break;
                }
            }
        }catch (SQLException e){
            e.printStackTrace();
        }
    }
}
