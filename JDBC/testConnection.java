package JDBC;

import java.sql.Connection;
import java.sql.SQLException;
import java.sql.Statement;

public class testConnection {
    public static void main(String[] args) {
        testConnectionPool testcp = new testConnectionPool(3);

        for(int i=0; i<100; i++) {
            Thread t1 = new Thread() {
                @Override
                public void run() {
                    Connection c = testcp.getConnection();
                    System.out.println(Thread.currentThread().getName() + " get a connection, and start to work");
                    try (Statement s = c.createStatement()) {
                        Thread.sleep(1000);
                        String sql = "select count(*) from hero";
                        s.execute(sql);
                    } catch (SQLException | InterruptedException e) {
                        e.printStackTrace();
                    }
                    testcp.returnConnection(c);
                }
            };
            t1.setName("working thread" + i);
            t1.start();
        }
    }
}
