#include <unistd.h>      // Pour write()
#include <stdio.h>       // Pour puts()

int ft_strlen(char *s)   // Fonction pour calculer la longueur d'une chaîne
{
	int i = 0;
	while (s[i])
		i++;
	return i;
}

// retourne 0 si déjà équilibrée
int min_to_remove(char *s) // Calcule le nombre minimal de parenthèses à retirer pour équilibrer la chaîne
{
    int open = 0, close = 0;
    for (int i = 0; s[i]; i++) // Parcourt chaque caractère
    {
        if (s[i] == '(')
            open++;            // Compte les parenthèses ouvrantes
        else if (s[i] == ')')
        {
            if (open > 0)
                open--;        // Annule une ouvrante avec une fermante
            else
                close++;       // Si aucune ouvrante, compte la fermante à retirer
        }
    }
return (open + close);    // Retourne le total à retirer pour équilibrer
}

// Fonction récursive pour générer toutes les combinaisons en retirant le minimum de parenthèses
void solve(int current_index, int total_to_remove, int n_removed, char *s)
{
// Cas de base : vérifier si la chaîne est équilibrée après avoir retiré le nombre minimal de parenthèses
if (current_index == ft_strlen(s)) // Si on a parcouru toute la chaîne
{
if (n_removed == total_to_remove && !min_to_remove(s)) // Si on a retiré le bon nombre et la chaîne est équilibrée
            puts(s);        // Affiche la solution
        return ;            // Fin de la branche récursive
    }
    // Arrêt anticipé : si on a déjà retiré trop de parenthèses
    if (n_removed > total_to_remove) // Si on retire trop de parenthèses, on arrête
        return ;
    if (s[current_index] == '(' || s[current_index] == ')') // Si le caractère est une parenthèse
    {
        // option 1 : retirer la parenthèse
        char temp = s[current_index];   // Sauvegarde le caractère
        s[current_index] = ' ';         // Retire la parenthèse (remplace par espace)
        solve(current_index + 1, total_to_remove, n_removed + 1, s); // Appel récursif en ayant retiré la parenthèse
        s[current_index] = temp;        // Restaure le caractère
        // option 2 : garder la parenthèse
        solve(current_index + 1, total_to_remove, n_removed, s); // Appel récursif en gardant la parenthèse
    }
    else // Pour les espaces ou autres caractères, on continue simplement
        solve(current_index + 1, total_to_remove, n_removed, s); // Si ce n'est pas une parenthèse, avance simplement
}

int main(int argc, char **argv)
{
    // gestion d'erreur si argc incorrect
    if (argc != 2)                  // Vérifie qu'il y a bien un argument (la chaîne à traiter)
    {
        write(1, "\n", 1);          // Affiche une ligne vide si erreur
        return 0;
    }
    char *s = argv[1];              // Récupère la chaîne à traiter
    // vérification si déjà équilibrée
    if (!min_to_remove(s))          // Si la chaîne est déjà équilibrée
    {
        puts(s);                    // Affiche la chaîne telle quelle
        return 0;
    }
    // résolution récursive
    solve(0, min_to_remove(s), 0, s); // Lance la résolution récursive
    return 0;
}

/****************************************************/
//SANS COMMENTAIRE

/*#include <unistd.h>
#include <stdio.h>

int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

int min_to_remove(char *s)
{
    int open = 0, close = 0;
    for (int i = 0; s[i]; i++)
    {
        if (s[i] == '(')
            open++;
        else if (s[i] == ')')
        {
            if (open > 0)
                open--;
            else
                close++;
        }
    }
    return (open + close);
}

void solve(int current_index, int total_to_remove, int n_removed, char *s)
{
    if (current_index == ft_strlen(s))
    {
        if (n_removed == total_to_remove && !min_to_remove(s))
            puts(s);
        return ;
    }
    if (n_removed > total_to_remove)
        return ;
    if (s[current_index] == '(' || s[current_index] == ')')
    {
        char temp = s[current_index];
        s[current_index] = ' ';
        solve(current_index + 1, total_to_remove, n_removed + 1, s);
        s[current_index] = temp;
        solve(current_index + 1, total_to_remove, n_removed, s);
    }
    else
        solve(current_index + 1, total_to_remove, n_removed, s);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        write(1, "\n", 1);
        return 0;
    }
    char *s = argv[1];
    if (!min_to_remove(s))
    {
        puts(s);
        return 0;
    }
    solve(0, min_to_remove(s), 0, s);
    return 0;
}*/