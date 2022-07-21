package JDBC;

import java.sql.*;
import java.util.ArrayList;
import java.util.Scanner;

public class deleteEnsure {
    public static void main(String[] args) {
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
        }catch(ClassNotFoundException e){
            e.printStackTrace();
        }

        String basePort = "jdbc:mysql://localhost:3306/";
        String databaseName = "how2java";
        String tail = "?characterEncoding=UTF-8";
        String userName = "root";
        String userPw = "root";

        try(Connection c = DriverManager.getConnection(basePort+databaseName+tail, userName, userPw);
        Statement s = c.createStatement();
        Scanner sc = new Scanner(System.in);
        ){
            int totalNum = 0;
            String sql = "select count(*) from hero";
            s.execute(sql);
            ResultSet rs = s.getResultSet();
            if(rs.next()){
                totalNum = rs.getInt(1);
            }

            c.setAutoCommit(false);

            int num = 0;
            ArrayList<Integer> idList = new ArrayList<>();
            for(int i=0; i<totalNum; i++){
                String sql2 = "select * from hero where id = " + i;
                s.execute(sql2);
                ResultSet rs2= s.getResultSet();
                if (rs2.next()) {
                    System.out.println("try to delete id =" + i + " datas");
                    num++;
                    idList.add(i);
                    if(num == 9){
                        break;
                    }
                }
            }

            System.out.println("are you sure to delete these datas(Y/N):");
            String str = sc.next();
            if("Y".equals(str)){
                for(int i=0; i<idList.size(); i++){
                    String sql3 = "delete from hero where id = " + idList.get(i);
                    s.execute(sql3);
                }
                c.commit();
                System.out.println("submit delete operation");
            }else if("N".equals(str)){
                System.out.println("give up to delete");
            }

        }catch (SQLException e){
            e.printStackTrace();
        }
    }
}
