package multipleThread;

import java.net.Inet4Address;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class lockMakeNoDeadLock {
    public static void main(String[] args) throws InterruptedException {
        Lock lock_a = new ReentrantLock();
        Lock lock_b = new ReentrantLock();

        Thread t1 = new Thread(){
            @Override
            public void run() {
                boolean a_locked = false;
                boolean b_locked = false;

                try{
                    a_locked = lock_a.tryLock(10, TimeUnit.SECONDS);
                    if(a_locked){
                        System.out.println("t1 occupied ahri");
                        Thread.sleep(1000);
                        System.out.println("t1 is tring to occupy annie in 10s");
                        try{
                            b_locked = lock_b.tryLock(10, TimeUnit.SECONDS);
                            if(b_locked){
                                System.out.println("t1 occupied annie succeed");
                            }else{
                                System.out.println("t1 cannot occupy annie, give up");
                            }
                        }finally {
                            if(b_locked){
                                System.out.println("t1 release annie");
                                lock_b.unlock();
                            }
                        }
                    }
                }catch (InterruptedException e1){
                    e1.printStackTrace();
                }finally {
                    if(a_locked){
                        System.out.println("t1 release arhi");
                        lock_a.unlock();
                    }
                }
            }
        };
        t1.start();
        Thread.sleep(100);

        Thread t2 = new Thread(){
            @Override
            public void run() {
                boolean a_locked = false;
                boolean b_locked = false;
                try{
                    b_locked = lock_b.tryLock(10, TimeUnit.SECONDS);
                    if(b_locked){
                        System.out.println("t2 locked annie");
                        Thread.sleep(1000);
                        System.out.println("t2 release annie");
                        try{
                            a_locked = lock_a.tryLock(10, TimeUnit.SECONDS);
                            if(a_locked){
                                System.out.println("t2 occupy arhi success");
                            }else{
                                System.out.println("t2 cannot occupy arhi, give up");
                            }
                        }finally {
                            if(a_locked){
                                System.out.println("t2 release annie");
                                lock_a.unlock();
                            }
                        }
                    }
                }catch (InterruptedException e){
                    e.printStackTrace();
                }finally {
                    if(b_locked){
                        System.out.println("t2 release ahri");
                        lock_b.unlock();
                    }
                }
            }
        };
        t2.start();
    }
}
