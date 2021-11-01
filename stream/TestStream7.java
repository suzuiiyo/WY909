package stream;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class TestStream7 {
    public static void main(String[] args){
        File f = new File("/home/youpub/Downloads/KK.txt");
        try(FileWriter fw = new FileWriter(f)){
            char[] all = {'M', 'N', 'B'};
            String data="jialebaxiuedsamdma";
            fw.write(data);
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
