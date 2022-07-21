package JDBC;

import java.sql.*;

public class troditionInsert100 {
    public troditionInsert100(){
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
        }catch (ClassNotFoundException e){
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        long t1 = System.currentTimeMillis();
        for(int i=0; i<100; i++){
            try(Connection c = DriverManager.getConnection("jdbc:mysql://localhost:3306/how2java?character=UTF-8", "root", "root");
                Statement s = c.createStatement()){
                String sql = "insert into hero value(null, 'TWICE', 87.2, 761)";
                s.execute(sql);
            }catch (SQLException e){
                e.printStackTrace();
            }
        }
        long t2 = System.currentTimeMillis();

        System.out.println(t2 - t1);
    }
}
