package com.how2j.jsoup;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.io.File;
import java.io.IOException;

public class testElement {
    public static void main(String[] args) throws IOException {
        File f = new File("/home/youpub/IdeaProjects/demo1/src/main/java/com/how2j/jsoup/b.html");
        if(!f.exists()) {
            return;
        }

        Document doc = Jsoup.parse(f, "utf-8");

        //by id
        Element e = doc.getElementById("productName");
        System.out.println(e);

        //by tag
        Elements es;
        es = doc.getElementsByTag("a");
        show(es);

        //by kinds of names
        es = doc.getElementsByClass("RightBox");
        show(es);

        //by properties
        es = doc.getElementsByAttribute("name");
        show(es);
    }

    private static void show(Elements es){
        for(Element e : es){
            System.out.println(e);
        }
    }
}
