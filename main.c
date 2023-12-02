#include <ctype.h>

#include <errno.h>

#include <fcntl.h>

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#define N 5000
// We have mainly 26 types of panels depending on the power and size.
struct Type_Of_Panel {
    int power;
    int quantity;
    float size;
    int price_for_selling;
    int price_for_producing;
    struct Type_Of_Panel *left, *right;
};


int insert(struct Type_Of_Panel **root, int power, int quantity, float size,
           int price_for_selling, int price_for_producing) {
    if (0 == *root) {
        *root = (struct Type_Of_Panel *)malloc(sizeof(struct Type_Of_Panel));
        (*root)->power = power;
        (*root)->quantity = quantity;
        (*root)->size = size;
        (*root)->price_for_selling = price_for_selling;
        (*root)->price_for_producing = price_for_producing;
        (*root)->left = 0;
        (*root)->right = 0;
    } else if (power < (*root)->power) {
        insert(&((*root)->left), power, quantity, size, price_for_selling,
               price_for_producing);
    } else if (power > (*root)->power) {
        insert(&((*root)->right), power, quantity, size, price_for_selling,
               price_for_producing);
    } else {
        return -1;
    }

    return 0;
}

int main() {
    //Ֆայլից կարդալ գցել buf զանգվածի մեջ
    char buf[N];
    int fd = open("data.txt", O_RDONLY);
    if (-1 == fd) {
        perror("Cannot open file");
        return errno;
    }
    ssize_t bytes = read(fd, buf, N);
    if (-1 == bytes) {
        perror("Cannot read file");
        return errno;
    }
    buf[bytes] = '\0';
    close(fd);

    //Հաշվել տողերի bytes-ի քանակը
    int ss = 0;
    int niqanak = 0;
    int qn[10];
    for (int j = 0; j < bytes; ++j) {
        if (buf[j] != ' ') {
            if (buf[j] == '\n') {
                
                if (ss > 1) {
                    qn[niqanak] = ss;
                    printf("%d\n", qn[niqanak]);
                    ++niqanak;
                }
                
                ss = 0;
            }
            ++ss;
        }
    }

    int powe[qn[0]];
    int quant[qn[1]];
    float size[qn[2]];
    int price_seller[qn[3]];
    int price_producing[qn[4]];
    int k = -1;
    int q = 0;
    int qq = 0;
    int qqq = 0;
    int qqqq = 0;
    int tox = 0;
    int quant_1[qn[5]];
    float size_1[qn[6]];
    int pr_1[qn[7]];
    int pr_2[qn[8]];

    int aa = 0;
    int aaa = 0;
    int aaaa = 0;
    int a = 0;

    if (isdigit(buf[0])) {
        powe[0] = atoi(&buf[0]);
        k = 0;
    }
    for (int i = 0; i < bytes; ++i) {
        if (isdigit(buf[i])) {
            continue;
        } else if (isdigit(buf[i + 1]) && (buf[i] != '\n')) {
            buf[i] = '\0';
            if (tox == 0) {
                k = k + 1;
                powe[k] = atoi(&buf[i + 1]);
            } else if (tox == 1) {

                quant[q] = atoi(&buf[i + 1]);
                ++q;
            } else if (tox == 2) {

                size[qq] = atoi(&buf[i + 1]);
                ++qq;
            } else if (tox == 3) {

                price_seller[qqq] = atoi(&buf[i + 1]);
                ++qqq;
            } else if (tox == 4) {

                price_producing[qqqq] = atoi(&buf[i + 1]);
                ++qqqq;
            } else if (tox == 5) {

                quant_1[a] = atoi(&buf[i + 1]);
                ++a;
            } else if (tox == 6) {

                size_1[aa] = atoi(&buf[i + 1]);
                ++aa;
            } else if (tox == 7) {

                pr_1[aaa] = atoi(&buf[i + 1]);
                ++aaa;
            } else if (tox == 8) {

                pr_2[aaaa] = atoi(&buf[i + 1]);
                ++aaaa;
            }
        } else if ((isdigit(buf[i + 1]) || isalpha(buf[i+1])) && (buf[i] == '\n')) {
            ++tox;
            buf[i] = '\0';
            if (tox == 0) {
                ++k;
                powe[k] = atoi(&buf[i + 1]);
            } else if (tox == 1) {

                quant[q] = atoi(&buf[i + 1]);
                ++q;
            } else if (tox == 2) {

                size[qq] = atoi(&buf[i + 1]);
                ++qq;
            } else if (tox == 3) {

                price_seller[qqq] = atoi(&buf[i + 1]);
                ++qqq;
            } else if (tox == 4) {

                price_producing[qqqq] = atoi(&buf[i + 1]);
                ++qqqq;
            } else if (tox == 5) {

                quant_1[a] = atoi(&buf[i + 1]);
                ++a;
            } else if (tox == 6) {

                size_1[aa] = atoi(&buf[i + 1]);
                ++aa;
            } else if (tox == 7) {

                pr_1[aaa] = atoi(&buf[i + 1]);
                ++aaa;
            } else if (tox == 8) {

                pr_2[aaaa] = atoi(&buf[i + 1]);
                ++aaaa;
            }
        }
    }


powe[k+1] = '\0';
    for (int i = 0; i < aaa; ++i) {
        // printf("%d    ", powe[i]);

        // printf("%d   ", quant[i]);

        // printf("%d   ", size[i]);

        // printf("%d   ", price_seller[i]);

        printf("%d   ", quant[i]);
    }

    struct Type_Of_Panel *root = 0;

    insert(&root, 10, 2, 4, 5, 6);

    return 0;
}