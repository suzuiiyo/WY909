package stream;

import java.io.IOException;
import java.io.InputStream;

public class TestSTream12 {
    public static void main(String[] args) {
        try(InputStream is = System.in) {
            while(true){
                int i = is.read();
                System.out.println(i);
            }
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
