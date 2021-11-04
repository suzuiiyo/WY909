package JDBC;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;

/**
 * @author youpub
 */
public class TraditionalWorkingThread extends Thread{
    @Override
    public void run(){
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
        }catch (ClassNotFoundException e1){
            e1.printStackTrace();
        }

        try(Connection c = DriverManager.getConnection("jdbc:mysql://localhost:3306/how2java?characterEncoding=UTF-8", "root", "root");
        Statement st = c.createStatement()){
            for(int i=0; i<TestConnectionPool.insertTime; i++){
                String sql = "insert into hero values(null," + "'TIMOO'" + "," + 313.0f + "," + 50 + ")";
                st.execute(sql);
            }
        }catch (SQLException e){
            e.printStackTrace();
        }
    }
}
