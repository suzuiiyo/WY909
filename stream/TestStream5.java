package stream;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class TestStream5 {
    public static void main(String[] args){
        File f = new File("/home/youpub/Downloads/WY9.pro");
        File f2 = new File("/home/youpub/Downloads/XYZ/WY9.pro");
        try{
            FileInputStream fis = new FileInputStream(f);
            byte[] arr = new byte[(int) f.length()];
            fis.read(arr);

            File dir = f.getParentFile();
            if(!dir.exists()){
                f2.mkdirs();
            }
            FileOutputStream fos = new FileOutputStream(f2);
            fos.write(arr);
            fis.close();
            fos.close();
        }catch (IOException e)
        {
            e.printStackTrace();
        }
    }
}
