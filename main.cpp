#include "Funkcje.h"
#include <cstdio>
int main() {
    int n;
    std::scanf("%d", &n);
    std::getchar();

    ExpressionConverter converter;
    for (int i = 0; i < n; ++i) {
        converter.processExpression();
    }

    return 0;
}