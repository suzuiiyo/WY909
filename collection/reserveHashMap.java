package collection;

import java.io.ObjectInputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

public class reserveHashMap {
    public static void main(String[] args) {
        HashMap heroMap = new HashMap();
        heroMap.put("adc", "physicalHero");
        heroMap.put("apc", "magicHero");
        heroMap.put("t", "tank");

        ArrayList<Object> proto = new ArrayList<>();
        ArrayList<Object> type = new ArrayList<>();

        proto.addAll(heroMap.keySet());
        type.addAll(heroMap.values());

        System.out.println(proto.toString());
        System.out.println(type.toString());

        heroMap.clear();
        for(int i=0; i<proto.size(); i++){
            heroMap.put(type.get(i), proto.get(i));
        }

        System.out.println(heroMap.toString());
    }
}
