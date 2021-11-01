package exceptions;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.File;

public class TestException6 {
    public static void main(String[] args)
    {
        File f = new File("/home/youpub/Downloads/wechat.exe");
        try{
            System.out.println("try to open file");
            new FileInputStream(f);
            System.out.println("open success");
        }
        catch(FileNotFoundException e){
            System.out.println("chat.exe doesn;t exist");
            e.printStackTrace();
        }
        finally {
            System.out.println("with or with out the file, this sentence will be execute");
        }
    }
}
