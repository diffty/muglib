#include "../src/utils/strings.h"


int main() {
    String testStr = str_create_string(0, 4);

    str_set_string(&testStr, "testpipi");
    printf("%s\n", testStr.data);
    str_set_string(&testStr, "oui");
    printf("%s\n", testStr.data);
    str_set_string(&testStr, "CACACACACACACACA");
    printf("%s\n", testStr.data);
    str_set_string(&testStr, "oko1");
    printf("%s\n", testStr.data);
    str_set_string(&testStr, "OMG????????");
    printf("%s\n", testStr.data);
    str_set_string(&testStr, "");
    printf("%s\n", testStr.data);
    str_set_string(&testStr, "Jacques Chirac (/ʒak ʃiʁak/b Écouter), né le 29 novembre 1932 dans le 5e arrondissement de Paris et mort le 26 septembre 2019 dans le 6e arrondissement de la même ville, est un haut fonctionnaire et homme d'État français. Il est Premier ministre de 1974 à 1976, puis de 1986 à 1988, et président de la République de 1995 à 2007.");
    printf("%s\n", testStr.data);
    str_set_string(&testStr, "proutent^^");
    printf("%s\n", testStr.data);
    str_free_string(&testStr);

    return 0;
}
