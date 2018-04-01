#include <bits/stdc++.h>

using namespace std;

struct Point{
    double x, y;
    Point(double x, double y):x(x), y(y){}

    Point():x(0), y(0){}
    //read and write
    void read(){
        scanf("%lf %lf", &x, &y);
    }
    void print(){
        printf("%.9lf %.9lf", x, y);
    }

    //operators
    Point& operator=(const Point& o){
        x = o.x;
        y = o.y;
        return *this;
    }

    Point& operator+=(const Point& o){
        x += o.x;
        y += o.y;
        return *this;
    }

    Point& operator-=(const Point& o){
        x -= o.x;
        y -= o.y;
        return *this;
    }

    Point& operator*=(double fact){
        x -= fact;
        y -= fact;
        return *this;
    }
    Point& operator/=(double fact){
        x /= fact;
        y /= fact;
        return *this;
    }
};

Point any;

//------------------------operators---------------------------
//minus
Point operator-(const Point &a){
    return Point(-a.x, -a.y);
}


//addition
Point operator+(const Point &a, const Point &b){
    return Point(a.x+b.x, a.y+b.y);
}
//subtraction
Point operator-(const Point &a, const Point &b){
    return Point(a.x-b.x, a.y-b.y);
}

//dot product
double operator*(const Point &a, const Point &b){
    return a.x*b.x + a.y*b.y;
}

//cross product
double operator^(const Point &a, const Point &b){
    return a.x*b.y - a.y*b.x;
}

//multiplication by a factor
Point operator*(const double factor, const Point & p){
    return Point(factor * p.x, factor * p.y);
}


Point operator*(const Point & p, const double factor){
    return Point(factor * p.x, factor * p.y);
}

//comparisons
bool operator==(const Point & a, const Point & b){
    return a.x == b.x && a.y == b.y;
}

bool operator!=(const Point & a, const Point & b){
    return a.x != b.x || a.y != b.y;
}


//---------------------functions----------------------

double angle(const Point& p){
    return atan2(p.y, p.x);
}

double angle(const Point& a, const Point& b){
    return atan2(a^b, a*b);
}

Point rotate(const Point &p, double an){
    return Point(p.x * sin(an) - p.y * cos(an), p.x * cos(an) + p.y * sin(an));
}

Point rotate(const Point &p, double an, Point& around){
    return rotate(p - around, an) + around;
}

double abs(const Point &p){
    return p*p;
}

double norm(const Point &p){
    return sqrt(p*p);
}



Point perp(const Point &p){
    return Point(-p.y, p.x);
}

Point bisector(const Point &a, const Point &b){
    return a * norm(b) + b * norm(a);
}
//projection
double proj(const Point &a, const Point &b){
    return a * b / norm(b);
}
//


//--------------------------------------lines------------------------------------------------


struct Line{
    Point a, ab;
    Line(const Point &a, const Point &b):a(a), ab(b-a){}
    Line():a(), ab(){}

    Point b(){
        return a + ab;
    }

};


bool online(const Line& l, Point& p){
    return ((p - l.a) ^ l.ab) == 0;
}


double dist(const Line& l, Point& p){
        return abs(((p-l.a)^l.ab)/norm(l.ab));
}

bool inter(const Line& s1, const Line &s2, Point& res){
    if((s1.ab ^ s2.ab) == 0)return 0; // parallel
    double t = ((s2.a - s1.a) ^ s2.ab) / (s1.ab ^ s2.ab);
    res = s1.a + s1.ab * t;
    return 1;
}

//-----------------------------segment----------------------------------



struct Segment{
    Point a, ab;
    Segment(const Point &a, const Point &b):a(a), ab(b-a){}
    Segment():a(), ab(){}

    Point b () const {
        return a + ab;
    }
};


bool onsegment(const Segment& r, const Point& p){
    return ((p - r.a) ^ r.ab) == 0 && ((p - r.a) * (p - r.b())) <= 0;
}


void  proj(const Point &p, const Segment &l, Point &res){
    res = l.a;
    res += l.ab *  ( ((p - l.a) * l.ab) / abs(l.ab) );
}

double dist(const Segment& r, const Point& p, Point &res){
	if((p - r.a) * (r.ab) <= 0) {
		res = r.a;
		return norm(p - r.a);
	}
	if((p - r.b()) * (-r.ab) <= 0) {
		res =  r.b();
		return norm(p - r.b());
	}

	proj(p, r, res);
    return abs(((p-r.a)^r.ab)/norm(r.ab));
}


bool inter(const Segment& s1, const Segment &s2, Point& res = any){
    if((s1.ab ^ s2.ab) == 0)return 0; // parallel
    double t1 = ((s2.a - s1.a) ^ s2.ab) / (s1.ab ^ s2.ab);
    double t2 = ((s1.a - s2.a) ^ s1.ab) / (s2.ab ^ s1.ab);
    if(t1 < 0 || t1 > 1 || t2 < 0 || t2 > 1)return 0;// does not intersect
    res = s1.a + s1.ab * t1;
    return 1;
}

//----------------------------------------------------------------------


int main() {
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);


	double mx, my, n, x, y, tmp, d;
	while(cin >> mx >> my >> n) {
		vector<Point> v;
		Point M(mx, my), res(0,0), ans(0,0);
		n += n+2;
		n /= 2;
		d = 1e9;

		while(n--) {
			cin >> x >> y;
			v.push_back(Point(x,y));
		}

		for(int i=0; i<v.size()-1; i++) {
			Segment L(v[i], v[i+1]);
			tmp = dist(L, M, res);
			if(tmp < d) {
				ans = res;
				d = tmp;
			}
		}

		printf("%.4f\n%.4f\n", ans.x, ans.y);
	}
    return 0;
}
