import java.util.HashMap;
import java.util.ArrayList;

public class basicHM {
    public static void test1() {
        HashMap<String, Integer> map = new HashMap<>();
        map.put("USA", 1000);
        map.put("IND", 10000);
        map.put("NEP", 90);
        map.put("usa", 9000);

        //replaces orignal "USA" key's value to 9990
        map.put("USA", 9990);

        //this key is not present in hashmap, therefore prints "null"
        System.out.println(map.get("BAN"));

        //prints the whole map
        System.out.println(map);

        //key set is array of all keys, here strings
        for (String s : map.keySet())
            System.out.println(s + " -> " + map.get(s));
    }

    // Frequency map of given string
    public static void test2(String str) {
        HashMap<Character, Integer> map = new HashMap<>();

        //internally getOrDefault function is written like this

        // for (int i = 0; i < str.length(); i++) {
        // char ch = str.charAt(i);
        // if (!map.containsKey(ch))
        // map.put(ch, 1);
        // else
        // map.put(ch, map.get(ch) + 1);
        // }

        for (int i = 0; i < str.length(); i++) {
            char ch = str.charAt(i);
            map.put(ch, map.getOrDefault(ch, 0) + 1);
        }
    }

    public static void test3(String str) {
        HashMap<Character, ArrayList<Integer>> map = new HashMap<>();
        for (int i = 0; i < str.length(); i++) {
            char ch = str.charAt(i);

            //if ch is not present in hashmap, add it value as an empty arraylist
            map.putIfAbsent(ch, new ArrayList<>());
            
            map.get(ch).add(i);
        }

        System.out.println(map);
    }

    public static void main(String[] args) {
        test3("abcaksjbabaabadabab");

    }

}
