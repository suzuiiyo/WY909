package socket;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.*;

public class wordsServer {
    private static List<String> cannotUnderstand = new ArrayList<>();
    static{
        cannotUnderstand.add("听求不懂啊");
        cannotUnderstand.add("说人话");
        cannotUnderstand.add("再说一遍？");
        cannotUnderstand.add("大声点");
        cannotUnderstand.add("老子在忙，一边玩儿去");
    }
    public static void main(String[] args) throws IOException {
        try {
            ServerSocket ss = new ServerSocket(8080);
            System.out.println("listen on port:8080");
            Socket s = ss.accept();

            InputStream is = s.getInputStream();
            DataInputStream dis = new DataInputStream(is);
            OutputStream os = s.getOutputStream();
            DataOutputStream dos = new DataOutputStream(os);

            while (true) {
                String msg = dis.readUTF();
                System.out.println(msg);

                List<words> ds = new wordsDAO().queryWords(msg);
                String response = null;
                if (ds.isEmpty()) {
                    Collections.shuffle(cannotUnderstand);
                    response = cannotUnderstand.get(0);
                } else {
                    Collections.shuffle(ds);
                    response = ds.get(0).response;
                }
                dos.writeUTF(response);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
