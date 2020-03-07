#include "Edge.h"
#include "exceptions.h"

Edge::Edge()
{
	weight = start = end = 0;
};

Edge::Edge(int _w, int _s, int _e)
{
	if (_w < 0 ||_s < 0 ||_e < 0)
		throw Exception("Incorrect edge's data!");

	weight = _w;
	start = _s;
	end = _e;
};

Edge::~Edge()
{
	weight = start = end = 0;
};
//------------------------------------------

int Edge::GetWeight() const
{
	return weight;
};

int Edge::GetStart() const
{
	return start;
};

int Edge::GetEnd() const
{
	return end;
};

const Edge& Edge::operator=(const Edge& _e)
{
	if (this == &_e)
		return *this;

	weight = _e.weight;
	start = _e.start;
	end = _e.end;

	return *this;
};

bool Edge::operator>(const Edge& _e) const
{
	return (weight > _e.weight);
};

bool Edge::operator>=(const Edge& _e) const
{
	return (weight >= _e.weight);
};

bool Edge::operator<(const Edge& _e) const
{
	return (weight < _e.weight);
};

bool Edge::operator<=(const Edge& _e) const
{
	return (weight <= _e.weight);
};

ostream& operator<<(ostream& _out, const Edge& _edge)
{
	_out << "Start: " << _edge.GetStart() << " End: " << _edge.GetEnd() << " Weight: " << _edge.GetWeight();

	return _out;
};