package JDBC;

import java.sql.Connection;
import java.sql.SQLException;
import java.sql.Statement;

/**
 * @author youpub
 */
public class ConnectionpoolWorkingThread extends Thread{
    private testConnectionPool cp;
    public ConnectionpoolWorkingThread(testConnectionPool cp){
        this.cp = cp;
    }

    @Override
    public void run(){
        Connection c = cp.getConnection();
        try(Statement st = c.createStatement()){
            for(int i=0; i<TestConnectionPool.insertTime; i++){
                String sql = "insert into hero values(null," + "'TIMOO'" + "," + 313.0f + "," +50 + ")";
                st.execute(sql);
            }
        }catch (SQLException e){
            e.printStackTrace();
        }
        cp.returnConnection(c);
    }
}
