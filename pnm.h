/**
 * pnm.h
 * 
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation d'images PNM.
 * 
 * @author: Dumoulin Peissone S193957
 * @date: 22/02/21
 * @projet: INFO0030 Projet 1
 */

/*
 * Include guard (pour éviter les problèmes d'inclusions multiplies
 * Bonne pratique: toujours encadrer un header avec un include guard
 */
#ifndef __PNM__
#define __PNM__

/**
 * Déclaration du type opaque PNM
 *
 */
typedef struct PNM_t PNM;

/**
 * load_pnm
 *
 * Charge une image PNM depuis un fichier.
 *
 * @param image l'adresse d'un pointeur sur PNM à laquelle écrire l'adresse
 *              de l'image chargée.
 * @param filename le chemin vers le fichier contenant l'image.
 *
 * @pre: image != NULL, filename != NULL
 * @post: image pointe vers l'image chargée depuis le fichier.
 *
 * @return:
 *     0 Succès
 *    -1 Erreur à l'allocation de mémoire
 *    -2 Nom du fichier malformé
 *    -3 Contenu du fichier malformé
 *
 */
int load_pnm(PNM **image, char* filename);

/**
 * write_pnm
 *
 * Sauvegarde une image PNM dans un fichier.
 *
 * @param image un pointeur sur PNM.
 * @param filename le chemin vers le fichier de destination.
 *
 * @pre: image != NULL, filename != NULL
 * @post: le fichier filename contient l'image PNM image.
 *
 * @return:
 *     0 Succès
 *    -1 Nom du fichier malformé
 *    -2 Erreur lors de la manipulation du fichier
 *
 */
int write_pnm(PNM *image, char* filename);

/*
 * *create_pnm
 * 
 * Crée et alloue dynamiquement une variable de type opaque PNM*
 * 
 * @param magicNumber l'entier représentant la chaîne de caractère initiale 
 *        (1 pour "P1", 2 pour "P2" et 3 pour "P3")
 * @param columns le nombre de pixels "verticaux"
 * @param rows le nombre de pixels "horizontaux"
 * @param maxValuePixel la valeur maximale que peut prendre un pixel
 * 
 * @pre: /
 * @post: *image alloué
 * 
 * @return:
 *    0 Succès
 *    NULL Erreur lors de l'allocation dynamique
 */
PNM *create_pnm(void);

/*
 * destroy_pnm
 * 
 * Libère la mémoire allouée par *create_pnm
 * 
 * @param image un pointeur sur PNM
 * 
 * @pre: image != NULL
 * @post: *image libéré
 * 
 * @return:
 *    0 Succès
 *    NULL Erreur lors de l'allocation dynamique
 */

void destroy_pnm(PNM *image);

/*
 * get_...
 * 
 * accesseurs en lecture
 * 
 * @param image un pointeur sur PNM
 * 
 * @pre: image != NULL
 * @post: champ de la structure associé à la fonction
 * 
 * @return:
 *    0 Succès
 *    NULL Erreur lors de l'allocation dynamique
 */

int get_magicNumber(PNM *image);

int get_columns(PNM *image);

int get_rows(PNM *image);

int get_maxValuePixel(PNM *image);

int **get_matrix(PNM *image);

/*
 * set_...
 * 
 * accesseurs en écriture
 * 
 * @param image un pointeur sur PNM
 * @param ... champ de la structure associé à la fonction
 * 
 * @pre: image != NULL
 * @post: *image correctement retourné
 * 
 * @return:
 *    0 Succès
 *    NULL Erreur lors de l'allocation dynamique
 */

PNM *set_magicNumber(PNM *image, int magicNumber);

PNM *set_columns(PNM *image, int columns);

PNM *set_rows(PNM *image, int rows);

PNM *set_maxValuePixel(PNM *image, int maxValuePixel);

PNM *set_matrix(PNM *image, int **matrix);

/*
 * **create_matrix
 * 
 * Crée et alloue dynamiquement la matrice de *image
 * 
 * @param image un pointeur sur PNM
 * 
 * @pre: image != NULL
 * @post: matrice allouée
 * 
 * @return:
 *    0 Succès
 *    NULL Erreur lors de l'allocation dynamique
 */

int **create_matrix(PNM *image);

/*
 * fill_matrix
 * 
 * Lecture dans un fichier et remplissage de la matrice de *image
 * 
 * @param image un pointeur sur PNM
 * @param fp un pointeur sur FILE
 * 
 * @pre: image != NULL, fp != NULL
 * @post: matrice chargée
 * 
 * @return:
 *    0 Succès
 *    -3 Contenu du fichier en input mal formé
 */

int load_matrix(PNM *image, FILE *fp);

/*
 * write_matrix
 * 
 * Ecriture de la matrice de *image dans un fichier
 * 
 * @param image un pointeur sur PNM
 * @param fp un pointeur sur FILE
 * 
 * @pre: image != NULL, fp != NULL
 * @post: matrice 
 * 
 * @return:
 *    0 Succès
 *    -2 la matrice n'a pas pu être sauvée dans le fichier
 */

int write_matrix(PNM *image, FILE *fp);

/*
 * destroy_matrix_rows
 * 
 * Libère la mémoire allouée par **create_matrix
 * 
 * @param image un pointeur sur PNM
 * 
 * @pre: image != NULL
 * @post: la matrice ligne est libérée
 * 
 * @return:
 *    0 Succès
 *    NULL Erreur lors de l'allocation dynamique
 */

void destroy_matrix_rows(PNM *image);

/*
 * destroy_matrix_columns
 * 
 * Libère la mémoire allouée par **create_matrix
 * 
 * @param image un pointeur sur PNM
 * 
 * @pre: image != NULL
 * @post: la matrice colonne est libérée
 * 
 * @return:
 *    0 Succès
 *    NULL Erreur lors de l'allocation dynamique
 */

void destroy_matrix_columns(PNM *image);

/*
 * manage_comments
 * 
 * Permet de gérer une ligne pour savoir si on doit l'ignorer (celles commençant par '#')
 * 
 * @param fp un pointeur sur FILE *
 * 
 * @pre: fp != NULL
 * @post: la ligne est correctement ignorée
 * 
 * @return:
 *    0 Succès
 *    -1 Echec
 */

int manage_comments(FILE *fp);

//int verify_filename(PNM *image, char *filename);

#endif // __PNM__

