package exceptions;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class TestException5 {
    public static void main(String[] args) {
        File f = new File("/home/youpub/Downloads/wechat.exe");
        try {
            System.out.println("try to open wechat.exe");
            new FileInputStream(f);
            System.out.println("opensuccess");
            SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
            Date d = sdf.parse("2019-06-03");
        }catch (FileNotFoundException | ParseException e){
            if(e instanceof FileNotFoundException) {
                System.out.println("wechat.exe doesn.t exist");
            }

            if(e instanceof  ParseException) {
                System.out.println("wrong style for the diary to parse");
            }
                e.printStackTrace();
            }
        }
}
