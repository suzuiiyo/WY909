package stream;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class testStream12 {
    public static void main(String[] args) {
        copyFile("vector.txt", "vector2.txt");
    }

    public static void copyFile(String srcFile, String destFile) {
        File srcf = new File("/home/youpub/Downloads/" + srcFile);
        File destf = new File("/home/youpub/Downloads/" + destFile);
        try (FileInputStream fis = new FileInputStream(srcf);
             FileOutputStream fos = new FileOutputStream(destf);)
        {
            byte[] arr = new byte[(int) srcf.length()];
            fis.read(arr);
            fos.write(arr);
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
