import re


def is_valid_email(email):
    pattern = r"^[a-zA-Z]+[0-9]*@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$"
    return re.match(pattern, email) is not None


def is_valid_age(age):
    return age >= 18


def register_user(email, age):
    if not is_valid_email(email):
        return (
            "Invalid Email: letters after numbers are not allowed "
            "before @"
        )

    if not is_valid_age(age):
        return "Age must be 18 or above"

    return f"Registration Successful\nEmail: {email}\nAge: {age}"


def main():
    email = input("Enter Email: ")
    age = int(input("Enter Age: "))

    result = register_user(email, age)
    print("\n" + result)


if __name__ == "__main__":
    main()