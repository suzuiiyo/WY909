package multipleThread;


import javax.imageio.stream.ImageInputStream;
import java.io.File;

public class TestThreadPools {
    static testThreadPool pool = new testThreadPool();
    public static void search(File file, String search){
        if(file.isFile()){
            if(file.getName().toLowerCase().endsWith(".java")){
                searchFileTask task = new searchFileTask(file, search);
                pool.add(task);
            }

            if(file.isDirectory()){
                File[] fs = file.listFiles();
                for(File f : fs){
                    search(f, search);
                }
            }
        }
    }

    public static void main(String[] args) {
        File folder = new File("/home/youpub/IdeaProjects/demo1/");
        search(folder, "magic");
    }
}
