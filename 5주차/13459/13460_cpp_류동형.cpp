#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

int answer = -1;
int N, M;
char map[11][11];
struct idx {
    int blue_x;
    int blue_y;
    int red_x;
    int red_y;
    int cnt;
};

queue<idx> q;
int bbx, bby, rrx, rry;
int checkR_O;
int checkB_O;

void clean_check() {
    checkR_O = 0;
    checkB_O = 0;
}

void check_r(int z, int x, int y) {//�� �� �Ʒ� ��
    if (z == 1) {
        for (int i = y; i >= 1; i--) {
            if (map[x][i] == 'O') { 
                checkR_O = 1;
                return;
            }
            if (map[x][i] == '#') {
                rrx = x;
                rry = i + 1;
                return;
            }
        }
    }
    else if (z == 2) {
        for (int i = y; i <= M; i++) {
            if (map[x][i] == 'O') {
                checkR_O = 1;
                return;
            }
            if (map[x][i] == '#') {
                rrx = x;
                rry = i - 1;
                return;
            }
        }
    }
    else if (z == 3) {
        for (int i = x; i <= N; i++) {
            if (map[i][y] == 'O') {
                checkR_O = 1;
                return;
            }
            if (map[i][y] == '#') {
                rrx = i - 1;
                rry = y;
                return;
            }
        }
    }
    else if (z == 4) {
        for (int i = x; i >= 1; i--) {
            if (map[i][y] == 'O') {
                checkR_O = 1;
                return;
            }
            if (map[i][y] == '#') {
                rrx = i + 1;
                rry = y;
                return;
            }
        }
    }
}

void check_b(int z, int x, int y) {//�� �� �Ʒ� ��
    if (z == 1) {
        for (int i = y; i >= 1; i--) {
            if (map[x][i] == 'O') { //
                checkB_O = 1;
                return;
            }
            if (map[x][i] == '#') {
                bbx = x;
                bby = i + 1;
                return;
            }
        }
    }
    else if (z == 2) {
        for (int i = y; i <= M; i++) {
            if (map[x][i] == 'O') {
                checkB_O = 1;
                return;
            }
            if (map[x][i] == '#') {
                bbx = x;
                bby = i - 1;
                return;
            }
        }
    }
    else if (z == 3) {
        for (int i = x; i <= N; i++) {
            if (map[i][y] == 'O') {
                checkB_O = 1;
                return;
            }
            if (map[i][y] == '#') {
                bbx = i - 1;
                bby = y;
                return;
            }
        }
    }
    else if (z == 4) {
        for (int i = x; i >= 1; i--) {
            if (map[i][y] == 'O') {
                checkB_O = 1;
                return;
            }
            if (map[i][y] == '#') {
                bbx = i + 1;
                bby = y;
                return;
            }
        }
    }
}

void bfs() {
    while (!q.empty()) {
        int b_x = q.front().blue_x;
        int b_y = q.front().blue_y;
        int r_x = q.front().red_x;
        int r_y = q.front().red_y;
        int cnt = q.front().cnt;
        q.pop();

        if (cnt == 11) { return; }

        //�������� ����
        if (r_y < b_y) {//�������� �� ���ʿ������� �����������̵�
            check_r(1, r_x, r_y);
            if (checkR_O != 1) { //�������� 0�̾ƴ� ����������
                map[rrx][rry] = '#';  //�� ������ ��ǥ�� ������ �ٲٱ�
            }
            check_b(1, b_x, b_y);  //�� ���¿��� �Ķ����˻�
            map[bbx][bby] = '#'; //�Ķ��� ��ǥ�� ������ �ٲٱ�  
        }
        else {
            check_b(1, b_x, b_y);
            map[bbx][bby] = '#';
            check_r(1, r_x, r_y);
            map[rrx][rry] = '#';
        }
        if (checkR_O == 1) {
            if (checkB_O != 1) {  //�������� 0�������µ� �Ķ����� 0���ȸ����� ������
                cout << cnt;
                exit(0);
            }

        }
        if (checkB_O != 1) {  //�Ķ����� 0�� ������ �ƴϸ�
            q.push({ bbx,bby,rrx,rry,cnt + 1 });  //queue�� �ְ� 
            map[bbx][bby] = '.'; //�����θ���� �ٽ� �̵������Ѱɷιٲٱ�
            map[rrx][rry] = '.'; //�����θ����� �ٽ� �̵������Ѱɷιٲٱ�
        }
        else {
            map[bbx][bby] = '0';   //�Ķ����� 0�� �����Ÿ� 0����
            map[rrx][rry] = '0';
        }
        clean_check();

        //���������� ����
        if (r_y > b_y) {//�������� �� �����ʿ������� �����������̵�
            check_r(2, r_x, r_y);
            if (checkR_O != 1) {
                map[rrx][rry] = '#';
            }
            check_b(2, b_x, b_y);
            map[bbx][bby] = '#';
        }
        else {
            check_b(2, b_x, b_y);
            map[bbx][bby] = '#';
            check_r(2, r_x, r_y);
            map[rrx][rry] = '#';
        }
        if (checkR_O == 1) {
            if (checkB_O != 1) {
                cout << cnt;
                exit(0);
            }
        }
        if (checkB_O != 1) {
            q.push({ bbx,bby,rrx,rry,cnt + 1 });
            map[bbx][bby] = '.';
            map[rrx][rry] = '.';
        }
        else {
            map[bbx][bby] = '0';
            map[rrx][rry] = '0';
        }
        clean_check();

        //�Ʒ��� ����
        if (r_x > b_x) {//�������� �� �Ʒ��������� �����������̵�
            check_r(3, r_x, r_y);
            if (checkR_O != 1) {
                map[rrx][rry] = '#';
            }
            check_b(3, b_x, b_y);
            map[bbx][bby] = '#';
        }
        else {
            check_b(3, b_x, b_y);
            map[bbx][bby] = '#';
            check_r(3, r_x, r_y);
            map[rrx][rry] = '#';
        }
        if (checkR_O == 1) {
            if (checkB_O != 1) {
                cout << cnt;
                exit(0);
            }
        }
        if (checkB_O != 1) {
            q.push({ bbx,bby,rrx,rry,cnt + 1 });
            map[bbx][bby] = '.';
            map[rrx][rry] = '.';
        }
        else {
            map[bbx][bby] = '0';
            map[rrx][rry] = '0';
        }
        clean_check();

        //���� ����
        if (r_x < b_x) {//�������� �� ���������� �����������̵�
            check_r(4, r_x, r_y);
            if (checkR_O != 1) {
                map[rrx][rry] = '#';
            }
            check_b(4, b_x, b_y);
            map[bbx][bby] = '#';
        }
        else {
            check_b(4, b_x, b_y);
            map[bbx][bby] = '#';
            check_r(4, r_x, r_y);
            map[rrx][rry] = '#';
        }
        if (checkR_O == 1) {
            if (checkB_O != 1) {
                cout << cnt;
                exit(0);
            }
        }
        if (checkB_O != 1) {
            q.push({ bbx,bby,rrx,rry,cnt + 1 });
            map[bbx][bby] = '.';
            map[rrx][rry] = '.';
        }
        else {
            map[bbx][bby] = '0';
            map[rrx][rry] = '0';
        }
        clean_check();
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int blue_x;
    int blue_y;
    int red_x;
    int red_y;
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        string a;
        cin >> a;
        for (int j = 0; j < a.size(); j++) {
            map[i][j + 1] = a.at(j);
            if (map[i][j + 1] == 'B') {
                blue_x = i;
                blue_y = j + 1;
            }
            else if (map[i][j + 1] == 'R') {
                red_x = i;
                red_y = j + 1;
            }
        }
    }
    map[blue_x][blue_y] = '.';
    map[red_x][red_y] = '.';
    q.push({ blue_x,blue_y,red_x,red_y,1 });

    bfs();
    cout << answer;
}