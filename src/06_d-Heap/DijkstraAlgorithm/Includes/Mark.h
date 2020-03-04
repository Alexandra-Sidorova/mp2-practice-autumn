#ifndef _MARK_H_
#define _MARK_H_

class Mark
{
public:
	int vert;
	float dist;
	
	Mark() : vert(0), dist(0) {};
	Mark(int, float);
	Mark(const Mark&);
	~Mark() {};

	const Mark& operator=(const Mark&);
	bool operator>(const Mark&) const;
	bool operator>=(const Mark&) const;
	bool operator<(const Mark&) const;
	bool operator<=(const Mark&) const;
};

#endif