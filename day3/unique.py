def find_unique_characters(file_path):
    unique_characters = set()

    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            for line in file:
                unique_characters.update(set(line))

        print("Unique Characters:")
        for char in sorted(unique_characters):
            print(f"'{char}',", end=' ')
        print("\nTotal unique characters:", len(unique_characters))

    except FileNotFoundError:
        print(f"Error: File not found at '{file_path}'")
    except Exception as e:
        print(f"An error occurred: {e}")

find_unique_characters('input.txt')
