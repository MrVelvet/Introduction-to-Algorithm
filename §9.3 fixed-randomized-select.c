#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void SORT(float *A,int num) //to sort the array A,this function is being used in the sebarray with no more than 5 elements
{
    int i = 0;//i and j is being settled as in the textbook
    int j = 0;
    float key = 0;//the standard description in the sort function in the textbook
    for(j = 1; j <= num-1; j++)
    {
        key = *(A+j);
        i = j-1;
        while( i >= 0 && *(A+i) > key)
        {
            *(A+i+1)=*(A+i);
            i--;
        }
        *(A+i+1) = key;
    }
}
int PARTITION(float *A,int p,int r)//qsort kernel code
{
    float x = 0;//the pivot element
    int i = 0;
    int j = 0;
    float transt = 0;//for exchange function
    x = *(A+r);
    i = p - 1;
    for(j = p;j <= r - 1;j++)
    {
        if (*(A+j) < x)
        {
            i++;
            transt = *(A+i);
            *(A+i) = *(A+j);
            *(A+j) = transt;
        }
    }
    transt = *(A+i+1);
    *(A+i+1) = *(A+r);
    *(A+r) = transt;
   i++;
   return(i);
}
float SELECT(float *A,int p ,int r,int i)//just the same symbol with the former code,it should be noticed that this function returns a niddle.
{
    float *E = NULL;//the niddle from E to G is simply settled to describe the element in array A in order,which are easy to read
    float **B = NULL;
    float **C = NULL;
    float **D = NULL;
    float *F = NULL;
    float *G = NULL;
    int pivot = 0;//the pivot col
    int num = 0;//how many colin the matrix
    int t =0,t1 = 0,t2 = 0,tt=0;//the predictor
    int indica=0;//indicate whether n mod 5 != 0
    int pivot_indica = 0;//indicate whether the pivot is found
    int pivot_indicator = 0;//whether the pivot col own 5 elements
    int indicat = 0;//indicate the medium of the last row
    float x = 0;//as defined in the book P123(chinese editor)
    float pip = 0;//for exchange
    int order = 0;//the result from partition function
    int sub_num = 0;//to sum the elements to be calculated in the next iteration
    if(p == r)
        return (*(A+p));
    num = (r-p+1)/5;
    if (5*num+p-1 != r)//there is a col with less than 5 elements
        {
            num++;
            indica = 1;
        }
    E =(float*)(malloc(sizeof(float)*10000));
    B = (float **)(malloc(sizeof(float *)*10000+sizeof(float)));
    C = (float **)(malloc(sizeof(float *)*10000+sizeof(float)));
    D = (float **)(malloc(sizeof(float *)*10000+sizeof(float)));
    F = (float *)(malloc(sizeof(float)*10000+sizeof(float)));
    G = (float *)(malloc(sizeof(float)*10000+sizeof(float)));
    if((r-p+1)<150)//the bottm limit of the iteration
        {
            SORT(A,(r-p+1));
            return (*(A+i-1));
         }
    for (;t <= num - 2;t++)
            *(B+t) = (A+5*t + 2);
    if (indica == 1)
        {
            indicat = ((r-p+1)%5)/2+((r-p+1)%5)%2;
            *(B+t) = (A+5*t+indicat-1);
        }
    else *(B+t) =(A+ 5*t+2);
     if(indica ==0)
         indicat = 3;
    //step 1 finished
    if(indica == 0)
        {
            for(t=0;t<=num-1;t++)
             {
               SORT((A+5*t),5);//+-5
             }
        }
    else
    {
        for(t=0;t<=num-2;t++)
          SORT((A+5*t),5);//+-5
    SORT((A+5*t),(r-5*(num-1)+1-p));               
    }
    for (t=0;t<num;t++)
        *(E+t)=**(B+t);
    //step 2 finished,the num in *B is desired n/5 medium.
    x = SELECT(E,0,num-1,(num+1)/2);//the iteration step
    for(t = 0; t <= num-1 ; t++)//divide the cols into different parts which are seperated by the reslut of the comparation between the medium of the col and the pivot value
    {
        if(**(B+t) < x)
            {
                *(C+t1) = *(B+t);
                t1 ++;
            }  
        else if (**(B+t) == x && pivot_indica == 0)
            {
                
                pivot = t;
                pivot_indica = 1; 
                if( t == num - 1 && indica == 1)
                    pivot_indicator = 1;
            } 
        else 
            {
                *(D+t2) = *(B+t);
                t2 ++;
            }
    }
    for (t = 0;t < r+1; t++)//to set a new matrix to get the elements in memory in order not to get the order confused
    {
        *(F+t)=*(A+t);
    }
    if(pivot_indicator == 0)
    {
        pip = *(F+5*pivot+2);
        *(F+5*pivot+2) = *(F+r);
        *(F+r) = pip;
    }
    else 
    {
        pip = *(F+r-((r-p+1)%5)/2);
        *(F+r-((r-p+1)%5)/2) = *(F+r);
        *(F+r) = pip;
    }
    order = PARTITION(F,0,r);//the value of the partition function with the pivot x,to locate where is the pivot x in the original matrix
    if(order == i-1)//to get the new matrix for the next iteration in condition of whether the element to found is in the low area or high area compared with the pivot x respectfully
        return *(F+i-1);
     else if(order > i-1)
    {
     if(t1 > 1 )
            {
                for(t=0;t<=t1-2;t++)
                 { 
                   for(tt=0;tt<5;tt++)
                    {
                        *(G+sub_num)=*(*(C+t)-2+tt);
                        sub_num++;
                    }
                 }
            }
        if( t1 > 0 )
        {
          if ((A+5*(num-1)+indicat-1) == (*(C+t1-1))&& indica ==1)
            { 
                 for(tt=0;tt<(r-p+1)%5;tt++)
                    {
                        *(G+sub_num)=*(A+(num-1)*5+tt);
                        sub_num++;
                    }
            }
            else
            {
                for(tt=0;tt<5;tt++)
                    {
                        *(G+sub_num)=*(*(C+t1-1)-2+tt);
                        sub_num++;
                    }
            }
        }
    if (pivot_indicator == 1)
    {
        for(tt=0;tt<(r-p+1)%5;tt++)
                    {
                        *(G+sub_num)=*(A+(num-1)*5+tt);
                        sub_num++;
                    }     
    }
    else 
   {
        for(tt=0;tt<5;tt++)
                    {
                        *(G+sub_num)=*(A+pivot*5+tt);
                        sub_num++;
                    }     
    }
    if(t2 > 0 )
    {
       if (((A+5*(num-1)+indicat-1) == (*(D+t2-1)))&&indica ==1)
        {
                  for(tt=0;tt<((r-p+1)%5)/2;tt++)
                    {
                        *(G+sub_num)=*(A+(num-1)*5+tt);
                        sub_num++;
                    }
        }
        else
        {
                        for(tt=0;tt<2;tt++)
                    {
                        *(G+sub_num)=*(*(D+t2-1)-2+tt);
                        sub_num++;
                    }
        }
        if(t2 > 1 )  
        {
            for(t=0;t<=t2-2;t++)
              {
                 for(tt=0;tt<2;tt++)
                    {
                        *(G+sub_num)=*(*(D+t)-2+tt);
                        sub_num++;
                    }
           }
        }
    }
    if(sub_num == (r-p+1))
          sub_num--;
    return (SELECT(G,0,sub_num-1,i));
}
else 
    {
       if(t1 > 1 )
        {
         for(t=0;t<t1-2;t++)
          {
            for(tt=0;tt<2;tt++)
                    {
                        *(G+sub_num)=*(*(C+t)+1+tt);
                        sub_num++;
                    }
          }
        }
        if (t1 >0)
            { 
             if ( (A+5*(num-1)+indicat-1)==*(C+t2-1)&& indica ==1)
             {
                for(tt=(((r-p+1)%5)/2+((r-p+1)%5)%2);tt<((r-p+1)%5);tt++)
                    {
                        *(G+sub_num)=*(A+(num-1)*5+tt);
                        sub_num++;
                    }
             }
             else 
             {
                for(tt=0;tt<2;tt++)
                    {
                        *(G+sub_num)=*(*(C+t1-1)+1+tt);
                        sub_num++;
                    }
             }
            }
    if ( pivot_indicator == 1 )
    {
        for(tt=0;tt<(r-p+1)%5;tt++)
                    {
                        *(G+sub_num)=*(A+(num-1)*5+tt);
                        sub_num++;
                    }     
    }
    else 
   {
        for(tt=0;tt<5;tt++)
                    {
                        *(G+sub_num)=*(A+pivot*5+tt);
                        sub_num++;
                    }     
    }
     if(t2 > 0 )
     {
        if ( (A+5*(num-1)+indicat-1) == (*(D+t2-1))&& indica == 1)
        {
            for(tt=0;tt<((r-p+1)%5);tt++)
                    {
                        *(G+sub_num)=*(A+(num-1)*5+tt);
                        sub_num++;
                    }
        }
        else
        {
            for(tt=0;tt<5;tt++)
                    {
                        *(G+sub_num)=*(*(D+t2-1)-2+tt);
                        sub_num++;
                    }
            }
        }
      if(t2 > 1 )
        {
         for(t=0;t<t2-2;t++)
           {
            for(tt=0;tt<5;tt++)
                    {
                        *(G+sub_num)=*(*(D+t)-2+tt);
                        sub_num++;
                    }
           }
        }//the normal rows to be counted
      if(sub_num == (r-p+1))
      {
          sub_num--;
          *G =*(G+sub_num);
      }
    return (SELECT(G,0,sub_num-1,i-(r-p+1-sub_num)));
    }
  free(B);
  free(C);
}
int  main()
{
    int  begin=clock();//set the clock-beginning time
    int end= 0;//set the clock-ending time
    int during_time = 0;//the running time
    int n = 0; //n represents the number of the array to be cooperated
    int i =0;//i represents the i-th number to be selected
    int j = 0;//
    float *A=NULL;//A is the arrayn 
    scanf("%d%d",&n,&i);
    A = (float*)(malloc(sizeof(float)*10000));
    if(A == NULL)
        exit(1);
    srand(time(0));
     for (j=0;j<n;j++)
        {
            *(A+j) = rand()%10000;
             *(A+j) =  *(A+j)/10000;
            printf("%f ",*(A+j));
         }
   printf("\nthe i-th number is %f\n",SELECT(A,0,n-1,i));
   free(A);
   end=clock();
   during_time = end - begin;
   printf("\n the running time is %d ",during_time);
}
