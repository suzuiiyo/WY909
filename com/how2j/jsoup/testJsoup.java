package com.how2j.jsoup;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

/**
 * @author youpub
 */
public class testJsoup {
    public static void main(String[] args) {
        File f = new File("/home/youpub/Downloads/IL5008A.cid");
        try(FileReader fr = new FileReader(f);) {
            char[] buffer = new char[(int)f.length()];
            fr.read(buffer);
            String xml = String.valueOf(buffer);
            Document doc = Jsoup.parse(xml);

            Elements as = doc.getElementsByTag("LN");
            for(Element e : as){
                System.out.println(e.text());
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
//        String html = "<web-app>\n" +
//                "  \n" +
//                "    <servlet>\n" +
//                "        <servlet-name>HelloServlet</servlet-name>\n" +
//                "        <servlet-class>HelloServlet</servlet-class>\n" +
//                "    </servlet>\n" +
//                "  \n" +
//                "    <servlet-mapping>\n" +
//                "        <servlet-name>HelloServlet</servlet-name>\n" +
//                "        <url-pattern>/hello</url-pattern>\n" +
//                "    </servlet-mapping>\n" +
//                "  \n" +
//                "</web-app>";
    }
}
