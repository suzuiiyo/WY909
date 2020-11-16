package dao;

import bean.Order;

import java.sql.*;

public class OrderDao extends DbUtil {
    public void insert(Order order){
        String sql = "INSERT INTO order_ values(null, ?)";
        try(Connection conn = getConn(); PreparedStatement ps = conn.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)){
            ps.setInt(1, order.getUser().getId());
            ps.executeUpdate();

            ResultSet rs = ps.getGeneratedKeys();
            if(rs.next()){
                int id = rs.getInt(1);
                order.setId(id);
            }
        }catch (SQLException e){
            e.printStackTrace();
        }
    }
}
