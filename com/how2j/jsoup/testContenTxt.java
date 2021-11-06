package com.how2j.jsoup;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;

import java.io.File;
import java.io.IOException;

public class testContenTxt {
    public static void main(String[] args) throws IOException {
        File f = new File("/home/youpub/IdeaProjects/demo1/src/main/java/com/how2j/jsoup/c.html");
        if(!f.exists()) {
            return;
        }
        Document doc = Jsoup.parse(f, "utf-8");
        Element e = doc.getElementById("d1");

        //get property
        System.out.println(e.attr("id"));

        //get all attributes
        System.out.println(e.attributes());

        //get id
        System.out.println(e.id());

        //get class name
        System.out.println(e.className());

        //get all class names
        System.out.println(e.classNames());

        //get txt
        System.out.println(e.text());

        //get html
        System.out.println(e.html());

        //get outhtml
        System.out.println(e.outerHtml());

        //get tagInfo
        System.out.println(e.tagName());
    }
}
