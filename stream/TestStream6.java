package stream;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class TestStream6 {
    public static void main(String[] args){
        File f = new File("/home/youpub/Downloads/KK.txt");
        try(FileReader fr = new FileReader(f)){
            char[] all = new char[(int) f.length()];
            fr.read(all);

            for(char c : all){
                System.out.println(c);
            }
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
