package stream;

import java.io.*;
import java.net.InterfaceAddress;
import java.nio.Buffer;

public class buffered2Byte {
    static File f = new File("/home/youpub/Downloads/KK.txt");
    static int x = 12;
    static int y = 34;

    public static void main(String[] args) {
//            try(    FileWriter fw = new FileWriter(f);
//                    BufferedWriter bw = new BufferedWriter(fw);
//
//                    FileReader fr = new FileReader(f);
//                    BufferedReader br = new BufferedReader(fr);
//            )
//            {
//                String str = "123*456";
//                bw.write(str);
//                String str2 = br.readLine();
//                System.out.println(str2);
//            }catch(IOException e){
//                e.printStackTrace();
//        }
        method1();

        method2();
    }

    private static void method1(){
        try(FileWriter fw = new FileWriter(f);
            PrintWriter pw = new PrintWriter(fw);

            FileReader fr = new FileReader(f);
            BufferedReader br = new BufferedReader(fr);
            )
        {
            pw.println(x+"@"+y);
            pw.flush();
            String str = br.readLine();
            String[] ss = str.split("@");
            int x = Integer.parseInt(ss[0]);
            int y = Integer.parseInt(ss[1]);

            System.out.printf("x:%d, y:%d", x, y);
        }catch (IOException e){
            e.printStackTrace();
        }
    }

    private static void method2(){
        try(FileInputStream fis = new FileInputStream(f);
            DataInputStream dis = new DataInputStream(fis);

            FileOutputStream fos = new FileOutputStream(f);
            DataOutputStream dos = new DataOutputStream(fos);
            )
        {
            dos.writeInt(x);
            dos.writeInt(y);

            int x=dis.readInt();
            int y=dis.readInt();
            System.out.printf("x:%d, y%d", x, y);
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
