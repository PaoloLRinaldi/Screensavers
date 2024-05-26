#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>
#include <fcntl.h>




#define SLARG 60
#define SHIGH 30


void screena(char ** des, int sl, int sh);
void printav(char** des, int sl, int sh);
void screenbb(char **des, int sl, int sh, int *coo, int stage);
void freeb(char **des, int *coo, int stage);
void screenba(char **des, int sl, int sh, int stagemax);
int dist (int *cooa, int *coob, int stmax);
int kbhit();
int getch();


int main() {
  int i, j, k, sl=SLARG, sh=SHIGH, stagemax=4;
  char **des=NULL;
  srand48(time(0));
  des=(char**)calloc(sh, sizeof(char*));
  for (i=0; i<sh; i++) des[i]=(char*)calloc(sl, sizeof(char));
  screenba(des, sl, sh, stagemax);
//  screena(des, sl, sh);
  
  





  exit(0);
}

void printav(char** des, int sl, int sh) {
  int i, j;
  
  system("clear\n");
  for (i=0; i<sh; i++) {
    for (j=0; j<sl; j++) putchar(des[i][j]);
    putchar(10);
  }
  return;
}


void screena(char ** des, int sl, int sh) { 
  int i, j;
  
  for (i=0; i<sh; i++) for (j=0; j<sl; j++) des[i][j]=32;
  do {
    system("clear\n");
    usleep(200000);
    des[15][30]=111;
    printav(des, sl, sh);
    usleep(100000);
    des[15][30]=32;
    des[14][29]=92;
    des[14][30]=124;
    des[14][31]=47;
    des[15][29]=45;
    des[15][31]=45;
    des[16][29]=47;
    des[16][30]=124;
    des[16][31]=92;
    printav(des, sl, sh);
    usleep(100000);
    des[14][29]=32;
    des[14][30]=32;
    des[14][31]=32;
    des[15][29]=32;
    des[15][31]=32;
    des[16][29]=32;
    des[16][30]=32;
    des[16][31]=32;
    
    des[13][28]=92;
    des[13][30]=124;
    des[13][32]=47;
    des[15][28]=45;
    des[15][32]=45;
    des[17][28]=47;
    des[17][30]=124;
    des[17][32]=92;
    printav(des, sl, sh);
    usleep(100000);
    
    des[13][28]=32;
    des[13][30]=32;
    des[13][32]=32;
    des[15][28]=32;
    des[15][32]=32;
    des[17][28]=32;
    des[17][30]=32;
    des[17][32]=32;
  } while (1);
  return;
}


void screenbb(char **des, int sl, int sh, int *coo, int stage) {
  if (!stage) {
  //  printf ("coo0  %d     coo1  %d\n", coo[0], coo[1]);
    des[coo[0]][coo[1]]=111;
  //  sleep(2);
  } else {
    if (stage==1) {
    des[coo[0]][coo[1]]=32;
    } else {
      stage--;
      des[coo[0]-stage][coo[1]-stage]=32;
      des[coo[0]-stage][coo[1]]=32;
      des[coo[0]-stage][coo[1]+stage]=32;
      des[coo[0]][coo[1]-stage]=32;
      des[coo[0]][coo[1]+stage]=32;
      des[coo[0]+stage][coo[1]-stage]=32;
      des[coo[0]+stage][coo[1]]=32;
      des[coo[0]+stage][coo[1]+stage]=32;
      stage++;
    }
    des[coo[0]-stage][coo[1]-stage]=92;
    des[coo[0]-stage][coo[1]]=124;
    des[coo[0]-stage][coo[1]+stage]=47;
    des[coo[0]][coo[1]-stage]=45;
    des[coo[0]][coo[1]+stage]=45;
    des[coo[0]+stage][coo[1]-stage]=47;
    des[coo[0]+stage][coo[1]]=124;
    des[coo[0]+stage][coo[1]+stage]=92;
    
  }

  return; 
}

void freeb(char **des, int *coo, int stage) {
 
      des[coo[0]-stage][coo[1]-stage]=32;
      des[coo[0]-stage][coo[1]]=32;
      des[coo[0]-stage][coo[1]+stage]=32;
      des[coo[0]][coo[1]-stage]=32;
      des[coo[0]][coo[1]+stage]=32;
      des[coo[0]+stage][coo[1]-stage]=32;
      des[coo[0]+stage][coo[1]]=32;
      des[coo[0]+stage][coo[1]+stage]=32;
      return; 
}


void screenba(char **des, int sl, int sh, int stagemax) {
  int **coo, maxb, i, j, minl, minh, cond, lextra, lastl, mintot, freq, **ava, totava, avan, index=0;
  int counter = 0;
  
  
  maxb=(sl*sh)/((2*stagemax-1)*(2*stagemax-1));
  coo=(int**)calloc(maxb, sizeof(int*));
  for (i=0; i<maxb; i++) coo[i]=(int*)calloc(3, sizeof(int));
  totava=(sl-2*(stagemax-1))*(sh-2*(stagemax-1));
//  printf ("%d\n", totava); sleep(3);
  ava=(int**)calloc(totava, sizeof(int*));
  for (i=0; i<totava; i++) ava[i]=(int*)calloc(2, sizeof(int));
  //minl=(cond=(sl>=(3*(2*stagemax-1)-2)))+cond*(sl-(3*(2*stagemax-1)-2))/(2*(2*stagemax-1)-1);
  cond=(sl>=(3*(2*stagemax-1)-2));
//  printf ("Condl=%d\n", cond);
// printf ("sl=%d    (3*(2*stagemax-1)-2)=%d \n", cond, sl, (3*(2*stagemax-1)-2));
  lextra=cond*(sl-(3*(2*stagemax-1)-2))/(2*(2*stagemax-1)-1);
//  printf ("lextra=%d\n", lextra);
  lastl=cond*((sl-(3*(2*stagemax-1)-2)-(lextra*(2*(2*stagemax-1)-1)))>=(2*stagemax-1));
//  printf ("lastl=%d\n", lastl);
  minl=(sl>=(2*stagemax-1))+lextra+lastl;
  //minl=(sl>=(2*stagemax-1)) + cond*(sl-(3*(2*stagemax-1)-2))/(2*(2*stagemax-1)-1);
  cond=(sh>=(3*(2*stagemax-1)-2));
//  printf ("Condl=%d\n", cond);
  lextra=cond*(sh-(3*(2*stagemax-1)-2))/(2*(2*stagemax-1)-1);
//  printf ("hextra=%d\n", lextra);
  lastl=cond*((sh-(3*(2*stagemax-1)-2)-(lextra*(2*(2*stagemax-1)-1)))>=(2*stagemax-1));
//  printf ("lasth=%d\n", lastl);
  minh=(sh>=(2*stagemax-1))+lextra+lastl;
  /* Con il calcolo di minl e minh vedo quanto è il minimo numero di immagini tali che non sia possibile metterne altre sia in larghezza (minl) sia in altezza (minh) */
//  printf ("minl=%d     minh=%d\n", minl, minh);
  mintot=minh*minl;
  freq=mintot/(stagemax+1);
  freq+=(!freq);
  if (!freq) printf ("freq=0!\n"), abort();
  
  for (i=0; i<sh; i++) for (j=0; j<sl; j++) des[i][j]=32;
  do {
    for (i=0; i<totava; i++) {
   //   printf("here...   %d   %d\n", i/(sl-2*(stagemax-1))+stagemax-1, i%(sl-2*(stagemax-1))+stagemax-1);
      ava[i][0]=(i/(sl-2*(stagemax-1)))+stagemax-1;
      ava[i][1]=(i%(sl-2*(stagemax-1)))+stagemax-1;
  //    printf("there\n");
    }
    avan=totava;
    for (i=0; i<maxb; i++) {
     if (coo[i][0]) {
 //      puts("segfault?\n");
      for (j=0; j<avan; j++) {
        if (dist(coo[i], ava[j], stagemax)) {
         ava[j][0]=ava[--avan][0];
         ava[j][1]=ava[avan][1];
	 j--;
        }
      }
     }
    }
//  puts("segfault?\n");
    if (avan)
    for (i=lrand48()%(freq+1); i>0; i--) {
      cond=lrand48()%avan;
      coo[index][0]=ava[cond][0];
      coo[index][1]=ava[cond][1];
  //    printf ("ava0 %d    ava1 %d\n", ava[cond][0], ava[cond][1]);
  //    usleep(1000000);
  //    printf ("i=%d\n", i);
      for (j=0; j<avan; j++) {
        if (cond!=j && dist(ava[cond], ava[j], stagemax)) {
         ava[j][1]=ava[--avan][1];
         ava[j][0]=ava[avan][0];
        }
//        printf("%d    %d   +++++++++\n", j, avan);
      }
 //   usleep(2000000);
//      abort();
      ava[cond][0]=ava[--avan][0];
      ava[cond][1]=ava[avan][1];
      index=(index+1)%maxb;
    }
    
    
/*    for (i=0; i<maxb; i++) if (coo[i][0]) printf ("%d     %d\n", coo[i][0], coo[i][1]);
    for (i=0; i<avan; i++) printf ("%d %d\n", ava[i][0], ava[i][1]);
    getch();       n*/
   // abort();
//  puts("\n\n\n\n\n\n\n\n\n\n------------------------segfault?\n");
    for (i=0; i<maxb; i++) {
     if (coo[i][0]) {
      if (coo[i][2]<=stagemax-1) screenbb(des, sl, sh, coo[i], coo[i][2]), coo[i][2]++;
      else {
        freeb (des, coo[i], stagemax-1);
        coo[i][0]=coo[i][1]=coo[i][2]=0;
      }
     }
    }
    usleep(100000);
    printav(des, sl, sh);
//    usleep(20000000);

    if (1)
    for (i=0; i<maxb; i++) {
     for (j=0; j<maxb; j++) {
      if (i!=j && coo[i][0] && coo[j][0] && dist(coo[i], coo[j], stagemax)) {
       printf ("Come on maaaan!\nCoo[%d][0]=%d  Coo[%d][1]=%d\nCoo[%d][0]=%d  Coo[%d][1]=%d\nStage1=%d   Stage2=%d\n", i, coo[i][0], i, coo[i][1], j, coo[j][0], j, coo[j][1], coo[i][2], coo[j][2]);
       printf ("counter = %d\n", counter);
       exit(0);
      }
     } 
    }
    counter++;
  } while (!kbhit());
  system("clear\n");
  
  
  
  
 return; 
}


/**************************************************/


int dist (int *cooa, int *coob, int stmax) {
  int conda, condb, distanza;
  
   /*   printf ("cooa[0]=%d\n", cooa[0]);
      printf ("cooa[1]=%d\n", cooa[1]);
      printf ("coob[0]=%d\n", coob[0]);
      printf ("coob[1]=%d\n", coob[1]);   */
      distanza=(2*(stmax-1)+1)*(2*(stmax-1)+1);
  conda=(((cooa[0]-coob[0])*(cooa[0]-coob[0]))<distanza);
 //     printf ("i=\n");
  condb=(((cooa[1]-coob[1])*(cooa[1]-coob[1]))<distanza);
 //     printf ("i=\n");
 return (conda && condb);
}
    



/**************************************************/


int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}


/**************************************************/


int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
