#include <stdio.h>

#include "cdict.h"

int main() {
    Dict *fruit_price = dict_create();

    dict_add(fruit_price, "Apple", "4500");
    dict_add(fruit_price, "Banana", "3000won");
    dict_add(fruit_price, "Pear (Delicious!)", "133$");
    dict_add(fruit_price, "Maybe grape?", "N/A");
    dict_add(fruit_price, "Watermelon", "Out of stock");

    const char *banana_price = dict_get(fruit_price, "Banana");
    if (banana_price)
        printf("Price of Banana: %s\n", banana_price);
    else
        printf("Can't find price of Banana\n");

    const char *apple_price = dict_get(fruit_price, "apple");
    if (apple_price)
        printf("Price of apple: %s\n", apple_price);
    else
        printf("Can't find price of apple\n");


    dict_delete(fruit_price, "Watermelon");
    dict_delete(fruit_price, "Watermelon");
    dict_delete(fruit_price, "Maybe grape?");

    dict_dump(fruit_price, stdout);

    dict_destroy(fruit_price);

    return 0;
}