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

   char *optstring = ":f:i:o:";
   int val;
   char *format, *input, *output;
   PNM *imageTest = create_pnm();

   //options courtes
   while((val=getopt(argc, argv, optstring))!=EOF){
      switch (val){
      case 'f':
         format = optarg;
         printf("format: %s\n", format);
         break;
      case 'i':
         input = optarg;
         printf("input: %s\n", input);
         break;
      case 'o':
         output = optarg;
         printf("output: %s\n", output);
         break;
      case '?':
         printf("unknown option: %c\n", optopt);
         return -1;
      case ':':
         printf("missing arg: %c\n", optopt);
         return -1;
      }
   }

   //erreur en cas de format inconnu
   while(strcmp(format, "PBM") != 0 && strcmp(format, "PGM") != 0 && strcmp(format, "PPM") != 0){
      printf("Incapable de lire ce type de format: %s. Veuillez réessayer:\n", format);
      scanf("%s", format);
   }
   
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
   switch (get_magicNumber(imageTest)){
   case 1:
      if(strcmp(format, "PBM") != 0){
         printf("Mauvais format passé en argument. Le fichier %s est du type PBM et non %s\n", input, format);
         destroy_matrix_columns(imageTest);
         destroy_matrix_rows(imageTest);
         destroy_pnm(imageTest);
         return -1;
      }
      break;
   case 2:
      if(strcmp(format, "PGM") != 0){
         printf("Mauvais format passé en argument. Le fichier %s est du type PGM et non %s\n", input, format);
         destroy_matrix_columns(imageTest);
         destroy_matrix_rows(imageTest);
         destroy_pnm(imageTest);
         return -1;
      }
      break;
   case 3:
      if(strcmp(format, "PPM") != 0){
         printf("Mauvais format passé en argument. Le fichier %s est du type PPM et non %s\n", input, format);
         destroy_matrix_columns(imageTest);
         destroy_matrix_rows(imageTest);
         destroy_pnm(imageTest);
         return -1;
      }
      break;
   }

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

