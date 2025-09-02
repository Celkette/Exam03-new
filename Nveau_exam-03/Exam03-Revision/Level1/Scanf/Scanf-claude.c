#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int c;
    int matched = 0;
    
    // Lit et ignore tous les caractères d'espacement
    while ((c = fgetc(f)) != EOF && isspace(c))
        matched = 1;
    
    if (c != EOF)
        ungetc(c, f);  // Remet le caractère non-espace dans le flux
    
    return matched ? 1 : (c == EOF ? -1 : 1);
}

int match_char(FILE *f, char expected)
{
    int c = fgetc(f);
    
    if (c == EOF)
        return -1;
    
    if (c == expected)
        return 1;
    
    ungetc(c, f);  // Remet le caractère dans le flux s'il ne correspond pas
    return 0;
}

int scan_char(FILE *f, va_list ap)
{
    int c = fgetc(f);
    
    if (c == EOF)
        return -1;
    
    char *ptr = va_arg(ap, char *);
    *ptr = (char)c;
    
    return 1;
}

int scan_int(FILE *f, va_list ap)
{
    int c;
    int sign = 1;
    int num = 0;
    int has_digits = 0;
    
    // Ignore les espaces initiaux
    while ((c = fgetc(f)) != EOF && isspace(c))
        ;
    
    if (c == EOF)
        return -1;
    
    // Gère le signe
    if (c == '-') {
        sign = -1;
        c = fgetc(f);
    } else if (c == '+') {
        c = fgetc(f);
    }
    
    // Lit les chiffres
    while (c != EOF && isdigit(c)) {
        num = num * 10 + (c - '0');
        has_digits = 1;
        c = fgetc(f);
    }
    
    if (c != EOF)
        ungetc(c, f);  // Remet le caractère non-chiffre
    
    if (!has_digits)
        return 0;  // Aucun chiffre trouvé
    
    int *ptr = va_arg(ap, int *);
    *ptr = num * sign;
    
    return 1;
}

int scan_string(FILE *f, va_list ap)
{
    int c;
    char *str = va_arg(ap, char *);
    int i = 0;
    
    // Ignore les espaces initiaux
    while ((c = fgetc(f)) != EOF && isspace(c))
        ;
    
    if (c == EOF)
        return -1;
    
    // Lit les caractères non-espaces
    while (c != EOF && !isspace(c)) {
        str[i++] = (char)c;
        c = fgetc(f);
    }
    
    if (c != EOF)
        ungetc(c, f);  // Remet l'espace ou EOF
    
    if (i == 0)
        return 0;  // Aucun caractère lu
    
    str[i] = '\0';  // Termine la chaîne
    return 1;
}

int match_conv(FILE *f, const char **format, va_list ap)
{
    switch (**format)
    {
        case 'c':
            return scan_char(f, ap);
        case 'd':
            match_space(f);
            return scan_int(f, ap);
        case 's':
            match_space(f);
            return scan_string(f, ap);
        case EOF:
            return -1;
        default:
            return -1;
    }
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
    int nconv = 0;

    int c = fgetc(f);
    if (c == EOF)
        return EOF;
    ungetc(c, f);

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            if (match_conv(f, &format, ap) != 1)
                break;
            else
                nconv++;
        }
        else if (isspace(*format))
        {
            if (match_space(f) == -1)
                break;
        }
        else if (match_char(f, *format) != 1)
            break;
        format++;
    }
    
    if (ferror(f))
        return EOF;
    return nconv;
}

int ft_scanf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int ret = ft_vfscanf(stdin, format, ap);
    va_end(ap);
    return ret;
}