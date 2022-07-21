package stream;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class TestStream9 {
    public static void main(String[] args) {
        File f = new File("/home/youpub/Downloads/KK.txt");
        try(FileWriter fw = new FileWriter(f); PrintWriter pw = new PrintWriter(fw)){
            pw.println("1111111111111111111111");
            pw.println("2222222222222222222222222");
            pw.println("3333333333333333333333333333");
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
