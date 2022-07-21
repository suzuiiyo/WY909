package javaDemo;

import com.alibaba.fastjson.JSON;

import java.util.List;

public class List2JSON1 {
    public static <ProgramLog> String List2Json(List<ProgramLog> list){
        String json = JSON.toJSONString(list);

        return json;
    }
}
