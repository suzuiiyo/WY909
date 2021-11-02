package generic;

import java.util.LinkedList;

public class MyStackEdge<T> {
    LinkedList<T> values = new LinkedList<>();

    public synchronized void push(T t) {
        while(values.size() >= 200) {
            try {
                this.wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        this.notifyAll();
        values.addLast(t);
    }

    public synchronized T pull(){

        while(values.isEmpty()){
            try{
                this.wait();
            }catch (InterruptedException e){
                e.printStackTrace();
            }
        }
        this.notifyAll();
        return values.removeLast();
    }

    public T peek(){
        return values.getLast();
    }
}
