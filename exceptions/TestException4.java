package exceptions;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class TestException4 {
    public static void main(String[] args) {
        File f = new File("/home/youpub/Downloads/wechat.exe");
        try {
            new FileInputStream(f);
            System.out.println("open success");
            SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
            Date d = sdf.parse("2016-15-03");
        } catch (FileNotFoundException e) {
            System.out.println("wechat.exe doesn;t exist");
            e.printStackTrace();
        } catch (ParseException e) {
            System.out.println("parse date style error");
            e.printStackTrace();
        }
    }
}
