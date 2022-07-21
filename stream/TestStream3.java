package stream;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class TestStream3 {
    public static void main(String[] args){
        try{
            File f = new File("/home/youpub/Downloads/WY9.pro");
            FileInputStream fis = new FileInputStream(f);

            //byte array
            byte[] all = new byte[(int) f.length()];
            fis.read(all);
            for(byte b : all){
                System.out.println(b);
            }

            fis.close();
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
