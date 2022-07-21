package com.how2j.test;

import cn.hutool.core.convert.Convert;
import cn.hutool.core.util.HexUtil;
import cn.hutool.core.util.ReflectUtil;
import cn.hutool.core.util.StrUtil;
import org.junit.Test;

import java.awt.*;
import java.lang.annotation.*;
import java.lang.reflect.Method;

import static java.lang.annotation.ElementType.METHOD;
import static java.lang.annotation.ElementType.TYPE;

public class testHex {
    @Test
    @Comment("judge whether or not hex")
    public void test1(){
        String s1 = "12";
        boolean b1 = HexUtil.isHexNumber(s1);
        String s2 = "0x12";
        boolean b2 = HexUtil.isHexNumber(s2);

        p2("String", s1, "whether or not hex", b1);
        p2("String", s2, "whether or not hex", b2);
    }

    @Test
    @Comment("String converse Hex")
    public void test2(){
        String s1 = "how2j.cn - java way";
        String s2 = HexUtil.encodeHexStr(s1);
        String s3 = HexUtil.encodeHexStr(s2);

        p2("source data", s1, "Hex code", s2);
        p2("hex", s2, "Hex decode", s3);
    }

    @Test
    @Comment("color change")
    public void test3(){
        Color color1 = Color.red;
        String s1 = HexUtil.encodeColor(color1);
        String s2 = "#112233";
        Color color2 = HexUtil.decodeColor(s2);
        p2("color object1", color1, "String", s1);
        p2("String", s2, "color objecct2", color2);
    }

    private String preComment = null;
    private void c(String msg){
        System.out.printf("\tackup: %s%n", msg);
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
        try {
            throw new Exception();
        } catch (Exception e) {
            String methodName = getTestMethodName(e.getStackTrace());
            Method m = ReflectUtil.getMethod(this.getClass(), methodName);
            Comment annotation = m.getAnnotation(Comment.class);
            if (null != annotation) {
                String comment = annotation.value();
                if (!comment.equals(preComment)) {
                    System.out.printf("%n%s exp: %n%n", comment);
                    preComment = comment;
                }
            }
        }
        int padLength = 12;
        type1 = StrUtil.padAfter(type1, padLength, Convert.toSBC(" ").charAt(0));
        type2 = StrUtil.padAfter(type2, padLength, Convert.toSBC(" ").charAt(0));
        if ("format".equals(format)) {
            System.out.printf("\t%s's:\t\"%s\" %n\t convert to------------>%n\t%s's :\t\"%s\" %n%n", type1, value1, type2, value2);
        }
        if ("format2".equals(format)) {
            System.out.printf("\tbase %s:\t\"%s\" %n\t get %s:\t\"%s\"%n%n", type1, value1, type2, value2);
        }
        if ("format3".equals(format)) {
            System.out.printf("\t%s:\t\"%s\" %n\t%n", type1, value1);
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
    public @interface Comment{
        String value();
    }
}