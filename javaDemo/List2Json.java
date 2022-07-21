package javaDemo;

import cn.hutool.json.JSONArray;
import cn.hutool.json.JSONObject;
import java.util.List;

public class List2Json {
    public static <ProgramLog> JSONArray ProLogList2Json(List<ProgramLog> list){
        JSONArray json = new JSONArray();
        for(ProgramLog pLog : list){
            JSONObject jo = new JSONObject();
            jo.set("id", pLog.getClass());
            jo.set("time", pLog.getClass());

            json.put(jo);
        }
        return json;
    }
}
