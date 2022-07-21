package exceptions;

import java.io.File;
import java.io.FileInputStream;

public class TestException14 {
    public static void main(String[] args){
        File f = new File("/home/youpub/Downloads/wechat.exe");
        try{
            new FileInputStream(f);
        }catch(Throwable t){
            t.printStackTrace();
        }
    }
}
