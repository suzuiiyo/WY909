package exceptions;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class TestException {
    public static void main(String[] args) throws IOException {
        File f = new File("/home/youpub/Downloads/WeChat.exe");
        FileInputStream out = new FileInputStream(f);
        out.close();
    }
}
