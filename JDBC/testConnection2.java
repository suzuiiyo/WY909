package JDBC;

import java.sql.Connection;
import java.sql.SQLException;
import java.sql.Statement;

public class testConnection2 {
    public static void main(String[] args) {
        testConnectionPool cp = new testConnectionPool(3);
        for(int i=0; i<100; i++){
            new WorkingThread("working thread" + i, cp).start();
        }
    }

    static class WorkingThread extends Thread {
        private testConnectionPool cp;
        public WorkingThread(String name, testConnectionPool cp){
            super(name);
            this.cp = cp;
        }

        @Override
        public void run() {
            Connection c = cp.getConnection();
            System.out.println(this.getName() + ":\t get a connection, start to work");
            try(Statement s = c.createStatement()){
                Thread.sleep(1000);
                s.execute("select * from hero");
            }catch (SQLException | InterruptedException e){
                e.printStackTrace();
            }
            cp.returnConnection(c);
        }
    }
}
