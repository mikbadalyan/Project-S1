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

/**
 * @brief This function counts the bytes in each line of the file.
 * 
 * @param bytes This parameter has initial value 0 which stores the bytes in each line. 
 * @param lines This parameter stores the number of lines of the file apart from the lines which contain only letters, spaces, or symbols.
 * @param buf This parameter has every character of the file in itself.
 * @param buf_bytes This is the number of bytes in our file.
 * @param column This array stores the number of bytes of each line.
 * @return int This parameter returns 0 if the function work without any errors.
 */
int count_the_line(int bytes, int lines, char * buf, int buf_bytes, int * column){

    for (int j = 0; j < buf_bytes; ++j) {
        if (buf[j] != ' ') {
            if (buf[j] == '\n') {

                if (bytes > 1) {
                column[lines] = bytes;
                printf("%d\n", column[lines]);
                ++lines;
                }else{
                    continue;
                }

                bytes = 0;
            }else{
                continue;
            }
        ++bytes;
        }else{
            continue;
        }
    }
    return 0;
}


int main() {
  //Reading data from the file and storing it in a buffer.
  char buf[N];
  int fd = open("data.txt", O_RDONLY);
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

  int by_tes = 0;
  int li_nes = 0;
  int column[10];
  count_the_line(by_tes, li_nes, buf, bytes, column);

  int powe[column[0]];
  int quant[column[1]];
  float size[column[2]];
  int price_seller[column[3]];
  int price_producing[column[4]];
  
  int quant_1[column[5]];
  float size_1[column[6]];
  int pr_1[column[7]];
  int pr_2[column[8]];
    int k = -1;
  int q = 0;
  int qq = 0;
  int qqq = 0;
  int qqqq = 0;
  int tox = 0;
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
    } else if (isdigit(buf[i + 1])) {
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
    }
    if (buf[i] == '\n' && buf[i + 1] != '\n') {
      ++tox;
    }
  }

  powe[k + 1] = '\0';
  powe[q + 1] = '\0';
  powe[qq + 1] = '\0';
  powe[qqq + 1] = '\0';
  powe[qqqq + 1] = '\0';
  powe[a + 1] = '\0';
  powe[aa + 1] = '\0';
  powe[aaa + 1] = '\0';
  powe[aaaa + 1] = '\0';
  for (int i = 0; i < aaa; ++i) {
    printf("%d   ", pr_1[i]);
  }

  struct Type_Of_Panel *root = 0;

  insert(&root, 10, 2, 4, 5, 6);

  return 0;
}