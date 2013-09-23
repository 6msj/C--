#include <iostream>
using namespace std;

const int PQ_SIZE = 50;

typedef int item_type;
typedef struct {
    item_type q[PQ_SIZE+1]; // body of queue
    int n; // number of queue elements
} priority_queue;

// In this priority queue, the root starts at 1 and not 0.

int pq_parent(int n);
int pq_young_child(int n);

void pq_insert(priority_queue *q, item_type x);
void bubble_up(priority_queue *q, int p);
void pq_swap(priority_queue *q, int child, int parent);
void pq_init();
void make_heap(priority_queue *q, item_type s[], int n);
void make_heap_alt(priority_queue *q, item_type[], int n);
item_type extract_min(priority_queue *q);
void bubble_down(priority_queue *q, int p);
void heap_sort(item_type s[], int n);

int main() {
    return 0;
}

int pq_parent(int n) {
    if (n == 1) {
        // 0 == root
        return -1;
    } else {
        return ((int) n / 2); // implicitly take floor (n/2)
    }
}

int pq_young_child(int n) {
    return (2 * n);
}

void pq_insert(priority_queue *q, item_type x) {
    if (q->n >= PQ_SIZE) {
        printf("Warning: priority queue overflow insert x=%d\n", x);
    } else {
        q->n = (q->n) + 1;
        q->q[ q->n ] = x;
        bubble_up(q, q->n);
    }
}

void bubble_up(priority_queue *q, int p) {
    if (pq_parent(p) == -1) {
        return; // root of heap, no parent
    }

    if (q->q[pq_parent(p)] > q->q[p] ) {
        pq_swap(q, p, pq_parent(p));
        bubble_up(q, pq_parent(p));
    }
}

void pq_swap(priority_queue *q, int child, int parent) {
    item_type temp = q->q[ child ];
    q->q[ child ] = q->q[ parent ];
    q->q[ parent ] = temp;
}

void pq_init(priority_queue *q) {
    q->n = 0;
}

void make_heap(priority_queue *q, item_type s[], int n) {
    int i; // counter
    pq_init(q);
    for (i = 0; i < n; ++i) {
        pq_insert(q, s[i]);
    }
}

item_type extract_min(priority_queue *q) {
    int min = -1; // minimum value

    if (q->n <= 0) {
        printf("Warning: empty priority queue.\n");
    } else {
        min = q->q[1]; // min heap, so minimum value is at the root

        q->q[1] = q->q[ q->n ];
        q->n = q->n - 1;
        bubble_down(q, 1);
    }

    return min;

}

void bubble_down(priority_queue *q, int p) {
    int c; // child index
    int i; // counter
    int min_index; // index of lightest child

    c = pq_young_child(p);
    min_index = p;

    for (i = 0; i <= 1; ++i) {
        if ((c+i) <= q->n) {
            if (q->q[min_index] > q->q[c+i]) {
                min_index = c+i;
            }
        }
    }

    if (min_index != p) {
        pq_swap(q, p, min_index);
        bubble_down(q, min_index);
    }

}

void heap_sort(item_type s[], int n) {
    int i; // counters
    priority_queue q; // heap for heapsort

    make_heap(&q, s, n);

    for (i = 0; i < n; ++i) {
        s[i] = extract_min(&q);
    }
}

void make_heap_alt(priority_queue *q, item_type s[], int n) {
    int i; // counter
    q->n = n;
    for (i = 0; i < n; ++i) {
        q->q[i+1] = s[i];
    }

    for (i = q->n; i >= 1; i--) {
        bubble_down(q, i);
    }
}
