[README_GNL.md](https://github.com/user-attachments/files/23425752/README_GNL.md)
# 📜 Get Next Line

**Get Next Line (GNL)** is a 42 project focused on reading text from a file descriptor **line by line**, regardless of the buffer size or line length.  
The goal is to understand how file reading works in C, including **buffers**, **static variables**, and **memory management**.

---

## 🧠 Purpose

The project aims to:
- Understand how to manage **file descriptors**  
- Learn how to store and reuse data between function calls using **static variables**  
- Handle **dynamic memory allocation** safely  
- Work efficiently with any **BUFFER_SIZE**  
- Prepare for more advanced I/O and parsing projects  

---

## ⚙️ Features

### Mandatory Part
- Reads one line from a file descriptor each time it’s called  
- Returns `NULL` when there is nothing else to read or an error occurs  
- Supports any `BUFFER_SIZE` defined at compile time  
- Efficient memory handling (no leaks, no overflows)

### Bonus Part
- Handles **multiple file descriptors** at the same time  
- Each file descriptor keeps its own buffer state independently  
- Works with standard input (`stdin`) as well as regular files  

---

## 🧩 Function Prototypes

### Mandatory
```c
char *get_next_line(int fd);
```

### Bonus
```c
char *get_next_line(int fd);
```
*(The same prototype — but must handle multiple file descriptors)*

---

## 📂 Project Structure

```
get_next_line/
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line.h
├── get_next_line_bonus.c
├── get_next_line_utils_bonus.c
├── get_next_line_bonus.h
└── main.c (for testing)
```

---

## 🧮 Compilation & Usage

### Compile (Mandatory)
```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -D BUFFER_SIZE=42
```

### Compile (Bonus)
```bash
cc -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils_bonus.c main.c -D BUFFER_SIZE=42
```

### Run Example
```bash
./a.out
```

---

## 🧰 Example

**Example file (`text.txt`):**
```
Hello world!
42 Network
Get Next Line Project
```

**Example program (`main.c`):**
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("text.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

**Output:**
```
Hello world!
42 Network
Get Next Line Project
```

---

## 🧱 Key Concepts

| Concept | Description |
|----------|--------------|
| **Static variable** | Keeps leftover data between function calls |
| **Buffer** | Temporarily holds data read from the file |
| **Newline detection** | Splits data until a `'
'` is found |
| **File descriptor** | An integer used to identify an open file |
| **Memory safety** | Each allocation must be freed properly |

---

## 🧪 Testing Tips

- Change `BUFFER_SIZE` to test performance and correctness  
- Test with empty files, long lines, and multiple newlines  
- Test reading from **stdin** using:  
  ```bash
  cat file.txt | ./a.out
  ```
- Use **Valgrind** or **leaks** to check for memory leaks  

---

## 👨‍💻 Author

- [**Semih Kaynar**](https://github.com/semihkaynar) — Developer  
- 42 Istanbul 🇹🇷  

---

## 📜 License

This project is developed as part of the **42 curriculum** and is intended for educational purposes only.
