package multipleThread;

import java.io.File;
import java.util.Locale;

/**
 * @author youpub
 */
public class SearchFileContent {
    public static void search(File file, String search){
        if(file.isFile()){
            if(file.getName().toLowerCase().endsWith(".java")){
                new SearchFileThread(file, search).start();
            }
        }
        if(file.isDirectory()){
            File[] fs = file.listFiles();
            for(File f : fs){
                search(f, search);
            }
        }
    }

    public static void main(String[] args){
        File folder = new File("/home/youpub/IdeaProjects/demo1");
        search(folder, "copy");
    }
}
