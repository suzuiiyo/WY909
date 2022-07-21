package com.how2j.test;

import cn.hutool.core.convert.Convert;
import cn.hutool.core.util.EscapeUtil;
import cn.hutool.core.util.ReflectUtil;
import cn.hutool.core.util.StrUtil;
import org.junit.Test;

import java.lang.annotation.*;
import java.lang.reflect.Method;

import static java.lang.annotation.ElementType.METHOD;
import static java.lang.annotation.ElementType.TYPE;

public class testEscape {
    @Test
    @Comment("trans and transReserve")
    public void test2(){
        String s1 = "<script>location.href='http://how2j.cn';</script>";
        String s2 = EscapeUtil.escapeHtml4(s1);
        String s3 = EscapeUtil.unescapeHtml4(s2);

        p2("source data", s1, "trans", s2);
        p2("after trans", s2, "source data", s3);
    }

    private String preComment = null;
    private void c(String msg){
        System.out.printf("\tbackup: %s%n", msg);
    }

    private void p1(String type1, Object value1, String type2, Object value2){
        p(type1, value1, type2, value2, "format1");
    }

    private void p2(String type1, Object value1, String type2, Object value2){
        p(type1, value1, type2, value2, "format2");
    }

    private void p3(String type1, Object value1){
        p(type1, value1, "", "", "format3");
    }

    private void p(String type1, Object value1, String type2, Object value2, String format) {
        try{
            throw new Exception();
        }catch (Exception e){
            String methodName = getTestMethodName(e.getStackTrace());
            Method m = ReflectUtil.getMethod(this.getClass(), methodName);
            Comment annotation = m.getAnnotation(Comment.class);
            if(null != annotation){
                String comment = annotation.value();
                if(!comment.equals(preComment)){
                    System.out.printf("%n%s exap: %n%n", comment);
                    preComment = comment;
                }
            }
        }

        int padLength = 12;
        type1=StrUtil.padAfter(type1, padLength, Convert.toSBC(" ").charAt(0));
        type2=StrUtil.padAfter(type2, padLength, Convert.toSBC(" ").charAt(0));
        if("format1".equals(format)){
            System.out.printf("\t%s's:\t\"%s\" %n\t is converse to----->%n\t%s's :\t\"%s\" %n%n", type1, value1, type2, value2);
        }

        if("format2".equals(format)) {
            System.out.printf("\t base on %s:\t\"%s\" %n\t get %s:\t\"%s\"%n%n", type1, value1, type2, value2);
        }

        if("format3".equals(format)){
            System.out.printf("\t%S.\t\"%s\" %n\t%n", type1, value1);
        }
    }

    private String getTestMethodName(StackTraceElement[] stackTrace){
        for(StackTraceElement se : stackTrace){
            String methodName = se.getMethodName();
            if(methodName.startsWith("test")) {
                return methodName;
            }
        }
        return null;
    }

    @Target({METHOD, TYPE})
    @Retention(RetentionPolicy.RUNTIME)
    @Inherited
    @Documented
    public @interface Comment {
        String value();
    }
}
