#include <stdio.h>
#include <math.h>
#include "the1.h"

/*
 * This function gets a parameter that indicates whether user will give initial values or not. If it evaluates false,
 * you will simply set all values of thearray -1. Otherwise, you will scan an integer from the user stating the number
 * of values that s/he willenter. User will enter that many integer index and value pairs. If the value for that index
 * is insertedbefore, or the index or the value is out of the range, you will simply ignore it.
*/
void initialize_the_tree(int binary_tree[MAX_LENGTH], int get_values_from_user) {
    int i,val_num,index;
    float value;
    for (i = 0;i <= MAX_LENGTH;i++){
        binary_tree[i] = -1;
    }
    if (get_values_from_user =! 0) {
        scanf("%d",&val_num);
        while (val_num > 0){
            val_num--;
            scanf("%d %f",&index,&value);
            if (binary_tree[index] == value || index < 0 || index > MAX_LENGTH ||value < MIN_VAL || value > MAX_VAL ){
                continue;
            }
            else {
                binary_tree[index] = value;
            }
            
        }
        
    }
    
}



/*
 * This function gets index of parent node, 'l'eft, 'r'ight or 'i'tself for where to insert and integer value.
 * If the value for the inserted node already exists, it ignores and does nothing.
 */
void insert_node(int binary_tree[MAX_LENGTH], int node, char where, int value) {

    if (where == 'l' && binary_tree[2*node+1] == -1 && 2*node+1 < MAX_LENGTH){
        binary_tree[2*node+1] = value;
    }
    else if (where == 'r' && binary_tree[2*node+2] == -1 && 2*node+2 < MAX_LENGTH){
        binary_tree[2*node+2] = value;
    }
    else if (where == 'i' && binary_tree[node] == -1 && node < MAX_LENGTH){
        binary_tree[node] = value;
    }
}


/*
 * This method  gets  the  index  of  the  node  to  be  deleted.   If  a  node  is  to  be deleted, all of its
 * descendants will be also purged.  Deleting means putting -1 value to the proper area in the array.
 */
void delete_node_rec(int binary_tree[MAX_LENGTH], int node) {
    if (node < MAX_LENGTH && binary_tree[node] != -1){
        binary_tree[node] = -1;
        delete_node_rec(binary_tree,2*node+1);
        delete_node_rec(binary_tree,2*node+2);
    }

    
}


/*
 * This is  a recursive function that prints the tree in in-order fashion. In other words, it will print the nodes 
 * starting from the left-most child and traverse the rest of the tree in that manner. Printing order will be 
 * <left-child, root, right-child>. It gets the index of the root and the depth value as control variable. Initial 
 * value of the depth will be the height of the tree. Be careful, any sub-tree can be given to the function.
 */
void tabgiver(int depth){

    if (depth > 0){
        printf("\t");
        tabgiver(depth-1);
    }
}
void draw_binary_tree_rec(int binary_tree[MAX_LENGTH], int root, int depth) {
    if (binary_tree[root] != -1 && root < MAX_LENGTH){
        draw_binary_tree_rec(binary_tree,2*root+1,depth-1);
        tabgiver(depth);
        printf("%d\n",binary_tree[root]);
        draw_binary_tree_rec(binary_tree,2*root+2,depth-1);
    }
    
}


/*
 * This is a recursive function that returns the height of the tree.  If given root does not have any child, its height
 * is 0.  Be careful, any sub-tree can be given to the function
 */

int find_height_of_tree_rec(int binary_tree[MAX_LENGTH], int root) {
    int left,right;
    if ((binary_tree[2*root+1] == -1 && binary_tree[2*root+2] == -1) || 2*root+1 > MAX_LENGTH ){
        return 0;
    }
    else {
        if (2*root+1 < MAX_LENGTH){
            left = find_height_of_tree_rec(binary_tree, 2*root+1);
        }
        if (2*root+2 < MAX_LENGTH){
            right = find_height_of_tree_rec(binary_tree, 2*root+2);
        }
        if (left > right) {
           return(left+1); 
        }
        else{
            return(right+1); 
       }
    }
    
}


/*
 * This is a recursive function that returns the minimum value given tree contains.
 * Be careful, any sub-tree can be given to the function.
 */
int minimizer(int binary_tree[MAX_LENGTH], int root, int min){
    if (root >= MAX_LENGTH){
        return min;
    }
    else if (binary_tree[root] < min && binary_tree[root] != -1){
        min = binary_tree[root];

    }
    return MIN(minimizer(binary_tree, 2*root+1, min),minimizer(binary_tree, 2*root+2, min));
}


int find_min_of_tree_rec(int binary_tree[MAX_LENGTH], int root) {
    return minimizer(binary_tree, root, MAX_VAL);
    
}

/*
 * This is an iterative function that performs breadth-first search on the given tree.  If the value does not appear
 * in the given tree,  it returns -1.  Otherwise,  it returns the index of the first observation of the value.
 * It gets the index of the root and the integer value that is to be searched.  Be careful, any sub-tree can be given to
 * the function and you will apply level-wise search in the tree
 */
int breadth_first_search_itr(int binary_tree[MAX_LENGTH], int root, int value) {
    int i,i0,root0;
    for (i = 1;; i = i*2){
        i0 = i;
        root0 = root;
        while (i > 0){
            if (root > MAX_LENGTH){
                return -1;
            }
            else if (binary_tree[root] == value){
                return root;
            }
            else{
                root++;
                i--;
            
            }
        }
        root = 2*root0+1;
        i = i0;
    }
}

/*
 * This is  a  recursive  function  that  performs  depth-first search on the given tree.  If the value does not appear
 * in the given tree,  it returns -1.  Otherwise,  itreturns the index of the first observation of the value.  It gets
 * the index of the root and the integer valuethat is to be searched.
 * Be careful, any sub-tree can be given to the function.
 */


int depth_first_search_rec(int binary_tree[MAX_LENGTH], int root, int value) {
    if (binary_tree[root] == -1){
        return -1;
    }
    depth_first_search_rec(binary_tree,2*root+1,value);
    if (binary_tree[root] == value){
        return root;
    }


    else if (depth_first_search_rec(binary_tree,2*root+1,value) == -1){
        depth_first_search_rec(binary_tree,2*root+2,value);
    }
    
    else if (root > MAX_LENGTH){
        return -1;
    }



}

/*
 * This is already given to you.
 */
void print_binary_tree_values(int binary_tree[MAX_LENGTH]) {
    int i;
    for (i = 0; i < MAX_LENGTH; i++) {
        if (binary_tree[i] != -1) {
            printf("%d - %d\n", i, binary_tree[i]);
        }
    }

}
