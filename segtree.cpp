#include <bits/stdc++.h>

using namespace std;

class SegTree {
private:
    int n = 256;
    int tree[256];

public:
    void build(int a[], int v, int left, int right) {
        if (left == right) {
            tree[v] = a[left];
        } else {
            int mid = (left + right)/2;
            build(a, v*2, left, mid);
            build(a, v*2 + 1, mid + 1, right);
            tree[v] = tree[v*2] + tree[v*2 + 1];
        }
    }

    int sum (int v, int left, int right, int l, int r) {
        if (l > r) {
            return 0;
        }
        if (l == left && r == right) {
            return tree[v];
        }
        int mid = (left + right)/2;
        return sum(v*2, left, mid, l, min(r, mid)) + sum(v*2 + 1, mid + 1, right, max(l, mid + 1), r);
    }

    void update (int v, int left, int right, int pos, int new_x) {
        if (left == right) {
            tree[v] = new_x;
        } else {
            int mid = (left + right)/2;
            if (pos <= mid) {
                update(v*2, left, mid, pos, new_x);
            } else {
                update(v*2 + 1, mid + 1, right, pos, new_x);
            }
            tree[v] = tree[v*2] + tree[v*2 + 1];
        }
    }
};

class Persistent_SegTree {
    
};