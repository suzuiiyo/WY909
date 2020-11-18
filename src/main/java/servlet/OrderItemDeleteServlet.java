package servlet;

import bean.Order;
import bean.OrderItem;
import bean.Product;
import dao.ProductDao;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class OrderItemDeleteServlet extends HttpServlet {
    @Override
    protected void service(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        int pid = Integer.parseInt(req.getParameter("pid"));

        List<OrderItem> ois = (List<OrderItem>) req.getSession().getAttribute("ois");
        List<OrderItem> ois4Delete = new ArrayList<>();
        /*if(null != ois){
            for(OrderItem oi : ois){
                if(oi.getProduct().getId() == pid){
                    ois4Delete.add(oi);
                }
            }
            ois.removeAll(ois4Delete);
        }*/
        ois.removeIf(oi -> oi.getProduct().getId() == pid);
        resp.sendRedirect("/listOrderItem");
    }
}
