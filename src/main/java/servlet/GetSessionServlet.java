package servlet;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Enumeration;

public class GetSessionServlet extends HttpServlet {
    @Override
    protected void service(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("text/html; charset=UTF-8");
        PrintWriter out = resp.getWriter();
        //获取session
        HttpSession session = req.getSession();
        //获取session中所有的键值
        Enumeration<String> attrs = session.getAttributeNames();
        //遍历attrs中的
        while(attrs.hasMoreElements()){
            //获取session键值
            String name = attrs.nextElement();
            //根据键值取session中的值
            Object value = session.getAttribute(name);
            //打印结果
            out.println(name + ": " + value + "<br>");
        }
    }
}
