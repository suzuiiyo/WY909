package JDBC;

import charactor.Hero;

import java.sql.*;

public class testORM {
    public static Hero get(int id){
        Hero hero = null;
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
        }catch (ClassNotFoundException e){
            e.printStackTrace();
        }

        String basePort = "jdbc:mysql://localhost:3306/";
        String dataBaseName = "how2java";
        String tail = "?characterEncoding=UTF-8";
        String userName = "root";
        String userPw = "root";

        try(Connection c = DriverManager.getConnection(basePort+dataBaseName+tail, userName, userPw);
        Statement s = c.createStatement();){
            String sql = "select * from hero where id = " + id;
            ResultSet rs = s.executeQuery(sql);

            if(rs.next()){
                hero = new Hero();
                String name = rs.getString(2);
                float hp = rs.getFloat("hp");
                int damage = rs.getInt(4);
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

    public static void main(String[] args) {
        Hero h = get(107);
        if(h!=null) {
            System.out.println(h.name);
        }else {
            System.out.println("no such hero where id = 107");
        }
    }
}
