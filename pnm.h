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
 * Include guard (pour éviter les problèmes d'inclusions multiples
 * Bonne pratique: toujours encadrer un header avec un include guard
 */
#ifndef __PNM__
#define __PNM__

/**
 * \file pnm.h
 * \brief Librairie pour gérer les fichiers d'extension pnm (.pbm, .pgm, .ppm)
 * \author Peissone Dumoulin - Université de Liège
 * \version 1.0
 * \date 22/02/2021
 * 
 * Déclaration du type opaque PNM
 *
 */
typedef struct PNM_t PNM;

/**
 * \fn int load_pnm(PNM **image, char* filename)
 * \brief Charge une image PNM depuis un fichier
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
 * \fn int write_pnm(PNM *image, char* filename)
 * \brief Sauvegarde une image PNM dans un fichier.
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

/**
 * \fn PNM *create_pnm(void)
 * \brief Crée et alloue dynamiquement une variable de type opaque PNM*
 * 
 * @param magicNumber l'entier représentant la chaîne de caractère initiale 
 *        (1 pour "P1", 2 pour "P2" et 3 pour "P3")
 * @param columns le nombre de pixels de hauteur
 * @param rows le nombre de pixels de largeur
 * @param maxValuePixel la valeur maximale que peut prendre un pixel
 * 
 * @pre: /
 * @post: *image alloué
 * 
 * @return:
 *    image Succès
 *    NULL Erreur lors de l'allocation dynamique
 */
PNM *create_pnm(void);

/**
 * \fn void destroy_pnm(PNM *image)
 * \brief Libère la mémoire allouée par *create_pnm
 * @param image un pointeur sur PNM
 * 
 * @pre: image != NULL
 * @post: *image libéré
 * 
 * @return:
 *    /
 */

void destroy_pnm(PNM *image);

/**
 * \fn int get_magicNumber(PNM *image)
 * \brief Accesseur en lecture pour le champ magicNumber de image*
 * 
 * @param image un pointeur sur PNM
 * 
 * @pre: image != NULL
 * @post: accès en lecture au champ magicNumber de *image
 * 
 * @return:
 *    image->magicNumber Succès
 */

int get_magicNumber(PNM *image);

/**
 * \fn int get_columns(PNM *image)
 * \brief Accesseur en lecture pour le champ columns de image*
 * 
 * @param image un pointeur sur PNM
 * 
 * @pre: image != NULL
 * @post: accès en lecture au champ columns de *image
 * 
 * @return:
 *    image->columns Succès
 */

int get_columns(PNM *image);

/**
 * \fn int get_rows(PNM *image)
 * \brief Accesseur en lecture pour le champ rows de image*
 * 
 * @param image un pointeur sur PNM
 * 
 * @pre: image != NULL
 * @post: accès en lecture au champ rows de *image
 * 
 * @return:
 *    image->rows Succès
 */

int get_rows(PNM *image);

/**
 * \fn int get_maxValuePixel(PNM *image)
 * \brief Accesseur en lecture pour le champ maxValuePixel de image*
 * 
 * @param image un pointeur sur PNM
 * 
 * @pre: image != NULL
 * @post: accès en lecture au champ maxValuePixel de *image
 * 
 * @return:
 *    image->getMaxValuePixel Succès
 */

int get_maxValuePixel(PNM *image);

/**
 * \fn int **get_matrix(PNM *image)
 * \brief Accesseur en lecture pour le champ matrix de image*
 * 
 * @param image un pointeur sur PNM
 * 
 * @pre: image != NULL
 * @post: accès en lecture au champ matrix de *image
 * 
 * @return:
 *    image->matrix Succès
 */

int **get_matrix(PNM *image);

/**
 * \fn PNM *set_magicNumber(PNM *image, int magicNumber)
 * \brief Accesseur en écriture pour le champ magicNumber de *image
 * 
 * @param image un pointeur sur PNM
 * @param magicNumber nombre qui caractérise le type de fichier
                      (1 pour pbm, 2 pour pgm, 3 pour ppm)
 * 
 * @pre: image != NULL
 * @post: accès en écriture au champ magicNumber de *image
 * 
 * @return:
 *    image Succès
 */

PNM *set_magicNumber(PNM *image, int magicNumber);

/**
 * \fn PNM *set_columns(PNM *image, int columns)
 * \brief Accesseur en écriture pour le champ columns de *image
 * 
 * @param image un pointeur sur PNM
 * @param columns nombre de pixels de hauteur
 * 
 * @pre: image != NULL
 * @post: accès en écriture au champ columns de *image
 * 
 * @return:
 *    image Succès
 */

PNM *set_columns(PNM *image, int columns);

/**
 * \fn PNM *set_rows(PNM *image, int rows)
 * \brief Accesseur en écriture pour le champ rows de *image
 * 
 * @param image un pointeur sur PNM
 * @param rows nombre de pixels de largeur
 * 
 * @pre: image != NULL
 * @post: accès en écriture au champ rows de *image
 * 
 * @return:
 *    image Succès
 */

PNM *set_rows(PNM *image, int rows);

/**
 * \fn PNM *set_maxValuePixel(PNM *image, int maxValuePixel)
 * \brief Accesseur en écriture pour le champ maxValuePixel de *image
 * 
 * @param image un pointeur sur PNM
 * @param maxValuePixel valeur maximale que peut prendre un pixel
 * 
 * @pre: image != NULL
 * @post: accès en écriture au champ maxValuePixel de *image
 * 
 * @return:
 *    image Succès
 */

PNM *set_maxValuePixel(PNM *image, int maxValuePixel);

/**
 * \fn PNM *set_matrix(PNM *image, int **matrix)
 * \brief Accesseur en écriture pour le champ matrix de *image
 * 
 * @param image un pointeur sur PNM
 * @param matrix matrice contenant la valeur de chaque pixel de l'image
 * 
 * @pre: image != NULL
 * @post: accès en écriture au champ matrix de *image
 * 
 * @return:
 *    image Succès
 */

PNM *set_matrix(PNM *image, int **matrix);

/**
 * \fn int **create_matrix(PNM *image)
 * \brief Crée et alloue dynamiquement la matrice de *image
 * 
 * @param image un pointeur sur PNM
 * 
 * @pre: image != NULL
 * @post: matrice allouée
 * 
 * @return:
 *    image->matrix Succès
 *    NULL Erreur lors de l'allocation dynamique
 */

int **create_matrix(PNM *image);

/**
 * \fn int load_matrix(PNM *image, FILE *fp)
 * \brief Lecture dans un fichier et remplissage de la matrice de *image
 * 
 * @param image un pointeur sur PNM
 * @param fp un pointeur sur FILE
 * 
 * @pre: image != NULL, fp != NULL
 * @post: matrice chargée
 * 
 * @return:
 *    0 Succès
 *    -3 Le contenu du fichier en input est mal formé (magicNumber)
 */

int load_matrix(PNM *image, FILE *fp);

/**
 * \fn int write_matrix(PNM *image, FILE *fp)
 * \brief Ecriture de la matrice de *image dans un fichier
 * 
 * @param image un pointeur sur PNM
 * @param fp un pointeur sur FILE
 * 
 * @pre: image != NULL, fp != NULL
 * @post: matrice 
 * 
 * @return:
 *    0 Succès
 *    -2 La matrice n'a pas pu être écrite dans le fichier
 */

int write_matrix(PNM *image, FILE *fp);

/**
 * \fn void destroy_matrix_rows(PNM *image)
 * \brief Libère la mémoire allouée par **create_matrix
 * 
 * @param image un pointeur sur PNM
 * 
 * @pre: image != NULL
 * @post: la matrice ligne est libérée
 * 
 * @return:
 *    /
 */

void destroy_matrix_rows(PNM *image);

/**
 * \fn void destroy_matrix_columns(PNM *image)
 * \brief Libère la mémoire allouée par **create_matrix
 * 
 * @param image un pointeur sur PNM
 * 
 * @pre: image != NULL
 * @post: la matrice colonne est libérée
 * 
 * @return:
 *    /
 */

void destroy_matrix_columns(PNM *image);

/**
 * \fn int manage_comments(FILE *fp)
 * \brief Permet de gérer une ligne pour savoir si on doit l'ignorer 
 *        (celles commençant par '#')
 * @param fp un pointeur sur FILE
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

