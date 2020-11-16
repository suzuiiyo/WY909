<%--
  Created by IntelliJ IDEA.
  User: yanGw
  Date: 2020/11/12
  Time: 16:45
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" pageEncoding="UTF-8" import="java.util.*" isELIgnored="false" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<script src="${pageContext.request.contextPath}/webjars/jquery/3.5.1/jquery.min.js"></script>

<script>
    $(function(){
        $("input.addCartButton").removeAttr("disabled");
        $("input.addCartButton").click(function(){
            $(this).attr("disabled", "disabled");
            var button = $(this);
            var pid = $(this).attr("pid");
            var number = $("input.number[pid="+pid+"]").val();
            var page = "/addOrderItem";
                $.get(
                    page,
                    {"num":number, "pid":pid},
                    function(result){
                        $("#addCartSuccessMessage").fadeIn(1200);
                        $("#addCartSuccessMessage").fadeOut(1200, function(){
                            button.removeAttr("disabled");
                        });
                    }
                );
        });
        $("#addCartSuccessMessage").hide();
    });
</script>
<html>
<head>
    <title>商品展示</title>
</head>
<body style="background-image: url(wallhaven-4x33gl_3840x3072.png); background-size: 100% 100%; background-attachment: fixed">
    <h1 style="font-size: xx-large; font-family: '微软雅黑 Light',sans-serif; color: indigo" align="center">商品展示</h1>
    <c:if test="${!empty user}">
        <div align="center">
            当前用户: ${user.name}
        </div>
    </c:if>

    <table style="width:450px; margin: 44px auto" align="center" border="1" cellspacing="0">
        <tr>
            <td>id</td>
            <td>名称</td>
            <td>价格</td>
            <td>购买</td>
        </tr>
        <c:forEach items="${products}" var="product" varStatus="st">
            <tr>
                <td>${product.id}</td>
                <td>${product.name}</td>
                <td>${product.price}</td>
                <td>
                        数量<label>
                    <input pid="${product.id}" class="number" type="text" value="1" name="num">
                </label>
                    <input class="addCartButton" pid="${product.id}" type="submit" value="加入购物车">
                </td>
            </tr>
        </c:forEach>
        <tr>
            <td colspan="6" align="center">
                <a href="${pageContext.request.contextPath}/listOrderItem">查看购物车</a>
            </td>
        </tr>
    </table>
</body>
</html>
