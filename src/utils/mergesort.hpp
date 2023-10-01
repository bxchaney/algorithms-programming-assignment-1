/*
 * Copyright 2023, Brandon Chaney
 */
#pragma once

template <typename T>
void merge(T* arr, int l, int m, int r, bool (*leq)(T*, T*)) {
    std::cout << "l: " << l << "m: " << m << "r: " << r << std::endl;
    int i, j, k, nl, nr;
    nl = m - l + 1;
    nr = r - m;

    // make temp arrays and copy array contents into them
    T* larr{new T[nl]};
    T* rarr{new T[nr]};

    for (i = 0; i < nl; i++) larr[i] = arr[l + i];
    for (j = 0; j < nr; j++) rarr[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    // merge arrays
    while (i < nl && j < nr) {
        if (leq(&(larr[i]), &(rarr[j]))) {
            arr[k] = larr[i];
            i++;
        } else {
            arr[k] = rarr[j];
            j++;
        }
        k++;
    }
    while (i < nl) {
        arr[k] = larr[i];
        i++;
        k++;
    }
    while (j < nr) {
        arr[k] = rarr[j];
        j++;
        k++;
    }

    delete[] larr;
    delete[] rarr;
}

template <typename T>
void merge_sort(T* arr, int l, int r, bool (*leq)(T*, T*)) {
    if (l < r) {
        int m{l + (r - l) / 2};
        merge_sort(arr, l, m, leq);
        merge_sort(arr, m + 1, r, leq);
        merge<T>(arr, l, m, r, leq);
    }
}
