package reflection;

import charactor.Hero;

import java.lang.reflect.Method;

public class testReflection7 {
    public static void main(String[] args) {
        Hero h = new Hero();
        try{
            Method m = h.getClass().getMethod("setName", String.class);
            m.invoke(h, "dedema");
            System.out.println(h.getName());
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}
