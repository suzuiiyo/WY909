<%--
  Created by IntelliJ IDEA.
  User: yanGw
  Date: 2020/11/12
  Time: 15:46
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>登录</title>
    <style type="text/css">
        .divForm{
            position: absolute;
            width: 500px;
            height: 300px;

            text-align: center;
            color:black;

            top: 50%;
            left: 50%;
            margin-top: -200px;
            margin-left: -250px;
        }
    </style>
</head>
<body style="background-image: url(wallhaven-4x33gl_3840x3072.png); background-size: 100% 100%; background-attachment: fixed">
    <div align="center">
        <form action="login" method="post" class="divForm">
            <p>
                账户<input type="text" name="name" placeholder="请输入账户名">
            </p>
            <p>
                密码<input type="text" name="password" placeholder="请输入账户密码">
            </p>
            <input type="submit" value="登录">
        </form>
    </div>
</body>
</html>
