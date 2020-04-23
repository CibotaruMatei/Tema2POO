#pragma once
#include <vector>

enum class stratVeh { urgent, closest, first };

enum class stratFirm { closest, fastest, fewest };

struct position {
	double x, y;
};

class Package {
private:
	double time;
	int size;
	bool rece;
	position dest, src;
public:
	Package();
	Package(double, int, bool, position, position);
	double getTime();
	int getSize();
	bool eRece();
	position getDest();
	position getSrc();
	bool operator==(const Package&);
	friend std::ostream& operator<<(std::ostream&, const Package&);
	friend std::istream& operator>>(std::istream&, Package&);
	Package& operator=(const Package&);
};

class Vehicul {
protected:
	double time;
	int size, speed;
	position pos;
	stratVeh receive, send;
	std::vector<Package> storage;
public:
	Vehicul();
	Vehicul(int);
	Vehicul(int, int, position, stratVeh, stratVeh);
	~Vehicul();
	virtual double getTimeToDest(position);
	void pickUp(Package);
	void drop(Package);
	void deliver(Package);
	int getSpace();
	friend std::ostream& operator<<(std::ostream&, const Vehicul&);
	friend std::istream& operator>>(std::istream&, Vehicul&);
	Vehicul& operator=(const Vehicul&);
};

class Scuter : public Vehicul {
public:
	Scuter();
	Scuter(int, position, stratVeh, stratVeh);
	double getTimeToDest(position dest) override;
	friend std::ostream& operator<<(std::ostream&, const Scuter&);
	friend std::istream& operator>>(std::istream&, Scuter&);
	Scuter& operator=(const Scuter&);
};

class Masina : public Vehicul {
public:
	Masina();
	Masina(int, position, stratVeh, stratVeh);
	double getTimeToDest(position dest) override;
	friend std::ostream& operator<<(std::ostream&, const Masina&);
	friend std::istream& operator>>(std::istream&, Masina&);
	Masina& operator=(const Masina&);
};

class Duba : public Vehicul {
private:
	bool frigorific;
public:
	Duba();
	Duba(int, position, stratVeh, stratVeh, bool);
	double getTimeToDest(position dest) override;
	bool eFrigorific();
	friend std::ostream& operator<<(std::ostream&, const Duba&);
	friend std::istream& operator>>(std::istream&, Duba&);
	Duba& operator=(const Duba&);
};