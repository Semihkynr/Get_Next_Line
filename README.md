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
- Reads one line from a file descriptor each time it's called
- Returns `NULL` when there is nothing else to read or an error occurs
- Supports any `BUFFER_SIZE` defined at compile time
- Efficient memory handling (no leaks, no overflows)

### Bonus Part
- Handles **multiple file descriptors** at the same time
- Each file descriptor keeps its own buffer state independently
- Works with standard input (`stdin`) as well as regular files

---

## 🧩 Function Prototype

```c
char *get_next_line(int fd);
```

The mandatory and bonus parts share the exact same prototype — the bonus implementation simply keeps the leftover data per file descriptor instead of a single global buffer, so several `fd`s can be read from in parallel without mixing their state.

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
└── README.md
```

---

## 🧮 Compilation & Usage

### Compile (Mandatory)
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o a.out
```

### Compile (Bonus)
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o a.out
```
> Note: to test the bonus part, `main.c` must `#include "get_next_line_bonus.h"` instead of `get_next_line.h`.

### Run
```bash
./a.out text.txt
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

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc < 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```

**Output:**
```
$ ./a.out text.txt
Hello world!
42 Network
Get Next Line Project
```

---

## 🧱 Key Concepts

| Concept | Description |
|---|---|
| **Static variable** | Keeps leftover data between function calls |
| **Buffer** | Temporarily holds data just read from the file |
| **Newline detection** | Splits the buffered data at the next `'\n'` |
| **File descriptor** | An integer used to identify an open file |
| **Memory safety** | Every allocation is freed once it's no longer needed |

---

## 🧪 Testing Tips

- Change `BUFFER_SIZE` (1, 42, 9999, ...) to check correctness under different chunk sizes
- Test with empty files, files without a trailing newline, and files that are only newlines
- Test reading from **stdin** using:
  ```bash
  cat text.txt | ./a.out /dev/stdin
  ```
- Use **Valgrind** or **AddressSanitizer** to check for memory leaks:
  ```bash
  cc -fsanitize=address,leak -g -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o a.out
  ./a.out text.txt
  ```

---

## 👨‍💻 Author

- [**Semih Kaynar**](https://github.com/semihkaynar) — Developer
- 42 Istanbul 🇹🇷

---

## 📜 License

This project is developed as part of the **42 curriculum** and is intended for educational purposes only.
