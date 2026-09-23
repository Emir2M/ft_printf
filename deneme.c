#include <stdarg.h>
#include <stdio.h>

// fonksiyon variadic olsun , yaş ortalamasını hesaplasın.

float avarage(int n, ...)
{
    va_list ap;
    int total;
    int i;

    va_start(ap, n);
    total = 0 ;
    i = 0 ;
    while (i <n)
    {
        total+=va_arg(ap, int);
        i++;
    }
    return (total/n);
}

int	main()
{
    float avarage_age;

    avarage_age = avarage(3, 21, 28,45);
    printf("kişilerin ortalama yaşi : %f\n", avarage_age);
}