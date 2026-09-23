#ifndef FT_PRİNTF_H
# define FT_PRİNTF_H

#include <stdarg.h> //va_... için
#include <stdio.h> //printf denemek için
#include <unistd.h> // write kütüphane

int ft_printf(const char *, ...);
int	ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_putnbr(int n);
int	ft_putunsigned(unsigned int n);
int	upper_hex(unsigned long long n);
int	lower_hex(unsigned long long n);
int	adresptr(void *ptr);

#endif
