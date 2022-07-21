package reflection;

public class testReflection3 {
    public static void main(String[] args) {
        Thread t1 = new Thread(){
            @Override
            public void run(){
                testReflection3.method1();
            }
        };
        t1.setName("first thread");
        t1.start();

        Thread t2 = new Thread(){
            @Override
            public void run(){
                testReflection3.method2();
            }
        };
        t2.setName("second thread");
        t2.start();
    }

    public static void method1(){
        synchronized(testReflection3.class){
            // 对于method1而言，同步对象是TestReflection.class，只有占用TestReflection.class才可以执行到这里
            System.out.println(Thread.currentThread().getName() + " get into method1");
            try{
                System.out.println("run 5 seconds");
                Thread.sleep(5000);
            }catch (InterruptedException e){
                e.printStackTrace();
            }
        }
    }

    public static void method2(){
        // 对于mehotd2而言，必然有个同步对象，通过观察发现，当某个线程在method1中，占用了TestReflection.class之后
        // 就无法进入method2，推断出，method2的同步对象，就是TestReflection3.class
        synchronized (testReflection3.class){
            System.out.println(Thread.currentThread().getName() + " get into method2");
            try{
                System.out.println("run 5 seconds");
                Thread.sleep(5000);
            }catch (InterruptedException e){
                e.printStackTrace();
            }
        }
    }
}
