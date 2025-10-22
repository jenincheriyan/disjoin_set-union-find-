#include <stdio.h>
#include <stdlib.h>



int parent[100];
int rankArr[100];
int elements[100]; 
int n;


int getIndex(int val) {
    for (int i = 0; i < n; i++)
        if (elements[i] == val)
            return i;
    return -1;
}


void makeSet() {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rankArr[i] = 0;
    }
}


int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}


void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) {
        printf("Elements %d and %d are already in the same set.\n", elements[x], elements[y]);
        return;
    }

    if (rankArr[rootX] < rankArr[rootY])
        parent[rootX] = rootY;
    else if (rankArr[rootX] > rankArr[rootY])
        parent[rootY] = rootX;
    else {
        parent[rootY] = rootX;
        rankArr[rootX]++;
    }

    printf("Union done between %d and %d\n", elements[x], elements[y]);
}

void displaySet(){
    for (int i =0; i<n;i++){
        printf("{%d}\n", elements[i]);
    }
}
void displayAllSet(){
    for (int i=0;i<n;i++){
      if(parent[i]==i){
        int value=parent[i];
        printf("{");
            for(int j=0;j<n;j++){
                if(parent[j]==value){
                printf("%d,", elements[j]);
                }
            }
        printf("}\n");
        }
    }

}
void displayParents() {
    printf("Representative:\n");
    for (int i = 0; i < n; i++){
        if(parent[i]==i){
            printf("{%d}\n", elements[parent[i]]);
        }
    }
}

int main() {
    int choice, xVal, yVal, idxX, idxY;

    printf("Enter number of elements in the set: ");
    scanf("%d", &n);

    printf("Enter the elements of the set:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &elements[i]);
    }

    makeSet();
    printf("Disjoint set created with %d elements.\n", n);

    while (choice!=4) {
        printf("1. Union\n");
        printf("2. Find\n");
        printf("3. Display parent array\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter two elements to union: ");
                scanf("%d %d", &xVal, &yVal);
                idxX = getIndex(xVal);
                idxY = getIndex(yVal);
                if (idxX != -1 && idxY != -1)
                    unionSets(idxX, idxY);
                else
                    printf("Invalid elements.\n");
                break;

            case 2:
                printf("Enter element to find its representative: ");
                scanf("%d", &xVal);
                idxX = getIndex(xVal);
                if (idxX != -1) {
                    int rep = find(idxX);
                    printf("Representative of %d is %d\n", xVal, elements[rep]);
                } else
                    printf("Invalid element.\n");
                break;

            case 3:
                displayParents();
                break;

            case 4:
                printf("Exiting program.\n");
                choice=0;
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
