package socket;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

/**
 * @author youpub
 */
public class wordsDAO {
    public wordsDAO(){
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
        }catch(ClassNotFoundException e){
            e.printStackTrace();
        }
    }

    public Connection getConnection() throws SQLException {
        return DriverManager.getConnection("jdbc:mysql://localhost:3306/android?characterEncoding=UTF-8", "root", "root");
    }

    public List<words> queryWords(String receive){
        List<words> ds = new ArrayList<words>();

        String sql = "select * from dictionary where receive = ?";
        try(Connection c = getConnection(); PreparedStatement ps = c.prepareStatement(sql)){
            ps.setString(1, receive);
            ResultSet rs = ps.executeQuery();
            while (rs.next()){
                words w = new words();
                int id = rs.getInt(1);
                String m_receive = rs.getString(2);
                String m_response = rs.getString(3);

                w.id = id;
                w.receive = m_receive;
                w.response = m_response;

                ds.add(w);
            }
        }catch (SQLException e){
            e.printStackTrace();
        }
        return  ds;
    }
}
