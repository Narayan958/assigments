from abc import ABC, abstractmethod


class LibraryItem(ABC):
    item_count = 0  

    def __init__(self, title, year):
        self.title = title
        self.year = year
        LibraryItem.item_count += 1

    @abstractmethod
    def display_info(self):
        pass



class Book(LibraryItem):
    def __init__(self, title, year, author):
        super().__init__(title, year)
        self.author = author

    def display_info(self):
        return f"Book: {self.title} ({self.year}), Author: {self.author}"



class DVD(LibraryItem):
    def __init__(self, title, year, duration, genre="General"):  # default argument
        super().__init__(title, year)
        self.duration = duration
        self.genre = genre

    def display_info(self):
        return f"DVD: {self.title} ({self.year}), Duration: {self.duration} mins, Genre: {self.genre}"



def show_library(items):
    for item in items:
        print(item.display_info())



if __name__ == "__main__":
    item1 = Book("The Alchemist", 1988, "Paulo Coelho")
    item2 = DVD("Inception", 2010, 148, "Sci-Fi")
    item3 = DVD("Interstellar", 2014, 169)  

    library = [item1, item2, item3]

    show_library(library)

    print("\nTotal Library Items:", LibraryItem.item_count)