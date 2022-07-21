package reflection;

import charactor.Hero;

import java.lang.reflect.Field;

public class testReflection6 {
    public static void main(String[] args) {
        Hero h = new Hero();
        h.name = "very1+1";
        try{
            Field f1 = h.getClass().getDeclaredField("favour");
            f1.setAccessible(true);
            f1.set(h, "tieshanfeihu");
            System.out.println(h.name);
            System.out.println(f1.get(h));
        }catch (NoSuchFieldException | IllegalAccessException e){
            e.printStackTrace();
        }
    }
}
