package socket;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class GUIServer {
    public static void main(String[] args) throws IOException {
        JFrame f = new JFrame();
        f.setTitle("server");

        f.setSize(400, 300);
        f.setLocation(100, 200);
        f.setLayout(null);

        JButton b = new JButton("send");
        b.setBounds(10, 10, 80, 30);
        f.add(b);

        final JTextField tf = new JTextField();
        tf.setBounds(10, 110, 80, 30);
        f.add(tf);

        final JTextArea ta = new JTextArea();
        ta.setBounds(110, 10, 200, 300);
        f.add(ta);

        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.setVisible(true);

        ServerSocket ss = new ServerSocket(8080);

        System.out.println("listening on port:8080");
        final Socket s = ss.accept();
        new Thread() {
            public void run() {
                while (true) {
                    try {
                        InputStream is = s.getInputStream();
                        DataInputStream dis = new DataInputStream(is);
                        String text = dis.readUTF();
                        ta.append(text + "\r\n");
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
        }.start();

        b.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String text = tf.getText();
                ta.append(text+"\r\n");

                try{
                    DataOutputStream dos = new DataOutputStream(s.getOutputStream());
                    dos.writeUTF(text);
                }catch (Exception ex){
                    ex.printStackTrace();
                }
            }
        });
    }
}
