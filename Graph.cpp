#include "Graph.h"
#include "Stack.h"
#include "MinHeap.h"
#include <set>

#define DFS_FIRST_PATH

template<typename TKey, typename TValue>
void MinHeap<TKey, TValue>::Push(TKey key, TValue value) {//push heap
	m_vec.push_back({ key,value });
	int i = m_vec.size()-1;
	while (1) {
		if (i == 0) break;
		if (m_vec[(i + 1) / 2 - 1].first > m_vec[i].first) {//if parent node is bigger than current node
			int tmp;//change
			tmp = m_vec[(i + 1) / 2 - 1].first;
			m_vec[(i + 1) / 2 - 1].first = m_vec[i].first;
			m_vec[i].first = tmp;
			tmp = m_vec[(i + 1) / 2 - 1].second;
			m_vec[(i + 1) / 2 - 1].second = m_vec[i].second;
			m_vec[i].second = tmp;
		}
		i = (i + 1) / 2 - 1; 
	}
}

template<typename TKey, typename TValue>
void MinHeap<TKey, TValue>::Pop() {//pop
	m_vec[0] = m_vec[m_vec.size()-1];
	m_vec.pop_back();
	int i = 0, si = m_vec.size() - 1;
	while (1) {
		if ((i + 1) * 2 - 1 > si) break;//no child
		if ((i + 1) * 2 > si) {//one child
			if (m_vec[(i + 1) * 2 - 1].first < m_vec[i].first) {//child node is smaller than current node
				pair<int, int> tmp = m_vec[i];//swap
				m_vec[i] = m_vec[(i + 1) * 2 - 1];
				m_vec[(i + 1) * 2 - 1] = tmp;
				i = (i + 1) * 2 - 1;
			}
			else break;
		}
		else {
			if (m_vec[(i + 1) * 2 - 1].first < m_vec[(i + 1) * 2].first) {//left child is small
				if (m_vec[(i + 1) * 2 - 1].first < m_vec[i].first) {//child node is smaller than current node
					pair<int, int> tmp = m_vec[i];//swap
					m_vec[i] = m_vec[(i + 1) * 2 - 1];
					m_vec[(i + 1) * 2 - 1] = tmp;
					i = (i + 1) * 2 - 1;
				}
				else break;
			}
			else {
				if (m_vec[(i + 1) * 2].first < m_vec[i].first) {//child node is smaller than current node
					pair<int, int> tmp = m_vec[i];//swap
					m_vec[i] = m_vec[(i + 1) * 2];
					m_vec[(i + 1) * 2] = tmp;
					i = (i + 1) * 2;
				}
				else break;
			}
		}
	}
}
template<typename TKey, typename TValue>
std::pair<TKey, TValue> MinHeap<TKey, TValue>::Top() {
	return m_vec[0];//return top
}
template<typename TKey, typename TValue>
std::pair<TKey, TValue> MinHeap<TKey, TValue>::Get(TValue target) {
	int i;
	for (i = 0; i < m_vec.size(); i++) {
		if (m_vec[i].second == target) return m_vec[i];
	}
}
template<typename TKey, typename TValue>
void MinHeap<TKey, TValue>::Heapify(int index) {//sort heap
	vector<pair<int,int>> v;
	int i, si = m_vec.size();
	for (i = 0; i < si; i++) {
		v.push_back(Top());
		Pop();
	}
	for (i = 0; i < si; i++) {
		m_vec.push_back(v[i]);
	}
}
template<typename TKey, typename TValue>
bool MinHeap<TKey, TValue>::IsEmpty() {//check heap
	if (m_vec.size() == 0) return true; else return false;
}
Graph::Graph()//graph initialize
{
	m_pVHead=nullptr;
	m_vSize=0;
}
void Graph::AddVertex(int vertexKey) {//add vertex
	int i;
	Vertex* v = m_pVHead;
	if (v == nullptr) {//if no vertex
		m_pVHead = new Vertex(vertexKey);//create vertex
		m_vSize++;
		return;
	}
	for (i = 2; i <= m_vSize; i++) v = v->GetNext();//link vertex
	v->SetNext(new Vertex(vertexKey));
	m_vSize++;
}
Vertex* Graph::FindVertex(int key) {//find key vertex
	Vertex* v = m_pVHead;
	while (1) {
		if (v->GetKey() == key) return v;
		v = v->GetNext();
	}
}
/// add edge from the vertex which the number is startVertexKey to the vertex which the number is endVertexKey
void Graph::AddEdge(int startVertexKey, int endVertexKey, int weight) {//add edge
	Vertex* v = FindVertex(startVertexKey);
	v->AddEdge(endVertexKey, weight);
}
int Graph::Size() const {//return vertex size
	return m_vSize;
}
void clear(Vertex* v) {//clear vertex
	if (v == nullptr) return;
	clear(v->GetNext());
	delete v;
}
void Graph::Clear() {
	clear(m_pVHead);
}
Graph::~Graph(){
	Clear();
}
void Graph::Print(std::ofstream& fout) {//print graph
	int i, j;
	Vertex* v = m_pVHead;
	if (m_vSize == 0) {//check graph exist
		fout << "GraphNotExist" << endl;
		return;
	}
	for (i = 0; i < m_vSize; i++) {//print graph
		Edge* e = v->GetHeadOfEdge();
		for (j = 0; j < m_vSize; j++) {
			if (e == nullptr) { fout << "0 "; continue; }
			if (e->GetKey() == j) { fout << e->GetWeight() << " "; e=e->GetNext(); }
			else fout << "0 ";
		}
		fout << endl;
		v = v->GetNext();
	}
}

bool Graph::IsNegativeEdge() {//check negative edge
	int i;
	Vertex* v = m_pVHead;
	for (i = 0; i < m_vSize; i++) {//search all edge
		Edge* e = v->GetHeadOfEdge();
		while (e != nullptr) {
			if (e->GetWeight() < 0) return true;
			e = e->GetNext();
		}
		v = v->GetNext();
	}
	return false;
}
std::vector<int> Graph::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey) {//run dijkstra using set
	std::set<pair<int, int>> s;
	std::vector<int> mi(m_vSize), wher(m_vSize);//mi : minimum length, wher : parent node
	std::vector<int> path1,path;
	int i;
	if (m_vSize == 0) {//if graph is empty
		path.push_back(-2);
		return path;
	}
	for (i = 0; i < m_vSize; i++) mi[i] = 2147483647;//initialize
	mi[startVertexKey] = 0;
	s.insert({ 0,startVertexKey });
	while (s.size()) {
		pair<int, int> p = *s.begin();
		int x = p.first, y = p.second;
		s.erase(s.begin());
		if (x != mi[y]) continue;
		Vertex* v = FindVertex(y);
		Edge* e = v->GetHeadOfEdge();
		while (e != nullptr) {
			if ((x + e->GetWeight()) < mi[(e->GetKey())]) {//update
				mi[(e->GetKey())] = (x + e->GetWeight());
				wher[(e->GetKey())] = y;
				s.insert({ (x + e->GetWeight()),(e->GetKey()) });
			}
			e = e->GetNext();
		}
	}
	int e = endVertexKey;
	while (1) {
		path1.push_back(e);
		if (e == startVertexKey) break;
		e = wher[e];
	}
	path.push_back(mi[endVertexKey]);//make path
	for (i = path1.size() - 1; i >= 0; i--) path.push_back(path1[i]);
	return path;
}

std::vector<int> Graph::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey) {
	MinHeap<int, int> h;//make heap
	std::vector<int> mi(m_vSize), wher(m_vSize);//mi : minimum length, wher : parent node
	std::vector<int> path1, path;
	int i;
	if (m_vSize == 0) {//if graph is empty
		path.push_back(-2);
		return path;
	}
	for (i = 0; i < m_vSize; i++) mi[i] = 2147483647;//initialize
	mi[startVertexKey] = 0;
	h.Push(0, startVertexKey);
	while (!h.IsEmpty()) {
		pair<int, int> p = h.Top();
		int x = p.first, y = p.second;
		h.Pop();
		if (x != mi[y]) continue;
		Vertex* v = FindVertex(y);
		Edge* e = v->GetHeadOfEdge();
		while (e != nullptr) {
			if ((x + e->GetWeight()) < mi[(e->GetKey())]) {//update
				mi[(e->GetKey())] = (x + e->GetWeight());
				wher[(e->GetKey())] = y;
				h.Push((x + e->GetWeight()), (e->GetKey()));
			}
			e = e->GetNext();
		}
	}
	int e = endVertexKey;
	while (1) {
		path1.push_back(e);
		if (e == startVertexKey) break;
		e = wher[e];
	}
	path.push_back(mi[endVertexKey]);//make path
	for (i = path1.size() - 1; i >= 0; i--) path.push_back(path1[i]);
	return path;
}
std::vector<int> Graph::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey) {
	std::vector<int> mi(m_vSize), wher(m_vSize);
	std::vector<int> mit(m_vSize), whert(m_vSize);
	std::vector<int> path1, path;
	int i,j,minus=0;
	if (m_vSize == 0) {//if graph is empty
		path.push_back(-2);
		return path;
	}
	for (i = 0; i < m_vSize; i++) mi[i] = 2147483647;//initialize
	mi[startVertexKey] = 0;
	for (i = 0; i < m_vSize; i++) mit[i] = 2147483647;
	mit[startVertexKey] = 0;
	for (i = 1; i <= m_vSize; i++) {
		Vertex* v = m_pVHead;
		while (v != nullptr) {
			Edge* e = v->GetHeadOfEdge();//search every edge
			while (e != nullptr) {
				if (mi[v->GetKey()] == 2147483647) break;
				if (mi[v->GetKey()] + (e->GetWeight()) < mit[e->GetKey()]) {//update
					mit[e->GetKey()] = mi[v->GetKey()] + (e->GetWeight());
					whert[e->GetKey()] = v->GetKey();
					if (i == m_vSize) minus = 1;
				}
				e = e->GetNext();
			}
			v = v->GetNext();
		}
		for (j = 0; j < m_vSize; j++) {
			mi[j] = mit[j];
			wher[j] = whert[j];
		}
	}
	if (minus == 1) {//if there is minus edge
		path.push_back(-1);
		return path;
	}
	int e = endVertexKey;
	while (1) {
		path1.push_back(e);
		if (e == startVertexKey) break;
		e = wher[e];
	}
	path.push_back(mi[endVertexKey]);//make path
	for (i = path1.size() - 1; i >= 0; i--) path.push_back(path1[i]);
	return path;
}
std::vector<vector<int> > Graph::FindShortestPathFloyd() {
	vector<vector<int>> vec(m_vSize, vector<int>(m_vSize, 2147483647));//initialize
	Vertex* v = m_pVHead;
	if (m_vSize == 0) {//if graph is empty
		return vec;
	}
	while (v != nullptr) {//initialize
		Edge* e = v->GetHeadOfEdge();
		while (e != nullptr) {
			vec[v->GetKey()][e->GetKey()] = e->GetWeight();
			e = e->GetNext();
		}
		v = v->GetNext();
	}
	int i, j, k;
	for (i = 0; i < m_vSize; i++) vec[i][i] = 0;
	for (k = 0; k < m_vSize; k++) {
		for (i = 0; i < m_vSize; i++) {
			for (j = 0; j < m_vSize; j++) {
				if (vec[i][k] == 2147483647 || vec[k][j] == 2147483647) continue;
				if (vec[i][j]>vec[i][k] + vec[k][j]) vec[i][j] = vec[i][k] + vec[k][j];//update
			}
		}
	}
	return vec;
}
