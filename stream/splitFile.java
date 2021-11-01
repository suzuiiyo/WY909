package stream;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class splitFile {
    public static void main(String[] args){
        File f = new File("/home/youpub/Downloads/toSplit.png");

        try{
            FileInputStream fis = new FileInputStream(f);

            for(int i =0; i<f.length()/(100*1000); i++) {
                byte[] arrFis = new byte[100*1000];
                fis.read(arrFis);

                String filePath = "/home/youpub/Downloads/XYZ/toSplit.png-" + String.valueOf(i);
                File f2 = new File(filePath);
                FileOutputStream fos = new FileOutputStream(f2);

                fos.write(arrFis);

                fis.close();
                fos.close();
            }
        }catch (IOException e){
            e.printStackTrace();
        }
    }

    public static class TestStream8 {
    }
}
