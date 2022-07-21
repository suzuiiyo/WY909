package stream;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class TestStream4 {
    public static void main(String[] args){
        try{
            File f = new File("/home/youpub/Downloads/WY9.pro");
            File f2 = new File("/home/youpub/Downloads/WY92.pro");
            FileInputStream fis = new FileInputStream(f);

            FileOutputStream fos = new FileOutputStream(f2);

            byte[] arr = new byte[(int) f.length()];

            fis.read(arr);

            fos.write(arr);

            fis.close();
            fos.close();

            System.out.println("copy is over");

        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
