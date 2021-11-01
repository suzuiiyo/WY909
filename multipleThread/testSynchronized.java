package multipleThread;

import java.text.SimpleDateFormat;
import java.util.Date;

public class testSynchronized {

    public static String now() {
        return new SimpleDateFormat("HH:mm:ss").format(new Date());
    }

    public static void main(String[] args) {
        final Object someObject = new Object();
        Thread t1 = new Thread() {
            @Override
            public void run() {
                try {
                    System.out.println(now() + " t1 thread has runned");
                    System.out.println(now() + this.getName() + "try to occupy the someObject");

                    synchronized (someObject) {
                        System.out.println(now() + this.getName() + "occuped the someObject");
                        Thread.sleep(5000);
                        System.out.println(now() + this.getName() + "release the someObject");
                    }
                    System.out.println(now() + "t1 Thread is over");
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        };
        t1.setName(" t1");
        t1.start();
        Thread t2 = new Thread() {
            @Override
            public void run() {
                try {
                    System.out.println(now() + " t2 thread has runned");
                    System.out.println(now() + this.getName() + "try ro occupy someOObject");

                    synchronized (someObject) {
                        System.out.println(now() + this.getName() + "occupied someObject");
                        Thread.sleep(5000);
                        System.out.println(now() + this.getName() + "release someObject");
                    }
                    System.out.println(now() + " t2 thread is over");
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        };
        t2.setName(" t2");
        t2.start();
    }
}



