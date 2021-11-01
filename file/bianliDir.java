package file;

import javax.swing.*;
import java.io.File;
import java.util.*;

public class bianliDir {
    public static void main(String[] args){
        File f = new File("/home/youpub/Downloads/");
        File[] fs = f.listFiles();

        if(null == fs) {
            return;
        }

        long minSize = Integer.MAX_VALUE;
        long maxSize = 0;

        File minFile = null;
        File maxFile = null;

        for(File file : fs){
            if(file.isDirectory()) {
                continue;
            }
            if(file.length()>maxSize){
                maxSize = file.length();
                maxFile = file;
            }
            if(file.length()!=0 && file.length()<minSize){
                minSize = file.length();
                minFile = file;
            }
        }
        System.out.printf("max file is %s, and the size is %,d bytes", maxFile.getAbsoluteFile(), maxFile.length());
        System.out.printf("min file is %s, and the size is %,d bytes", minFile.getAbsoluteFile(), minFile.length());
    }
}
