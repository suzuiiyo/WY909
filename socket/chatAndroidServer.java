package socket;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.*;
import java.util.Objects;

/**
 * @author youpub
 */
public class chatAndroidServer {
    public static void main(String[] args) throws IOException {
        ServerSocket ss = new ServerSocket(8080);
        Socket s = ss.accept();

        InputStream is = s.getInputStream();
        DataInputStream dis = new DataInputStream(is);

        while(true) {
            String accept_str = dis.readUTF();
            String respon_str = Objects.requireNonNull(searchKeyword(accept_str)).response;
            System.out.println(respon_str);
        }
    }

    static public words searchKeyword(String keyword){
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
        }catch (ClassNotFoundException e){
            e.printStackTrace();
        }

        words w = null;
        try(Connection c = DriverManager.getConnection("jdbc:mysql://localhost:3306/android?characterEncoding=UTF-8", "root", "root");
            Statement s = c.createStatement()){
            String sql = "select * from dictionary where binary receive = '" + keyword + "'";

            ResultSet rs = s.executeQuery(sql);
            while(rs.next()){
                w = new words();
                int id = rs.getInt(1);
                String receive = rs.getString(2);
                String response = rs.getString(3);

                w.id = id;
                w.receive = receive;
                w.response = response;
            }

            return w;
        }catch (SQLException e){
            e.printStackTrace();
            return new words("no such response");
        }
    }
}
