class ScoreProcessor:

    def process_score_file(self, file_path: str) -> int:
        try:
            # Open the file
            file = open(file_path, "r")

            # Read data
            data = file.read().strip()

            # Convert to integer
            score = int(data)

        except FileNotFoundError:
            print("Error: File not found")
            raise

        except ValueError:
            print("Error: Invalid number format")
            raise

        else:
            print("Data processed successfully")
            return score * 10

        finally:
            print("File cleanup completed")

            try:
                file.close()
            except:
                pass


# Driver code
processor = ScoreProcessor()

try:
    result = processor.process_score_file("valid.txt")
    print("Final Result:", result)

except Exception:
    print("Program ended due to an error.")