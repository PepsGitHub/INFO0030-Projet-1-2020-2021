/**
 * main.c
 * 
 * Ce fichier contient la fonction main() du programme de manipulation
 * de fichiers pnm.
 *
 * @author: Dumoulin Peissone S193957
 * @date: 22/02/21
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <string.h>

#include "pnm.h"


int main(int argc, char *argv[]) {

   char *format = NULL, *input = NULL, *output = NULL;
   PNM *imageTest = create_pnm();

   //appel de short_options pour la gestion des arguments lors de l'exécution du programme
   short_options(argc, argv, &format, &input, &output);
   
   //appel de load_pnm et checking des valeurs de retour
   switch(load_pnm(&imageTest, input)){
      case 0:
         printf("Tout s'est bien passé et l'image est correctement chargée en mémoire dans *image\n");
         break;
      case -1:
         printf("Il est impossible d'allouer suffisamment de mémoire pour l'image\n");
         return 0;
      case -2:
         printf("Le nom du fichier en input est mal formé\n");
         destroy_pnm(imageTest);
         return 0;
      case -3:
         printf("Le contenu du fichier en input est mal formé\n");
         return 0;
      default:
         printf("Valeur de retour inconnue\n");
         return 0;
   }

   //permet de gérer les erreurs entre le format du fichier et le format tous deux passés en argument
   if(manage_format_input(imageTest, format, input) == -1)
      return -1;

   if(verify_filename_output(imageTest, output) == -1)
      return -1;

   //appel de write_pnm et checking des valeurs de retour
   switch(write_pnm(imageTest, output)){
      case 0:
         printf("Tout s'est bien passé et l'image a pu être correctement sauvée dans un fichier\n");
         break;
      case -1:
         printf("Le nom du fichier output passé en argument n'est pas valide\n");
         return 0;
      case -2:
         printf("L'image n'a pas pu être sauvée dans un fichier\n");
         return 0;
      default:
         printf("Valeur de retour inconnue\n");
         return 0;
   }

   //libération de la mémoire
   destroy_matrix_columns(imageTest);
   destroy_matrix_rows(imageTest);
   destroy_pnm(imageTest);
   
   return 0;
}

