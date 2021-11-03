package multipleThread;

import java.util.concurrent.atomic.AtomicInteger;

public class testAutomicINteger {
    public static void main(String[] args) {
        AtomicInteger atomicI = new AtomicInteger();
        int i = atomicI.decrementAndGet();
        int j = atomicI.incrementAndGet();
        int k = atomicI.addAndGet(3);

        System.out.println(i);
        System.out.println(j);
        System.out.println(k);
    }
}
