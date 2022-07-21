package collection;

import charactor.Hero;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class testLinkedListQueue {
    public static void main(String[] args) {
        List ll = new LinkedList<Hero>();

        Queue<Hero> q=new LinkedList<Hero>();

        System.out.println("initial the queue: \n");
        q.offer(new Hero("hero1"));
        q.offer(new Hero("hero2"));
        q.offer(new Hero("hero3"));
        q.offer(new Hero("hero4"));

        System.out.println(q);
        System.out.println("poll the first element:");
        Hero h = q.poll();
        System.out.println(h);
        System.out.println("get the queue after the first element: ");
        System.out.println(q);

        h=q.peek();
        System.out.println("see the first element of: ");
        System.out.println(h);
        System.out.println("ckeck won't make the first element out");
        System.out.println(q);
    }
}
