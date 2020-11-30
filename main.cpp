#include <iostream>
#include <time.h>
#include <string>
using namespace std;

struct point{
    int number;
    uint8_t used;
};

int** create_array(int size) {
//    srand(time(NULL));
//    int** array = new int *[size];
//    for (int i = 0; i < size; i++) {
//    array[i] = new int[size];
//        for (int l = 0; l < size; l++) {
//            array[i][l] = rand() % 9 + 1;
//        }
//    }
    int **array = new int *[size];
    for (int i = 0; i < size; i++) {
        array[i] = new int[size];
    }
    array[0][0] = 2500; array[0][1] = 4000; array[0][2] = 3500;
    array[1][0] = 4000; array[1][1] = 6000; array[1][2] = 3500;
    array[2][0] = 2000; array[2][1] = 4000; array[2][2] = 2500;
//    array[0][0] = 1500; array[0][1] = 4000; array[0][2] = 4500;
//    array[1][0] = 2000; array[1][1] = 6000; array[1][2] = 3500;
//    array[2][0] = 2000; array[2][1] = 4000; array[2][2] = 2500;
    return array;
}

void out(int** array, int size){
    cout << "Our Matrix" << endl;
    for (int i = 0; i < size; i++) {
        for (int l = 0; l < size; l++){
            int amount = to_string(array[i][l]).size();
            for (int j = 0; j < 6 - amount; j++){ cout << ' ';}
            cout << array[i][l] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int find_min_in_row(int* array, int size){
    int min = array[0];
    for (int i = 0; i < size; i++) {
        if (array[i] < min) min = array[i];
    }
    return min;
}

int find_min_in_column(int** array, int column_index, int size){
    int min = array[0][column_index];
    for (int i = 0; i < size; i++) {
        if (array[i][column_index] < min) min = array[i][column_index];
    }
    return min;
}

void work_with_rows(int** array, int size){
    for (int i = 0; i < size; i++) {
        int min = find_min_in_row(array[i], size);
        for (int l = 0; l < size; l++) {
           array[i][l] = array[i][l] - min;
        }
    }
}

void work_with_columns(int** array, int size){
    for (int l = 0; l < size; l++) {
        int min = find_min_in_column(array, l, size);
        for (int i = 0; i < size; i++) {
            array[i][l] = array[i][l] - min;
        }
    }
}

int find_prev_zero(point** points, int size, int column_index, int row_index) {
    for (int i = 0; i < column_index; i++) {
        if (points[row_index][i].used == 1 && points[row_index][i].number == 0){

        }
    }
}

void find_zeros(int** array, int size){
    point** new_array;
    for (int i = 0; i < size; i++) {
        new_array[i] = new point[size];
        for (int l = 0; l < size; l++) {
            new_array[i][l].number = array[i][l];
        }
    }
    for (int i = 0; i < size; i++) {
        for (int l = 0; l < size; l++) {
            if (new_array[l][i].number == 0){

                new_array[l][i].used = 1;
            }
        }
    }
//    return NULL;
}

void work_with_matrix(int** array, int size){
    work_with_rows(array, size);
    work_with_columns(array, size);
    out(array, size);
}

int main() {
    int** a = create_array(3);
    work_with_matrix(a, 3);
    return 0;
}
