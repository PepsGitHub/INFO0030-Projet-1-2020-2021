/**
 * pnm.c
 * 
 * Ce fichier contient les définitions de types et 
 * les fonctions de manipulation d'images PNM.
 * 
 * @author: Dumoulin Peissone S193957
 * @date: 19/02/21
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <getopt.h>

#include "pnm.h"


/**
 * Définition du type opaque PNM
 *
 */
struct PNM_t {
   int magicNumber; /*Nombre qui caractérise le type de fichier
                      (1 pour pbm, 2 pour pgm, 3 pour ppm)*/
   int columns; //Nombre de pixels de hauteur
   int rows; //Nombre de pixels de largeur
   int maxValuePixel; //Valeur maximale que peut prendre un pixel
   int **matrix; //Matrice contenant la valeur de chaque pixel de l'image
};

//debut constructeur
PNM *create_pnm(){
   PNM *image = malloc(sizeof(PNM));
   if(!image)
      return NULL;

   return image;
}//fin constructeur

//debut destructeur

void destroy_pnm(PNM *image){
   assert(image != NULL);

   free(image);
}//fin destructeur

//debut accesseurs en lecture
int get_magicNumber(PNM *image){
   assert(image!=NULL);

   return image->magicNumber;
}

int get_columns(PNM *image){
   assert(image!=NULL);

   return image->columns;
}

int get_rows(PNM *image){
   assert(image!=NULL);

   return image->rows;
}

int get_maxValuePixel(PNM *image){
   assert(image!=NULL);

   return image->maxValuePixel;
}

int **get_matrix(PNM *image){
   assert(image!=NULL);

   return image->matrix;
}//fin accesseurs en lecture

//debut accesseurs en ecriture
PNM *set_magicNumber(PNM *image, int magicNumber){
   assert(image!=NULL);

   image->magicNumber = magicNumber;

   return image;
}

PNM *set_columns(PNM *image, int columns){
   assert(image!=NULL);

   image->columns = columns;

   return image;
}

PNM *set_rows(PNM *image, int rows){
   assert(image!=NULL);

   image->rows = rows;

   return image;
}

PNM *set_maxValuePixel(PNM *image, int maxValuePixel){
   assert(image!=NULL);

   image->maxValuePixel = maxValuePixel;

   return image;
}

PNM *set_matrix(PNM *image, int **matrix){
   assert(image!=NULL);

   image->matrix = matrix;

   return image;
}//fin accesseurs en ecriture

//debut create_matrix
int **create_matrix(PNM *image){
   assert(image != NULL);
   image->matrix = malloc(image->rows * sizeof(int*));
   if(!image->matrix){
      destroy_pnm(image);
      return NULL;
   }

   if(get_magicNumber(image) == 3){
      for(int i = 0;i < image->rows;i++){
         image->matrix[i] = malloc(image->columns * 3 * sizeof(int));

         if(!image->matrix[i]){
            destroy_matrix_rows(image);
            destroy_pnm(image);
            return NULL;
         }
      }
   }else{
      for(int i = 0;i < image->rows;i++){
         image->matrix[i] = malloc(image->columns * sizeof(int));

         if(!image->matrix[i]){
            destroy_matrix_rows(image);
            destroy_pnm(image);
            return NULL;
         }
      }
   }

   return image->matrix;
}//fin create_matrix

//debut load_matrix
int load_matrix(PNM *image, FILE *fp){
   assert(image != NULL && fp != NULL);

   switch(get_magicNumber(image)){
   case 1:
      for(int i = 0; i < get_rows(image); i++){
         for(int j = 0; j < get_columns(image); j++){
            manage_comments(fp);
            fscanf(fp,"%d ", &(image->matrix[i][j]));
         }
         fscanf(fp, "\n");
      }
      break;
   case 2:
      for(int i = 0; i < get_rows(image); i++){
         for(int j = 0; j < get_columns(image); j++){
            manage_comments(fp);
            fscanf(fp,"%d ", &(image->matrix[i][j]));
         }
         fscanf(fp, "\n");
      }
      break;
   case 3:
      for(int i = 0; i < get_rows(image); i++){
         for(int j = 0; j < 3 * get_columns(image); j++){
            manage_comments(fp);
            fscanf(fp,"%d ", &(image->matrix[i][j]));
         }
         fscanf(fp, "\n");
      }
      break;
   default:
      printf("Le contenu du fichier en input est mal formé (magicNumber)\n");
      destroy_all(image);
      return -3;
   }
   return 0;
}//fin load_matrix

//debut write_matrix
int write_matrix(PNM *image, FILE *fp){
   assert(image != NULL && fp != NULL);

   switch(get_magicNumber(image)){
   case 1 :
      for(int i=0;i<get_rows(image);i++){
         for(int j=0;j<get_columns(image);j++){
            fprintf(fp,"%d ", image->matrix[i][j]);
         }
         fprintf(fp,"\n");
      }
      break;
   case 2 :
      fprintf(fp, "%d\n", get_maxValuePixel(image));
      for(int i=0;i<get_rows(image);i++){
         for(int j=0;j<get_columns(image);j++){
            fprintf(fp,"%d ", image->matrix[i][j]);
         }
         fprintf(fp,"\n");
      }
      break;
   case 3 :
      fprintf(fp, "%d\n", get_maxValuePixel(image));
      for(int i=0;i<get_rows(image);i++){
         for(int j=0;j<3*get_columns(image);j++){
            fprintf(fp,"%d ", image->matrix[i][j]);
         }
         fprintf(fp,"\n");
      }
      break;
   default :
      printf("L'image n'a pas pu être sauvée dans un fichier (magicNumber)");
      destroy_all(image);
      return -2;
   }
   return 0;
}//fin write_matrix

//debut destroy_matrix
void destroy_matrix_rows(PNM *image){
   assert(image != NULL);

   free(image->matrix);
}//fin destroy_matrix

//debut destroy_matrix_i
void destroy_matrix_columns(PNM *image){
   assert(image != NULL);

   for(int i = 0;i < image->rows;i++)
      free(image->matrix[i]);
}//fin destroy_matrix_i

void destroy_all(PNM *image){
   assert(image != NULL);

   destroy_matrix_columns(image);
   destroy_matrix_rows(image);
   destroy_pnm(image);
}

//debut short_options
int short_options(int argc, char **argv, char **format, 
                  char **input, char **output){
   assert(argv != NULL);

   char *optstring = ":f:i:o:";
   int val;
   while((val=getopt(argc, argv, optstring))!=EOF){
      switch (val){
      case 'f':
         *format = optarg;
         printf("format: %s\n", *format);
         break;
      case 'i':
         *input = optarg;
         printf("input: %s\n", *input);
         break;
      case 'o':
         *output = optarg;
         printf("output: %s\n", *output);
         break;
      case '?':
         printf("option inconnue: %c\n", optopt);
         return -1;
      case ':':
         printf("argument manquant: %c\n", optopt);
         return -2;
      }
   }

   return 0;
}
//fin short_options

//debut manage_format_input
int manage_format_input(PNM *image, char *format, char *input){
   assert(image != NULL && format != NULL && input != NULL);

   switch (get_magicNumber(image)){
   case 1:
      if(strcmp(format, "PBM") != 0){
         printf("Mauvais format passé en argument. ");
         printf("Le fichier %s est du type PBM et non %s\n", input, format);
         destroy_all(image);
         return -1;
      }
      break;
   case 2:
      if(strcmp(format, "PGM") != 0){
         printf("Mauvais format passé en argument. ");
         printf("Le fichier %s est du type PGM et non %s\n", input, format);
         destroy_all(image);
         return -1;
      }
      break;
   case 3:
      if(strcmp(format, "PPM") != 0){
         printf("Mauvais format passé en argument. ");
         printf("Le fichier %s est du type PPM et non %s\n", input, format);
         destroy_all(image);
         return -1;
      }
      break;
   default:
      printf("Incapable de lire ce type de format: %s\n", format);
      return -1;
      break;
   }
   return 0;
}
//fin manage_format_input

//debut verify_filename_output
int verify_output(PNM *image, char *output){
   assert(image != NULL && output != NULL);

   char *invalidCharacter = "/\\:*?\"<>|";

   for(int i=0; output[i] != '\0';i++){
      for(int j=0; invalidCharacter[j] != '\0'; j++){
         if(output[i]==invalidCharacter[j]){
            printf("Caractère invalide dans le nom du fichier: '%c'\n",
                   output[i]);
            destroy_all(image);
            return -1;
         }
      }
   }
   return 0;
}//fin verify_filename

//debut manage_comments
int manage_comments(FILE *fp){
   assert(fp != NULL);

   int character = 0;

   while((character = fgetc(fp)) != EOF && (character == '#')){
      if(character == '#')
         fscanf(fp, "%*[^\n] ");
   }

   if(character == EOF)
      return -1;
   
   ungetc(character, fp);
   return 0;
}//fin manage_comments

char magicNumber[2];

//debut load_pnm
int load_pnm(PNM **image, char* filename){

   assert(image != NULL && filename != NULL);
   
   FILE *fp = fopen(filename, "r");
   if(!fp)
      return -2;

   int columns = 0, rows = 0, maxValuePixel = 0;

   manage_comments(fp);
   
   fscanf(fp, "%s\n", magicNumber);

   if(strcmp(magicNumber, "P1") == 0){
      set_magicNumber(*image, 1);
      manage_comments(fp);
   }else if(strcmp(magicNumber, "P2") == 0){
      set_magicNumber(*image, 2);
      manage_comments(fp);
   }else if(strcmp(magicNumber, "P3") == 0){
      set_magicNumber(*image, 3);
      manage_comments(fp);
   }else{
      destroy_pnm(*image);
      fclose(fp);
      return -3;
   }

   fscanf(fp, "%d %d\n", &columns, &rows);

   if(columns < 1 || rows < 1 || columns > 5000 || rows > 5000){
      fclose(fp);
      return -1;
   }

   if(columns )

   set_columns(*image, columns);
   set_rows(*image, rows);

   manage_comments(fp);
   
   switch(get_magicNumber(*image)){
   case 1 :
      set_maxValuePixel(*image, 1);
      create_matrix(*image);
      load_matrix(*image, fp);
      break;
   case 2 :
      fscanf(fp,"%d\n", &maxValuePixel);
      set_maxValuePixel(*image, maxValuePixel);
      create_matrix(*image);
      load_matrix(*image, fp);
      break;
   case 3 :
      fscanf(fp,"%d\n", &maxValuePixel);
      set_maxValuePixel(*image, maxValuePixel);
      create_matrix(*image);
      load_matrix(*image, fp);
      break;
   default :
      printf("ce type de fichier n'existe pas");
      fclose(fp);
      return -3;
   }
   manage_comments(fp);
   fclose(fp);
   return 0;
}//fin load_pnm

//debut write_pnm
int write_pnm(PNM *image, char* filename) {
   assert(image != NULL && filename != NULL);

   FILE *fp = fopen(filename, "w");
   if(!fp)
      return -1;

   fprintf(fp,"%s\n%d %d\n", magicNumber, get_columns(image), get_rows(image));

   write_matrix(image, fp);

   fclose(fp);
   return 0;
}//fin write_pnm