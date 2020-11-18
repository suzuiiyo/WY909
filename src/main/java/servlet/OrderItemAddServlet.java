package servlet;

import bean.OrderItem;
import bean.Product;
import dao.ProductDao;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;

/**
 * @author yanGw
 */
public class OrderItemAddServlet extends HttpServlet {
    @Override
    protected void service(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        int num = Integer.parseInt(req.getParameter("num"));
        int pid = Integer.parseInt(req.getParameter("pid"));

        Product product = new ProductDao().getProduct(pid);

        //根据product和oi创建OrderItem对象
        OrderItem oi = new OrderItem();
        oi.setProduct(product);
        oi.setNum(num);

        List<OrderItem> ois = (List<OrderItem>) req.getSession().getAttribute("ois");
        if (null == ois) {
            ois = new ArrayList<>();
            req.getSession().setAttribute("ois", ois);
        }

        boolean found = false;
        for (OrderItem orderItem : ois) {
            //session中去除的product的id和页面获取的product的id一样
            if (orderItem.getProduct().getId() == oi.getProduct().getId()) {
                //已有的数量和页面获取的新增的数量
                orderItem.setNum(orderItem.getNum() + oi.getNum());
                found = true;
                break;
            }
        }
        //如果没有找到
        if (!found) {
            ois.add(oi);
        }
        ois.add(oi);

        resp.sendRedirect("/listOrderItem");
    }
}
