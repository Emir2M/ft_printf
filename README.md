*This project has been created as part of the 42 curriculum by emirhyil.*

# ft_printf

## Description

ft_printf is a project from the 42 curriculum. The goal is to recode the `printf()` function from the C standard library (`libc`) and package it as a static library called `libftprintf.a`.

The prototype of the function is:

```c
int	ft_printf(const char *format, ...);
```

Like the original `printf()`, `ft_printf()` walks through a format string, prints ordinary characters as they are, replaces each conversion specifier with the matching argument, and returns the total number of characters printed.

The main learning goal of the project is **variadic functions** in C: functions that accept a variable number of arguments. The project also reinforces concepts from Libft, such as:

- Variadic arguments with `va_list`, `va_start`, `va_arg` and `va_end`
- Recursion
- Number base conversion (decimal and hexadecimal)
- Signed and unsigned integer types
- Printing memory addresses
- Writing directly to standard output with `write`
- Static libraries and Makefiles

As the subject requires, the buffer management of the original `printf()` is not implemented. Every character is written to standard output as soon as it is processed.

---

## Supported Conversions

| Conversion | Argument type    | Output                                         |
|------------|------------------|------------------------------------------------|
| `%c`       | `int` (as `char`)| A single character                             |
| `%s`       | `char *`         | A string, or `(null)` if the pointer is `NULL` |
| `%p`       | `void *`         | The address in hexadecimal with a `0x` prefix, or `(nil)` if the pointer is `NULL` |
| `%d`       | `int`            | A signed decimal (base 10) number              |
| `%i`       | `int`            | A signed integer in base 10                    |
| `%u`       | `unsigned int`   | An unsigned decimal (base 10) number           |
| `%x`       | `unsigned int`   | A hexadecimal (base 16) number in lowercase    |
| `%X`       | `unsigned int`   | A hexadecimal (base 16) number in uppercase    |
| `%%`       | none             | A percent sign                                 |

The `(null)` and `(nil)` outputs match the behavior of the original `printf()` on Linux (glibc).

The bonus part (flags and field width) is not implemented.

---

## Project Structure

| File                | Contents |
|---------------------|----------|
| `ft_printf.h`       | Header file with all function prototypes and the required includes (`stdarg.h`, `unistd.h`) |
| `ft_printf.c`       | `ft_printf()` and the dispatcher function `format()` |
| `ft_print_utils.c`  | `ft_putchar`, `ft_putstr`, `ft_putnbr`, `ft_putunsigned`, `adresptr` |
| `ft_print_utils2.c` | `lower_hex`, `upper_hex` |
| `Makefile`          | Builds `libftprintf.a` |

---

## Algorithm and Data Structures

### Main loop

`ft_printf()` reads the format string one character at a time with an index `i`, and keeps a counter `len` for the number of characters printed.

1. `va_start` initializes the `va_list` so the variadic arguments can be read.
2. For each character of the format string:
   - If the character is not `%`, it is printed with `ft_putchar` and `len` increases by 1.
   - If the character is `%`, the index moves to the next character (the conversion specifier) and it is passed to `format()`, together with the `va_list`.
3. When the end of the string (`'\0'`) is reached, `va_end` cleans up the `va_list` and `len` is returned.

The algorithm runs in a single pass over the format string, so its time complexity is linear in the length of the format string plus the length of the printed output.

### Dispatcher: `format()`

`format()` looks at the conversion specifier and decides which helper function to call. It reads the next argument with `va_arg`, using the correct type for each conversion:

- `%c`, `%d`, `%i` read an `int` (a `char` is promoted to `int` when it is passed to a variadic function, so `va_arg(ap, char)` would be incorrect)
- `%s` reads a `char *`
- `%p` reads a `void *`
- `%u`, `%x`, `%X` read an `unsigned int`

Each helper returns the number of characters it printed, and `format()` returns that value to `ft_printf()`. This way the total count is built up without any global variable.

I chose a simple chain of `if` statements because the number of conversions is small and fixed. It is easy to read, easy to defend during evaluation, and easy to extend: adding a new conversion only needs one new `if` and one new helper function.

### Helper functions

Every helper prints its value and **returns the number of characters it wrote**. This return value is what makes the final count of `ft_printf()` correct.

- **`ft_putchar`** writes one character with `write(1, &c, 1)` and returns `1`. All other helpers are built on top of it.
- **`ft_putstr`** prints a string character by character. If the pointer is `NULL`, it prints `(null)` instead, like the original `printf()`.
- **`ft_putnbr`** prints a signed integer recursively. `-2147483648` (`INT_MIN`) is handled as a special case, because `-n` would overflow an `int`. For other negative numbers, a `-` is printed and the number is made positive.
- **`ft_putunsigned`** works like `ft_putnbr` but for `unsigned int`, so there is no sign to handle.
- **`lower_hex` / `upper_hex`** print a number in base 16. Each one uses a lookup string (`"0123456789abcdef"` or `"0123456789ABCDEF"`) and takes the digit with `hex[n % 16]`. The only difference between the two is the lookup string.
- **`adresptr`** prints a pointer. If it is `NULL`, it prints `(nil)`. Otherwise, it prints `0x` and then the address in lowercase hexadecimal using `lower_hex`.

### Why recursion for numbers

Dividing a number by its base gives the digits from right to left, but they must be printed from left to right. Recursion solves this without an extra buffer:

```text
ft_putnbr(123)
 └─ ft_putnbr(12)
     └─ ft_putnbr(1)  -> prints '1'
    prints '2'
 prints '3'
```

The function first calls itself with `n / base` until only one digit is left, then prints `n % base` while the calls return. This avoids allocating memory with `malloc` (so there is no risk of memory leaks), and it avoids a temporary array whose size would depend on the base and type. The recursion depth is small: at most 10 levels for a 32-bit decimal number and at most 16 levels for a 64-bit hexadecimal number.

### Why `unsigned long long` for hexadecimal

`lower_hex` and `upper_hex` take an `unsigned long long` so the same function can print both:

- `%x` / `%X` values, which are `unsigned int` (32 bits), and
- `%p` addresses, which are 64 bits on a 64-bit system.

An `unsigned int` would cut off the upper half of a 64-bit address. Using one wide unsigned type avoids duplicate code for pointers and hexadecimal numbers.

### Data structures

No complex data structure is needed. The project only uses:

- a `va_list` to walk through the variadic arguments,
- an `int` index to walk through the format string,
- an `int` counter for the number of printed characters,
- constant lookup strings for the hexadecimal digits.

No memory is allocated on the heap, so there is nothing to free and no possible memory leak.

---

## Instructions

### Compilation

The project includes a `Makefile` that compiles the source files and creates the static library:

```bash
make
```

After successful compilation, the following library is generated at the root of the repository:

```text
libftprintf.a
```

The source files are compiled with:

```text
cc -Wall -Wextra -Werror
```

The static library is created with the `ar` command (`ar rcs`), as the subject requires. The `libtool` command is not used.

### Makefile Rules

```bash
make
```

Compiles the source files and creates `libftprintf.a`.

```bash
make clean
```

Removes the generated object files.

```bash
make fclean
```

Removes the object files and `libftprintf.a`.

```bash
make re
```

Performs a full recompilation by running `fclean` followed by `all`.

---

## Using ft_printf

Include the header in your C source file:

```c
#include "ft_printf.h"
```

Example:

```c
#include "ft_printf.h"

int main(void)
{
    int n;
    int len;

    n = 42;
    len = ft_printf("Char: %c | String: %s\n", 'A', "Hello");
    ft_printf("Decimal: %d | Integer: %i | Unsigned: %u\n", -42, 2147483647, 4294967295u);
    ft_printf("Hex: %x | HEX: %X | Pointer: %p\n", 255, 255, &n);
    ft_printf("Percent: %%\n");
    ft_printf("First line length: %d\n", len);
    return (0);
}
```

Compile the program together with the library:

```bash
cc main.c libftprintf.a -o program
```

Then run it:

```bash
./program
```

Output (the pointer address will be different on your machine):

```text
Char: A | String: Hello
Decimal: -42 | Integer: 2147483647 | Unsigned: 4294967295
Hex: ff | HEX: FF | Pointer: 0x7ffd5c3a1b2c
Percent: %
First line length: 24
```

---

## Resources

The resources used during the development of this project were:

- The official 42 ft_printf subject
- Peer learning and discussions with other 42 students
- [A YouTube video on variadic functions in C](https://www.youtube.com/watch?v=7Sph8JlRo0g)

Almost the entire project was built through peer learning. Discussing problems and different approaches with other students helped me understand how `printf()` behaves and how to structure my own implementation.

To understand variadic functions, I watched the YouTube video above. After understanding what was done in the video, I coded the examples again on my own as practice, then applied what I learned to `ft_printf()`.

### Testing

I tested my implementation in two ways:

- I wrote my own `main` files that call both `ft_printf()` and the original `printf()` with the same arguments, then compared their outputs.
- I used a community tester to check the conversions and edge cases.

---

## AI Usage

AI was almost not used in this project.

The code was written, debugged and tested by me, with the help of peer learning and the YouTube video listed in the Resources section. AI was not used to write, explain or debug any part of the source code.

AI was only used to help write and structure this README, based on my source code and on the README requirements of the subject. I reviewed its content to make sure it correctly describes my implementation.
