package stream;

import java.io.*;

public class fileContent {
    public static void main(String[] args) {
        search(new File("/home/youpub/IdeaProjects/demo1/"), "hero");
    }

    public static void search(File folder, String search){
        File[] listFiles = folder.listFiles();
        for(File f : listFiles){
            if(f.isFile() && f.getName().endsWith(".java")){
                try(FileReader fr = new FileReader(f);){
                      char[] arr = new char[(int)f.length()];
                      fr.read(arr);

                      String fileContent = new String(arr);
                      if(fileContent.contains(search)){
                          System.out.println("the file name is:" + f.getName());
                          System.out.println("the file content is: " + fileContent);
                      }
                }catch (IOException e){
                    e.printStackTrace();
                }
            }else if(f.isDirectory()){
                search(f, search);
            }
        }
    }
}
