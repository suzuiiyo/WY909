package socket;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class multipleServer {
    public static void main(String[] args) {
        try {
            ServerSocket ss = new ServerSocket(8080);

            System.out.println("listen on port:8080");
            Socket s = ss.accept();

            //
            new sendThread(s).start();
            //
            new receiveThread(s).start();

        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
