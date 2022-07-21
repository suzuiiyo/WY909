package reflection;

import charactor.Hero;

public class testREflection2 {
    public static void main(String[] args) {
        String className = "charactor.Hero";
        try{
            Class pClass1=Class.forName(className);
            Class pClass2=Hero.class;
            Class pClass3=new Hero().getClass();
        }catch (ClassNotFoundException e){
            e.printStackTrace();
        }
    }
}
