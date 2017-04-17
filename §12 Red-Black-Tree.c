#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int t = 0;
struct tree_node//the structure of the red-black-tree nodes
	{
		int color;//0 shows the black while 1 shows the red
		int key;//key value
		struct tree_node *left;//left child
		struct tree_node *right;//right child
		struct tree_node *parent;//parent indicator
		int rank;//the size of the value in the total tree
	};
struct tree_node *T_nil;//the T.nil node as defined in the text book
struct tree_node *T;//the root of the tree
struct tree_node *left_rorate_RBT(struct tree_node *Node,struct tree_node *T)
{
	int rank_change1;
	int rank_change2;
	int rank_change3;
	struct tree_node *B;
	B = Node->right;
	rank_change1 = Node->left->rank;
	rank_change2 = Node->right->left->rank;
	rank_change3 = Node->right->right->rank;
	Node->right = B->left;
	if ( B->left != T_nil )
		B->left->parent = Node;
	B->parent = Node->parent;
	if ( Node == T )
		T = B;
	else if ( Node == Node->parent->left )
		Node->parent->left = B;
	else Node->parent->right = B;
	B->left = Node;
	Node->parent = B;
	Node->rank = rank_change1 + rank_change2 + 1;
	Node->parent->rank = rank_change1 + rank_change2 + rank_change3 + 2;
	return T;
}
struct tree_node * right_rorate_RBT(struct tree_node *Node,struct tree_node *T)
{
	int rank_change1;
	int rank_change2;
	int rank_change3;
	struct tree_node *B;
	B = Node->left;
	rank_change1 = Node->left->left->rank;
	rank_change2 = Node->left->right->rank;
	rank_change3 = Node->right->rank;
	Node->left = B->right;
	if ( B->right != T_nil )
		B->right->parent = Node;
	B->parent = Node->parent;
	if ( Node == T )
		T = B;
	else if ( Node == Node->parent->right )
		Node->parent->right = B;
	else Node->parent->left = B;
	B->right = Node;
	Node->parent = B;
	Node->rank = rank_change3 + rank_change2 + 1;
	Node->parent->rank = rank_change1 + rank_change2 + rank_change3 + 2;
	return T;
}
int search(struct tree_node *A)//middle order sort
{
	t++;
	if( A != T_nil)
	{
		search(A->left);
		printf("the value is %d   the color of the node is %d\n",A->key,A->color);
		search(A->right);
	}
	return 0;
}
struct tree_node *minimum_RBT(struct tree_node *A)
{
	while( A->left != T_nil)
	{
		A = A->left;
		t++;
	}
	printf("the minimun element in the RBT is %d\n",A->key);
	printf("the running time is %d\n",t);
	return A;
}
int maximam_RBT(struct tree_node *A)
{
	while( A->right != T_nil)
	{
		A = A->right;
		t++;
	}
	printf("the maximan element in the RBT is %d\n",A->key);
	printf("the running time is %d\n",t);
	return 0;
}
int latter_RBT(struct tree_node *A)
{
	struct tree_node *y;
	if ( A == T_nil )
	{
		printf("the running time is 1\n");
		printf("the item has no successor\n");
	}
	else
	{
		if( A->right != T_nil )
		{
			A = A->right;
			while( A->left != T_nil)
			{
				A = A->left;
				t++;
			}
			printf("the successor is %d\n",A->key);
			printf("the running time is %d\n",t);
		}
 		else
 		{
 			y = A->parent;
 			while (( y != T_nil ) && ( A == y->right ))
 			{
 				A = y;
 				y = y->parent;
 				t++;
 			}
 			printf("the running time is %d\n",t);
 			if( y->key != 0)
 				printf("the successor is %d\n",y->key);
 			else printf("the item has no successor\n");
 		}
	}
	return 0;
}
int former_RBT(struct tree_node *A)
{
	struct tree_node *y;
	if ( A == T_nil )
	{	
		printf("the running time is 1\n");
		printf("the item has no previous value\n");
	}
	else
	{
		if( A->left != T_nil )
		{
			A = A->left;
			while( A->right != T_nil)
			{
				A = A->right;
				t++;
			}
			printf("the running time is %d\n",t);
			printf("the previous element is %d\n",A->key);
		}
 		else
 		{
 			y = A->parent;
 			while (( y != T_nil ) && ( A == y->left ))
 			{
 				A = y;
 				y = y->parent;
 				t++;
 			}
 			printf("the running time is %d\n",t);
 			if( y->key != 0)
 				printf("the previous element is %d\n",y->key);
 			else printf("the item has no previous value\n");
 		}
	}
	return 0;
}
struct tree_node *fixup_insert_BRT(struct tree_node *T,struct tree_node *Node)
{
	struct tree_node *y;
	if( T == Node )
		T->color = 0;
	else
		while( (Node->parent)->color == 1)
		{
			t++;
			if( Node->parent == Node->parent->parent->left )
			{
				y = Node->parent->parent->right;
				if ( y->color == 1 )
				{
					Node->parent->color = 0;
					y->color = 0;
					Node->parent->parent->color = 1;
					Node = Node->parent->parent;
				}
				else 
				{
					if ( Node == Node->parent->right )
					{
						Node = Node->parent;
						T = left_rorate_RBT(Node,T);
					}
				Node->parent->color = 0;
				Node->parent->parent->color = 1;
				T = right_rorate_RBT(Node->parent->parent,T);
				}
			}
			else
			{
				y = Node->parent->parent->left;
				if ( y->color == 1 )
				{
					Node->parent->color = 0;
					y->color = 0;
					Node->parent->parent->color = 1;
					Node = Node->parent->parent;
				}
				else  
				{
					if ( Node == Node->parent->left )
				    {
						Node = Node->parent;
						T = right_rorate_RBT(Node,T);
					}
				Node->parent->color = 0;
				Node->parent->parent->color = 1;
				T = left_rorate_RBT(Node->parent->parent,T);
			    }
			}
			T->color = 0;
        }
    return T;
}
struct tree_node *insert_BRT(struct tree_node *T,int keye)
{
	struct tree_node *Node;
	struct tree_node *y;
	struct tree_node *x;//defined as in the text
	Node = (struct tree_node *)malloc(sizeof(struct tree_node));
	Node->key = keye;
	Node->parent = T_nil;
	Node->left = T_nil;
	Node->right = T_nil;
	Node->rank = 1;
	Node->color = 0;
	y = T_nil;
	x = T;
	while( x != T_nil)
	{
		t++;
		x->rank++;
		y = x;
		if( Node->key < x->key )
			x = x->left;
		else x = x->right;
	}
	Node->parent = y;
	if ( y == T_nil)
		T = y;
	else if ( Node->key < y->key )
		y->left = Node;
	else y->right = Node;
	Node->color = 1;
	T = fixup_insert_BRT(T,Node);
	return T;
}
struct tree_node *transplant(struct tree_node *T,struct tree_node *u,struct tree_node *v)
{
	if( v != T_nil )
	{
		if( u->parent == T_nil)
			T = v;
		else if ( u == u->parent->left )
			u->parent->left = v;
		else u->parent->right = v;
		v->parent = u->parent;
		return T;
	}
	else 
	{
		if( u->parent == T_nil)
			T = T_nil;
		else if ( u == u->parent->left )
			u->parent->left = v;
		else u->parent->right = v;
		return T;
	}
}
struct tree_node *fixup_delete_BRT(struct tree_node *T,struct tree_node *Node)
{
	struct tree_node *w;
	while(( Node != T) && ( Node->color == 0 ))
	{
		t++;
		if( Node == Node->parent->left )
		{
			w = Node->parent->right;
			if( w->color == 1 )
			{
				w->color = 0;
				Node->parent->color = 1;
				T = left_rorate_RBT(Node->parent,T);
				w = Node->parent->right;
			}
			if(( w->left->color == 0 ) && (w->right->color == 0 ))
			{
				w->color = 1;
				Node = Node->parent;
			}
			else 
			{
				if ( w->right->color == 0)
				{
					w->left->color = 0;
					w->color = 1;
					T = right_rorate_RBT(w,T);
					w = Node->parent->right;
				}
				w->color = Node->parent->color;
				Node->parent->color = 0;
				w->right->color = 0;
				T = left_rorate_RBT(Node->parent,T);
				Node = T;
			}
		}
		else
		{
			w = Node->parent->left;
			if( w->color == 1 )
			{
				w->color = 0;
				Node->parent->color = 1;
				T = right_rorate_RBT(T,Node->parent);
				w = Node->parent->left;
			}
			if(( w->right->color == 0 ) && (w->left->color == 0 ))
			{
				w->color = 1;
				Node = Node->parent;
			}
			else 
			{
				if ( w->left->color == 0)
				{
					w->right->color = 0;
					w->color = 1;
					T = left_rorate_RBT(T,w);
					w = Node->parent->left;
				}
				w->color = Node->parent->color;
				Node->parent->color = 0;
				w->left->color = 0;
				T = right_rorate_RBT(T,Node->parent);
				Node = T;
			}
		}
	}
	return T;
}
struct tree_node *delete_BRT(struct tree_node *Node,struct tree_node *T)
{
	struct tree_node * nulsinstant;
	struct tree_node *y = Node;
	struct tree_node *x;
	int cutor =2;
	int indoca = 0;
	struct tree_node *change;
	change = Node;
	if( Node->parent->left == Node )
		indoca = 1;
	nulsinstant = (struct tree_node *)malloc(sizeof(struct tree_node));
	nulsinstant->parent = Node->parent;
	nulsinstant->key = -1;
	nulsinstant->left = T_nil;
	nulsinstant->right = T_nil;
	nulsinstant->rank = 0;
		nulsinstant->color = 0;
	while ( change != T )
	{
		t++;
		change = change->parent;
		change->rank--;
	}
	cutor = y->color;
	if( Node->left == T_nil)
	{
		x = Node->right;
		T = transplant(T,Node,Node->right);
	}
	else if (Node->right == T_nil)
	{
		x = Node->left;
		T = transplant(T,Node,Node->left);
	}
	else
	{
		y = minimum_RBT(Node->right);
		cutor = y->color;
		x = y->right;
		if( y->parent == Node)
			x->parent = y;
		else 
		{
			T = transplant(T,y,y->right);
			y->right = Node->right;
			y->right->parent = y;
		}
	T = transplant(T,Node,y);
	y->left = Node->left;
	y->left->parent = y;
	y->color = Node->color;
	}
	if(( cutor == 0) && ( x != T_nil ))
		T = fixup_delete_BRT(T,x);
	else if ( cutor == 0 )
	{
		if( indoca == 1 )
		{
			nulsinstant->parent->left = nulsinstant;
			T = fixup_delete_BRT(T,nulsinstant);
			nulsinstant->parent->left = T_nil;
		}
		else 
		{
			nulsinstant->parent->right = nulsinstant;
			T = fixup_delete_BRT(T,nulsinstant);
			nulsinstant->parent->right = T_nil;
		}
	}
	return T;
}
int rank_selection_RBT(struct tree_node *T,int i)
{
	int r = 0;
	t++;
	r = T->left->rank + 1;
	if ( i == r )
	{
		printf("the i-th value in the RBT is %d\n",T->key);
		return 0;
	}
	else if( i < r )
		rank_selection_RBT(T->left,i);
	else rank_selection_RBT(T->right,i-r);
	return 0;
}
int main(void)
{
	struct tree_node *sr;
	int keyr = 0;
	int i;
	int end;
	int during_time = 0;//the running time
	T_nil = (struct tree_node *)malloc(sizeof(struct tree_node));
	T = (struct tree_node *)malloc(sizeof(struct tree_node));
	T->parent = NULL;
	T_nil->color = 0;
	T_nil->left = NULL;
	T_nil->right = NULL;
	T_nil->parent = NULL;
	T_nil->key = 0;
	T_nil->rank = 0;
	srand(time(0));
	for(i=0;i<1000;i++)
	{
		keyr = rand()%1000000+1;
		if(T->parent == NULL)
		{
			T->parent = T_nil;
			T->key = keyr;
			T->left = T_nil;
			T->right = T_nil;
			T->color = 0;
			T->rank = 1;
		}
		else T = insert_BRT(T,keyr);
	}
	printf("the running time is %d\n",t);
	t = 0;
	printf("the maximum value of the RBT:");
	maximam_RBT(T);
	t = 0;
	printf("the minimum value of the RBT:");
	sr = minimum_RBT(T);
	t = 0;
	printf("the successor of the root:");
	latter_RBT(T);
	t = 0;
	printf("the previous value of the root:");
	former_RBT(T);
	t = 0;
	printf("the successor of the left child of the root:");
	latter_RBT(T->left);
	t = 0;
	printf("the previous value of the left child of the root:");
	former_RBT(T->left);
	t = 0;
	printf("middle sequence sortion of the RBT");
    search(T);
    printf("the running time is %d\n",t);
	t = 0;
    printf("the 50th number of the RBT");
    rank_selection_RBT(T,50);
    printf("the running time is %d\n",t);
	t = 0;
    printf("delete the minimun value of the RBT,");
	T = delete_BRT(sr,T);
	printf("the running time is %d\n",t);
	t = 0;
	printf("after delete the minimun value in RBT,the RBT is like this: \n");
	search(T);
    printf("the running time is %d\n",t);
	t = 0;
	printf("the 50th number of the RBT");
	rank_selection_RBT(T,50);
    printf("the running time is %d\n",t);
	t = 0;
	printf("---------------------------------------------------\n");
	return 0;
}