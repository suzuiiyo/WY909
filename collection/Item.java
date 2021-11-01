package collection;

import java.text.CollationElementIterator;
import java.util.*;

public class Item implements Comparable<Item> {
    String name;
    float price;

    public Item(){

    }

    public Item(String nameVar, float priceVar){
        this.name = nameVar;
        this.price = priceVar;
    }

    @Override
    public int compareTo(Item o) {
        if(price < o.price){
            return 1;
        }
        else
        {
            return -1;
        }
    }

    public static void main(String[] args) {
        ArrayList<Item> itemList = new ArrayList<>();
        Random r = new Random();
        for(int i=0; i<10; i++){
            itemList.add(new Item("item " + i, r.nextInt(100)));
        }
        Collections.sort(itemList);

        System.out.println(itemList.toString());
        for(Item i : itemList){
            System.out.println(i.price);
        }
    }
}
