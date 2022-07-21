package stream;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class toMerge {
    public static void main(String[] args){
        File f = new File("/home/youpub/Downloads/XYZ/twice.png");
        try{
            FileOutputStream fos = new FileOutputStream(f);
            File[] fileList = f.getParentFile().listFiles();
            for(File file : fileList){
                FileInputStream fis = new FileInputStream(file);
                byte[] arr = new byte[(int)file.length()];

                fis.read(arr);
                fos.write(arr);

                fis.close();
            }
            fos.close();
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
