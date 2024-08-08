#include <stdio.h>
#include <math.h>
#define MAX 256


int hashFunction(int key){
    double a = 1.0 / 3.14;
    double i;

    double f = modf(key * a, &i);

    float m = 256 * f;

    modf(m, &i);
    int index = (int) i;

    return index;
}

int main(){
    int key;
    scanf("%d", &key);

    int m = hashFunction(key);

    printf("%d\n\n", m);
}