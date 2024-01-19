#include <stdio.h>
#include <stdlib.h>

#include "../src/utils/strings.h"


int main() {
    String testStr = str_create(0, 4);

    str_set(&testStr, "testpipi");
    printf("%s\n", testStr.data);
    str_set(&testStr, "oui");
    printf("%s\n", testStr.data);
    str_set(&testStr, "CACACACACACACACA");
    printf("%s\n", testStr.data);
    str_set(&testStr, "oko1");
    printf("%s\n", testStr.data);
    str_set(&testStr, "OMG????????");
    printf("%s\n", testStr.data);
    str_set(&testStr, "");
    printf("%s\n", testStr.data);
    str_set(&testStr, "Jacques Chirac (/ʒak ʃiʁak/b Écouter), né le 29 novembre 1932 dans le 5e arrondissement de Paris et mort le 26 septembre 2019 dans le 6e arrondissement de la même ville, est un haut fonctionnaire et homme d'État français. Il est Premier ministre de 1974 à 1976, puis de 1986 à 1988, et président de la République de 1995 à 2007.");
    printf("%s\n", testStr.data);
    str_set(&testStr, "proutent^^");
    printf("%s\n", testStr.data);
    str_free(&testStr);
    
    String concatTest = String(0);
    str_concat(&concatTest, "ok");
    str_concat(&concatTest, "oui");
    str_concat(&concatTest, "koiiiiiii");
    printf("%s\n", concatTest.data);
    str_free(&concatTest);

    return 0;
}
