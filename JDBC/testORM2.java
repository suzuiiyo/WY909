package JDBC;

import charactor.Hero;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class testORM2 {
    public static void add(Hero h){
        getConn conn = new getConn();
        String sql = "insert into hero values(?, ?, ?, ?)";
        try(Connection c = DriverManager.getConnection(conn.basePort+conn.dataBaseName+conn.tail, conn.userName, conn.userPw);
            PreparedStatement ps = c.prepareStatement(sql);){
            ps.setInt(1, h.id);
            ps.setString(2, h.name);
            ps.setFloat(3, h.hp);
            ps.setFloat(4, h.damage);
            ps.execute();
        }catch (SQLException e){
            e.printStackTrace();
        }
    }

    public static void delete(Hero h){
        getConn conn = new getConn();
        try(Connection c = DriverManager.getConnection(conn.basePort+conn.dataBaseName+conn.tail, conn.userName, conn.userPw);
        Statement s = c.createStatement();) {
            String sql = "delete from hero where id =" + h.id;
            s.execute(sql);
        }catch (SQLException e){
            e.printStackTrace();
        }
    }

    public static void update(Hero h){
        getConn conn = new getConn();
        String sql = "update hero set name = ?, hp = ?, damage = ? where id = ?";
        try(Connection c= DriverManager.getConnection(conn.basePort+ conn.dataBaseName+conn.tail, conn.userName, conn.userPw);
        PreparedStatement ps = c.prepareStatement(sql);){
            ps.setInt(4, h.id);
            ps.setString(1, h.name);
            ps.setFloat(2, h.hp);
            ps.setFloat(3, h.damage);

            ps.execute();
        }catch (SQLException e){
            e.printStackTrace();
        }
    }

    public static List<Hero> list(){
        getConn conn = new getConn();
        List<Hero> heros = new ArrayList<>();
        String sql = "select * from hero";
        try(Connection c = DriverManager.getConnection(conn.basePort+conn.dataBaseName+conn.tail, conn.userName, conn.userPw);
        Statement s = c.createStatement();){
            ResultSet rs = s.executeQuery(sql);
            while (rs.next()){
                Hero h = new Hero();
                int id = rs.getInt(1);
                String name = rs.getString(2);
                float hp = rs.getFloat(3);
                float damage = rs.getFloat(4);

                h.id = id;
                h.name=name;
                h.hp=hp;
                h.damage=damage;

                heros.add(h);
            }
        }catch (SQLException e){
            e.printStackTrace();
        }
        return heros;
    }

    public static void main(String[] args) {
        Hero h = new Hero();
        h.id = 80;
        h.name = "KKL";
        h.hp = 967.8f;
        h.damage = 312;

        update(h);
        List<Hero> heros = list();
        for(Hero hero : heros){
            System.out.println(hero.toString());
        }
    }
}
