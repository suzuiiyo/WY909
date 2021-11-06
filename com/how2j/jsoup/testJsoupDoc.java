package com.how2j.jsoup;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.net.URL;

public class testJsoupDoc {
    public static void main(String[] args) {
        File f = new File("/home/youpub/Downloads/IL5008A.cid");
        try(FileReader fr = new FileReader(f)){
            char[] buffer = new char[(int) f.length()];
            fr.read(buffer);
            String xml = String.valueOf(buffer);

            Document doc1 = Jsoup.parse(xml);
//            System.out.println("基于字符串方式得到的 Document:\r\n"+ doc1);

            if(f.exists()){
                Document doc2 = Jsoup.parse(f, "utf-8");
//                System.out.println("基于文件方式得到的 Document:\r\n"+ doc2);
            }

            String url = "http://www.baidu.com";
            Document doc3 = Jsoup.parse(new URL(url), 5000);
            System.out.println("基于URL方式得到的 Document:\r\n"+ doc3);
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
