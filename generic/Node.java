package generic;

import java.util.ArrayList;
import java.util.List;

public class Node<T> {
    public Node<T> leftNode;
    public Node<T> rightNode;

    public T value;

    public void add(T t){
        if(null == value){
            value = t;
        }
        else{
            if((Integer) t - ((Integer) value) <= 0){
                if(null == leftNode) {
                    leftNode = new Node<T>();
                }
                leftNode.add(t);
            }
            else{
                if(null == rightNode) {
                    rightNode = new Node<T>();
                }
                rightNode.add(t);
            }
        }
    }

    //middle seq traverse all nodes
    public List<T> values(){
        List<T> values = new ArrayList<>();

        if(null != leftNode){
            values.addAll(leftNode.values());
        }

        values.add(value);

        if(null != rightNode){
            values.addAll(rightNode.values());
        }
        return values;
    }

    public static void main(String[] args) {
        int randoms[] = new int[] {67, 7, 30, 73, 0, 78, 81, 10, 74};
        Node<Integer> roots = new Node<>();
        for(int number : randoms){
            roots.add(number);
        }
        System.out.println(roots.values());
    }
}
