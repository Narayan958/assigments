from registrationservice import is_valid_email


def test_valid_email():
    assert is_valid_email("abc@gmail.com") is True


def test_valid_email_with_numbers():
    assert is_valid_email("abc123@gmail.com") is True


def test_invalid_email_letters_after_numbers():
    assert is_valid_email("abc12abc@gmail.com") is False


def test_invalid_email_starting_with_number():
    assert is_valid_email("123abc@gmail.com") is False