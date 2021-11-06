package com.how2j.jsoup;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;

import java.io.File;
import java.io.IOException;

public class testjsoup2 {
    static Document doc;

    public static void main(String[] args) throws IOException {
        File f = new File("/home/youpub/IdeaProjects/demo1/src/main/java/com/how2j/jsoup/a.html");
        if(!f.exists()) {
            return;
        }

        doc = Jsoup.parse(f, "utf-8");
        System.out.println(doc);

        Element e = doc.select("p").first();
        e.attr("class", "class1");

        e.appendText("Hello JSoup");
        System.out.println();
        System.out.println(doc);
    }
}
