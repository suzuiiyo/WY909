package stream;

import java.io.*;

public class TestStream10 {
    public static void main(String[] args) {
        write();
        read();
    }

    private static void read(){
        File f = new File("/home/youpub/Downloads/KK.txt");
        try(FileInputStream fis = new FileInputStream(f); DataInputStream dis = new DataInputStream(fis)){
            boolean b = dis.readBoolean();
            int i = dis.readInt();
//            String str = dis.readUTF();

            System.out.println("read bool value:" + b);
            System.out.println("read integer value:" + i);
//            System.out.println("read String:" + str);
        }catch (IOException e){
            e.printStackTrace();
        }
    }

    private static void write(){
        File f = new File("/home/youpub/Downloads/KKK.txt");
        try(FileOutputStream fos = new FileOutputStream(f); DataOutputStream dos = new DataOutputStream(fos)){
            dos.writeBoolean(true);
            dos.writeInt(300);
            dos.writeUTF("123 this is garen");
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
