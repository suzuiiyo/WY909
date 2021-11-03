package JDBC;

public class getConn {
    String basePort = "jdbc:mysql://localhost:3306/";
    String dataBaseName = "how2java";
    String tail = "?chracterEncoding=UTF-8";
    String userName = "root";
    String userPw = "root";

    public getConn() {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
