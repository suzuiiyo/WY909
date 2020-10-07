package filter;

import javax.servlet.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class FirstFilter implements Filter {
    @Override
    public void init(FilterConfig filterConfig) throws ServletException {
        System.out.println("First Filter init()");
    }

    @Override
    public void doFilter(ServletRequest servletRequest, ServletResponse servletResponse, FilterChain filterChain) throws IOException, ServletException {
        HttpServletRequest request = (HttpServletRequest) servletRequest;
        HttpServletResponse response = (HttpServletResponse) servletResponse; 
        String           ip   = servletRequest.getRemoteAddr();
        String           url  = request.getRequestURL().toString();
        SimpleDateFormat sdf  = new SimpleDateFormat("yy-MM-dd HH: hh:mm:ss");
        Date             d    = new Date();
        String           date = sdf.format(d);

        System.out.printf("%s %s 访问了 %s%n", date, ip, url);
        filterChain.doFilter(servletRequest, servletResponse);
    }

    @Override
    public void destroy() {

    }
}
