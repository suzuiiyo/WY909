package stream;

import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class classFile {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        System.out.println("plz input the name of class:");
        String className = s.nextLine();
        System.out.println("plz input the class type:");
        String type = s.nextLine();
        System.out.println("plz input the property name:");
        String property = s.nextLine();
        String Uproperty = toUpperFirstLetter(property);

        File modelFile = new File("/home/youpub/Downloads/modelFile.txt");
        String modelContent = null;
        try(FileReader fr = new FileReader(modelFile))
        {
            char cs[] = new char[(int) modelFile.length()];
            fr.read(cs);
            modelContent= new String(cs);
        }catch(IOException e){
            e.printStackTrace();
        }

        String fileContent = modelContent.replaceAll("@class@", className);
        fileContent = fileContent.replaceAll("@type@", type);
        fileContent = fileContent.replaceAll("@property@", property);
        fileContent = fileContent.replaceAll("@Uproperty@", Uproperty);
        String fileName = className + ".java";

        System.out.println("after replace the file content:");
        System.out.print(fileContent);
        File file = new File("/home/youpub/Downloads/", fileName);

        try(FileWriter fw = new FileWriter(file);){
            fw.write(fileContent);
        }catch (IOException e){
            e.printStackTrace();
        }
        System.out.println("file saves in:" + file.getAbsolutePath());
    }

    private static String toUpperFirstLetter(String str) {
        char upperCaseFirst = Character.toUpperCase(str.charAt(0));
        String rest = str.substring(1);
        return upperCaseFirst + rest;
    }
}








