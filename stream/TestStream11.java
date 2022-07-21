package stream;
import charactor.Hero;

import java.io.*;

public class TestStream11 {
    public static void main(String[] args) {
        Hero h = new Hero();
        h.name = "UnderWater";
        h.hp = 89;

        File f = new File("/home/youpub/Downloads/KK.txt");

        try(
            FileOutputStream fos = new FileOutputStream(f);
            ObjectOutputStream oos = new ObjectOutputStream(fos);

            FileInputStream fis = new FileInputStream(f);
            ObjectInputStream ois = new ObjectInputStream(fis);
        ){
            oos.writeObject(h);
            Hero h2 = (Hero) ois.readObject();
            System.out.println(h2.name);
            System.out.println(h2.hp);
        }catch (IOException e){
            e.printStackTrace();
        }catch (ClassNotFoundException e){
            e.printStackTrace();
        }
    }
}
