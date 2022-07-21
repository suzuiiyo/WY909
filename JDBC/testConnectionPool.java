package JDBC;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 * @author youpub
 */
public class testConnectionPool {
    List<Connection> cs = new ArrayList<Connection>();
    int size;

    public testConnectionPool(int size){
        this.size = size;
        init();
    }

    private void init() {
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            for(int i=0; i<size; i ++){
                Connection c = DriverManager.getConnection("jdbc:mysql://localhost:3306/how2java?characterEncoding=UTF-8", "root", "root");
                cs.add(c);
            }
        }catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        }
    }

    public synchronized Connection getConnection(){
        while (cs.isEmpty()){
            try{
                this.wait();
            }catch (InterruptedException e){
                e.printStackTrace();
            }
        }
        //if not empty
        Connection c = cs.remove(0);
        return c;
    }

    public synchronized void returnConnection(Connection c){
        //return connection and notify others
        cs.add(c);
        this.notifyAll();
    }
}
