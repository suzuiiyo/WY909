package multipleThread;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class testTryLock {
    public static String now(){
        return new SimpleDateFormat("HH:mm:ss").format(new Date());
    }

    public static void log(String msg){
        System.out.printf("%s %s %s %n", now(), Thread.currentThread().getName(), msg);
    }

    public static void main(String[] args) {
        Lock lock = new ReentrantLock();

        Thread t1 = new Thread(){
            @Override
            public void run(){
                boolean locked = false;
                try {
                    log("thread starts");
                    log("try to occupy object: lock");

                    locked = lock.tryLock(1, TimeUnit.SECONDS);
                    if (locked) {
                        log("occupy object: lock");
                        log("5s service operating");
                        Thread.sleep(5000);
                    } else {
                        log("after 1s, even not occupy object, give up to occupy object");
                    }
                }catch(InterruptedException e){
                    e.printStackTrace();
                }finally {
                    if(locked){
                        log("release: lock");
                        lock.unlock();
                    }
                }
                log("thread is over");
           }
        };

        t1.setName("t1");
        t1.start();

        try{
            Thread.sleep(2000);
        }catch (InterruptedException e1){
            e1.printStackTrace();
        }
        Thread t2 = new Thread(){
            public void run(){
                boolean locked = false;
                try{
                    log("thread starts");
                    log("try to occupy object: lock");

                    locked = lock.tryLock(1, TimeUnit.SECONDS);
                    if(locked){
                        log("occupied object: lcok");
                        log("5s service operating");
                        Thread.sleep(5000);
                    }
                    else{
                        log("after 1s , ever not occupyied object, give up to occupy");
                    }
                }catch (InterruptedException e){
                    e.printStackTrace();
                }finally {
                    if(locked){
                        log("release object: lock");
                        lock.unlock();
                    }
                }
                log("Thread is over");
            }
        };
        t2.setName("t2");
        t2.start();
    }
}
