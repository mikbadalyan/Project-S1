#include <ctype.h>

#include <errno.h>

#include <fcntl.h>

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <string.h>

#define N 5000
// We have mainly 26 types of panels depending on the power and size.
struct Type_Of_Panel {
    int power;
    int quantity;
    float size;
    int price_for_selling;
    int price_for_producing;
    int profit;
    long int polysilicon;
    double silver;
    double aluminum;
    struct Type_Of_Panel *left, *right;
};

/**
 * @brief This function inserts values to each node of a binary search tree. We
 * have to give some parameters to the function.
 *
 * @param root This is a binary search tree node which contains some values in
 * it related to solar panels.
 * @param power This parameter is the power of each solar panel (the unit of
 * measure is watt).
 * @param quantity This parameter gets the quantity of each type of solar panel
 * which the seller company wanted to preorder
 * @param size This parameter is the size of panels (The measure of unit is
 * meter square)
 * @param price_for_selling This parameter is the prise of the panel which the
 * manufacturing company sells the seller company. (the measure of unit is AMD)
 * @param price_for_producing This parameter is the prise of the panel which the
 * manufacturing company spend to produce it. (the measure of unit is AMD)
 * @return int if all the parameters are true and the function is working, it
 * returns 0, otherwise -1.
 */

int insert(struct Type_Of_Panel **root, int power, int quantity, float size,
           int price_for_selling, int price_for_producing) {
    if (0 == *root) {
        *root = (struct Type_Of_Panel *)malloc(sizeof(struct Type_Of_Panel));
        (*root)->power = power;
        (*root)->quantity = quantity;
        (*root)->size = size;
        (*root)->price_for_selling = price_for_selling;
        (*root)->price_for_producing = price_for_producing;
        (*root)->profit =
            (*root)->quantity * (price_for_selling - price_for_producing);
        (*root)->polysilicon = (*root)->power * 8 * (*root)->quantity;
        (*root)->silver = (*root)->power * 0.07 * (*root)->quantity;
        (*root)->aluminum = (*root)->size * 2000 * (*root)->quantity;
        (*root)->left = 0;
        (*root)->right = 0;
    } else if (power < (*root)->power) {
        insert(&((*root)->left), power, quantity, size, price_for_selling,
               price_for_producing);
    } else if (power > (*root)->power) {
        insert(&((*root)->right), power, quantity, size, price_for_selling,
               price_for_producing);
    } else if (power == (*root)->power && size == (*root)->size) {
        (*root)->quantity = (*root)->quantity + quantity;
        (*root)->profit =
        (*root)->quantity * (price_for_selling - price_for_producing);
        (*root)->polysilicon = (*root)->power * 8 * (*root)->quantity;
        (*root)->silver = (*root)->power * 0.07 * (*root)->quantity;
        (*root)->aluminum = (*root)->size * 2000 * (*root)->quantity;
    } else {
        return -1;
    }

    return 0;
}


/**
 * @brief This function is for counting the lines of the file and the bytes of each line.
 * 
 * @param buf is used for analysing the file content where all data of solar panels are stored.
 * @param bytes has the value of all bytes in data file.
 * @param bytes_per_line is the number of all bytes in the current line. It gets 0 value after counting the bytes of that line.
 * @param niqanak is the number of new lines in a code, if there is at least 2 characters.
 * @param arr_bytes is an array that stores the quantity of bytes in each line. 
 * @return int The return value is 0 which indicates that the function has ended.
 */
int count_of_lines(char * buf, int bytes, int bytes_per_line, int niqanak, int * arr_bytes) {
    for (int j = 0; j < bytes; ++j) {
        if (buf[j] != ' ') {
            if (buf[j] == '\n' || j == bytes - 1) {

                if (bytes_per_line > 1) {

                    arr_bytes[niqanak] = bytes_per_line;
                    printf("%d\n", arr_bytes[niqanak]);
                    ++niqanak;
                }
                bytes_per_line = 0;
            }
            ++bytes_per_line;
        }
    }


    return 0;
}

/**
 * @brief Using this function and giving the proper parameters we get 2 most profitable solar panels.
 * 
 * @param root is the binary search tree which contains the data of solar panels.
 * @param profitab is the array which has 2 elements. It stores the profits from two most profitable two solar panels.
 * @return int It returns 0 when when all parameters are given properly and function has ended.
 */
int profitable(struct Type_Of_Panel **root, int * profitab) {
    if (0 != (*root)->left) {
        profitable(&(*root)->left, profitab);
    }
    if (0 != (*root)->right) {
        profitable(&(*root)->right, profitab);
    }
    if ((*root)->profit > profitab[0]) {
        profitab[1] = profitab[0];
        profitab[0] = (*root)->profit;
    }

    return 0;
}


/**
 * @brief Using this function and giving the proper parameters we get 2 most profitable solar panels.
 * 
 * @param root is the binary search tree which contains the data of solar panels.
 * @param most_quantity is an array which has 2 elements. It stores the quantities from two solar panels which have more demand.
 * @return int It returns 0 when when all parameters are given properly and function has ended.
 */
int most(struct Type_Of_Panel **root, int * most_quantity) {
    if (0 != (*root)->left) {
        most(&(*root)->left, most_quantity);
    }
    if (0 != (*root)->right) {
        most(&(*root)->right, most_quantity);
    }
    if ((*root)->quantity > most_quantity[0]) {
        most_quantity[1] = most_quantity[0];
        most_quantity[0] = (*root)->quantity;
    }

    return 0;
}

/**
 * @brief This function gets some data from the binary search tree
 * 
 * @param root is the given binary search tree
 * @param profitab is the array which has 2 profits.
 * @param prof_power is the data from the binary search tree for the first element of profitab.
 * @param prof_quantity is the data from the binary search tree for the first element of profitab.
 * @param prof_size is the data from the binary search tree for the first element of profitab.
 * @param prof2_power is the data from the binary search tree for the second element of profitab.
 * @param prof2_quantity is the data from the binary search tree for the second element of profitab.
 * @param prof2_size is the data from the binary search tree for the second element of profitab.
 * @return int The function returns 0 when when all parameters are given properly and function has ended.
 */
int get(struct Type_Of_Panel **root, int *profitab, char * prof_power, char * prof_quantity,
        char * prof_size, char * prof2_power, char *prof2_quantity, char *prof2_size) {
    if (0 != (*root)->left) {
        get(&(*root)->left, profitab, prof_power, prof_quantity, prof_size, prof2_power, prof2_quantity, prof2_size);
    }
    if (0 != (*root)->right) {
        get(&(*root)->right, profitab, prof_power, prof_quantity, prof_size, prof2_power, prof2_quantity, prof2_size);
    }
    if (profitab[0] == (*root)->profit) {
        sprintf(prof_power, "%d", (*root)->power);
        sprintf(prof_size, "%f", (*root)->size);
        sprintf(prof_quantity, "%d", (*root)->quantity);
    }
    if (profitab[1] == (*root)->profit) {
        sprintf(prof2_power, "%d", (*root)->power);
        sprintf(prof2_size, "%f", (*root)->size);
        sprintf(prof2_quantity, "%d", (*root)->quantity);
    }
    return 0;
}

/**
 * @brief This function gets some data from the binary search tree
 * 
 * @param root is the given binary search tree
 * @param most_quantity is the array which has 2 values of solar panel quantities.
 * @param prof_power is the data from the binary search tree for the first element of most_quantity.
 * @param prof_quantity is the data from the binary search tree for the first element of most_quantity.
 * @param prof_size is the data from the binary search tree for the first element of most_quantity.
 * @param prof2_power is the data from the binary search tree for the second element of most_quantity.
 * @param prof2_quantity is the data from the binary search tree for the second element of most_quantity.
 * @param prof2_size is the data from the binary search tree for the second element of most_quantity.
 * @return int The function returns 0 when when all parameters are given properly and function has ended.
 */
int get_quantity(struct Type_Of_Panel **root, int *most_quantity, char * prof_power, char * prof_quantity,
        char * prof_size, char * prof2_power, char *prof2_quantity, char *prof2_size) {
    if (0 != (*root)->left) {
        get_quantity(&(*root)->left, most_quantity, prof_power, prof_quantity, prof_size, prof2_power, prof2_quantity, prof2_size);
    }
    if (0 != (*root)->right) {
        get_quantity(&(*root)->right, most_quantity, prof_power, prof_quantity, prof_size, prof2_power, prof2_quantity, prof2_size);
    }
    if (most_quantity[0] == (*root)->quantity) {
        sprintf(prof_power, "%d", (*root)->power);
        sprintf(prof_size, "%f", (*root)->size);
        sprintf(prof_quantity, "%d", (*root)->quantity);
    }
    if (most_quantity[1] == (*root)->quantity) {
        sprintf(prof2_power, "%d", (*root)->power);
        sprintf(prof2_size, "%f", (*root)->size);
        sprintf(prof2_quantity, "%d", (*root)->quantity);
    }
    return 0;
}


/**
 * @brief This function counts all raw material which are neccessary to manifacture solar panels. 
 * 
 * @param root is the given binary search tree
 * @param polysilicon stores the data of the quantity of polysillicon in it.
 * @param silver stores the data of the quantity of silver in it.
 * @param aluminum stores the data of the quantity of aluminum in it.
 * @return int The function returns 0 when when all parameters are given properly and function has ended.
 */
int check_raw_material(struct Type_Of_Panel **root, long int * polysilicon,
                       double * silver, double * aluminum) {

    if (0 != (*root)->left) {
        check_raw_material(&(*root)->left, polysilicon, silver, aluminum);
    }
    if (0 != (*root)->right) {
        check_raw_material(&(*root)->right, polysilicon, silver, aluminum);
    }

    *polysilicon = *polysilicon + (*root)->polysilicon;
    *silver = *silver + (*root)->silver;
    *aluminum = *aluminum + (*root)->aluminum;

    return 0;
}


/**
 * @brief This function frees all allocated memory to prevent memory leak.
 * 
 * @param root is the given binary search tree.
 * @return int The function returns 0 when all binary search tree nodes are freed.
 */
int free_bst(struct Type_Of_Panel **root) {
    if (0 != (*root)->left) {
        free_bst(&(*root)->left);
    }
    if (0 != (*root)->right) {
        free_bst(&(*root)->right);
    }
    free((*root));

    return 0;
}

int main() {
    // Reading data from the file and storing it in a buffer.
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
    // We have to write '\0' so as not to get some random values which could
    // affect our code.
    buf[bytes] = '\0';
    close(fd);

// This part is for declareing and defining variables.
    int bytes_per_line = 0;
    int niqanak = 0;
    int arr_bytes[10];
    
    count_of_lines(buf, bytes, bytes_per_line, niqanak, arr_bytes);

    int powe[arr_bytes[0]];
    int quant[arr_bytes[1]];
    float size[arr_bytes[2]];
    int price_seller[arr_bytes[3]];
    int price_producing[arr_bytes[4]];

    int power_coef = -1;
    int q = 0;
    int qq = 0;
    int qqq = 0;
    int qqqq = 0;
    int row = 0;

    int quant_1[arr_bytes[5]];
    float size_1[arr_bytes[6]];
    int pr_1[arr_bytes[7]];
    int pr_2[arr_bytes[8]];

    int a = 0;
    int aa = 0;
    int aaa = 0;
    int aaaa = 0;
    
  //Storing the data of the buffer in separate arrays. Each line of the file is in one array.
    if (isdigit(buf[0])) {
        powe[0] = atoi(&buf[0]);
        power_coef = 0;
    }
    for (int i = 0; i < bytes; ++i) {
        if (buf[i] == '\n' && buf[i + 1] != '\n') {
            ++row;
        }
        if (isdigit(buf[i])) {
            continue;
        } else if (isdigit(buf[i + 1]) && (buf[i] != '.')) {

            if (row == 0) {
                power_coef = power_coef + 1;
                powe[power_coef] = atoi(&buf[i + 1]);

            } else if (row == 1) {

                quant[q] = atoi(&buf[i + 1]);
                ++q;

            } else if (row == 2) {
                char *end;
                size[qq] = strtod(&buf[i + 1], &end);
                ++qq;
            } else if (row == 3) {

                price_seller[qqq] = atoi(&buf[i + 1]);
                ++qqq;
            } else if (row == 4) {

                price_producing[qqqq] = atoi(&buf[i + 1]);
                ++qqqq;
            } else if (row == 5) {

                quant_1[a] = atoi(&buf[i + 1]);
                ++a;
            } else if (row == 6) {

                char *endd;
                size_1[aa] = strtod(&buf[i + 1], &endd);
                ++aa;
            } else if (row == 7) {

                pr_1[aaa] = atoi(&buf[i + 1]);
                ++aaa;
            } else if (row == 8) {

                pr_2[aaaa] = atoi(&buf[i + 1]);
                ++aaaa;
            }
        }
    }

    ++power_coef;
    powe[power_coef] = '\0';
    quant[q] = '\0';
    size[qq] = '\0';
    price_seller[qqq] = '\0';
    price_producing[qqqq] = '\0';
    quant_1[a] = '\0';
    size_1[aa] = '\0';
    pr_1[aaa] = '\0';
    pr_2[aaaa] = '\0';

    struct Type_Of_Panel *acc_to_power = 0;
    struct Type_Of_Panel *acc_to_second = 0;
//Inserting data into the binary search trees.
    for (int i = 0; i < power_coef; ++i) {
        insert(&acc_to_power, powe[i], quant[i], size[i], price_seller[i],
               price_producing[i]);
    }

    for (int j = 0; j < power_coef; ++j) {
        insert(&acc_to_second, powe[j], quant_1[j], size_1[j], pr_1[j],
               pr_2[j]);
    }

//Getting 2 most profitable order requests.
    int profitab[2];
    profitab[0] = 0;
    profitab[1] = 0;
    profitable(&acc_to_power, profitab);
    profitable(&acc_to_second, profitab);
    printf("%d,,,,,,,%d", profitab[0], profitab[1]);

//Getting 2 solar panels quantities which have more demand.
    int most_quantity[4];
    most_quantity[0] = 0;
    most_quantity[1] = 0;
    most(&acc_to_power, most_quantity);
    most(&acc_to_second, most_quantity);

    printf("\n %d", most_quantity[0]);
    printf("\n %d", most_quantity[1]);
//Storing all raw material data in variables.
    long int total_polysillicon;
    double total_silver;
    double total_aluminum;

    check_raw_material(&acc_to_power, &total_polysillicon, &total_silver, &total_aluminum);
    check_raw_material(&acc_to_second, &total_polysillicon, &total_silver, &total_aluminum);

    long int warehouse_polysilicon = 242000000;
    double warehouse_silver = 1800500;
    double warehouse_aluminum = 131000000;

    char prof_power[4];
    char prof_quantity[5];
    char prof_size[7];
    char prof2_power[4];
    char prof2_quantity[5];
    char prof2_size[7];
    get(&acc_to_power, profitab, prof_power, prof_quantity, prof_size, prof2_power, prof2_quantity, prof2_size);
    get(&acc_to_second, profitab, prof_power, prof_quantity, prof_size, prof2_power, prof2_quantity, prof2_size);
    int filedescriptor = open("result.txt", O_WRONLY | O_APPEND);
    if (-1 == filedescriptor) {
        perror("Cannot open file");
        return errno;
    }

    // This part writes the data in a file.
    
    write(filedescriptor, "\n ------------------------------------------------ \n", 53);
    write(filedescriptor, "\n Production Line 2 \n", 20);
    write(filedescriptor, "\nSolar Panel 1 \n", 17);
    ssize_t text_bytes = write(filedescriptor, prof_power, 4);
    write(filedescriptor, "\n", 1);
    ssize_t tex_bytes = write(filedescriptor, prof_quantity, 5);
    write(filedescriptor, "\n", 1);
    ssize_t tet_bytes = write(filedescriptor, prof_size, 7);
    write(filedescriptor, "\n\n\nSolar Panel 2 \n", 18);
    ssize_t t_bytes = write(filedescriptor, prof2_power, 4);
    write(filedescriptor, "\n", 1);
    ssize_t tess_bytes = write(filedescriptor, prof2_quantity, 5);
    write(filedescriptor, "\n", 1);
    ssize_t tetss_bytes = write(filedescriptor, prof2_size, 7);
    if (-1 == bytes) {
        perror("Cannot read file");
        return errno;
    }

    // Checking the availability of these raw materials.
    if (warehouse_polysilicon >= total_polysillicon) {
        write(filedescriptor,
              "\n\n\n The polysillicon quantity in the warehouse is sufficient "
              "for tomorrows production line.",
              91);
    } else {
        write(filedescriptor,
              "\n\n\n The polysillicon quantity in the warehouse isn't "
              "sufficient for tomorrow's production line.",
              95);
    }
    if (warehouse_silver >= total_silver) {
        write(filedescriptor,
              "\n\n\n The silver quantity in the warehouse is sufficient for "
              "tomorrow's production line.",
              86);
    } else {
        write(filedescriptor,
              "\n\n\n The silver quantity in the warehouse is not sufficient "
              "for tomorrow's production line.",
              90);
    }
    if (warehouse_aluminum >= total_aluminum) {
        write(filedescriptor,
              "\n\n\n The aluminum quantity in the warehouse is sufficient for "
              "tomorrow's production line.",
              88);
    } else {
        write(filedescriptor,
              "\n\n\n The aluminum quantity in the warehouse is not sufficient "
              "for tomorrow's production line.",
              92);
    }
    
    
    //Writing 2 solar panel data in a file which are in high demand.
    get_quantity(&acc_to_power, most_quantity, prof_power, prof_quantity, prof_size, prof2_power, prof2_quantity, prof2_size);
    get_quantity(&acc_to_second, most_quantity, prof_power, prof_quantity, prof_size, prof2_power, prof2_quantity, prof2_size);
    
    
    write(filedescriptor, "\n ------------------------------------------------ \n", 53);
    write(filedescriptor, "\n Production Line 3 \n", 20);
    write(filedescriptor, "\nSolar Panel 1 \n", 17);
    ssize_t text3_bytes = write(filedescriptor, prof_power, 4);
    write(filedescriptor, "\n", 1);
    ssize_t tex3_bytes = write(filedescriptor, prof_quantity, 5);
    write(filedescriptor, "\n", 1);
    ssize_t tet3_bytes = write(filedescriptor, prof_size, 7);
    write(filedescriptor, "\n\n\nSolar Panel 2 \n", 18);
    ssize_t t3_bytes = write(filedescriptor, prof2_power, 4);
    write(filedescriptor, "\n", 1);
    ssize_t tess3_bytes = write(filedescriptor, prof2_quantity, 5);
    write(filedescriptor, "\n", 1);
    ssize_t tetss3_bytes = write(filedescriptor, prof2_size, 7);    
    
    
    



    close(fd);

    free_bst(&acc_to_power);
    free_bst(&acc_to_second);
    return 0;
}