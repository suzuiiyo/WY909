package exceptions;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.File;
import java.nio.file.FileSystemNotFoundException;

public class TestException7 {
    public static void main(String[] args) {
        method1();
    }

    private static void method1(){
        try{
            method2();
        }
        catch(FileNotFoundException e)
        {
            e.printStackTrace();
        }
    }

    private static void method2() throws FileNotFoundException{
        File f = new File("/home/youpub/Downloads/");

        System.out.println("try to open the wechat.exe");
        new FileInputStream(f);
        System.out.println("open success");
    }
}