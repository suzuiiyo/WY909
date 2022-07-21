package exceptions;

import java.io.File;
import java.io.FileInputStream;

public class TestException3 {
    public static void main(String[] args){
        File f = new File("/home/youpub/Downloads/wechat.exe");
        try{
            System.out.println("try to open wechat.exe");
            new FileInputStream(f);
            System.out.println("open success");
        }
        catch(Exception e){
            System.out.println("in the directory wechat.exe doesn;t exist");
            e.printStackTrace();
        }
    }
}
