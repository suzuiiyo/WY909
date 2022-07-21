package generic;

import java.util.LinkedList;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * @author youpub
 */
public class MyStackLock<T> {
    LinkedList<T> values = new LinkedList<>();
    Lock lock = new ReentrantLock();
    Condition lockCondition = lock.newCondition();

    public void push(T t){
        try {
            lock.lock();
            while (values.size() >= 200) {
                try {
                    lockCondition.await();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            lockCondition.signalAll();
            values.addLast(t);
        }finally{
            lock.unlock();
        }
    }

    public T pull(){
        try {
            lock.lock();
            while (values.isEmpty()) {
                try {
                    lockCondition.await();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            lockCondition.signalAll();
            return values.removeLast();
        }finally {
            lock.unlock();
        }
    }

    public T peek(){
        return values.getLast();
    }

    public static void main(String[] args) {

    }
}
