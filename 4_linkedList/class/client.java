public class client {

    //thows Exception is written because some functions of ll are capable of throwing Exceptions, and they are invoked from main
    public static void main(String [] args) throws Exception{
        linkedlist ll = new linkedlist();
        ll.addLast(5);
        System.out.println(ll.size());
    }
}
