package exceptions;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;

public class TestException10 {
    public static void main(String[] args){
        File f = new File("/home/youpub/Downloads/wechat.exe");

        try{
            System.out.println("try to open wechat.exe");
            new FileInputStream(f);
            System.out.println("open success");
        }
        catch (FileNotFoundException e){
            System.out.println("/home/youpub/Downloads/wechat");
            e.printStackTrace();
        }
    }
}
