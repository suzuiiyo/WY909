package generic;

import charactor.Hero;
import collection.Item;

import java.util.LinkedList;

public class MyStack<T> {
    LinkedList<T> values = new LinkedList<T>();

    public void push(T t){
        values.addLast(t);
    }

    public T pull(){
        return values.removeLast();
    }

    public T peek(){
        return values.getLast();
    }

    public static void main(String[] args) {
        MyStack<Hero> heroStack = new MyStack<Hero>();
        heroStack.push(new Hero());

        MyStack<Item> itemStack = new MyStack<>();
        itemStack.push(new Item());
    }
}
