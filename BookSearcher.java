import java.util.ArrayList;
import java.util.Scanner;

public class BookSearcher {

    public static void main(String[] args) {
        ArrayList<String> books = new ArrayList<>();
        
        books.add("The Great Gatsby");
        books.add("To Kill a Mockingbird");
        books.add("1984 by George Orwell");
        books.add("Pride and Prejudice");
        books.add("The Catcher in the Rye");
        books.add("Brave New World");

        System.out.println("Book titles stored:");
        for (String book : books) {
            System.out.println("- " + book);
        }

        Scanner scanner = new Scanner(System.in);
        System.out.print("\nEnter a word to search in book titles: ");
        String searchWord = scanner.nextLine();

        System.out.println("\nBooks containing '" + searchWord + "':");
        boolean found = false;
        
        for (String book : books) {
            if (book.toLowerCase().contains(searchWord.toLowerCase())) {
                System.out.println("- " + book);
                found = true;
            }
        }

        if (!found) {
            System.out.println("No books found matching the search word.");
        }

        scanner.close();
    }
}