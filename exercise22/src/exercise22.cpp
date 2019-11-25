
// author : Gabriel De Ioannes
// author : Sagar Nagaraj

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <math.h>

using namespace std;

class Point{
public:
	bool pick=true;
	float x=0;
	float y=0;
};

vector<Point> GetPointList();
int ORI(Point p1, Point p2,Point p3);
Point PointLineDistance(Point a, Point b, vector<Point> list);
vector<Point> DeleteDuplicates(vector<Point> list);
bool ComparePoints(Point a, Point b);


int main() {
	vector<Point> points = GetPointList();

	vector<Point> hull;
	Point point;
	bool endHull=false;
	int hullCounter=0;

	while(points.size()>2){
	++hullCounter;
	hull.clear();
	hull.push_back(point);
	hull.push_back(point);
	hull.push_back(point);
	hull.push_back(point);

	//cout << "end" << endl;
	for(int i=0;i<points.size();i++){
		if(points[i].x > hull[3].x || hull[3].pick){
			hull[3]=points[i];
			hull[3].pick=false;
		}
		if(points[i].y > hull[2].y || hull[2].pick){
			hull[2]=points[i];
			hull[2].pick=false;
		}
		if(points[i].x < hull[1].x || hull[1].pick){
			hull[1]=points[i];
			hull[1].pick=false;
		}
		if(points[i].y < hull[0].y || hull[0].pick){
			hull[0]=points[i];
			hull[0].pick=false;
		}
	}

	hull=DeleteDuplicates(hull);

	vector<Point> pbl;
	int count=hull.size()-1;
	bool noMorePointsFlag=true;

		while(!endHull){
			//Point Between Lines clear in every iteration
			pbl.clear();
			for(int i=0;i<points.size();i++){
				if(count==0){
					//Last and first comparison
					if(ORI(hull[0],hull[hull.size()-1],points[i])==-1
							&& !(ComparePoints(points[i],hull[0]) ||
									ComparePoints(points[i],hull[hull.size()-1]))){
						pbl.push_back(points[i]);
						noMorePointsFlag=false;
					}
				}else{
					//Compare by segments counter-clock whise 3-2 2-1 1-0 0-3
					if(ORI(hull[count],hull[count-1],points[i])==-1
							&& !(ComparePoints(points[i],hull[count]) ||
									ComparePoints(points[i],hull[count-1])||
										ComparePoints(hull[count],hull[count-1]))){
						pbl.push_back(points[i]);
						noMorePointsFlag=false;
					}
				}
			}
			if(pbl.size()!=0){
				Point farPoint=PointLineDistance(hull[count],hull[count-1],pbl);
				hull.insert(hull.begin()+count,farPoint);
			}
			count--;
			if(count==-1){
				if(noMorePointsFlag){
					endHull=true;
				}else{
					noMorePointsFlag=true;
					count=hull.size()-1;
				}
			}
		}

		cout << hull.size() << " # "<< hullCounter << "st onion layer ( convex hull ) contains "<<hull.size()<<" points" << endl;

		for(int i=0;i<hull.size();i++){
			cout << hull[i].x << " " << hull[i].y << endl;
		}

		//Delete use points
		for(int i=0;i<hull.size();i++){
			for(int k=0;k<points.size();k++){
				if(ComparePoints(hull[i],points[k])){
					points.erase(points.begin()+k);
					break;
				}
			}
		}
	}
}

vector<Point> DeleteDuplicates(vector<Point> list){
	for(int i=0;i<list.size();i++){
		for(int k=0;k<list.size();k++){
			if(i!=k){
				if(ComparePoints(list[i],list[k])){
					list.erase(list.begin()+i);
					break;
				}
			}
		}

	}
	return list;
}

vector<Point> GetPointList(){
	string str;
	int num;
	int count=0;
	getline(cin,str);
	istringstream ss(str);
	//Number of points
	ss >> num;
	//List of Points
	vector<Point> points;
	while(getline(cin,str)){
		istringstream ss(str);
		Point point;
		ss >> point.x >> point.y;
		points.push_back(point);
		count++;
		if(count==num){
			break;
		}
	}

	return points;
}

Point PointLineDistance(Point a, Point b, vector<Point> list){

	Point f;
	float saveh=0;

	for(int i=0;i<list.size();i++){
		Point c=list[i];
		float s1= sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
		float s2=sqrt(pow(a.x-c.x,2)+pow(a.y-c.y,2));
		float s3=sqrt(pow(b.x-c.x,2)+pow(b.y-c.y,2));
		float s=(s1+s2+s3)/2;
		float area= sqrt(s*(s-s1)*(s-s2)*(s-s3));
		float h=area/(0.5*s1);
		if(saveh<h){
			saveh=h;
			f=c;
		}
	}
	return f;
}

bool ComparePoints(Point a, Point b){
	return a.x == b.x && a.y==b.y;
}

int ORI(Point p1, Point p2,Point p3){
	double dx21 = p2.x - p1.x;
	double dy21 = p2.y - p1.y;
	double dx31 = p3.x - p1.x;
	double dy31 = p3.y - p1.y;
	if (dx21*dy31 < dy21*dx31) return -1; // ccw

	if (dx21*dy31 > dy21*dx31) return +1; // cw

	if (dx21*dx31 < 0 || dy21*dy31<0) return -1; // ccw

	if (dx31*dx31 + dy31*dy31 > dx21*dx21 + dy21*dy21) return +1; //cw

	return 0; // p3 is inside p1,p2
}
