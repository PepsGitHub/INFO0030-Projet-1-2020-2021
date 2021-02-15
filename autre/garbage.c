/*
//Pas sûr

//debut constructeur
PNM *create_pnm(int magicNumber, int columns,
                int rows, int **matrix){
   PNM *image = malloc(sizeof(PNM));
   if(!image)
      return -1;

   image->magicNumber = magicNumber;
   image->columns = columns;
   image->rows = rows;
   image->matrix = matrix;

   return image;
}//fin constructeur

//debut destructeur

void destroy_pnm(PNM *image){
   assert(image!=NULL);

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

PNM *set_matrix(PNM *image, char* pnmType){
   assert(image!=NULL);

   image->matrix = matrix;

   return image;
}//fin accesseurs en ecriture

fin pas sûr
*/