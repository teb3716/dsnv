#include "Edge.h"

Edge::Edge() {//edge initialize
	m_key = 0;
	m_weight = 0;
	m_pNext = nullptr;
}
Edge::Edge(int key, int weight) {//edge initialize with key, weight
	m_key = key;
	m_weight = weight;
	m_pNext = nullptr;
}
void Edge::SetNext(Edge* pNext) {//set next edge
	m_pNext = pNext;
}
int Edge::GetKey() const {//get key
	return m_key;
}

/// get the weight of this edge
int Edge::GetWeight() const {//get weight
	return m_weight;
}

/// get the next pointer of this edge
Edge* Edge::GetNext() const {//get next edge
	return m_pNext;
}
