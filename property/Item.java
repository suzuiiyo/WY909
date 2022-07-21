package property;

public class Item implements Comparable<Item>{
    public int id;
    public String name;
    public int price;

    public Item(){
        this.name = name;
    }

    public void effect(){
        System.out.println("after using item, with effect");
    }

    public boolean diposable(){
        return false;
    }

    @Override
    public int compareTo(Item o) {
        return o.price - this.price;
    }

    @Override
    public String toString() {
        return "Item [name=" + name + ", price=" + price + "]\r\n";
    }
}
