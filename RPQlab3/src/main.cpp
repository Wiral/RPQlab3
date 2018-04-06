#include <iostream>
#include <fstream>
#include <algorithm>

//Task class
class PWDtask {
	 int _p; 	// preparing time
	 int _w ;	// processing time
	 int _d;	// quiting time
	// int _t;
public:
	PWDtask( int p, int w, int d): _p(p),_w(w), _d(d) {} //init with default times for the current process, init starting time with the preparing time
	PWDtask(): _p(0), _w(0), _d(0){}
	void setP( int p) { _p = p;}
	//void setT(int t) { _t = t;}
	void setW( int w) { _w = w;}
	void setD( int d) { _d = d;}
	const int p() const {return _p;}
	const int w() const {return _w;}
	const int d() const {return _d;}
	//const int t() const {return _t;}
};

class PWDproc {
	PWDtask* _tasks = nullptr;
	int _numTasks = 0;
	int _numCol = 0;

public:
	PWDproc(std::fstream& file);	//init structure with tasks using the file
	~PWDproc() {
		delete[] _tasks;
	}
	int procTime();	//calculates the time needed to finish and close all the tasks (cMax)
	int numTasks() {
		return _numTasks;
	}	//number of tasks in the _task array
	int tardness();
};

int PWDproc::tardness(){
	int c = 0;
	int t = 0;
	int i = 0;
	for(; i < _numTasks; i++){
		c += _tasks[i].p();
		t += std::max(c - _tasks[i].d(), 0) * _tasks[i].w();
	}

	return t;
}

//initialize structure with tasks specified in a file
PWDproc::PWDproc(std::fstream& file) {
	int p,w,d, i;
	file >> _numTasks;
	_tasks = new PWDtask[_numTasks];

	for (i = 0; i < _numTasks; i++) {
		file >> p;
		file >> w;
		file >> d;
		_tasks[i] = PWDtask(p,w,d);
	}

}

int main() {
	std::string path_names, path;
	std::fstream file_names, file, output;
	std::cout << "Wskaz sciezke do pliku z nazwami: \n";
	std::cin >> path_names;

	output.open("output.txt");
	file_names.open(path_names.c_str());

	if (file_names.is_open()) {
		while (!file_names.eof()) {	//read file names to open
			file_names >> path;
			file.open(path.c_str());
			if (file.is_open()) {//open file and read data. Save it to the txt file.
				std::cout << "==== " << path << " ====" << std::endl;
				PWDproc process(file);
				std::cout << "T: " << process.tardness() <<std::endl;
				file.close();
			}
		}

	}

	return 0;
}


