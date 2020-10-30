#include <iostream>
#include <algorithm>
#include <vector>

struct item {

    item() {}
    item(int min, int cnt) : m(min), c(cnt) {}
    int m, c;
};

struct segtree {

    int size;
    std::vector<item> values;

    item NEUTRAL_ELEMENT = {1000000001, 0};

    item merge(item a, item b) {
        if (a.m < b.m) return a;
        if (a.m > b.m) return b;
        return {a.m, a.c + b.c};
    }

    item build_single(int v) {
        return {v, 1};
    }

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        values.resize(2*size);
    }

    void build(std::vector<int> &a, int x, int lx, int rx) {
        if (lx == rx) {
            if (lx < (int)a.size()) {
                values[x] = build_single(a[lx]);
            }

            return;
        }

        int mid = (lx + rx) / 2;

        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid + 1, rx);
        values[x] = merge(values[2*x + 1], values[2*x + 2]);
    }

    void build(std::vector<int> &a) {
        build(a, 0, 0, size-1);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx) {
            values[x] = build_single(v);
            return;
        }

        int mid = (lx + rx) / 2;

        if (i <= mid) {
            set(i, v, 2*x + 1, lx, mid);
        } else {
            set(i, v, 2*x + 2, mid + 1, rx);
        }

        values[x] = merge(values[2*x + 1], values[2*x + 2]);
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size - 1);
    }

    item min(int l, int r, int x, int lx, int rx) {
        if (lx > r || rx < l) return NEUTRAL_ELEMENT;
        if (l <= lx && rx <= r) return values[x];

        int mid = (lx + rx) / 2;

        item left = min(l, r, 2*x + 1, lx, mid);
        item right = min(l, r, 2*x + 2, mid + 1, rx);

        return merge(left, right);
    }

    item min(int l, int r){
        return min(l, r, 0, 0, size-1);
    }
};

int main(){
    std::ios_base::sync_with_stdio(0);

    int n, m;
    std::cin >> n >> m;

    segtree st;
    st.init(n);
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    st.build(a);
    while(m--) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int i, v;
            std::cin >> i >> v;
            st.set(i, v);
        } else {
            int l, r;
            std::cin >> l >> r;

            --r;
            item min = st.min(l, r);
            std::cout << min.m << " " << min.c << "\n";
        }
    }

    return 0;
}