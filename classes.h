//LABKA 2-4 v.1 Class
#pragma once

struct Monom {
	double coef{ 0 };
	double pow{ 0 };
};

class Polynom {
private:
	struct LE {
		Monom data;
		LE* next;
	};
	LE* first{ nullptr };
public:
	Polynom() = default;
	Polynom(const Polynom&);
	Polynom(Polynom&&) noexcept;
	Polynom& operator = (const Polynom&);
	Polynom& operator = (Polynom&&) noexcept;
	Polynom operator + (const Polynom&) const;
	Polynom operator - (const Polynom&) const;
	Polynom& operator += (const Polynom&);
	~Polynom();

	void push(const Monom&);
	bool pop(Monom&);
	void dispose();

	class Iter {
	public:
		Iter() = default;
		Iter(Polynom::LE*);
		Monom& operator*();
		Iter& operator ++ (); // ++i
		Iter& operator ++ (int); // i++
		bool operator == (const Iter&);
		bool operator != (const Iter&);
	private:
		LE* current{ nullptr };
	};
	Iter begin() const;
	Iter end() const;
};

void operator >>(std::istream& s, Polynom& p);
void operator <<(std::ostream& s, const Polynom& p);

void close(std::istream& s);
void close(std::ostream& s);
