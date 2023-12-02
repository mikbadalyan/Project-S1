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

/**
 * @brief This function inserts values to each node of a binary search tree. We have to give some parameters to the function.
 * 
 * @param root This is a binary search tree node which contains some values in it related to solar panels.
 * @param power This parameter is the power of each solar panel (the unit of measure is watt).
 * @param quantity This parameter gets the quantity of each type of solar panel which the seller company wanted to preorder
 * @param size This parameter is the size of panels (The measure of unit is meter square)
 * @param price_for_selling This parameter is the prise of the panel which the manufacturing company sells the seller company. (the measure of unit is AMD)
 * @param price_for_producing This parameter is the prise of the panel which the manufacturing company spend to produce it. (the measure of unit is AMD)
 * @return int if all the parameters are true and the function is working, it returns 0.
 */

int insert(struct Type_Of_Panel **root, int power, int quantity, float size, int price_for_selling, int price_for_producing) {
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
    insert(&((*root)->left), power, quantity, size, price_for_selling, price_for_producing);
  } else if (power > (*root)->power) {
    insert(&((*root)->right), power, quantity, size, price_for_selling, price_for_producing);
  } else {
    return -1;
  }

  return 0;
}

int count_of_lines(char * buf, int bytes, int ss, int niqanak, int * qn){
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

//     for (int i = 0; i < bytes; ++i) {
//     printf("%d", qn[i]);
//   }
    return 0;
}

int main() {
  //Reading data from the file and storing it in a buffer.
  char buf[N];
  int fd = open("ordered_data.txt", O_RDONLY);
  if (-1 == fd) {
    perror("Cannot open file");
    return errno;
  }
  // This function reads the file (only N bytes), stores it in a buffer.
  ssize_t bytes = read(fd, buf, N);
  if (-1 == bytes) {
    perror("Cannot read file");
    return errno;
  }
  //We have to write '\0' so as not to get some random values which could affect our code. 
  buf[bytes] = '\0';
  close(fd);

//   for (int i = 0; i < bytes; ++i) {
//     printf("%c", buf[i]);
//   }
  
  int ss = 0;
  int niqanak = 0;
  int qn[10];
  count_of_lines(buf, bytes, ss, niqanak,qn);
  

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
    if (buf[i] == '\n' && buf[i + 1] != '\n') {
      ++tox;
    }
    if (isdigit(buf[i])) {
      continue;
    } else if (isdigit(buf[i + 1]) && (buf[i] != '.')) {
      
      if (tox == 0) {
        k = k + 1;
        powe[k] = atoi(&buf[i + 1]);
      } else if (tox == 1) {

        quant[q] = atoi(&buf[i + 1]);
        ++q;
      } else if (tox == 2) {
        char*end;
        size[qq] = strtod(&buf[i + 1], &end);
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

        char*endd;
        size_1[aa] = strtod(&buf[i + 1], &endd);
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

  powe[k + 1] = '\0';
  quant[q + 1] = '\0';
  size[qq + 1] = '\0';
  price_seller[qqq + 1] = '\0';
  price_producing[qqqq + 1] = '\0';
  quant_1[a + 1] = '\0';
  size_1[aa + 1] = '\0';
  pr_1[aaa + 1] = '\0';
  pr_2[aaaa + 1] = '\0';
  for (int i = 0; i < aaa; ++i) {
    printf("%.2f   ", size_1[i]);
  }

  struct Type_Of_Panel *root = 0;

  insert(&root, 10, 2, 4, 5, 6);

  return 0;
}