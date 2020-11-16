package dao;

import bean.Product;

import java.nio.file.Path;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 * @author yanGw
 */
public class ProductDao extends DbUtil{
    public Product getProduct(int id){
        Product result = null;
        String sql = "SELECT * FROM product where id = ?";
        try(Connection conn = getConn(); PreparedStatement ps = conn.prepareStatement(sql)){
            ps.setInt(1, id);
            ResultSet rs = ps.executeQuery();
            while(rs.next()){
                result = new Product();
                String name = rs.getString(2);
                Float price = rs.getFloat(3);

                result.setName(name);
                result.setPrice(price);
            }
        }catch (SQLException e){
            e.printStackTrace();
        }
        return result;
    }

    public List<Product> listProduct(){
        return listProduct(0, Short.MAX_VALUE);
    }

    public List<Product> listProduct(int start, int count) {
        List<Product> products = new ArrayList<>();
        Product result = null;
        String        sql      = "SELECT * FROM product order by id desc limit ?, ?";
        try (Connection conn = getConn(); PreparedStatement ps = conn.prepareStatement(sql)) {
            ps.setInt(1, start);
            ps.setInt(2, count);
            ResultSet rs = ps.executeQuery();
            while (rs.next()){
                result = new Product();
                int id = rs.getInt(1);
                String name = rs.getString("name");
                float price = rs.getFloat("price");

                result.setId(id);
                result.setName(name);
                result.setPrice(price);

                products.add(result);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return products;
    }
}
