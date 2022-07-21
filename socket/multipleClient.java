package socket;

import java.io.IOException;
import java.net.Socket;

public class multipleClient {
    public static void main(String[] args) {
        try{
            Socket s = new Socket("127.0.0.1", 8080);

            new sendThread(s).start();
            new receiveThread(s).start();

        } catch (IOException e){
            e.printStackTrace();
        }
    }
}
