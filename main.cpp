#include <iostream>
#include <time.h>
#include <string>
using namespace std;

struct point{
    int number;
    uint8_t used;
};

int** create_array(int size) {
    srand(time(NULL));
    int** array = new int *[size];
    for (int i = 0; i < size; i++) {
    array[i] = new int[size];
        for (int l = 0; l < size; l++) {
            array[i][l] = (rand() % 20) + 1;
        }
    }

//    int **array = new int *[size];
//    for (int i = 0; i < size; i++) {
//        array[i] = new int[size];
//    }
//    array[0][0] = 2500; array[0][1] = 4000; array[0][2] = 3500;
//    array[1][0] = 4000; array[1][1] = 6000; array[1][2] = 3500;
//    array[2][0] = 2000; array[2][1] = 4000; array[2][2] = 2500;

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

void out(point** array, int size){
    cout << "Our Matrix(POINTS)" << endl;
    for (int i = 0; i < size; i++) {
        for (int l = 0; l < size; l++){
            int amount = to_string(array[i][l].number).size();
            for (int j = 0; j < 6 - amount; j++){ cout << ' ';}
            cout << array[i][l].number << "(" << (int)array[i][l].used << ") ";
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

void delete_min_from_rows(int** array, int size){
    for (int i = 0; i < size; i++) {
        int min = find_min_in_row(array[i], size);
        for (int l = 0; l < size; l++) {
           array[i][l] = array[i][l] - min;
        }
    }
}

void delete_min_from_columns(int** array, int size){
    for (int l = 0; l < size; l++) {
        int min = find_min_in_column(array, l, size);
        for (int i = 0; i < size; i++) {
            array[i][l] = array[i][l] - min;
        }
    }
}

int find_used_zero(point** points, int size, int row_index) {
    for (int i = 0; i < size; i++) {
        if (points[row_index][i].used == 1 && points[row_index][i].number == 0){
            return i;
        }
    }
    return -1;
}

point** copy(int** array, int size){
    point** new_array = new point *[size];
    for (int i = 0; i < size; i++) {
        new_array[i] = new point[size];
        for (int l = 0; l < size; l++) {
            new_array[i][l].number = array[i][l];
        }
    }
    return new_array;
}

int** copy_int_array(int** array, int size){
    int** new_array = new int *[size];
    for (int i = 0; i < size; i++) {
        new_array[i] = new int[size];
        for (int l = 0; l < size; l++) {
            new_array[i][l] = array[i][l];
        }
    }
    return new_array;
}

void change_to_unused_state(point** array, int size, int column_index) {
    for (int l = 0; l < size; l++) {
        if (array[l][column_index].number == 0 && array[l][column_index].used == 1) {
            array[l][column_index].used = 0;
            break;
        }
    }
}

bool rec2(point** new_array, int size, int column, int start_column){
    if (start_column == column) return false;
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (new_array[i][column].number == 0) {
            count++;
            int index = find_used_zero(new_array, size, i);
            if (index == -1){
                change_to_unused_state(new_array, size, column);
                new_array[i][column].used = 1;
                return true;
            }
        }
    }
    if (count == 1) return false;
    for (int l = 0; l < size; l++) {
        if (new_array[l][column].number == 0) {
            int column_index = find_used_zero(new_array, size, l);
            if (rec2(new_array, size, column_index, start_column)) {
                new_array[l][column].used = 1;
                return true;
            }
        }
    }
    return false;
}

void rec(point** new_array, int size, int i){
    bool flag = false;
    for (int l = 0; l < size; l++) {
        if (new_array[l][i].number == 0) {
            int index = find_used_zero(new_array, size, l);
            if (index == -1) {
                flag = true;
                new_array[l][i].used = 1;
                break;
            }
        }
    }
    if (!flag){
        for (int l = 0; l < size; l++) {
            if (new_array[l][i].number == 0) {
                int column_index = find_used_zero(new_array, size, l);
                if (rec2(new_array, size, column_index, i)) {
                    new_array[l][i].used = 1;
                    new_array[l][column_index].used = 0;
                    break;
                } else new_array[l][i].used = 2;
            }
        }
    }
    out(new_array, size);
}

point** set_zeros(int** array, int size){
    point** new_array = copy(array, size);
    for (int i = 0; i < size; i++) {
        rec(new_array, size, i);
    }
    return new_array;
}

point** set_zeros(point** array, int size){
    for (int i = 0; i < size; i++) {
        rec(array, size, i);
    }
    return array;
}

int find_sum(int** array, point** point_array, int size){
    int sum = 0;
    for (int i = 0; i < size; i++) {
        for (int l = 0; l < size; l++) {
            if (point_array[l][i].used == 1){
                sum += array[l][i];
                break;
            }
        }
    }
    return sum;
}

bool check_every_column(point** array, int size){
    for (int i = 0; i < size; i++) {
        bool flag = false;
        for (int l = 0; l < size; l++){
            if (array[l][i].used == 1) {
                flag = true;
                break;
            }
        }
        if (!flag) return false;
    }
    return true;
}

void second_step(point** array, int size) {
    bool *rows = new bool[size];
    bool *columns = new bool[size];
    for (int i = 0; i < size; i++) {
        rows[i] = false;
        columns[i] = false;
    }
    bool flag = false;
    for (int i = 0; i < size; i++) {
        for (int l = 0; l < size; l++) {
            if (array[l][i].used == 1) {
                for (int j = 0; j < size; j++) {
                    if (array[l][j].used == 2) {
                        rows[l] = true;
                        flag = true;
                        break;
                    }
                }
            }
            if (flag) break;
        }
        if (!flag) columns[i] = true;
    }
    int min = INT16_MAX;
    for (int i = 0; i < size; i++) {
        for (int l = 0; l < size; l++) {
            if (!rows[i] && !columns[l])
                if (min > array[i][l].number) min = array[i][l].number;
        }
    }
    for (int i = 0; i < size; i++) {
        for (int l = 0; l < size; l++) {
            if (!rows[i] && !columns[l]) array[i][l].number-= min;
            if (rows[i] && columns[l]) array[i][l].number+= min;
            array[i][l].used = 0;
        }
    }
}

void work_with_matrix(int** array, int size){
    int** initial_array = copy_int_array(array, size);
    out(array ,size);
    delete_min_from_rows(array, size);
    delete_min_from_columns(array, size);
    point** final_array = set_zeros(array, size);
    if (!check_every_column(final_array, size)) {
        second_step(final_array, size);
        final_array = set_zeros(final_array, size);
    }
    int sum = find_sum(initial_array, final_array, size);
    cout << "SUM: " << sum << endl;
}

void start(int size){
    int** a = create_array(size);
    work_with_matrix(a, size);
}

int main() {
    start(3);
    return 0;
}
