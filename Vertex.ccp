#include "Vertex.h"

Vertex::Vertex() {//vertex initialize
	m_key = 0;
	m_size = 0;
	m_pEHead = nullptr;
	m_pNext = nullptr;
}
Vertex::Vertex(int n) {//vertex initialize with key, size
	m_key = n;
	m_size = 0;
	m_pEHead = nullptr;
	m_pNext = nullptr;
}
void Vertex::SetNext(Vertex* pNext) {//set next vertex
	m_pNext = pNext;
}
int Vertex::GetKey() const {//get key
	return m_key;
}
Vertex* Vertex::GetNext() const {//get next vertex
	return m_pNext;
}
int Vertex::Size() const {//get vertex size
	return m_size;
}
void Vertex::AddEdge(int edgeKey, int weight) {//add edge
	int i;
	Edge* e = new Edge(edgeKey, weight);
	if (m_pEHead == nullptr) {//if no edge
		m_pEHead = e;
		m_size = 1;
	}
	else {
		Edge* end = m_pEHead;
		for (i = 2; i <= m_size; i++) end = end->GetNext();
		end->SetNext(e);//link edeg
		m_size++;
	}
}
Edge* Vertex::GetHeadOfEdge() const {//get head of edge
	return m_pEHead;
}
void clear(Edge* e) {//clear edge
	if (e->GetNext() != nullptr) clear(e->GetNext());
	delete e;
}
void Vertex::Clear() {
	clear(m_pEHead);
}
Vertex::~Vertex() {
	Clear();
}
