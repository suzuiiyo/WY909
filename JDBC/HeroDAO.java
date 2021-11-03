package JDBC;

import charactor.Hero;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class HeroDAO implements DAO{
    public HeroDAO(){
        try{
            Class.forName("com.mysql.jdbc.Driver");
        }catch (ClassNotFoundException e){
            e.printStackTrace();
        }
    }

    public Connection getConnection() throws SQLException{
        return DriverManager.getConnection("jdbc:mysql://localhost:3306/how2java?characterEncoding=UTF-8", "root", "root");
    }

    public int getTotal(){
        int total = 0;
        try(Connection c = getConnection(); Statement s = c.createStatement();){
            String sql = "select count(*) from hero";
            ResultSet rs = s.executeQuery(sql);
            while (rs.next()){
                total = rs.getInt(1);
            }
            System.out.println("total: " + total);
        }catch (SQLException e){
            e.printStackTrace();
        }
        return total;
    }

    @Override
    public void add(Hero hero) {
        String sql = "insert into hero values(null, ?, ?, ?)";
        try(Connection c = getConnection(); PreparedStatement ps = c.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS);){
            ps.setString(1, hero.name);
            ps.setFloat(2, hero.hp);
            ps.setFloat(3, hero.damage);

            ps.execute();

            //get increase ID to be convenient for using after;
            ResultSet rs = ps.getGeneratedKeys();
            if(rs.next()){
                int id = rs.getInt(1);
                hero.id = id;
            }
        }catch (SQLException e){
            e.printStackTrace();
        }
    }

    @Override
    public void update(Hero hero) {
        String sql = "update hero set name = ?, hp = ?, damage =? where id = ?";
        try(Connection c = getConnection(); PreparedStatement ps = c.prepareStatement(sql);){
            ps.setString(1, hero.name);
            ps.setFloat(2, hero.hp);
            ps.setFloat(3, hero.damage);
            ps.setInt(3, hero.id);

            ps.execute();
        }catch (SQLException e){
            e.printStackTrace();
        }
    }

    @Override
    public void delete(int id) {

        try(Connection c = getConnection(); Statement s = c.createStatement();){
            String sql = "delete from hero where id =" + id;
            s.execute(sql);
        }catch (SQLException e){
            e.printStackTrace();
        }

    }

    @Override
    public Hero get(int id) {
        Hero hero = null;
        try(Connection c = getConnection(); Statement s = c.createStatement();){
            String sql = "select * from hero where id = " + id;
            ResultSet rs = s.executeQuery(sql);

            if(rs.next()){
                hero = new Hero();
                String name = rs.getString(1);
                float hp = rs.getFloat("hp");
                float damage = rs.getFloat("3");

                hero.name = name;
                hero.hp = hp;
                hero.damage = damage;
                hero.id = id;
            }
        }catch (SQLException e){
            e.printStackTrace();
        }
        return hero;
    }

    @Override
    public List<Hero> list() {
        return list(0, Short.MAX_VALUE);
    }

    @Override
    public List<Hero> list(int start, int count) {
        List<Hero> heros = new ArrayList<>();
        String sql = "select * from hero order by id asc limit ?, ?";
        try(Connection c = getConnection(); PreparedStatement ps = c.prepareStatement(sql);) {
            ps.setInt(1, start);
            ps.setInt(2, count);

            ResultSet rs = ps.executeQuery();
            while (rs.next()){
                Hero h = new Hero();
                int id = rs.getInt(1);
                String name = rs.getString(2);
                float hp = rs.getFloat(3);
                float damage = rs.getFloat(4);

                h.id = id;
                h.name = name;
                h.hp = hp;
                h.damage = damage;

                heros.add(h);
            }
        }catch(SQLException e){
            e.printStackTrace();
        }
        return  heros;
    }
}
