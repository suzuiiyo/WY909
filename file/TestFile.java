package file;

import java.io.File;
import java.nio.file.FileSystemNotFoundException;

public class TestFile {
    public static void main(String[] args){
        File f1 = new File("/home/youpub/Downloads");
        System.out.println("f1 absolute path:" + f1.getAbsolutePath());

        File f2 = new File("wechat.exe");
        System.out.println("f2 absolute path:" + f2.getAbsolutePath());

        File f3 = new File(f1, f2.getName());
        System.out.println("f3 absolute path: " + f3.getAbsolutePath());
    }
}
