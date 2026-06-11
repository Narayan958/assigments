public class Account {
    private int accountNumber;
    private String ownerName;
    private double balance;

   
    public Account() {
        this(0, "Unknown", 0.0); // constructor chaining
    }

 
    public Account(int accountNumber, String ownerName, double balance) {
        this.accountNumber = accountNumber;
        this.ownerName = ownerName;
        setBalance(balance);
    }

   
    public int getAccountNumber() {
        return accountNumber;
    }

    public String getOwnerName() {
        return ownerName;
    }

    public double getBalance() {
        return balance;
    }

   
    public void setOwnerName(String ownerName) {
        if (ownerName == null || ownerName.isEmpty()) {
            throw new IllegalArgumentException("Invalid name");
        }
        this.ownerName = ownerName;
    }

    public void setBalance(double balance) {
        if (balance < 0) {
            throw new IllegalArgumentException("Balance cannot be negative");
        }
        this.balance = balance;
    }

    
    public void deposit(double amount) {
        if (amount <= 0) {
            throw new IllegalArgumentException("Invalid deposit");
        }
        balance += amount;
    }

    
    public void withdraw(double amount) {
        if (amount <= 0) {
            throw new IllegalArgumentException("Invalid withdrawal");
        }
        if (amount > balance) {
            throw new IllegalArgumentException("Insufficient balance");
        }
        balance -= amount;
    }

    // Display
    public void display() {
        System.out.println("Account No: " + accountNumber);
        System.out.println("Name: " + ownerName);
        System.out.println("Balance: " + balance);
    }
}