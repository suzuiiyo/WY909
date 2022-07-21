package JDBC;

import java.sql.Connection;
import java.sql.SQLException;
import java.sql.Statement;

public class poolinsert100 {
    public static void main(String[] args) {
        testConnectionPool cp = new testConnectionPool(10);
        long t1 = System.currentTimeMillis();
        for(int i=0; i<100; i++){
            new WorkingThread("working thread" + i, cp).start();
        }
        long t2 = System.currentTimeMillis();
        System.out.println(t2 - t1);
    }

    static class WorkingThread extends Thread{
        private testConnectionPool cp;
        public WorkingThread(String name, testConnectionPool cp){
            super(name);
            this.cp = cp;
        }

        @Override
        public void run() {
            Connection c = cp.getConnection();
            try(Statement s = c.createStatement()){
                s.execute("insert into hero value(null, 'pool', 76.3, 89)");
            }catch (SQLException e){
                e.printStackTrace();
            }
            cp.returnConnection(c);
        }
    }
}
