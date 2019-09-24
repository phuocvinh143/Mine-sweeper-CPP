#include<bits/stdc++.h>

using namespace std;

#define MINE -1

int x, y;
int M, N, k;
set<pair<int, int> > ss;

int B[100][100];

int T[100][100];

int dx[] = {0, 0, -1, 1, 1, 1, -1, -1};
int dy[] = {-1, 1, 0, 0, -1, 1, -1, 1};

void print_note(){
    cout << "\"#\": didn't open, you can open it\n";
    cout << "\".\": don't have mine around, please choose\n";
    cout << "\"x\": this is bom\n";
    cout << "a number: have 'number' mine(s) around, be careful\n";
}

void choose_Level() {
    printf("\nYou want to play level 1, 2 or 3? ");
    int Level;
    scanf("%d", &Level);
    if (Level == 1) {
        M = 5; N = 5; k = 3;
    }
    if (Level == 2) {
        M = N = 9; k = 8;
    }
    if (Level == 3) {
        M = 11; N = 11; k = 10;
    }
}

void randomMINE() {
    srand(time(NULL));
    while (ss.size() < k) {
        int rand_x = rand()%M;
        int rand_y = rand()%N;
        ss.insert(make_pair(rand_x, rand_y));
    }
    for (set<pair<int, int> >::iterator i = ss.begin(); i != ss.end(); ++i) {
        pair<int, int> rand_pair = *i;
        //cout << rand_pair.first << " " << rand_pair.second << endl;
        B[rand_pair.first][rand_pair.second] = MINE;
    }
}

void init(){
    choose_Level();
    randomMINE();
}

bool inside(int x, int y){
    if (x >= 0 && y >= 0 && x <= M-1 && y <= N-1) return 1;
    return 0;
}

void count_mines(){
    int i, j;
    for (i = 0; i < M; ++i) {
        for (j = 0; j < N; ++j) {
            if (!B[i][j]) {
                int k, cnt = 0;
                for (k = 0; k < 8; ++k) {
                    int x = dx[k] + i;
                    int y = dy[k] + j;
                    if (inside(x, y) && B[x][y] == -1) ++cnt;
                }
                B[i][j] = cnt;
            }
        }
    }
}

void printMap1(){
    int i, j;
    printf("   ");
    for (i = 0; i < M; ++i) printf("%02d ", i);
    printf("\n");
    for (i = 0; i < N; ++i) {
        printf("%d ", i);
        for (j = 0; j < M; ++j) {
            if (!B[i][j]) printf(". ");
            else if (B[i][j] == -1) printf("x ");
            else printf("%d ", B[i][j]);
        }
        printf("\n");
    }
}

void printMap2(){
    int i, j;
    printf("   ");
    for (i = 0; i < M; ++i) printf("%d ", i);
    printf("\n");
    for (i = 0; i < N; ++i) {
        printf("%2d ", i);
        for (j = 0; j < M; ++j) {
            if (!T[i][j]) printf("# ");
            else {
                if (!B[i][j]) printf(". ");
                else if (B[i][j] == -1) printf("x ");
                else printf("%d ", B[i][j]);
            }
        }
        printf("\n");
    }
}

void printMap3(){
    int i, j;
    printf("   ");
    for (i = 0; i < M; ++i) printf("%d ", i);
    printf("\n");
    for (i = 0; i < N; ++i) {
        printf("%2d ", i);
        for (j = 0; j < M; ++j) {
            if (!T[i][j]) printf("x ");
            else {
                if (!B[i][j]) printf(". ");
                else if (B[i][j] == -1) printf("x ");
                else printf("%d ", B[i][j]);
            }
        }
        printf("\n");
    }
}

int count_remain(){
    int i, j, cnt = 0;
    for (i = 0; i < M; ++i) {
        for (j = 0; j < N; ++j) {
            if (!T[i][j]) ++cnt;
        }
    }
    return cnt;
}

void open_cell_1(int r, int c){
    if (!T[r][c]) T[r][c] = 1;
}

void open_cell_2(int r, int c){
    int i;
    T[r][c] = 1;
    if (!B[r][c]) {
        for (i = 0; i < 8; ++i) {
            int x = dx[i] + r;
            int y = dy[i] + c;
            if (inside(x, y)) open_cell_1(x, y);
        }
    }
}

void open_cell_3(int r, int c){
    int i;
    if (T[r][c]) return;
    T[r][c] = 1;
    if (!B[r][c]) {
        for (i = 0; i < 8; ++i) {
            int x = dx[i] + r;
            int y = dy[i] + c;
            if (inside(x, y)) open_cell_3(x, y);
        }
    }
}

int main(){
    int stop;
    print_note();
    init();
    count_mines();
    while (1) {
        printMap2();
        printf("Your Turn: ");
        scanf("%d%d", &x, &y);
        if (B[x][y] == MINE) {
            printMap1();
            printf("You were chose in the bom cell and you lose!");
            return 0;
        }
        open_cell_3(x, y);
        stop = count_remain();
        if (stop == k) {
            printMap3();
            printf("You Win!");
            return 0;
        }
    }
}
