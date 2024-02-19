#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    
    int a[11],b[11],n =0,m = 0, *p = a, *q;
    
    scanf("%d",p);
    while(*(p++) != 0){
        scanf("%d",p);
        n++;
    }
    
    p = b;
    scanf("%d",p);
    while(*(p++) != 0){
        scanf("%d",p);
        m++;
    }
    
    for(p = a;p < a + n;p++){
        for(q = a;q < a + n - 1;q++){
            if(*q < *(q+1)){
                int tmp = *q;
                *q = *(q+1);
                *(q+1) = tmp;
            }
        }
    }
    for(p = b;p < b + m;p++){
        for(q = b;q < b + m - 1;q++){
            if(*q > *(q+1)){
                int tmp = *q;
                *q = *(q+1);
                *(q+1) = tmp;
            }
        }
    }
    
    for(p = a;p < a + n;p++){
        for(q = b;q < b + m;q++){
            if(*q > *p){
                int tmp = *q;
                *q = *p;
                *p = tmp;
            }
        }
    }
    for(p = a;p < a + n;p++){
        printf("%d ",*p);
    }
    printf("\n");
    for(p = b;p < b + m;p++){
        printf("%d ",*p);
    }
    printf("\n");
    
    return 0;
}
