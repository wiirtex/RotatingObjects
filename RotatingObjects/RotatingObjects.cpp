
#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

const int N = 17;
const double PI = 3.14159265359;
constexpr double center = N / 2;
const char empty_char = ' ';
const char center_char = '@';

typedef double dd;


struct point {
    dd x, y;
    char model;
    int priority;
    point(dd x_, dd y_, char model_, int priority_ = 0) {
        x = x_;
        y = y_;
        model = model_;
        priority = priority_;
    }
} typedef point;


vector<vector<vector<point>>> picture;


void init() {
    picture.resize(N);
    for (int i = 0; i < N; i++) {
        picture[i].resize(N);
        for (int j = 0; j < N; j++) {
            picture[i][j].push_back(point(i, j, empty_char));
        }
    }
    picture[center][center].insert(picture[center][center].begin(), point(center, center, center_char, 10));
}

void drawOneFigure(const point& point_, vector<vector<vector<point>>>& pic) {
    if (round(point_.x + center) >= N || round(point_.x + center) < 0 || round(point_.y + center) >= N || round(point_.y + center) < 0) {
        pic[center][center].push_back(point(point_.x + center, point_.y + center, point_.model, -1));
    }
    else {
        pic[round(point_.x + center)][round(point_.y + center)].push_back(point(point_.x + center, point_.y + center, point_.model, 5));
    }
}
void draw() {
   int x = 7;
    int y = 0;
    drawOneFigure(point(x, y, '#', 5), picture);
    x = 5;
    y = 0;
    drawOneFigure(point(x, y, '#', 5), picture);
    x = 6;
    y = 0;
    drawOneFigure(point(x, y, '#', 5), picture);
    x = 4;
    y = 0;
    drawOneFigure(point(x, y, '#', 5), picture);
    x = 3;
    y = 0;
    drawOneFigure(point(x, y, '#', 5), picture);
    x = 2;
    y = 0;
    drawOneFigure(point(x, y, '#', 5), picture);
    x = 1;
    y = 0;
    drawOneFigure(point(x, y, '#', 5), picture);
    x = 7;
    y = -1;
    drawOneFigure(point(x, y, '#', 5), picture);
    x = 7;
    y = -2;
    drawOneFigure(point(x, y, '#', 5), picture);
    x = 7;
    y = -3;
    drawOneFigure(point(x, y, '#', 5), picture);
    x = 7;
    y = -4;
    drawOneFigure(point(x, y, '#', 5), picture);

}

void print() {
    system("cls");
    for (int i = N - 1; i >= 0; i--) {
        for (int j = 0; j < N; j++) {
            point max_priority_point = point(j, i, 'e', -1);
            for (auto point_ : picture[j][i]) {
                if (max_priority_point.priority < point_.priority) {
                    max_priority_point = point_;
                }
            }
            cout << max_priority_point.model << " ";
        }
        cout << endl;
    }
}

void rotate(double angle) {
    vector<vector<vector<point>>> newPicture;
    newPicture.resize(N);
    for (int i = 0; i < N; i++) {
        newPicture[i].resize(N);
        for (int j = 0; j < N; j++) {
            newPicture[i][j].push_back(point(i, j, empty_char));
        }
    }
    newPicture[center][center].push_back(point(center, center, center_char, 10));
    angle = angle / 180. * PI;
    for (int i = N - 1; i >= 0; i--) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < picture[j][i].size(); k++) {
                if (picture[j][i][k].model != empty_char && picture[j][i][k].model != center_char) {
                    dd X = picture[j][i][k].x - center, Y = picture[j][i][k].y - center;
                    dd newX = X * cos(angle) + Y * sin(angle);
                    dd newY = -X * sin(angle) + Y * cos(angle);
                    drawOneFigure(point(newX, newY, picture[j][i][k].model, 5), newPicture);
                }
            }
        }
    }
    picture = newPicture;
}

int main()
{
    init();
    draw();
    print();
    for (int i = 0; i < 100000; i++) {
        rotate(30);
        print(); 
        Sleep(50);
    }
    /*Sleep(1000);
    rotate(45);
    print();*/
}