#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>

//  (fork()) crece vertical   

//  (!fork())  crece horizontal

int main (int argc, char *argv[]){
	
  int i,j,k;

  // Pedimos al usuario el número de tallos
  int tallos = atoi(argv[1]);
  // Pedimos al usuario el número de flores
  int flores = atoi(argv[2]);
  // Pedimos al usuario el número de pétalos por flor
  int petalos = atoi(argv[3]);
	
  for(i=0;i<tallos+flores-1;i++){   //niveles
	if(fork()){
		if(i>tallos-1){    //Horizontal
			if(!fork()){
				for(j=0;j<petalos;j++){
					if(!fork())     // Horizontales
					break;
				}
			}
		}
	  break;
	}
	
	if(i==tallos+flores-2){
		if(!fork()){
			for(int r=0;r<petalos;r++){
				if(!fork())
				break;
				}
			}
	}
	
   }

   sleep(30);
	
   return 0;	
}
