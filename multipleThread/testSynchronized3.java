package multipleThread;

import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * @author youpub
 */
public class testSynchronized3 {
    public static String now(){
        return new SimpleDateFormat("HH:mm:ss").format(new Date());
    }

    public static void main(String[] args) {
        final Object someObject = new Object();

        Thread t1 = new Thread(){
            @Override
            public void run() {
                try{
                    System.out.println(now() + " t1Thread is running");
                    System.out.println(now() + this.getName() + "is trying to occupy someObject");
                    synchronized (someObject){
                        System.out.println(now() + this.getName() + " occupied object : someObject");
                        Thread.sleep(5000);
                        System.out.println(now() + this.getName() + " occupied object : someObject");
                    }
                    System.out.println(now() + "t1 Thread is over");
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        };
        t1.setName("t1");
        t1.start();

        Thread t2 = new Thread(){
            @Override
            public void run(){
                try {
                    System.out.printf(now() + "t2 thread is running");
                    System.out.println(now() + this.getName() + "is trying to occupy: someObject");
                    synchronized (someObject) {
                        System.out.println(now() + this.getName() + " occupied object: someObject");
                        Thread.sleep(5000);
                        System.out.println(now() + this.getName() + " release object: someObject");
                    }
                    System.out.println(now() + "t2 Thread is over");
                }catch (InterruptedException e){
                    e.printStackTrace();
                }
            }
        };
        t2.setName(" t2");
        t2.start();
    }
}
