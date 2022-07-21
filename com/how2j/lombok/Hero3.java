package com.how2j.lombok;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor

@Builder
public class Hero3 {
    private int id;
    private String name;

    public static void main(String[] args) {
        //troditional way
        Hero3 h1 = new Hero3();
        h1.setId(1);
        h1.setName("gareen");
        System.out.println(h1);

        //builder way
        Hero3 h2 = Hero3.builder().id(1).name("gareen").build();
        System.out.println(h2);
    }
}
