# include <stdio.h>
# include <stdlib.h>
# include <time.h>
int PARTITION(float *A,int p,int r)//qsort kernel code
{
    float x = 0;
    int i = 0;
    int j = 0;
    float transt = 0;
    x = *(A+r-1);
    i = p - 2;
    for(j = p-1;j <= r - 2;j++)
    {
        if (*(A+j) <= x)
        {
            i++;
            transt = *(A+i);
            *(A+i) = *(A+j);
            *(A+j) = transt;
        }
    }
    transt = *(A+i+1);
    *(A+i+1) = *(A+r-1);
    *(A+r-1) = transt;
   i++;
   return(i);
}
int RANDOMIZED_PARTITION(float *A,int p,int r)//generate a random pivot 
{
    float trans=0;
    int i = 0;
    srand(time(0));
    i = rand()%(r-p+1)+p;
    trans = *(A+r-1);
    *(A+r-1) = *(A+i-1);
    *(A+i-1) = trans;
    return PARTITION(A,p,r);
}
float RANDOMIZED_SELECT(float *A,int p,int r,int i)//divide and conquer
{
    int q = 0; 
    int k = 0;
    if ( r == p)
        return (*(A+r-1));
    q = RANDOMIZED_PARTITION(A,p,r);
    k = q - p + 2;
    if( i == k) //the pivot vale is the answer
      return(*(A+q));
    else if (i < k )
        return (RANDOMIZED_SELECT(A,p,q,i));
    else return (RANDOMIZED_SELECT(A,q+2,r,i-k));
}
void main()
{
    int  begin=clock();//set the clock-beginning time
    int end= 0;//set the clock-ending time
    int during_time = 0;//the running time
    float *A=NULL;//A is the array
    int n = 0; //n represents the number of the array to be cooperated
    int j = 0;//
    int i =0;//i represents the i-th number to be selected
    scanf("%d%d",&n,&i);
    A = (float*)(malloc(sizeof(float)*n+4));
    if(A == NULL)
        exit(1);
    srand(time(0));
    for (j=0;j<n;j++)
        {
            *(A+j) = rand()%n;
             *(A+j) =  *(A+j)/100;
            printf("%f ",*(A+j));
         }
    *(A+j) = '\0';
   printf("\nthe i-th number is %f\n",RANDOMIZED_SELECT(A,1,n,i));
   free(A);
   end=clock();
   during_time = end - begin;
   printf("\n the running time is %d ",during_time);
}