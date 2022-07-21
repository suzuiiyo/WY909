package multipleThread;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class searchFileTask implements Runnable{
    private File file;
    private String search;
    public searchFileTask(File file, String search){
        this.file = file;
        this.search = search;
    }

    @Override
    public void run() {
        String fileContent = readFileContent(file);
        if(fileContent.contains(search)){
            System.out.printf("Thread %s find target String %s in file: %s%n", Thread.currentThread().getName(), search, file);
        }
    }

    public String readFileContent(File file){
        try(FileReader fr = new FileReader(file)){
            char[] all = new char[(int)file.length()];
            fr.read(all);
            return new String(all);
        }catch(IOException e){
            e.printStackTrace();
            return null;
        }
    }
}
