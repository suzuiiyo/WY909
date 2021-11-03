package JDBC;

import java.sql.*;

public class getDatabaseMeta {
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

        try(Connection c = DriverManager.getConnection(basePort+databaseName+tail, userName, userPw);){
            DatabaseMetaData dbmd = c.getMetaData();

            System.out.println("database product name:\t"+ dbmd.getDatabaseProductName());
            //
            System.out.println("database product version:\t" + dbmd.getDatabaseProductVersion());
            //
            System.out.println("database and tables separator:\t" + dbmd.getCatalogSeparator());
            //
            System.out.println("database driver version:\t" + dbmd.getDriverName());
            //
            System.out.println("avaliable database tables:");
            //
            ResultSet rs = dbmd.getCatalogs();

            while(rs.next()){
                System.out.println("database name:\t" + rs.getString(1));
            }
        }catch (SQLException e){
            e.printStackTrace();
        }
    }
}
