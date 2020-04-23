#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include "main.h"

bool canGet(Vehicul* v, Package p) {
	if (p.eRece())
		if (Duba* d = dynamic_cast<Duba*>(v))
			if (!d->eFrigorific()) return false;
		else return false;
	if (v->getSpace() < p.getSize()) return false;
	if (p.getTime() < 0) {
		if (v->getTimeToDest(p.getDest()) > p.getTime()) return false;
	}
	else if (p.getTime() > 0) {
		if (p.getTime() + v->getTimeToDest(p.getDest()) > p.getTime()) return false;
	}
	return true;
}

Vehicul::Vehicul() : size(0), time(0), speed(0), receive(stratVeh::closest), send(stratVeh::closest) {
	pos.x = pos.y = 0;
}

Vehicul::Vehicul(int speed) : size(0), time(0), speed(speed), receive(stratVeh::closest), send(stratVeh::closest) {
	pos.x = pos.y = 0;
}

Vehicul::Vehicul(int size, int speed, position pos, stratVeh receive, stratVeh send)
	: size(size), speed(speed), pos(pos), receive(receive), send(send), time(0) {}

Vehicul::~Vehicul() {
	try {
		if (storage.size() != 0) throw "Vehicle still has packages";
	}
	catch (const char* msg) {
		std::cout << msg;
	}
}

Scuter::Scuter() : Vehicul(20) {}

Scuter::Scuter(int size, position pos, stratVeh receive, stratVeh send)
	: Vehicul(size, 20, pos, receive, send) {}

Masina::Masina() : Vehicul(10) {}

Masina::Masina(int size, position pos, stratVeh receive, stratVeh send)
	: Vehicul(size, 10, pos, receive, send) {}

Duba::Duba() : Vehicul(5), frigorific(false) {}

Duba::Duba(int size, position pos, stratVeh receive, stratVeh send, bool frigorific)
	: Vehicul(size, 5, pos, receive, send), frigorific(frigorific) {}

bool Duba::eFrigorific() { return frigorific; }

double Vehicul::getTimeToDest(position dest) {
	return 0;
}

double Scuter::getTimeToDest(position dest) {
	return sqrt(pow(pos.x - dest.x, 2) + pow(pos.y - dest.y, 2)) / speed;
}

double Masina::getTimeToDest(position dest) {
	return (abs(pos.x - dest.x) + abs(pos.y - dest.y)) / speed;
}

double Duba::getTimeToDest(position dest) {
	return (abs(pos.x - dest.x) + abs(pos.y - dest.y)) / speed;
}

void Vehicul::pickUp(Package pkg) {
	storage.push_back(pkg);
}

void Vehicul::drop(Package pkg) {
	storage.erase(std::find(storage.begin(), storage.end(), pkg));
}

void Vehicul::deliver(Package pkg) {
	time += getTimeToDest(pkg.getDest());
	pos = pkg.getDest();
	drop(pkg);
}

Package::Package() : time(0), size(0), rece(false) {
	src.x = src.y = dest.x = dest.y = 0;
}

Package::Package(double time, int size, bool rece, position src, position dest)
	: time(time), size(size), rece(rece), src(src), dest(dest) {}

double Package::getTime() { return time; }

int Package::getSize() { return size; }

bool Package::eRece() { return rece; }

position Package::getDest() { return dest; }

position Package::getSrc() { return src; }

bool Package::operator==(const Package& o) {
	return dest.x == o.dest.x &&
			dest.y == o.dest.y &&
			time == o.time &&
			rece == o.rece &&
			size == o.size;
}

int Vehicul::getSpace() {
	int used = 0;
	for (auto& pkg : storage) {
		used += pkg.getSize();
	}
	return size - used;
}

std::ostream& operator<<(std::ostream& os, const Vehicul& v) {
	os << "Vehicul la pozitia " << v.pos.x << ", " << v.pos.y << ", cu capacitatea " << v.size << ", in momentul " << v.time << ", cu viteza " << v.speed << ", cu strategiile ";
	switch (v.receive) {
	case stratVeh::closest:
		std::cout << "closest";
		break;
	case stratVeh::first:
		std::cout << "first";
		break;
	case stratVeh::urgent:
		std::cout << "urgent";
		break;
	}
	std::cout << " si ";
	switch (v.send) {
	case stratVeh::closest:
		std::cout << "closest";
		break;
	case stratVeh::first:
		std::cout << "first";
		break;
	case stratVeh::urgent:
		std::cout << "urgent";
		break;
	}
	std::cout << ", cu pachetele:\n";
	for (auto& pkg : v.storage) {
		os << pkg;
	}
	return os;
}

std::istream& operator>>(std::istream& is, Vehicul& v) {
	is >> v.pos.x >> v.pos.y >> v.size;
	std::string s = "";
	while (s == "") std::getline(is, s);
	if (s == "closest") {
		v.receive = stratVeh::closest;
	} else if (s == "first") {
		v.receive = stratVeh::first;
	} else if (s == "urgent") {
		v.receive = stratVeh::urgent;
	}
	s = "";
	while (s == "") std::getline(is, s);
	if (s == "closest") {
		v.send = stratVeh::closest;
	}
	else if (s == "first") {
		v.send = stratVeh::first;
	}
	else if (s == "urgent") {
		v.send = stratVeh::urgent;
	}
	return is;
}

Vehicul& Vehicul::operator=(const Vehicul& v) {
	pos = v.pos;
	receive = v.receive;
	send = v.send;
	size = v.size;
	speed = v.speed;
	storage = v.storage;
	time = v.time;

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Scuter& s) {
	os << "Scuter la pozitia " << s.pos.x << ", " << s.pos.y << ", cu capacitatea " << s.size << ", in momentul " << s.time << ", cu viteza " << s.speed << ", cu strategiile ";
	switch (s.receive) {
	case stratVeh::closest:
		std::cout << "closest";
		break;
	case stratVeh::first:
		std::cout << "first";
		break;
	case stratVeh::urgent:
		std::cout << "urgent";
		break;
	}
	std::cout << " si ";
	switch (s.send) {
	case stratVeh::closest:
		std::cout << "closest";
		break;
	case stratVeh::first:
		std::cout << "first";
		break;
	case stratVeh::urgent:
		std::cout << "urgent";
		break;
	}
	std::cout << ", cu pachetele:\n";
	for (auto& pkg : s.storage) {
		os << pkg;
	}
	return os;
}

std::istream& operator>>(std::istream& is, Scuter& s) {
	Vehicul& r = s;
	return is >> r;
}

Scuter& Scuter::operator=(const Scuter& s) {
	Vehicul& r = *this;
	r = s;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Masina& m) {
	os << "Masina la pozitia " << m.pos.x << ", " << m.pos.y << ", cu capacitatea " << m.size << ", in momentul " << m.time << ", cu viteza " << m.speed << ", cu strategiile ";
	switch (m.receive) {
	case stratVeh::closest:
		std::cout << "closest";
		break;
	case stratVeh::first:
		std::cout << "first";
		break;
	case stratVeh::urgent:
		std::cout << "urgent";
		break;
	}
	std::cout << " si ";
	switch (m.send) {
	case stratVeh::closest:
		std::cout << "closest";
		break;
	case stratVeh::first:
		std::cout << "first";
		break;
	case stratVeh::urgent:
		std::cout << "urgent";
		break;
	}
	std::cout << ", cu pachetele:\n";
	for (auto& pkg : m.storage) {
		os << pkg;
	}
	return os;
}

std::istream& operator>>(std::istream& is, Masina& m) {
	Vehicul& r = m;
	return is >> r;
}

Masina& Masina::operator=(const Masina& m) {
	Vehicul& r = *this;
	r = m;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Duba& d) {
	os << "Duba" << (d.frigorific ? " frigorifica" : "") << " la pozitia " << d.pos.x << ", " << d.pos.y << ", cu capacitatea " << d.size << ", in momentul " << d.time << ", cu viteza " << d.speed << ", cu strategiile ";
	switch (d.receive) {
	case stratVeh::closest:
		std::cout << "closest";
		break;
	case stratVeh::first:
		std::cout << "first";
		break;
	case stratVeh::urgent:
		std::cout << "urgent";
		break;
	}
	std::cout << " si ";
	switch (d.send) {
	case stratVeh::closest:
		std::cout << "closest";
		break;
	case stratVeh::first:
		std::cout << "first";
		break;
	case stratVeh::urgent:
		std::cout << "urgent";
		break;
	}
	std::cout << ", cu pachetele:\n";
	for (auto& pkg : d.storage) {
		os << pkg;
	}
	return os;
}

std::istream& operator>>(std::istream& is, Duba& d) {
	Vehicul& r = d;
	is >> r;
	std::string s = "";
	while (s == "") getline(is, s);
	if (s == "true") d.frigorific = true;
	else if (s == "false") d.frigorific = false;
	else throw "Invalid boolean value";
	return is;
}

Duba& Duba::operator=(const Duba& v) {
	Vehicul& r = *this;
	r = v;
	this->frigorific = v.frigorific;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Package& p) {
	os << "Pachet" << (p.rece ? " rece" : "") << " de la pozitia "  << p.src.x << ", " << p.src.y << " pentru pozitia " << p.dest.x << ", " << p.dest.y << " de marimea " << p.size;
	if (p.time > 0) {
		os << " pana la " << p.time << "\n";
	}
	else if (p.time < 0) {
		os << " in " << p.time << "\n";
	}
	return os;
}

std::istream& operator>>(std::istream& is, Package& p) {
	std::string s = "";
	is >> p.src.x >> p.src.y >> p.dest.x >> p.dest.y >> p.size;
	while (s == "") std::getline(is, s);
	if (s == "any") p.time = 0;
	else if (s == "until") is >> p.time;
	else if (s == "in") {
		is >> p.time;
		p.time = -p.time;
	}
	else throw "Invalid indicator for time value";

	s = "";
	while (s == "") std::getline(is, s);
	if (s == "rece" || s == "true") p.rece = true;
	else if (s == "false") p.rece = false;
	else throw "Invalid boolean value";

	return is;
}

Package& Package::operator=(const Package& p) {
	dest.x = p.dest.x;
	dest.y = p.dest.y;
	src.x = p.src.x;
	src.y = p.src.y;
	rece = p.rece;
	size = p.size;
	time = p.time;

	return *this;
}

std::vector<Vehicul*> read_n_veh(std::istream& is, int n) {
	std::vector<Vehicul*> v;
	for (int i = 0; i < n; i++) {
		std::string s = "";
		while (s == "") std::getline(is, s);
		Vehicul* p;
		if (s == "Scuter") {
			p = new Scuter();
			is >> *dynamic_cast<Scuter*>(p);
		}
		else if (s == "Masina") {
			p = new Masina();
			is >> *dynamic_cast<Masina*>(p);
		}
		else if (s == "Duba") {
			p = new Duba();
			is >> *dynamic_cast<Duba*>(p);
			std::cout << *dynamic_cast<Duba*>(p);
		}
		else {
			throw "Vehicul invalid";
		}
		v.push_back(p);
	}
	return v;
}

std::vector<Package*> read_n_pac(std::istream& is, int n) {
	std::vector<Package*> v;
	for (int i = 0; i < n; i++) {
		Package* p = new Package();
		is >> *p;
		v.push_back(p);
	}
	return v;
}

int main()
{
	std::fstream f("input.txt", std::ios::in);
	std::vector<Vehicul*> v;
	std::vector<Package*> p;
	try {
		int n, m;
		f >> n;
		v = read_n_veh(f, n);
		f >> m;
		p = read_n_pac(f, m);
	}
	catch (const char* e) {
		std::cout << e;
	}
	return 0;
}