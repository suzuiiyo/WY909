package stream;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class TestStream2 {
    public static void main(String[] args){
        File f = new File("/home/youpub/Downloads/WY9.Pro");
        try{
            FileOutputStream fos = new FileOutputStream(f);
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
