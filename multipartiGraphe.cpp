

#include <iostream>
#include <fstream>
#include <iostream>
#include <vector>
/*********************************************************
Ici , nous definissons la structure d'un multiparti
un multiparti est un graphe constitue de plusieurs famille
et les familles sont aussi constitue de plusieurs ensembles
formes de plussieurs elements.Dans cette structure on est
considere comme etant un ensemble uniquement dans la
classe a laquelle on appartient et dans les familles superieures
les ensembles sont simplement des elements representes de facon
uniquement par un couple d'indice (la famille d'origine ) et
le rang qui est sa position dans la famille.

**********************************************************/


using namespace std;
#define MAX_VERTICES 1000



//____________________________
class ELEMENT {
public:
  int rang;                                                                  // sa postion dans une famille
  int indice;
  };                                                                       // le numero d'orde de la famille exp V5 rang =2 et indice 5

//____________________________



class ENSEMBLE {
public:

  vector< ELEMENT>ens;                                                  // le sous ensemble associe;

};
//____________________________


class FAMILLE:ENSEMBLE {
public:
  int size;
  vector< ENSEMBLE > fam;                                        // les ensembles auxquels sont associes une famille


};
//___________________________
class MULTIPARTI:FAMILLE{
  public:

    int size;
    vector < FAMILLE> multi;

};
//___________________________
class BIPARTI {
    public:
    int clique;                                         // permet de donner le nombre de clique
    vector < vector < int> >bipart;
};

   BIPARTI    MathGraphe;
   MULTIPARTI MonGraphe;

  ENSEMBLE A,B, C , SousEns;



int COINCIDE(int p,ENSEMBLE A, ENSEMBLE B) {
  /******************************************************************
   Cette fonction permet de verifier si l'element de position p dans
   A est aussi dans B
  ******************************************************************/
  int j;
  for (j = 0; j <(int) B.ens.size(); j++){
    if (A.ens[p].rang == B.ens[j].rang && A.ens[p].indice==B.ens[j].indice)
      return 1;
  };

  if(j==(int)B.ens.size()) return 0;
  return 0;
}

int INTERSECT(ENSEMBLE A, ENSEMBLE B, ENSEMBLE &C ) {

  /****************************************************************
   Apres avoir parcourir tout l'ensemble A element par element
   en utilisant la fonction concide , on recopie dans C les elements d
    de A qui sont a la fois  dans A et dans B
 **********************************************************************/
ELEMENT ele;
 // ele.indice= new(int);
  //ele.rang= new(int);
   if ( A.ens.size()> B.ens.size() )
          { for ( int i=0 ; i< (int)B.ens.size() ; i++)
                   {
                       if (COINCIDE (i,B,A)) {
                                    ele.rang=B.ens[i].rang;
                                    ele.indice=B.ens[i].indice;
                                    C.ens.push_back(ele);
                                   };
             };
          }
         else
            for ( int j=0; j< (int)A.ens.size();j++){
                       if (COINCIDE(j,A,B)){

                                    ele.rang=A.ens[j].rang;
                                    ele.indice=A.ens[j].indice;
                                    C.ens.push_back(ele);
                                   };
            };

 if ( C.ens.size()==0) return 0;
 else return 1;

}

/******************************************************************
 donne les elements de B qui ne sont pas dans A return 0 si la diff
 est vide et 1 si non
*******************************************************************/


int DIFFSYM(ENSEMBLE A, ENSEMBLE B, ENSEMBLE &C){
      ELEMENT ele;
//      ele.indice= new(int);
  //    ele.rang= new(int);
           for ( int i=0 ; i< (int)B.ens.size() ; i++)
                   {
                       if (!(COINCIDE (i,B,A))) {
                                    ele.rang=B.ens[i].rang;
                                    ele.indice=B.ens[i].indice;
                                    C.ens.push_back(ele);
                                   };
             };
if ( C.ens.size()==0) return 0;
return 1;
}

/********************************************************************
 cette fonction est tres importante dans ce code car elle permet de
faire la copie d'un ensemble vers un autre, sans detruire le contenu
anterieure de l'ensemble receptrice
*********************************************************************/

void COPY(ENSEMBLE &A , ENSEMBLE B) {
   //  int p=(int) A.ens.size();
     ELEMENT ele;
   //  ele.indice= new(int);
   //  ele.rang= new(int);

     for ( int i=0 ; i< (int)B.ens.size();i++){

         ele.indice=B.ens[i].indice;
         ele.rang=B.ens[i].rang;
         A.ens.push_back( ele);

     };
     return;
}
/***********************************************************************
Cette fonction realise egalement une copie , mais elle detruire le contenu
anterieur de la fonction receptrice
************************************************************************/


void COPYFORCER(ENSEMBLE &A , ENSEMBLE B) {
   //  int p=(int) A.ens.size();
     ELEMENT ele;
   //  ele.indice= new(int);
   //  ele.rang= new(int);

     for ( int i=0 ; i< (int)B.ens.size();i++){
          if (i <(int) A.ens.size()) {
                 A.ens[i].indice=B.ens[i].indice;
                 A.ens[i].rang=B.ens[i].rang;
                 A.ens.push_back( ele);
          }else{
         ele.indice=B.ens[i].indice;
         ele.rang=B.ens[i].rang;
         A.ens.push_back( ele);
          }
     };
     return;
}

/*******************************************************************
Elle teste si un ensemble A est dans  B et renvoie vrai si oui
et non pour le cas contraire ainsi est une inclusion au sens large
********************************************************************/


bool INCLUSION(ENSEMBLE A, ENSEMBLE B){

    ENSEMBLE RES;
    INTERSECT ( A ,B ,RES);
    if ( RES.ens.size()==A.ens.size() ) return true;
    else return false;

}
/******************************************************************
Elle teste si un ensemble A est dans  B et renvoie vrai si oui
et non pour le cas contraire ainsi est une inclusion au sens strict
********************************************************************/


bool INCLUSION_S(ENSEMBLE A, ENSEMBLE B){

    ENSEMBLE RES,C;
    INTERSECT ( A ,B ,RES);
    DIFFSYM(B,A,C);
    if ( RES.ens.size()==A.ens.size() && (int)C.ens.size()>0 ) return true;
    else return false;

}

/**************************************************************************
Elle permet de realiser la reunion de deux ensembles et met le resultat
des 2 ensemble dans RES
**************************************************************************/

void REUNION (ENSEMBLE A , ENSEMBLE B , ENSEMBLE &RES){
    ENSEMBLE INT,DIFF;

    if (INCLUSION(A,B)) {COPY(RES,B); return;};
    if (INCLUSION(B,A)) {COPY(RES,A); return;};
    if (INTERSECT(A,B,INT)==1){
                         COPY(RES,A);
                       if (DIFFSYM(INT,B,DIFF)==1)  COPY(RES,DIFF);
                      //   COPY(RES,DIFF);

    }else {
            COPY ( RES,A);
            COPY ( RES,B);
    };
    return;
}
/***************************************************************************
Ces deux fonctions permettent de liberer respectivement les espaces occupes
par un ensemble et par une famille
***************************************************************************/

 void LIBERER( ENSEMBLE &Q){
   Q.ens.clear();
  }
  void LIBERERF( FAMILLE & F){
      for ( int i=0 ; i < F.size ; i++){
          LIBERER( F.fam[i]);
      }
   F.size=0;
  }
/***************************************************************************************
Permet de verifier s'il existe un ensemble dans la famille F qui est plus petit que
A dans le sens d'inclusion et si c 'est le cas on retourne la position de cette element
dans la variable pos.
Ceci va pemettre de retirer et liberer l'espace pour inserer la nouveau ensemble
***************************************************************************************/
int MAXENS( int &pos, ENSEMBLE A, FAMILLE F_sup){

      int i;
      int p=(int) F_sup.size;
      if (p==0) return 0;
      for ( i=0 ; i<p ; i++) {
         //pos++;
             if (INCLUSION(F_sup.fam[i],A)) return 1;
             if (INCLUSION(A ,F_sup.fam[i])) return 2;
               //if (INCLUSION(A,F_sup.fam[i])) return 1;
             //  if (INCLUSION(F_sup.fam[i],A)) return 2;
             pos++;                                // on a trouve un element plus petit que A
      };
      if( p==i){ pos++;
                return 0;
      }
      return 2;
  }
/**********************************************************************************
permet de verifier si deux ensembles sont egaux et retourne 1 si c'est vrai
et 0 au cas contraire
**********************************************************************************/
int
  EGALITE( ENSEMBLE A , ENSEMBLE B){
      if ( A.ens.size() != B.ens.size()) return 0;
      if (INCLUSION ( A,B) && INCLUSION(B,A)) return 1;
      else return 0;
  };


/**********************************************************************************
Effectue les memes operations que Maxens , mais dans ce cas , on doit verifier que
l'inclusion entre les deux ensemble est au sens stricte , A est inclu dans B et
A n'est pas egal a B

**********************************************************************************/

  int MAXENS_S( int &pos, ENSEMBLE A, FAMILLE F_sup){ // pos est la position ou on devra inserer A s'il est grand en inclusion
                                                    // que les autres contenus dans Famille
      int i;
      int p=(int) F_sup.size;
      if (p==0) return 0;
      for ( i=0 ; i<p ; i++) {
        // pos++;
            // if (INCLUSION_S(F_sup.fam[i],A)) return 1;
           //  if (INCLUSION_S(A ,F_sup.fam[i])) return 2;
             if (INCLUSION_S(A,F_sup.fam[i])) return 1;
             if (INCLUSION_S(F_sup.fam[i],A)) return 2;
              pos++;                                // on a trouve un element plus petit que A
      };
      if( p==i){ pos++;
                return 0;
      }
      return 2;
  }
/************************************************************************************
Renvoie l'etape d'execution du multiparti
*************************************************************************************/


 int Etape1 ( MULTIPARTI M){

    int a=M.size;
    return a;
}
/**********************************************************************************
Teste si l'intersection de l'ensemble de et de la famille aumoins deux elements
et renvoie la valeur de la premiere grandeur de l'intersection qui est superieure
ou egale a deux
***********************************************************************************/
  int TEST1 ( ENSEMBLE A , FAMILLE F) {    //  permet de voir si l'intersection de l'ensemble et la famille a aumoins deux elements de F
      ENSEMBLE B,C;

      int taille=0;
     // COPY(A,F.fam[0]);

      for ( int i=0 ;i< (int)  F.size; i++) {
              LIBERER(B);
              COPY(B,F.fam[i]);
              if (INTERSECT(A,B,C)==1){
                                             taille=taille + C.ens.size();
                                             LIBERER(C);
                                             if ( taille >=3){  LIBERER(B);
                                                               return taille;
                                             }

                                           };
      };
      LIBERER(A);
      LIBERER(C);
      LIBERER(B);
    return taille;
}
/***********************************************************************************
donne l'ensemble resultante de l'intersection d'un ensemble et d'une famille dans l'en
semble RES
*************************************************************************************/

int INTERSECTF_E( ENSEMBLE A , FAMILLE F , ENSEMBLE &RES){  // donne l'intersection d'un ensemble de une famille
  ENSEMBLE D;
  ENSEMBLE C;

if (F.size==0) return 0;

INTERSECT ( A , F.fam[0], RES);
for ( int i=1 ; i < F.size ; i++){
     //  REUNION( RES, B);
       COPY(D,RES);
       LIBERER(RES);
       LIBERER(B);
       INTERSECT( A , F.fam[i], B);
       REUNION( B, D,RES);
       LIBERER(D);
}

if (RES.ens.size()==0 ) return 0;
else return 1;
return 1;
}

/**************************************************************************************
Cette fonction genere tous les sous ensembles d'une famille inferieure en testant a
chaque fois si l'ensmble formes des combinaison est un bon candidat
1- verifie le critere de non trivialite
2-verifie le cas ou l'etape d'exection est d'ordre superieure
3-verifie a la sortie si le resultat de l'intersection avec la famille de rang -2 a une
cardinalite superieure ou egale a 1
***************************************************************************************/
 int TEST2( ENSEMBLE A , ENSEMBLE B , MULTIPARTI M,int p) {
     int cont=0;
     ENSEMBLE RES1, RES2;
    for ( int i =0 ; i < p ; i++) {
         if (i!=1) {
              if( ( INTERSECTF_E ( A , M.multi[i],RES1)==1) && ( INTERSECTF_E ( A , M.multi[i],RES2)==1) ){
                       if ( EGALITE ( RES2, RES1) ) cont++;
                       else return 0;
                       LIBERER ( RES1);
                       LIBERER (RES2);
              } else return 0;
         }
    }
    if ( cont == p) return 1;
    LIBERER (RES1);
    LIBERER (RES2);
    return 0;
 }

int  PARTITION(int p,ENSEMBLE &RES, FAMILLE F , int pivot ,int taille ,int depl, MULTIPARTI M){
     // je construires les elements de la famille superieure
    // partant d'une famille inferieure F et p est le numero de famille anterieure
    ELEMENT ele;
   // ele.indice= new(int);
  //  ele.rang= new(int);
    ENSEMBLE sousEns,sousEns1,RES1;
    ENSEMBLE U,B,A,C,_A,_B,_C;
         LIBERER(A);
         LIBERER(B);
        COPY(A, F.fam[pivot]);
          ele.indice=p;
          ele.rang=pivot;
          _A.ens.push_back(ele);
          RES.ens.push_back(ele);                          // j'insere l'indice du premier candidat
 if ( p<4){                                               // teste si l'ordre d'execution est inferieure a 1
    for (int i = pivot+1 ; i < pivot+taille; i++){
           LIBERER(B);
           COPY( B,F.fam[i]);
            ele.indice=p;
            ele.rang=i;
 if (INTERSECT( A,B,sousEns)==1){ RES.ens.push_back( ele);// j'insere l'indice du nouveau candidat car l'intersection est non vide avec le
                                                         // le precedent et je garde le resultat de l'intersection dans une variable
                                                        // qui permettrait de choisir les prochains meilleurs candidats
                                             LIBERER(A);
                                             COPY(A,sousEns);
                                             LIBERER(sousEns);
                                }
           else { LIBERER(RES);

                  return 0;
                 };
}

 if (INTERSECT( A,F.fam[depl],sousEns)==1){ if (sousEns.ens.size()<2) return 0;// je traite le dernier ensemble

                                                         ele.indice=p;
                                                         ele.rang=depl;
                                                         RES.ens.push_back(ele);
                                                         COPY(RES,sousEns);
                                                         LIBERER(sousEns);
                                              }
                else { LIBERER(RES);
                       return 0;
                     }


      }

//__________________Le dernier critere a ajouter______________________________________________________
else {
//if(p==4)
 //       { if (INTERSECTF_E(A, M.multi[p-4], RES1) ==0) return 0;} // traitement special de 4 pour controler le cas de 1
//if (p>4)
  //      { if ( INTERSECTF_E(A, M.multi[p-3], RES1)==0) return 0;}

 for (int i = pivot+1 ; i < pivot+taille; i++){
          LIBERER(B);
           COPY( B,F.fam[i]);
     //     if(p==4)
      //  { if (INTERSECTF_E(B, M.multi[p-4], sousEns) ==0) return 0;}

    //     if (p>4)
      //   { if ( INTERSECTF_E(B, M.multi[p-3],sousEns) ==0) return 0;}

            ele.indice=p;
            ele.rang=i;
          if (TEST2(A , B , M , p-3 )==1){  if(INTERSECT( A,B,sousEns1)==1){
                                                                             RES.ens.push_back( ele);

                                                                              LIBERER(A);

                                                                              COPY(A,sousEns1);

                                                                              LIBERER(B);

                                                                              LIBERER(sousEns1);
                                                                           }
                                       }
           else { LIBERER(RES);

                  return 0;
                };

                //if ( INTERSECTF_E( RES,M.multi[p-2], sousEns)

    };

   //if(p==4)
 //{ if (INTERSECTF_E(F.fam[depl], M.multi[p-4], sousEns) ==0) return 0;}

   // if (p>4)
  //{ if ( INTERSECTF_E(F.fam[depl], M.multi[p-3],sousEns) ==0) return 0;}

                    if (TEST2( A, F.fam[depl], M , p-3)==1){ if (INTERSECT( A,F.fam[depl],sousEns1)==1){ //COPY(RES,sousEns);/on traite le dernier element
                                                                  ele.indice=p;
                                                                  ele.rang=depl;
                                                           //      if (RES1.ens.size()<2) return 0;

                                                               RES.ens.push_back(ele);

                                                                COPY(RES,sousEns1);// on renvoie le resultat des intersection dans RES

                                                                 LIBERER(sousEns1);
                                                              //    LIBERER(RES1);
                                                                 LIBERER(sousEns);
                                                           }
                                                     }
                     else{ LIBERER(RES);
                            return 0;
                          }
    }
          if (p>=2){

          if ( INTERSECTF_E( RES, M.multi[p-2], sousEns)==1 ) {if (sousEns.ens.size() < 2) { LIBERER(RES);
                                                                                            return 0;
                                                                                          }
                                                              }
          }


       LIBERER(SousEns);
       LIBERER(A);
       LIBERER(_A);
       LIBERER(_B);
       LIBERER(_C);
          return 1;
    }
/***********************************************************************************************
Bloc principal de la generation de nouvelle famille en utilisant les famille anterieure
************************************************************************************************/

int GENERER( FAMILLE F_inf , int p ,FAMILLE &F_sup, MULTIPARTI M ){  // la valeur p est le rang de la famille qu'on souhaiterai generer ses elemets.
    ENSEMBLE A;
    ENSEMBLE B;
    ELEMENT ele;

    F_sup.size=0;
    F_sup.fam.resize(0);
    int Dim = (int) F_inf.size;
    for( int taille=0 ; taille< Dim ; taille++)
       for ( int pivot=0 ; pivot < Dim; pivot++){
           if (taille==0)//{

              taille=taille+1;  // on traite le cas d'un elements non trivial 1;

       //       } else

           for ( int j=(pivot+taille) ; j< Dim; j++){
           if(PARTITION(p-1,A, F_inf, pivot ,taille, j, M)==1){ ele.indice=p;
   ///
                                                    //  if ( p>=2 &&  TEST1 (A , M.multi[p-2])>=2){
                               //   if (( p>=2 &&  TEST1 (A , M.multi[p-2])>=2)||( p>2 &&  TEST1 (A , M.multi[p-2])>=3)){

                                                             int pos=0;
                                                          //   ele.indice=p;
   ///
                                                       if( MAXENS(pos,A,F_sup)==1){ // RETIRER(pos, F_sup);
                                                                                      LIBERER(F_sup.fam[pos]);
                                                                                //    LIBEREREs(F_sup.fam[pos]);


                                                                                      ele.rang=pos;
                                                                              //    A.ens.insert(A.ens.begin(),ele);
                                                                              //      F_sup.fam.push_back(A);
                                                                                  //  REUNION(
                                                                                  //  COPY( F_sup.fam[pos], A);
                                                                                    COPYFORCER( F_sup.fam[pos], A);

                                                                                    //  A.ens.clear();
                                                                                       LIBERER(A);
                                                                                  //    F_sup.size--;
                                                                                     //  LIBEREREs(A);

                                                                            };
                                                  /*  if(MAXENS(pos,A,F_sup)==0 && pos==0){ele.rang=0;
                                                                                //     A.ens.insert(A.ens.begin(),ele);
                                                                                        COPY ( F_sup.fam[0],A);
                                                                                        F_sup.size++;
                                                                                        LIBERER(A);
                                                                                 //    A.ens.clear();
                                                                                           };
                                                                                           */

                                                        if(MAXENS(pos,A,F_sup)==0){ ele.rang=pos;
                                                                             //   A.ens.insert(A.ens.begin(),ele);
                                                                          //     LIBERER(F_sup.fam[pos]);
                                                                                 F_sup.fam.push_back(A);
                                                                               //  COPY(F_sup.fam[0],A);
                                                                                 F_sup.size++;
                                                                              //   A.ens.clear();
                                                                                  LIBERER(A);
                                                                               };
                                                      ///  if(MAXENS(pos,A,F_sup)==4{



                                                                       //     }

                                                 //    };
           }
                                                     LIBERER(A);
                                                     continue;


                             };
       };
       LIBERER(A);
       return 1;
}
/* LA phase des controles des cas triviaux ou pas
  realiser le 04/05/2009
*/

void FAMILLE_MAX( int p, FAMILLE F , FAMILLE &FMAX)// cette genere la famille effective des maximales;

                   {
    FMAX.size=0;
    ENSEMBLE A,B;
    ELEMENT ele;
    int pos=0;
    int j;
    FMAX.fam.resize(0);
             //  B.ens.clear();

    for ( int i =0 ; i < F.size; i++) {
           bool just=true;
          //LIBERER(A);
         //  B.ens.clear();
           //COPY( B, F.fam[i]);
             COPYFORCER( B, F.fam[i]);
           j=0;
            int cont=0;
            while( j < F.size && just ) {

         // for ( j=0; j < F.size ; j++ ) {
           //  if( j< F.size) continue;
             if (INCLUSION_S(B,F.fam[j])) { just=false;
                                              break;
             }
             else j++;
                cont++;
          }
             if ( cont==F.size ) {
                            ele.indice =p;
                            ele.rang=pos;
                           // B.ens.push_back(ele);
                            B.ens.insert(B.ens.begin(),ele);
                              //  pos++;
                    // if (B.ens.size()>2){
                     if ( B.ens[1].indice!=0) {
                                          FMAX.fam.push_back(B);
                                          //COPYFORCER( FMAX.fam, B);
                                          FMAX.size++;
                                          }
                         //  COPY(  F.fam[FMAX.size],B);
                       //    FMAX.size++;
                           LIBERER(B);
                           pos++;
                }
          }


    }
    int Etape ( MULTIPARTI M){

    int a=M.size;
    return a;
}
  int TEST ( ENSEMBLE A , FAMILLE F) {    //  permet de voir si l'intersection de l'ensemble et la famille a aumoins deux elements de F
      ENSEMBLE B,C;

      int taille=0;
     // COPY(A,F.fam[0]);

      for ( int i=0 ;i< (int)  F.size; i++) {
              LIBERER(B);
              COPY(B,F.fam[i]);
              if (INTERSECT(A,B,C)==1){
                                             taille=taille + C.ens.size();
                                             LIBERER(C);
                                             if ( taille >2) return taille;

                                           };
      };
      LIBERER(A);
      LIBERER(C);
      LIBERER(B);
    return taille;
}


int isnotEnd( MULTIPARTI M){  // la taille des nouveaux elements de la famille doivent une intersection de taille>2 avec les autre
     ENSEMBLE A,B;                    // familles
     FAMILLE  F;
      int controle=0, i, j,a;
if (Etape(M)>2) {  a= Etape(M);
                       for (j =0 ; j < (int) M.multi[a-1].size; j++) {
                             LIBERER(A);
                            COPY (A, M.multi[a-1].fam[j]);
                        for (  i=0 ; i < a-2 ; i++) {
                             if ( i!=1){

                           if ( TEST(A, M.multi[i])>2)  controle++;
                           else return 0;
                           }

                       }

                       };
}

  else  return 1;

  if ( controle==(i-1)*(j-1)) return 1;
    LIBERER(A);
    LIBERER(B);

  return 0;

};

/*************************************************************************
Cette fonction recoit les donnes sous forme de graphes biparti et les
transfert dans le multiparti, creation des deux premieres entrees du
multiparti
**************************************************************************/




void transBiparti( BIPARTI  graph, MULTIPARTI &Mygraph){
  ELEMENT elt;
  ENSEMBLE B,C,A;
  FAMILLE F,F1;
  F.size=0;
  F1.size=0;
  //Fmax.size=0;
  Mygraph.size=0;
//for(int k=0 ; k< (int)graph.size() ;k++){  // traitements de la premiere entree des sommets
for(int k=0 ; k< graph.clique ;k++){


    for( int i=0; i< (int) graph.bipart[k].size() ; i++)
       {
                elt.indice=0 ;
                elt.rang=graph.bipart[k][i];
                B.ens.push_back(elt);
                if (!INCLUSION(B,A)) A.ens.push_back(elt);
                LIBERER(B);

                }
      }

                F.fam.push_back(A);
                F.size++;

                LIBERER(A);
                Mygraph.multi.push_back(F);
                Mygraph.size++;
                LIBERERF (F);
 //-------------------------------------------------------------------------------
    for(int k=0 ; k< graph.clique ;k++){

    for( int i=0; i< (int) graph.bipart[k].size() ; i++)
       {
                elt.indice=0 ;
                elt.rang=graph.bipart[k][i];
                A.ens.push_back(elt);


           }
           elt.rang=k;
           elt.indice=1;
           A.ens.insert(A.ens.begin(),elt);
           F1.fam.push_back(A);
           F1.size++;

             LIBERER(A);
    }
        Mygraph.multi.push_back(F1);
        Mygraph.size++;
        LIBERERF(F1);

     }
/*******************************************************************************
Cette fonction utilise un matrice d'entier prise en entre et le trans forme
en un biparti
*******************************************************************************/


  void CreerBipartite( vector < vector < int > > graph , BIPARTI &VEC){
      VEC.clique=0;
     vector<int>Ens;
     for (int i =0 ; i <(int) graph.size() ; i++){
        for (int j=0 ; j < (int) graph[i].size(); j++){
               Ens.push_back( graph[i][j]);

            VEC.bipart.push_back(Ens);
            VEC.clique++;
        }
     }
     return ;
 }
/********************************************************************************
Permet d'afficher le multiparti
********************************************************************************/
void AFFICHE( MULTIPARTI  M){
    int i;

     for ( int k=0 ; k < (int) M.size; k++) {
            cout << "famille" <<k <<endl;
            cout<<endl;
       //  for ( int j =0 ; j < (int) M[k].fam.size(); j++) {
       for ( int j =0 ; j < (int) M.multi[k].size; j++){
                      if (M.multi[k].size<=1 && k>0) break;
                      cout << " { ";
                   // cout << " { ";
                // int i;

             for ( i=0 ; i< (int) M.multi[k].fam[j].ens.size(); i++) {
                   if(i<(int) M.multi[k].fam[j].ens.size()-1){
                    cout <<  M.multi[k].fam[j].ens[i].indice;
                    cout <<  M.multi[k].fam[j].ens[i].rang;
                    cout <<  "|";
                   };
                    if(i==(int) M.multi[k].fam[j].ens.size()-1){
                    cout <<  M.multi[k].fam[j].ens[i].indice;
                    cout <<  M.multi[k].fam[j].ens[i].rang;
                    cout<<"}";
                    cout << " ";
             }

             }

              if ( j < (int) M.multi[k].size-1)   cout << "<->";
         };
       cout << endl;
     };
}


void LANCERMULTI( BIPARTI GRAPHE, MULTIPARTI &M) {
    FAMILLE F1, Fmax;
    transBiparti(GRAPHE, M);
   bool  CONTINUE=true;
    int i=1;
    while( CONTINUE) {

        if (GENERER(M.multi[i],i+1,F1,M)==1){

                      //   if (isnotEnd( M)==0 ) return ;
                         if ( F1.size<2) return;

                          FAMILLE_MAX(i+1,F1,Fmax);
                         cout<< Fmax.size<<" la taille de Fmax"<< endl;
                     //     if ( F1.size = M.multi[i].size) return;

                       //  M.multi.resize(i+2);
                      //    M.multi.push_back(F1);
                       //  M.size++;
                        // i++;
                  if ( F1.size == M.multi[i].size) return;
                 if ( F1.size>=1)  M.multi.push_back(Fmax);
                              M.size++;
                                i++;
              //                   }
            // else{CONTINUE =false; return;}
                      //   cout<< endl;
                     //    cout<< Fmax.size<<" me voici"<<endl;
                        // LIBERERF(Fmax);
                     //   if ( F1.size == M.multi[i].size) return;
                           LIBERERF(F1);
                         LIBERERF(Fmax);
                         AFFICHE( M);
                  //     if ( F1.size == M.multi[i].size) return;

                        CONTINUE=true;
        }
        else return;
     };
   // AFFICHE( M);
      LIBERERF(F1);
      LIBERERF(Fmax);

   return ;

}

int main()

{ ENSEMBLE A, B;
//  ELEMENT ele;
// ele.indice= new(int);
 //ele.rang= new(int);
 //BIPARTI VEC;

 //   vector<FAMILLE>M;
     MULTIPARTI M,M_test;
     M.size=0;
     FAMILLE F , Fmax;
    // Fmax.size;
     BIPARTI VEC;
     VEC.clique=0;
   //  ELEMENT ele;
     vector<int>Ens;
    // int n;
    // int n=0;
 for ( int i=0 ; i< 11 ; i++){
    // switch(i){


    if(i==0){ Ens.push_back(1);
            Ens.push_back(2);
            VEC.bipart.push_back(Ens);

            Ens.clear();
            VEC.clique++;
    };
    if(i==1){
             Ens.push_back(2);
             Ens.push_back(3);
             Ens.push_back(4);
            // Ens.push_back(5);//ajouter
             VEC.bipart.push_back(Ens);
             Ens.clear();
             VEC.clique++;
    };

    if (i==2){

             Ens.push_back(3);
             Ens.push_back(4);
             Ens.push_back(5);
             Ens.push_back(6);
             VEC.bipart.push_back(Ens);
             Ens.clear();
             VEC.clique++;
    };
    if (i==3){
             Ens.push_back(4);
             Ens.push_back(5);
             Ens.push_back(6);
             Ens.push_back(7);
             VEC.bipart.push_back(Ens);
             Ens.clear();
             VEC.clique++;


  };

    if (i==4){
             Ens.push_back(5);
             Ens.push_back(6);
             Ens.push_back(7);
             Ens.push_back(8);
             VEC.bipart.push_back(Ens);
             Ens.clear();
             VEC.clique++;
    };


 if (i==5){
             Ens.push_back(6);
             Ens.push_back(7);
             Ens.push_back(8);
             Ens.push_back(9);
             VEC.bipart.push_back(Ens);
             Ens.clear();
             VEC.clique++;
    };
if (i==6){
             Ens.push_back(7);
             Ens.push_back(8);
             Ens.push_back(9);
             Ens.push_back(10);
             VEC.bipart.push_back(Ens);
             Ens.clear();
             VEC.clique++;
    };
if (i==7){
             Ens.push_back(8);
             Ens.push_back(9);
             Ens.push_back(10);
             Ens.push_back(11);
             VEC.bipart.push_back(Ens);
             Ens.clear();
             VEC.clique++;
    };
    if (i==8){
             Ens.push_back(9);
             Ens.push_back(10);
             Ens.push_back(11);
             Ens.push_back(12);
             VEC.bipart.push_back(Ens);
             Ens.clear();
             VEC.clique++;
    };
    if (i==9){
             Ens.push_back(10);
             Ens.push_back(11);
             Ens.push_back(12);
             Ens.push_back(13);
             VEC.bipart.push_back(Ens);
             Ens.clear();
             VEC.clique++;
    };
    if (i==10){
             Ens.push_back(11);
             Ens.push_back(12);
             Ens.push_back(13);
             Ens.push_back(14);
             VEC.bipart.push_back(Ens);
             Ens.clear();
             VEC.clique++;
    };
     };
 //  //  LIBERER(A);
 //A.ens.erase( A.ens.begin(),A.ens.end());
/* mes travaux du 8/05 etait de redefinir la structure du multiparti en inserrant le champ size et clique pour le comptage
des structures de donnees differemment a ceux contenus dans les vector

*/
  /*
    for ( int i =0 ; i < 2 ; i++){
         for( int j=0 ; j< (int)VEC.bipart[i].size() ;j++){
            if (i==0) {     ele.rang=VEC.bipart[i][j];
                            ele.indice=0;
                           // cout<< ele;
                            A.ens.push_back(ele);
                      }
            if ( i==1) {    ele.rang=VEC.bipart[i][j];
                            ele.indice=0;
//                          cout << ele;
                            B.ens.push_back(ele);

            };
         }
    }
   // B.ens.erase(B.ens.begin()+1);
     cout <<B.ens[0].indice;
     cout <<B.ens[0].rang;
     cout<<endl;
     cout <<B.ens[1].indice;
     cout <<B.ens[1].rang;
     cout<< endl;
     cout <<B.ens[2].indice;
     cout <<B.ens[2].rang;
cout<<"______________________________"<<endl;

 // LIBERER(A);
    //A.ens.erase( A.ens.begin(),A.ens.end());
  //A.ens.clear();
  cout<< A.ens.size()<<endl<<"taille";
     cout <<A.ens[1].rang<<"son rang";
      cout<<endl;
     cout <<A.ens[0].indice;
     cout <<A.ens[0].rang;
     cout<< endl;
     cout <<A.ens[1].indice;
     cout <<A.ens[1].rang;



cout<<"______________________________"<<endl;

   if (INCLUSION( A,B)) cout<<" c'est bon"<<endl;
  // REUNION(A,B,C);
  int n=DIFFSYM(A,B,C);
   if ( n==1) {

  for ( int i =0 ; i < (int) C.ens.size(); i++){
                       cout<< C.ens[i].rang;
                       cout<< C.ens[i].indice;
                       cout<<endl;
   };

   };

  //if ((INCLUSION( A, B)) cout<<" c'est bon";


 // A.ens.clear();

   cout<< " les parametres"<<endl;
   cout<<VEC.bipart[1].size()<<endl;
   cout<<VEC.bipart[1].size()<<endl;
   cout<<VEC.clique<<endl;
   cout<<VEC.bipart[0][1]<<endl;
   cout<<VEC.bipart[0].size();
 // cout<< M.size;
 // cout << VEC[3][2];

     LIBERER(B);
     LIBERER(A);
 cout<< "test du code ________________"<<endl;

  transBiparti(VEC ,M);
  //AFFICHE(M);
  M.size++;
  GENERER(M.multi[0],2,F,M);
  M.multi.resize(2);
 // M.multi.push_back(F);
  //M.size++;
  //AFFICHE(M);
  FAMILLE_MAX(2, F,Fmax);
  M.multi.push_back(Fmax);
  cout << Fmax.size<<endl;
  M.size++;
  AFFICHE (M);
  if (isnotEnd(M)) cout << " merci"<<endl;

  //cout<<M.multi[0].size<<endl;
cout<<"_________la comportement de F__________________"<<endl;

 //  cout<< " 1----4--5     "<<endl;
  // cout<< "/ \   |\/|\    "<< endl;
//cout<<   "/   \  |/\|\\   "<< endl;
//cout<<  "2     \ 3--6--7  "<< endl;

  cout<< F.size<<endl;

    if (INCLUSION( F.fam[1],F.fam[0])) cout<<" c'est bon"<<endl;
  // REUNION(A,B,C);
  //int n=(F.fam[0],F.fam[1],C);
 // LIBERER(C);
   //n=DIFFSYM(F.fam[0],F.fam[1],C);
  // if ( n==1) {
  //INTERSECT(F.fam[0],F.fam[1],C);
  //REUNION(F.fam[0],F.fam[1],C);

  LIBERER(C);
  COPY (C, F.fam[3]);
  for ( int i =0 ; i < (int) C.ens.size(); i++){

                      cout<< C.ens[i].indice;
                      cout<< C.ens[i].rang;
                      cout<<endl;
   };
  */

  LANCERMULTI(VEC,M_test);
   AFFICHE(M_test);
cout << M_test.multi[0].fam[0].ens[0].indice<<endl;
cout << " COMPLEX_ NETWORK_VERSION_1"<<endl;

cout<<endl;
cout<<endl;
cout<<endl;
 cout << "___LES STATISTIQUES_______"<<endl;

cout <<endl;

cout << "Ce graphe a :.............."<<endl;

cout <<  M_test.multi[1].size <<" cliques"<<endl;

for ( int i=0 ; i < M_test.size ; i++){
  if (i==0){ cout << "La famille" << i <<" a "<<"  "<< M_test.multi[0].fam[0].ens.size()<< " " << "sommets"<<endl;}
  else  { cout << "La famille" << i <<" a "<<"  "<< M_test.multi[i].size<< " " << "ensembles"<<endl;}
}

//cout << "La famille 0 a "<<" "<< M_test.multi[0].fam[0].ens.size()<< " " << "sommets"<<endl;
//cout << "La famille 1 a "<<" "<< M_test.multi[1].size<< " " << "ensembles"<<endl;
//cout << "La famille 2 a "<<" "<< M_test.multi[2].size<< " " << "ensembles"<<endl;
//cout << "La famille 3 a "<<" "<< M_test.multi[3].size-1<< " " << "aucun ensemble candidat"<<endl;

//cout <<  M_test.size <<" cliques"<<endl;


  // };
  //cout<< F.fam[0].ens[0].indice;
 // cout<< F.fam[0].ens[0].rang<<endl;

  //cout<< F.fam[0].ens.size()<<endl;
  //cout<< F.fam[0].ens[3].indice;
 // cout<< F.fam[0].ens[3].rang<<endl;
  //cout<< F.fam[2].ens[0].rang;
 // cout<< F.fam[2].ens[1].indice;
  //cout<< F.fam[2].ens[1].rang;


 // transBiparti(VEC ,M);
  //int pos=0;



  /*for ( int i =0 ; i < (int) C.ens.size(); i++){
                      cout<< C.ens[i].rang;
                      cout<< C.ens[i].indice;
                      cout<<endl;
   }
*/




  // cout << n;

   //  cout<< VEC[3][1]<<endl;

// je m arrete a la situatin qu'il f\aut continue  a l'etape suivantde je consider
// actuellement je suis au niveau pour lancer le multipati
// la fonction famille_max qui cause un problemes


   // cout << "Hello world!" << endl;
    return 0;
}
