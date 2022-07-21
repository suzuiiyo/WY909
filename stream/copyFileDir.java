package stream;

import java.awt.*;
import java.io.*;

public class copyFileDir {
    /**
     * @param srcPath
     * @param destPath
     */

    public static void copyFile(String srcPath, String destPath){
        File  srcf = new File( srcPath);
        File destf = new File( destPath);

        //cache
        byte[] buffer = new byte[1024];
        try(FileInputStream fis = new FileInputStream(srcf);
            FileOutputStream fos = new FileOutputStream(destf))
        {
            while(true){
                //实际读取的长度是 actuallyReaded,有可能小于1024
                int actuallyReaded = fis.read(buffer);
                //return -1 means nongthing to read
                if(-1==actuallyReaded){
                    break;
                }
                fos.write(buffer, 0, actuallyReaded);
                fos.flush();
            }
        }catch (IOException e){
            e.printStackTrace();
        }
    }

    /**
     *
     * @param srcPath 源文件夹
     * @param destPath 目标文件夹
     */
    public static void copyFolder(String srcPath, String destPath){
        File srcFolder = new File( srcPath);
        File destFolder = new File( destPath);

        //yuan wenjianjiabucun
        if(!srcFolder.exists()){
            return;
        }

        //yuanwenjian bushi wenjianjia
        if(!srcFolder.isDirectory())
        {
            return;
        }

        //mubiaowenjianjiashiyigewenjian
        if(destFolder.isFile()){
            return;
        }

        //mubiaowenjianjia bucunzai
        if(!destFolder.exists()){
            destFolder.mkdirs();
        }

        File[] fileList = srcFolder.listFiles();
        for(File srcFile : fileList){
            if(srcFile.isFile()){
                File newDestFile = new File(destFolder, srcFile.getName());
                copyFile(srcFile.getAbsolutePath(), newDestFile.getAbsolutePath());
            }

            //digui
            if(srcFile.isDirectory()){
                File newDestFolder = new File(destFolder, srcFile.getName());
                copyFolder(srcFile.getAbsolutePath(), newDestFolder.getAbsolutePath());
            }
        }
    }

    public static void main(String[] args) {
        copyFolder("/home/youpub/Downloads/simsun", "/home/youpub/Downloads/simsun2");
    }
}
