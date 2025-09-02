
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int ft_vfscanf(FILE *f, const char *format, va_list ap);

//@Rôle : Passes les espaces, puis remet le premier caractère non-espace pour la prochaine lecture
//Utilité : Permet d’ignorer les espaces avant de lire une valeur (utile pour %d et %s).
int match_space(FILE *f)
{
    int x = fgetc(f);		// Lit un caractère depuis le flux f et le stocke dans x.
    if(x == EOF)			// Si on atteint la fin du flux ou une erreur,
        return -1;			// on retourne -1 pour signaler l’erreur.
    while (isspace(x))		// Tant que x est un caractère d’espacement (espace, tab, retour à la ligne…)
        x = fgetc(f);		// on lit le caractère suivant.
	if (x != EOF)
    	ungetc(x, f);		    // On remet le dernier caractère non-espace dans le flux pour qu’il soit lu plus tard.
    //return (1);		    // (commenté) On pourrait retourner 1 pour signaler qu’on a consommé des espaces.
    return (0);				// On retourne 0 (aucune erreur, mais pas d’indication sur le nombre d’espaces lus).
}

//@Rôle : Vérifie si le prochain caractère du flux correspond à c.
//Si oui, elle le consomme ; 
//sinon, elle le remet dans le flux et indique qu’il ne correspond pas.
//Utilité : Permet de vérifier et consommer un caractère précis dans l’entrée (par exemple, un séparateur).
//ft_scanf("%d,%s") ==> cherche ','
//ft_scanf("%d-hello- %s") ==> cherche '-hello-'
//ft_scanf("%d %s") ==> ne sert pas car pas de separateur
int match_char(FILE *f, char c)
{
    int x = fgetc(f);		// Lit un caractère depuis le flux f et le stocke dans x.
    if(x == EOF)			// Si on atteint la fin du flux ou une erreur,
        return -1;			// on retourne -1 pour signaler l’erreur.
    if(x == c)				// Si le caractère lu est égal à celui attendu (c),
        return 1;			// on retourne 1 pour signaler que le caractère correspond.
    ungetc(x, f);			// Sinon, on remet le caractère dans le flux pour qu’il soit lu plus tard.
    return (0);				// On retourne 0 pour signaler que le caractère ne correspond pas.
}
//@Rôle : Lit un caractère du flux et le stocke dans la variable passée en argument, 
//remet le caractère dans le flux (pour cohérence avec le reste du parsing), et indique 
//le succès.
//Utilité : Sert à gérer la conversion %c.
int scan_char(FILE *f, va_list ap)
{
    int x = fgetc(f);		     // Lit un caractère depuis le flux f et le stocke dans x.
    char *y = va_arg(ap, char *);// Récupère le pointeur vers la variable où stocker le caractère.
    if(x == EOF)		         // Si on atteint la fin du flux ou une erreur,
        return -1;		         // on retourne -1 pour signaler l’erreur.
    *y = x;				   	     // Stocke le caractère lu dans la variable pointée par y.
    //ungetc(x, f);		         // Remet le caractère dans le flux pour qu’il soit lu à nouveau si besoin.
    return (1);		             // Retourne 1 pour signaler qu’un caractère a été lu et stocké.
}
//@Rôle : Lit un entier (avec gestion du signe) depuis le flux, le construit chiffre par 
//chiffre, le stocke dans la variable passée, et remet le premier caractère non-chiffre 
//dans le flux pour la suite du parsing.
//Utilité : Sert à gérer la conversion %d.
int scan_int(FILE *f, va_list ap)
{
    int x = fgetc(f);		     // Lit le premier caractère du flux.
    int *y = va_arg(ap, int *);      // Récupère le pointeur vers la variable où stocker l'entier.
    int res = 0;		          // Initialise le résultat à 0.
    int sign = 1;		         // Initialise le signe à positif.

    if(x == '-' || x == '+')         // Si le caractère est un signe (- ou +),
    {
        if(x == '-')		      // Si c'est un '-', le signe devient négatif.
		 sign = -1;
        int xx = fgetc(f);		// Lit le caractère suivant.
        if(!isdigit(xx))		  // Si ce n'est pas un chiffre,
        {
		 ungetc(xx, f);		// Remet le caractère dans le flux.
		 ungetc(x, f);		 // Remet aussi le signe dans le flux.
		 return -1;		    // Retourne -1 pour signaler une erreur.
        }
        x = xx;				// Sinon, x devient ce chiffre.
    }
    if(!isdigit(x))		       // Si le caractère n'est pas un chiffre,
    {
        ungetc(x, f);		     // On le remet dans le flux.
        return -1;		        // Retourne -1 pour signaler une erreur.
    }
    while(isdigit(x))		     // Tant que le caractère est un chiffre,
    {
        res = res * 10 + (x - 48);   // On construit l'entier chiffre par chiffre.
        x = fgetc(f);		     // Lit le caractère suivant.
    }
    *y = res * sign;		      // Stocke le résultat (avec le signe) dans la variable.
    ungetc(x, f);		         // Remet le dernier caractère non-chiffre dans le flux.
    return (1);				// Retourne 1 pour signaler qu'un entier a été lu et stocké.
}

//@Rôle : Lit et stocke les caractères dans la chaîne jusqu’à rencontrer un espace ou la 
//fin du flux, puis termine la chaîne et remet le dernier caractère dans le flux pour la 
//suite du parsing.
//Utilité : Sert à gérer la conversion %s.
int scan_string(FILE *f, va_list ap)
{
    int x = fgetc(f);		     // Lit le premier caractère du flux.
    char *s = va_arg(ap, char *);    // Récupère le pointeur vers la variable où stocker la chaîne.
    int y = 0;				 // Initialise l’index pour remplir la chaîne.

    while(!isspace(x) && x != EOF)   // Tant que le caractère n’est pas un espace ou la fin du flux,
    {
        s[y++] = x;		       // Stocke le caractère dans la chaîne et avance l’index.
        x = fgetc(f);		     // Lit le caractère suivant.
    }
    s[y] = '\0';		          // Termine la chaîne par le caractère nul.
    ungetc(x, f);		         // Remet le dernier caractère non pris (espace ou EOF) dans le flux.
    return (1);				// Retourne 1 pour signaler qu’une chaîne a été lue et stockée.
}

//@Rôle : Pprépare la gestion des arguments variables, appelle la fonction qui fait le vrai travail de lecture (ft_vfscanf), puis termine proprement et retourne le résultat.
//C’est l’interface utilisateur, équivalente à scanf
//Utilité : Fait le lien entre le format et la fonction de lecture.
int ft_scanf(const char *format, ...)
{
	va_list ap;				  // Déclare une variable pour gérer les arguments variables.
	va_start(ap, format);		   // Initialise la liste d’arguments variables à partir de 'format'.
	int ret = ft_vfscanf(stdin, format, ap); // Appelle la fonction principale de lecture, en passant l’entrée standard, le format et les arguments.
	va_end(ap);				  // Termine l’utilisation de la liste d’arguments variables.
	return ret;				  // Retourne le nombre de valeurs lues et assignées.
}
/************************************************************/
//@Rôle : Parcourt la chaîne de format, appelle les fonctions de lecture selon les conversions trouvées, et compte le nombre de valeurs lues.
//choisit la bonne fonction de lecture selon le caractère de conversion (c, d, s), ignore les espaces si besoin, et retourne le résultat de la lecture.
//Si la conversion n’est pas reconnue ou en cas de fin de flux, elle retourne -1.
int match_conv(FILE *f, const char **format, va_list ap)
{
    switch (**format)		         // Examine le caractère de conversion pointé par format.
    {
        case 'c':				  // Si c'est 'c' (conversion caractère),
		 return scan_char(f, ap);     // Appelle scan_char pour lire un caractère.
        case 'd':				  // Si c'est 'd' (conversion entier),
		 match_space(f);		   // Ignore les espaces avant de lire l'entier.
		 return scan_int(f, ap);      // Appelle scan_int pour lire un entier.
        case 's':				  // Si c'est 's' (conversion chaîne),
		 match_space(f);		   // Ignore les espaces avant de lire la chaîne.
		 return scan_string(f, ap);   // Appelle scan_string pour lire une chaîne.
        case EOF:				  // Si on atteint la fin du flux,
		 return -1;		        // Retourne -1 pour signaler une erreur ou fin.
        default:				   // Pour tout autre caractère (conversion non gérée),
		 return -1;		        // Retourne -1 pour signaler une erreur.
    }
}
//@Rôle : Parcourt le format, appelle les fonctions de lecture appropriées, gère les espaces et les caractères fixes, 
//et compte le nombre de valeurs lues avec succès.
//Elle s’arrête en cas d’erreur ou de fin de flux
//Utilité : Cœur du système de lecture, gère la logique principale.
int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
    int nconv = 0;		        // Compteur du nombre de conversions réussies.

    int c = fgetc(f);		     // Lit le premier caractère du flux.
    if (c == EOF)		         // Si fin de flux ou erreur,
        return EOF;		       // retourne EOF.
    ungetc(c, f);		         // Remet le caractère dans le flux pour la suite.

    while (*format)		       // Parcourt la chaîne de format caractère par caractère.
    {
        if (*format == '%')          // Si on trouve un '%', c'est une conversion.
        {
			format++;		     // Passe au caractère de conversion.
			if (match_conv(f, &format, ap) != 1) // Tente la conversion.
				break;		    // Si échec, on arrête la lecture.
			else
				nconv++;		 // Sinon, on incrémente le compteur de conversions réussies.
        }
        else if (isspace(*format))   // Si le format attend un espace,
        {
			if (match_space(f) == -1) // Ignore les espaces dans le flux.
				break;		    // Si erreur, on arrête.
        }
        else if (match_char(f, *format) != 1) // Si le format attend un caractère précis,
		 	break;		        // Si le caractère ne correspond pas, on arrête.
        format++;		         // Passe au caractère suivant du format.
    }

    if (ferror(f))		        // Si une erreur de flux est détectée,
        return EOF;		       // retourne EOF.
    return nconv;		         // Retourne le nombre de conversions réussies.
}




int main()
{
	int i;
	char x[100];
	//scanf("%d %s", &i, x);
	//printf("scanf ==> %d %s", i, x);
	ft_scanf("%d %s", &i, x);
	printf("ft_scanf ==> %d %s", i, x);
}

//int main(void) 
//{
//	int entier;
//	char mot[100];
//	printf("Entrez un entier puis un mot : ");
//	if (ft_scanf("%d %s", &entier, mot) != 2)
//	{
//		printf("Erreur de saisie.\n");
//		return 1;
//	}
//	printf("Entier lu : %d\nMot lu    : %s\n", entier, mot);
//	return 0;
//}
