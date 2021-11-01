package file;

import java.io.IOException;
import java.io.File;

/**
 * @author youpub
 */
public class TestFile3 {
    public static void main(String[] args) throws IOException{
        File f = new File("/home/youpub/Downloads/WY9.Pro");

        f.list();

        File[] fs = f.listFiles();

        f.getParent();

        f.getParentFile();

        f.mkdirs();

        f.createNewFile();

        f.getParentFile().mkdirs();

        f.listRoots();

        f.delete();

        f.deleteOnExit();
    }
}
