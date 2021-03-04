/**
 * main.c
 * 
 * Ce fichier contient la fonction main() du programme de manipulation
 * de fichiers pnm.
 *
 * @author: Dumoulin Peissone S193957
 * @date: 19/02/21
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
   PNM *image;

   char *optstring = ":f:i:o:";
   int val;
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
         printf("option inconnue: %c\n", optopt);
         return -1;
      case ':':
         printf("argument manquant: %c\n", optopt);
         return -2;
      }
   }
   
   //appel de load_pnm et checking des valeurs de retour
   switch(load_pnm(&image, input)){
      case 0:
         printf("Tout s'est bien passé et l'image est ");
         printf("correctement chargée en mémoire dans *image\n");
         break;
      case -1:
         printf("Il est impossible d'allouer suffisamment ");
         printf("de mémoire pour l'image\n");
         return 0;
      case -2:
         printf("Le nom du fichier en input est mal formé\n");
         destroy(image, 3);
         return 0;
      case -3:
         printf("Le contenu du fichier en input est mal formé\n");
         return 0;
      default:
         printf("Valeur de retour inconnue\n");
         return 0;
   }

   //permet de gérer les erreurs entre le format du fichier et le format
   if(manage_format_input(image, format, input))
      return -1;
   //permet de gérer les caractères interdits dans l'output
   if(verify_output(image, output))
      return -1;

   //appel de write_pnm et checking des valeurs de retour
   switch(write_pnm(image, output)){
      case 0:
         printf("Tout s'est bien passé et l'image a pu être correctement ");
         printf("sauvée dans un fichier\n");
         break;
      case -1:
         printf("Le nom du fichier output passé en argument ");
         printf("n'est pas valide\n");
         return 0;
      case -2:
         printf("L'image n'a pas pu être sauvée dans un fichier\n");
         return 0;
      default:
         printf("Valeur de retour inconnue\n");
         return 0;
   }

   //libération de la mémoire
   
   destroy(image, 3);
   
   return 0;
}

