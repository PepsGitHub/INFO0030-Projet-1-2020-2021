#define P1 1
#define P2 2
#define P3 3

int magicNumber;
switch(magicNumber){
   case 1 :
      cree_PBM();
      break;
   case 2 :
      cree_PGM();
      break;
   case 3 :
      cree_PPM();
      break;
   default :
   printf("ce type de fichier n'existe pas");
      break;
}