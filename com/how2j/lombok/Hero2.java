package com.how2j.lombok;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor

public class Hero2 {
    private int id;
    private String name;

    public static void main(String[] args) {
        System.out.println(new Hero2(1, "gareen"));
        System.out.println(new Hero2());
    }
}
