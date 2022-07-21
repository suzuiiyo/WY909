package JDBC;

import java.sql.*;

public class testDeleteLastAuto {
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

        String sql = "insert into hero values(null, ?, ?, ?)";
        try(Connection c = DriverManager.getConnection(basePort+databaseName+tail, userName, userPw);
            PreparedStatement ps = c.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS);
            Statement st = c.createStatement();) {
            ps.setString(1, "gaigai");
            ps.setFloat(2, 123);
            ps.setInt(3, 100);

            ps.execute();

            ResultSet rs1 = ps.getGeneratedKeys();
            int autoId = -1;
            if(rs1.next()){
               autoId = rs1.getInt(1);
            }
            System.out.println("insert just datas'id is:" + autoId);

            for(int i=autoId-1; i>0; i--){
                int targetId = i;
                String sql2 = "select * from hero where id = " + targetId;
                ResultSet rs2 = st.executeQuery(sql2);

                if(rs2.next()){
                    System.out.println("id=" + targetId + " data exist and delete it");
                    String deleteSQL = "delete from hero where id = " + targetId;
                    st.execute(deleteSQL);
                    break;
                }
            }
        }catch (SQLException e){
            e.printStackTrace();
        }
    }
}
