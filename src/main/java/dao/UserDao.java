package dao;

import bean.User;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UserDao extends DbUtil {

    public User getUser(String name, String password) {
        User result = null;
        String sql  = "SELECT * from user where name = ? and password = ?";
        try (Connection conn = getConn(); PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setString(1, name);
            ps.setString(2, password);
            ResultSet rs = ps.executeQuery();
            while (rs.next()) {
                result = new User();
                int id = rs.getInt(1);

                result.setId(id);
                result.setName(name);
                result.setPassword(password);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return result;
    }

    public void insert(User user) {
        String sql = "INSERT INTO user values(null, ?, ?)";
        try (Connection conn = getConn(); PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setString(1, user.getName());
            ps.setString(2, user.getPassword());
            ps.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
