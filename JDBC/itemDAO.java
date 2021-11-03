package JDBC;
import com.mysql.cj.jdbc.CallableStatement;
import property.Item;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

/**
 * @author youpub
 */
public class itemDAO{
    public itemDAO() {
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
        }catch (ClassNotFoundException e){
            e.printStackTrace();
        }
    }

    public Connection getConnction() throws SQLException {
        return DriverManager.getConnection("jdbc:mysql://localhost:3306/how2java?characterEncoding=UTF-8", "root", "root");
    }

    public void getTotal() {
        int total = 0;
        try(Connection c = getConnction(); Statement s = c.createStatement();) {
            String sql =  "select count(*) from item";
            ResultSet rs = s.executeQuery(sql);
            while (rs.next()){
                total = rs.getInt(1);
            }
            System.out.println("total:" + total);
        }catch (SQLException e){
            e.printStackTrace();
        }
    }

    public void add(Item item) {
        String sql = "insert into item values(null, ?, ?)";
        try(Connection c = getConnction(); PreparedStatement ps = c.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)){
            ps.setString(1, item.name);
            ps.setInt(2, item.price);

            ps.execute();

            //get auto increment id
            ResultSet rs = ps.getGeneratedKeys();
            if(rs.next()){
                int id = rs.getInt(1);
                item.id = id;
            }
        }catch (SQLException e){
            e.printStackTrace();
        }
    }

    public void update(Item item) {
        String sql = "update item set name = ?, price = ? where id = ?";
        try(Connection c  = getConnction(); PreparedStatement ps = c.prepareStatement(sql)){
            ps.setString(1, item.name);
            ps.setInt(2, item.price);
            ps.setInt(3, item.id);

            ps.execute();
        }catch (SQLException e){
            e.printStackTrace();
        }
    }

    public void delete(int id) {
        try(Connection c = getConnction(); Statement s = c.createStatement()){
            String sql = "delete from item where id = " + id;
            s.execute(sql);
        }catch (SQLException e){
            e.printStackTrace();
        }
    }

    public Item get(int id) {
        Item i = null;
        try(Connection c = getConnction(); Statement s = c.createStatement()){
            String sql = "select * from item where id = " + id;

            ResultSet rs = s.executeQuery(sql);
            if(rs.next()){
                i = new Item();
                String name = rs.getString("2");
                int price = rs.getInt("3");

                i.name = name;
                i.price = price;
                i.id = id;
            }
        }catch (SQLException e){
            e.printStackTrace();
        }
        return  i;
    }

    public List<Item> list() {
        return list(0, Short.MAX_VALUE);
    }

    public List<Item> list(int start, int count) {
        List<Item> items = new ArrayList<>();
        String sql = "select * from item order by id desc limit ?, ?";
        try(Connection c = getConnction(); PreparedStatement ps = c.prepareStatement(sql)) {
            ps.setInt(1, start);
            ps.setInt(2, count);

            ResultSet rs = ps.executeQuery();
            while(rs.next()){
                Item item = new Item();
                int id = rs.getInt(1);
                String name = rs.getString(2);
                int price = rs.getInt(3);

                item.id = id;
                item.name = name;
                item.price = price;

                items.add(item);
            }
        }catch (SQLException e){
            e.printStackTrace();
        }
        return  items;
    }
}
