#include <vector>
#include <iostream>
#include <exception>
#include <cmath>

/*
* Минибаев Айдар М8О-201Б
* ========================
* Вариант 9:
* Треугольник
* Квадрат
* Прямоугольник
*/

class Point {
public:
    double x, y;
    Point(double a = 0, double b = 0) : x(a), y(b) {}
    Point readPoint();
    friend double dist(Point p1, Point p2){
        return sqrt(((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y) * (p1.y - p2.y)));
    }
};

bool isNumber(const std::string& s){
    return !s.empty() && s.find_first_not_of("-.0123456789") == std::string::npos; }


Point Point::readPoint(){
    double a,b;
    std::string x, y;
    bool check = true;
    while(check) {
        std::cout << "x = ";
        std::cin >> x;
        std::cout << "y = ";
        std::cin >> y;
        if (isNumber(x) && isNumber(y)) {
            a = std::stod(x);
            b = std::stod(y);
            Point C(a, b);
            check = false;
            return C;
        } else {
            std::cout << "Incorrect input of coordinates" << std::endl;
            std::cout << "Re-enter the coordinates of this point" << std::endl;
        }
    }
}


class Figure {
protected:
    Point centre;
    double area;
    std::string name = "";
public:
    virtual double Area() = 0;
    virtual Point Centre() = 0;
    virtual std::ostream &Print(std::ostream &out) = 0;
    virtual std::istream &Read(std::istream &in) = 0;
    virtual ~Figure() = default;
};

class Triangle: public Figure{
    Point A, B, C;
public:
    Triangle() {}
    Triangle(Point a, Point b, Point c);
    Point Centre() override;
    double Area() override;
    std::ostream &Print(std::ostream &out) override;
    std::istream &Read(std::istream &in) override;
};

class Square: public Figure{
    Point A, B, C, D;
public:
    Square() {}
    Square(Point a, Point c, Point b, Point d);
    Point Centre() override;
    double Area() override;
    std::ostream &Print(std::ostream &out) override;
    std::istream &Read(std::istream &in) override;
};

class Rectangle: public Figure{
    Point A, B, C, D;
public:
    Rectangle() {}
    Rectangle(Point a, Point c, Point b, Point d);
    Point Centre() override;
    double Area() override;
    std::ostream &Print(std::ostream &out) override;
    std::istream &Read(std::istream &in) override;
};



Triangle::Triangle(Point a, Point b, Point c) {
    name = "Triangle";
    A = a; B = b; C = c;
    area = Area();
    centre = Centre();
}

Point Triangle::Centre() {
    Point O;
    O.x = (A.x + B.x + C.x) / 3;
    O.y = (A.y + B.y + C.y) / 3;
    return O;
}

double Triangle::Area() {
    double S, p, AB, AC, BC;
    AB = dist(A,B);
    AC = dist(A,C);
    BC = dist(B,C);
    p = (AB + BC + AC) / 2;
    S = sqrt(p* (p-AB) * (p-AC) * (p-BC));
    return S;
}
std::ostream &Triangle::Print(std::ostream &out) {
    out << std::endl << name << ":" << std::endl;
    out << "Peaks: " << "A(" << A.x << ";" << A.y << "), B("
    << B.x << ";" << B.y << "), C(" << C.x << ";" << C.y << ")" << std::endl;
    out << "Geometric center: O(" << centre.x << ";" << centre.y << ")" << std::endl;
    out << "Area: " << area << std::endl;
    out << std::endl;
    return out;
}

std::istream &Triangle::Read(std::istream &in) {
    Point a, b, c;
    bool k = true;
    double AB, BC, AC;
    std::cout << "Enter the three coordinates of the triangle" << std::endl;
    while(k){
        std::cout << "Enter the coordinates of point a by x, y :" << std::endl;
        a = a.readPoint();
        std::cout << "For point b:" << std::endl;
        b = b.readPoint();
        std::cout << "For point c:" << std::endl;
        c = c.readPoint();
        AB = dist(a, b);
        AC = dist(a, c);
        BC = dist(b, c);
        if (((AB + AC) > BC) && ((AB + BC) > AC) && ((BC + AC) > AB)) {
            (*this) = Triangle(a, b, c);
            return in;
            k = false;
        } else {
            std::cout << "the triangle is incorrect" << std::endl;
            std::cout << "Re-enter the triangle parameters" << std::endl;
        }
    }
}

Square::Square(Point a, Point c, Point b, Point d){
    name = "Square";
    A = a; C = c; B = b; D = d;
    area = Area();
    centre = Centre();
}

Point Square::Centre() {
    Point O;
    O.x = (A.x + C.x) / 2;
    O.y = (A.y + C.y) / 2;
    return O;
}

double Square::Area() {
    double S, AB;
    AB = dist(A,B);
    S = AB * AB;
    return S;
}

std::ostream &Square::Print(std::ostream &out) {
    out << std::endl << name << ":" << std::endl;
    out << "Peaks: " << "A(" << A.x << ";" << A.y << "), B("
    << B.x << ";" << B.y << "), C(" << C.x << ";" << C.y << "), D("
    << D.x << ";" << D.y << ")" << std::endl;
    out << "Geometric center: O(" << centre.x << ";" << centre.y << ")" << std::endl;
    out << "Area: " << area << std::endl;
    out << std::endl;
    return out;
}

std::istream &Square::Read(std::istream &in) {
    Point a, c;
    bool k = true;
    double AB, AD;
    std::cout << "Enter the two coordinates of the Square" << std::endl;
    while(k){
        std::cout << "Enter the coordinates lower left point a by x, y :" << std::endl;
        a = a.readPoint();
        std::cout << "For right upper point С:" << std::endl;
        c = c.readPoint();
        Point b(a.x, c.y), d(c.x, a.y);
        AB = dist(a,b);
        AD = dist(a,d);
        if ((a.x < c.x) && (a.y < c.y) && (AB == AD)) {
            (*this) = Square(a, c, b, d);
            return in;
            k = false;
        } else {
            std::cout << "the square is incorrect" << std::endl;
            std::cout << "Re-enter the square parameters" << std::endl;
        }
    }
}

Rectangle::Rectangle(Point a, Point c, Point b, Point d) {
    name = "Rectangle";
    A = a; C = c; B = b; D = d;
    area = Area();
    centre = Centre();
}

Point Rectangle::Centre() {
    Point O;
    O.x = (A.x + C.x) / 2;
    O.y = (A.y + C.y) / 2;
    return O;
}

double Rectangle::Area() {
    double S, AB, AD;
    AB = dist(A,B);
    AD = dist(A,D);
    S = AB * AD;
    return S;
}

std::ostream &Rectangle::Print(std::ostream &out) {
    out << std::endl << name << ":" << std::endl;
    out << "Peaks: " << "A(" << A.x << ";" << A.y << "), B("
    << B.x << ";" << B.y << "), C(" << C.x << ";" << C.y << "), D("
    << D.x << ";" << D.y << ")" << std::endl;
    out << "Geometric center: O(" << centre.x << ";" << centre.y << ")" << std::endl;
    out << "Area: " << area << std::endl;
    out << std::endl;
    return out;
}

std::istream &Rectangle::Read(std::istream &in) {
    Point a, c;
    bool k = true;
    double AB, AD;
    std::cout << "Enter the two coordinates of the Rectangle" << std::endl;
    while(k){
        std::cout << "Enter the coordinates lower left point a by x, y :" << std::endl;
        a = a.readPoint();
        std::cout << "For right upper point С:" << std::endl;
        c = c.readPoint();
        Point b(a.x,c.y), d(c.x, a.y);
        AB = dist(a,b);
        AD = dist(a,d);
        if ((a.x < c.x) && (a.y < c.y) && (AB != AD)) {
            (*this) = Rectangle(a, c, b, d);
            return in;
            k = false;
        } else {
            std::cout << "the rectangle is incorrect" << std::endl;
            std::cout << "Re-enter the rectangle parameters" << std::endl;
        }
    }
}



struct list_empty : public std::exception {
    const char* what() const throw ()
    {
        return "The list is currently empty";
    }
};

void PrintVec(const std::vector<Figure*> &l) {
    int num = 1;
    for (auto e : l) {
        std::cout << num << ". ";
        e->Print(std::cout);
        std::cout << std::endl;
        ++num;
    }
}

double TotalArea(const std::vector<Figure*>& l) {
    double res = 0;
    for (auto &e : l) {
        res += e->Area();
    }
    return res;
}



int main() {
    std::vector<Figure*> FigureVec;
    bool check = true;
    int command = 0, option = 6;
    Figure *fig;

    while(check) {
        switch(option) {
            case 0:
                check = false;
                break;
            case 1:
                std::cout << "1) Triangle" << std::endl;
                std::cout << "2) Square" << std::endl;
                std::cout << "3) Rectangle" << std::endl;
                std::cin >> command;
                switch (command) {
                    case 0: break;
                    case 1:
                        fig = new Triangle;
                        fig->Read(std::cin);
                        FigureVec.push_back(fig);
                        std::cout << "Triangle added" << std::endl;
                        fig->Print(std::cout);
                        break;

                    case 2:
                        fig = new Square();
                        fig->Read(std::cin);
                        FigureVec.push_back(fig);
                        std::cout << "Square added" << std::endl;
                        fig->Print(std::cout);
                        break;
                    case 3:
                        fig = new Rectangle();
                        fig->Read(std::cin);
                        FigureVec.push_back(fig);
                        std::cout << "Rectangle added" << std::endl;
                        fig->Print(std::cout);
                        break;
                }
                break;
            case 2:
                if(FigureVec.empty()) throw list_empty();
                PrintVec(FigureVec);
                break;
            case 3 :
                if (FigureVec.empty()) throw list_empty();
                std::cout << "The total area of all shapes is " << TotalArea(FigureVec) << std::endl;
                break;
            case 4:
                if (FigureVec.empty()) throw list_empty();
                for (std::vector<Figure *>::iterator i = FigureVec.begin(); i != FigureVec.end(); i++) {
                    delete *i;
                }
                FigureVec.erase(FigureVec.begin(), FigureVec.end());
                std::cout << "Vector is now empty" << std::endl;
                break;
            case 5 :
                int num;
                if (FigureVec.empty()) throw list_empty();
                std::cout << "Number of the shape: ";
                std::cin >> num;
                if (num < 1 || num > FigureVec.size()) throw std::runtime_error("Incorrect index");
                delete FigureVec[--num];
                FigureVec.erase(FigureVec.begin() + num);
                break;
            case 6:
                std::cout << "Enter a number for action:" << std::endl;
                std::cout << "1) Add Figure" <<
                          std::endl << "2) Display data of all figures" <<
                          std::endl << "3) Print total area" <<
                          std::endl << "4) Remove all figure" <<
                          std::endl << "5) Remove figure by index" <<
                          std::endl << "5) Print Menu" <<
                          std::endl << "0) Exit" << std::endl;
                break;
        }
        if(check){
            std::cout << "Enter a number for action:" << std::endl;
            std::cin >> option;
        }
    }
    return 0;
}