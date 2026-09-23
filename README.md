*This project has been created as part of the 42 curriculum by emirhyil.*

# ft_printf - Because ft_putnbr() and ft_putstr() aren't enough

## 📌 Description

The **ft_printf** project is a core 42 curriculum assignment that requires recoding the standard C C-library `printf()` function. The main goal of this project is to gain a thorough understanding of **variadic functions** in C, memory management, low-level string manipulation, and system calls (`write`).

The resulting library `libftprintf.a` contains the custom `ft_printf()` function, which mimics the core behaviors and conversion specifiers of the original C standard function without complex buffer management.

---

## 🔣 Supported Format Specifiers

The mandatory part of `ft_printf` handles the following specifiers:

| Specifier | Description | Example Output |
| :---: | :--- | :--- |
| `%c` | Prints a single character | `a` |
| `%s` | Prints a string of characters | `Hello World` |
| `%p` | Prints a `void *` pointer in hexadecimal format | `0x7ffeefbff5c0` |
| `%d` | Prints a signed decimal (base 10) integer | `-42` |
| `%i` | Prints an integer in base 10 | `42` |
| `%u` | Prints an unsigned decimal (base 10) number | `4294967295` |
| `%x` | Prints a number in hexadecimal (base 16) **lowercase** | `2a` |
| `%X` | Prints a number in hexadecimal (base 16) **uppercase** | `2A` |
| `%%` | Prints a percent sign | `%` |

---

## 📐 Algorithm & Data Structures

### 1. Data Structures & Variadic Functions
This project relies on C's native variadic argument macros defined in `<stdarg.h>`:
- **`va_list`**: A specialized data type used as a state variable to hold the information needed by `va_arg`, `va_start`, and `va_end`.
- **`va_start`**: Initializes the `va_list` object to iterate through the optional arguments starting after the last named argument.
- **`va_arg`**: Retrieves the next argument in the parameter list according to the specified type (e.g., `int`, `char *`, `void *`).
- **`va_end`**: Cleans up the `va_list` object before the function returns to prevent undefined behavior.

### 2. Execution Flow & Parsing Logic
The function iterates over the format string character by character:
1. **Regular Characters**: If the current character is not `%`, it is immediately output using `write(1, ...)` and increments the character counter.
2. **Specifier Detection**: When `%` is encountered, the parser inspects the subsequent character to determine the target conversion type.
3. **Dispatcher Function**: A single function dispatcher routes the specifier to its dedicated handler function (`ft_print_char`, `ft_print_str`, `ft_print_int`, `ft_print_hex`, `ft_print_ptr`, etc.).
4. **Base Conversion & Recursion**:
   - Integers (`%d`, `%i`, `%u`) and hexadecimal values (`%x`, `%X`, `%p`) are processed recursively or via positional modulo arithmetic using target base strings (`"0123456789"` and `"0123456789abcdef"` / `"0123456789ABCDEF"`).
5. **Return Value Tracking**: Every helper function returns the exact number of bytes written to standard output. The main function sums these values and returns the total byte count, matching standard `printf` behavior.

---

## 🛠️ Instructions

### Compilation

To compile the library, navigate to the root directory and run `make`. This will create the static library `libftprintf.a`.

```bash
make
-a