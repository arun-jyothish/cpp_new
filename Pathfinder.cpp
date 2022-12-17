#include <iostream>
#include <map>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std; 

void errLog(int);

template<typename T>
class Solution{
	private:
		/* vector<vector<int>> mat; */
		T mat;
		vector<vector<pair<int,int>>> solutionMatrix;
		pair<int,int> SourcePair;
		pair<int,int> DestPair;
		pair<int,int> Initialpair{-1,-1};
		vector<vector<pair<int,int>>> result;
	public:
		void fstore(string fileName,void (*fn)(ostream&));
		vector<pair<int,int>> mkPairlist(pair<int,int> Npr ,pair<int,int> Ppr);
		void getPath(pair<int,int> Spr ,pair<int,int> Ppr );
		vector <vector<char>> generateMatrix();
		vector <vector<char>> generateMatrix(int rw,int cl);
		void printVisual(auto mat,auto vect,auto Spr,auto Dpr);
		void printPaths(ostream& out=cout);
		void print(ostream& out = cout);
		void sortSolution();
		pair<pair<int,int>,pair<int,int>> randomPositionTarget();
		void putTargets (pair<pair<int,int>,pair<int,int>> TargetPairs);
		bool comp(vector<pair<int,int>> element1,vector<pair<int,int>> element2);
		vector<vector<pair<int,int>>> allPaths();
		T getMatrix()	{
			return mat;
		}
		Solution(){};
		Solution(T mat){
			if( typeid(T) != typeid(vector<vector<char>>) ){
				cout << "Wrong Type Matrix Recieved"<<endl;
					errLog(112);
				return;
			}
			this->mat = mat;
		}
};

template <typename T>
void Solution<T>::putTargets (pair<pair<int,int>,pair<int,int>> TargetPairs){
	SourcePair = TargetPairs.first;
	DestPair = TargetPairs.second;
}
template <typename T>
bool Solution<T>::comp(vector<pair<int,int>> element1,vector<pair<int,int>> element2){
	return element1.size()<element2.size();
}
template <typename T>
void Solution<T>::sortSolution(){
	sort(solutionMatrix.begin(),solutionMatrix.end(),comp);
}
// put random rat and cheese
template <typename T>
pair<pair<int,int>,pair<int,int>> Solution<T>::randomPositionTarget(){
	pair<int,int> Spr;
	pair<int,int> Dpr;

	Spr.first = rand()%mat.size();
	Spr.second = rand()%mat[0].size();
	mat[Spr.first][Spr.second]	= '&';		// rat
							//
	Dpr.first = rand()%mat.size();
	Dpr.second = rand()%mat[0].size();
	mat[Dpr.first][Dpr.second]	= '@';		// cheese

	return {Spr,Dpr};
}

template <typename T>
void Solution<T>::fstore(string fileName,void (*fn)(ostream&)){
	// fstore function receives any object and perform _obj.print(store)_  operation
	// in which store is a output file stream.
	//
	// print() function should be print(ostream& out) where _out_ recieves file stream & when calling this function
	
	/* fstream store("out.txt",ios::out); */
	fstream store(fileName,ios::app);
	fn(store);
	store.close();
}
int otherMain();

// Generate Random bool matrix , when row and coloumn are specified.
template <typename T>
vector<vector<char>> Solution<T>::generateMatrix(int rw,int cl){
	vector<char> arr;
	vector <vector<char>> matrix;
	for (int i=0; i< rw; ++i){
		for (int j=0; j< cl; ++j){
			bool state = rand()%7 <= 1;			// probability of tracks 1/7
			char ch = state?'.':' ';
			arr.push_back(ch);
		}
		matrix.push_back(arr);
		arr.clear();
	}
	return matrix;
}

// Generate random matrix
template <typename T>
vector <vector<char>> Solution<T>::generateMatrix(){
	 int cl = 19+rand()%9;	// random number bw 3 and 8
	 int rw = 19+rand()%9;
	 return generateMatrix(rw,cl);
}

/* int nextMain(){ */
int main(int argc, char *argv[])
{
	srand(time(0));
	/* auto ranMat = generateMatrix(); */
	Solution<vector<vector<char>>> S1;
	S1.generateMatrix();
	auto pos = S1.randomPositionTarget();
	S1.print();
	S1.putTargets(pos);
	/* S1.getPath(pos.first,pos.second); */
	S1.printPaths();
	/* cout << S1.result.empty(); */
	/*
	errLog(0xFF01);
	errLog(0x0A01);
	errLog(0x0FF1);
	S1.print();
	*/
	return 0;
}


template<typename T>
void Solution<T>::print(ostream& out){
	if ( typeid(this->mat) != typeid(vector<vector<char>>))
	{
	out << "type doesn't match" <<endl;
	return;
	}
	out << "\tGIVEN MATRIX "<<endl;
	out <<"ROWS: " << mat.size()<<" COLOUMS: "<< mat[0].size()<<endl;
	for (auto arr: mat){
		for ( auto val: arr ){
			out <<"  "<< val;
		}
		out << endl;
	}
	out << endl;
}

template<typename T>
void Solution<T>::getPath( pair<int,int> Spr, pair<int,int> Ppr) {
	static vector<pair<int,int>> temp;
	static map <pair<int,int>,bool> mp;
	if (Spr == DestPair){
		/* cout << "dest reach" <<endl; */
		temp.push_back(Spr);
		result.push_back(temp);
		/* mp.clear(); */
		temp.pop_back();
	}
	else if(mp[Spr]){
 	/* cout << "same node"  <<endl; */
	}
	else{
		/* cout << "else"  <<endl; */
		temp.push_back(Spr);
		mp[Spr] = true;
		/* printList(temp); */
		auto nextPathlist = mkPairlist(Spr,Ppr);
		/* printList(nextPathlist); */
		for (auto CurrentPair: nextPathlist){
			getPath(CurrentPair,Spr);
		}
		mp[temp.back()]=false;
		temp.pop_back();
	}
}
// print obtained paths
template<typename T>
void Solution<T>::printPaths(ostream& out){
	for (auto arr: solutionMatrix){
		for(auto pr:arr ){
			out << "("<<pr.first << "," <<pr.second <<")";
			out << "->" ;
		}
		out <<endl;
	}
}
void errLog(int errInt){
	fstream err("errLog.txt",ios::app);
	err << errInt ;
	/* err.width(10); */
	err << "\t:";
	/* err.width(20); */
	if (errInt > 0xAA00){
		err <<"\t\t\t";
	}
	else if (errInt > 0x0A00){
		err <<"\t\t";
	}
	else if (errInt > 0x00FF){
		err <<"\t";
	}
	switch(errInt)
	{
		case 0x00FA:
			err << "Matrix type doesn't match" ;
			break;
		case 0xFFFF:
			err << "recursion timeout" ;
			break;
		default:
			/* err.width(6); */
			err << "error";
	}
	err << endl;
}

template<typename T>
void Solution<T>::printVisual(auto mat,auto vect,auto Spr,auto Dpr){
	pair<int,int> pr;
	map<pair<int,int>,bool> mp; 
	for (auto cont: vect){
		cout <<endl<<"New Path:"<<endl;
		for (auto Mpr: cont){
			mp[Mpr] = true;
		}
			for(int i=0; i <mat.size(); ++i){
				for(int j=0; j <mat[0].size(); ++j){
					pr = {i,j};
					if ( pr == Spr){
							cout <<" & ";
					}
					else if ( pr == Dpr){
							cout <<" @ ";
					}
						else if(mp[pr]){
							cout <<" . ";
						}
						else
							cout << "   ";
					}
				cout<<endl;
		}
			mp.clear();
	}
}

template<typename T>
vector<pair<int,int>> Solution<T>::mkPairlist(pair<int,int> Npr ,pair<int,int> Ppr){
	pair<int,int> pr;
	vector<pair<int,int>> rtPr;
	int rwSize = mat.size();
	int clSize = mat[0].size();

	pair<int,int> rightPr = {Npr.first+1, Npr.second};
	pair<int,int> leftPr= {Npr.first-1, Npr.second};
	pair<int,int> bottomPr = {Npr.first, Npr.second+1};
	pair<int,int> topPr = {Npr.first, Npr.second-1};

	vector<pair<int,int>> direction = { rightPr,bottomPr,leftPr,topPr };

	for (auto pr: direction){
		if ( pr.first < rwSize && pr.first >= 0 ){
			if ( pr.second < clSize && pr.second >= 0 )
				if ( pr == Ppr);
				else
				{
					/* int  ch = mat[pr.first][pr.second]; */
					char ch = mat[pr.first][pr.second];
					/* if (ch == 1) */
					if (ch == '.')
					rtPr.push_back(pr); 
				}
		}
	}
	return rtPr;
}