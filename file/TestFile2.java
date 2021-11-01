package file;

import java.io.File;
import java.util.Date;

public class TestFile2 {
    public static void main(String[] args){
        File f = new File("/home/youpub/Downloads/wechat.exe");
        System.out.println("current file is:" + f);

        System.out.println("judge is there: " + f.exists());

        System.out.println("judge is a directory or not: " + f.isDirectory());

        System.out.println("judge is a file or not: " + f.isFile());

        System.out.println("get the length of the file:" + f.length());

        long time = f.lastModified();

        Date d = new Date(time);
        System.out.println("get the last modified time:" + d);
        //设置文件修改时间为1970.1.1 08:00:00
        f.setLastModified(0);

        File f2 = new File("/home/youpub/Downloads/QQ.exe");
        f.renameTo(f2);
        System.out.println("change wechat.exe to DOTA.exe");

        System.out.println("注意： 需要在D:\\LOLFolder确实存在一个LOL.exe,\r\n才可以看到对应的文件长度、修改时间等信息");
    }
}
