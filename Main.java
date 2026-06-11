import java.util.*;

public class Main {
    public static void main(String[] args) {

        List<Account> accounts = new ArrayList<>();

        accounts.add(new SavingsAccount(101, "Aditya", 5000, 5));
        accounts.add(new CurrentAccount(102, "Rahul", 3000, 2000));

       
        for (Account acc : accounts) {
            acc.display();
            System.out.println("----------------------");
        }

       
        Account a = new SavingsAccount(103, "Riya", 4000, 4);
        a.deposit(1000);
        a.withdraw(2000);
        a.display();
    }
}