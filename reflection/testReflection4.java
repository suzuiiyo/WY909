package reflection;

import charactor.Hero;

import java.lang.reflect.Field;

public class testReflection4 {
    public static void main(String[] args) {
        Hero h = new Hero();
        h.name = "gaigai";
        try {
            Field f1 = h.getClass().getDeclaredField("name");
            f1.set(h, "delta");
            System.out.println(h.name);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
