#include <stdlib.h>

void uniform(int len,int*arr){
    for(int i=0;i<len;i++){
        arr[i]=rand()%(len);
    }
}

void constant(int len, int*arr){
	for(int i=0;i<len;i++){
        arr[i]=0;
    } 
}

void ascending(int len, int*arr){
	for(int i=0;i<len;i++){
        arr[i]=i;
    } 

}

void descending(int len, int*arr){
	for(int i=0;i<len;i++){
    arr[i]=len-i;
    } 
}

void AShape(int len, int*arr){
	for(int i=0;i<len;i++){
		if (i>len/2){
			arr[i]=len-i;		
		}
        else{
            arr[i]=i;
        }
    } 
}

void VShape(int len, int*arr){
	for(int i=0;i<len;i++){
		if (i>len/2){
			arr[i]=i;		
		}
        else{
            arr[i]=len-i;
		}
    } 
}
