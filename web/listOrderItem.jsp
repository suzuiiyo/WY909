<%--
  Created by IntelliJ IDEA.
  User: yanGw
  Date: 2020/11/12
  Time: 17:25
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" pageEncoding="UTF-8" import="java.util.*" isELIgnored="false" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<html>
<head>
    <title>购物车展示</title>
    <h1 style="font-size: xx-large; font-family: '微软雅黑 Light',sans-serif; color: indigo" align="center">购物车</h1>
</head>
<body style="background-image: url(wallhaven-4x33gl_3840x3072.png); background-size: 100% 100%; background-attachment: fixed">
    <c:if test="${!empty user}">
        <div align="center">
            当前用户: ${user.name}
        </div>
    </c:if>

    <table style="width: 450px; margin: 44px auto" align="center" border="1" cellspacing="0">
        <tr>
            <td>商品名</td>
            <td>单价</td>
            <td>数量</td>
            <td>小计</td>
            <td>删除</td>
        </tr>

        <c:forEach items="${ois}" var="oi" varStatus="st">
            <tr>
                <td>${oi.product.name}</td>
                <td>${oi.product.price}</td>
                <td>${oi.num}</td>
                <td>${oi.product.price*oi.num}</td>
                <td><a href="deleteOrderItem?pid=${oi.product.id}">删除</a></td>
            </tr>
        </c:forEach>
        <tr>
            <td colspan="6" align="center">
                <a href="listProduct">继续购物</a>
            </td>
        </tr>
    </table>
</body>
</html>
