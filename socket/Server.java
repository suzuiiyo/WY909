package socket;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class Server {
    public static void main(String[] args) {
        try {
            //get
            ServerSocket ss = new ServerSocket(8888);

            System.out.println("listen on port:8888");
            Socket s = ss.accept();

            InputStream is = s.getInputStream();
            DataInputStream dis = new DataInputStream(is);
            OutputStream os_server = s.getOutputStream();
            DataOutputStream dos_server = new DataOutputStream(os_server);

            while(true) {
                String msg = dis.readUTF();
                System.out.println("connection came " + msg);

                Scanner sc_server = new Scanner(System.in);
                dos_server.writeUTF(sc_server.next());
            }
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
