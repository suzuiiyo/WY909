package com.how2j.lombok;

import lombok.Data;

@Data
public class Hero {
    private int id;
    private String name;

    public static void main(String[] args) {
        System.out.println(new Hero().getName());
        System.out.println(new Hero().toString());
    }
}
