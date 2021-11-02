package multipleThread;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class testTHreadTry {
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
                try{
                    log("thread starts");
                    log("try to lock object: lock");

                    lock.lock();

                    log("occupy: lock");
                    log("5s service operating");
                    Thread.sleep(5000);
                }catch (InterruptedException e){
                    e.printStackTrace();
                }finally {
                    log("release: lock");
                    lock.unlock();
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
            @Override
            public void run() {
               try{
                   log("thread is running");
                   log("try to occupy: lock");

                   lock.lock();

                   log("occupy object: lock");
                   log("5s service operating");
                   Thread.sleep(5000);
               }catch (InterruptedException e){
                   e.printStackTrace();
               }finally {
                   log("release object: lock");
                   lock.unlock();
               }
               log("thread is over");
            }
        };
        t2.setName("t2");
        t2.start();
    }
}
