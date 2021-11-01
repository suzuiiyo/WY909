package multipleThread;

import java.awt.desktop.QuitStrategy;
import java.io.*;

public class findFileContent {
    public static void main(String[] args) throws Exception {
        searchFileContent("/home/youpub/IdeaProjects/demo1");
    }

    public static void searchFileContent(String filePath) throws Exception {
        File file = new File(filePath);
        if (!file.exists()) {
            throw new Exception("file not found");
        } else {
            File[] fList = file.listFiles();
            for (File f : fList) {
                if (f.isFile() && f.getName().endsWith(".java")) {
                    Thread t1 = new Thread() {
                        @Override
                        public void run() {
                            try (FileReader fr = new FileReader(f)) {
                                char[] buffer = new char[(int) f.length()];
                                fr.read(buffer);
                                String fileContent = String.valueOf(buffer);
                                System.out.printf("this java file's content is: %s%n", fileContent);
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                        }
                    };
                    t1.start();
                } else if (f.isDirectory()) {
                    searchFileContent(f.getAbsolutePath());
                }
            }
        }
    }
}
