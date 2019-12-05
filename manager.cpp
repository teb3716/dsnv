#include "Manager.h"
#include "graph.h"
#include <cstring>
#include <vector>

Manager::~Manager()
{
    if (fout.is_open())
        fout.close();

}
int compare(char* x, const char* y) {//check command
	int l = strlen(y),i;
	for (i = 0; i < l; i++) {
		if (x[i] != y[i]) return 0;
	}
	return 1;
}
void Manager::Run(const char* filepath)
{
	std::ifstream fin(filepath);
    fout.open(RESULT_LOG_PATH);
	if (!fin) {//check CommandFileNotExist error
		fout << "====== SYSTEM ======" << endl;
		fout << "CommandFileNotExist" << endl;
		fout << "=====================" << endl;
		return;
	}
	char com[300];
	Result R;
	while (!fin.eof()) {
		fin.getline(com, 100);
		if (compare(com,"LOAD")==1) {//LOAD command
			fout << "====== LOAD ======" << endl;
			R=Load(com+5);
			if (R == Success) fout << "Success" << endl;//LOAD success
			if (R == LoadFileNotExist) fout << "LoadFileNotExist " << endl;//File not exist
			fout << "===================" << endl << endl;
			PrintError(R);
		}
		else if (compare(com, "PRINT") == 1) {//PRINT command
			fout << "===== PRINT =====" << endl;
			R=Print();
			PrintError(R);
		}
		else if (compare(com, "FLOYD") == 1) {//FLOYD command
			fout << "===== FLOYD =====" << endl;
			R=FindShortestPathFloyd();
			PrintError(R);
		}
		else if (compare(com, "DIJKSTRAMIN") == 1) {//DIJKSTRAMIN command
			fout << "====== DIJKSTRAMIN ====== " << endl;
			if (m_graph.Size() == 0) {//check graph exist
				fout << "GraphNotExist" << endl;
				fout << "=================" << endl << endl;
				PrintError(GraphNotExist);
				continue;
			}
			if (m_graph.IsNegativeEdge() == true) {//check negative edge
				fout << "InvalidAlgorithm" << endl;
				fout << "=================" << endl << endl;
				PrintError(InvalidAlgorithm);
				continue;
			}
			int n = 0, m = 0, i, l = strlen(com), j,ch=0;
			for (i = 11; i < l; i++) {//select first number
				if (!(com[i] >= '0' && com[i] <= '9' || com[i] == ' ')) {//check negative
					ch = -1;
					break;
				}
				if (com[i] >= '0' && com[i] <= '9') {
					ch++;
					for (j = i; j <= l; j++) {
						if (!(com[j] >= '0' && com[j] <= '9')) break;
						n *= 10; n += com[j] - '0';
					}
					break;
				}
			}
			if(ch==-1 || m_graph.Size()-1<n){//if number is negative or number is bigger then graph size
				fout << "InvalidVertexKey" << endl;
				fout << "=================" << endl << endl;
				PrintError(InvalidVertexKey);
				continue;
			}
			if (ch != 1) {// if there is no number
				fout << "VertexKeyNotExist " << endl;
				fout << "=================" << endl << endl;
				PrintError(VertexKeyNotExist);
				continue;
			}
			for (i = j; i < l; i++) {//select second number
				if (!(com[i] >= '0' && com[i] <= '9' || com[i] == ' ')) {//check negative
					ch = -1;
					break;
				}
				if (com[i] >= '0' && com[i] <= '9') {
					ch++;
					for (j = i; j <= l; j++) {
						if (!(com[j] >= '0' && com[j] <= '9')) break;
						m *= 10; m += com[j] - '0';
					}
					break;
				}
			}
			if (ch == -1 || m_graph.Size() - 1<m) {//if number is negative or number is bigger then graph size
				fout << "InvalidVertexKey" << endl;
				fout << "=================" << endl << endl;
				PrintError(InvalidVertexKey);
				continue;
			}
			if (ch != 2) {//if there is no number
				fout << "VertexKeyNotExist " << endl;
				fout << "=================" << endl << endl;
				PrintError(VertexKeyNotExist);
				continue;
			}
			R=FindShortestPathDijkstraUsingMinHeap(n, m);
			PrintError(R);
		}
		else if (compare(com, "DIJKSTRA") == 1) {
			fout << "===== DIJKSTRA =====" << endl;
			if (m_graph.Size() == 0) {//check graph exist
				fout << "GraphNotExist" << endl;
				fout << "=================" << endl << endl;
				PrintError(GraphNotExist);
				continue;
			}
			if (m_graph.IsNegativeEdge() == true) {//check negative edge
				fout << "InvalidAlgorithm" << endl;
				fout << "=================" << endl << endl;
				PrintError(InvalidAlgorithm);
				continue;
			}
			int n=0, m=0,i,l=strlen(com),j,ch=0;
			for (i = 8; i < l; i++) {//select first number
				if (!(com[i] >= '0' && com[i] <= '9' || com[i] == ' ')) {//check negative edge
					ch = -1;
					break;
				}
				if (com[i] >= '0' && com[i] <= '9') {
					ch++;
					for (j = i; j <= l; j++) {
						if (!(com[j] >= '0' && com[j] <= '9')) break;
						n *= 10; n += com[j] - '0';
					}
					break;
				}
			}
			if (ch == -1 || m_graph.Size() - 1<n) {//if number is negative or number is bigger then graph size
				fout << "InvalidVertexKey" << endl;
				fout << "=================" << endl << endl;
				PrintError(InvalidVertexKey);
				continue;
			}
			if (ch != 1) {//if there is no number
				fout << "VertexKeyNotExist " << endl;
				fout << "=================" << endl << endl;
				PrintError(VertexKeyNotExist);
				continue;
			}
			for (i = j; i < l; i++) {//select second number
				if (!(com[i] >= '0' && com[i] <= '9' || com[i] == ' ')) {//if number is negative or number is bigger then graph size
					ch = -1;
					break;
				}
				if (com[i] >= '0' && com[i] <= '9') {
					ch++;
					for (j = i; j <= l; j++) {
						if (!(com[j] >= '0' && com[j] <= '9')) break;
						m *= 10; m += com[j] - '0';
					}
					break;
				}
			}
			if (ch == -1 || m_graph.Size() - 1<m) {//if number is negative or number is bigger then graph size
				fout << "InvalidVertexKey" << endl;
				fout << "=================" << endl << endl;
				PrintError(InvalidVertexKey);
				continue;
			}
			if (ch != 2) {//if there is no number
				fout << "VertexKeyNotExist " << endl;
				fout << "=================" << endl << endl;
				PrintError(VertexKeyNotExist);
				continue;
			}
			R=FindShortestPathDijkstraUsingSet(n, m);
			PrintError(R);
		}
		else if (compare(com, "BELLMANFORD") == 1) {
			fout << "===== BELLMANFORD ===== " << endl;
			if (m_graph.Size() == 0) {//check graph exist
				fout << "GraphNotExist" << endl;
				fout << "=================" << endl << endl;
				PrintError(GraphNotExist);
				continue;
			}
			int n = 0, m = 0, i, l = strlen(com), j,ch=0;
			for (i = 11; i < l; i++) {//select first number
				if (!(com[i] >= '0' && com[i] <= '9' || com[i] == ' ')) {//if number is negative or number is bigger then graph size
					ch = -1;
					break;
				}
				if (com[i] >= '0' && com[i] <= '9') {
					ch++;
					for (j = i; j <= l; j++) {
						if (!(com[j] >= '0' && com[j] <= '9')) break;
						n *= 10; n += com[j] - '0';
					}
					break;
				}
			}
			if (ch == -1 || m_graph.Size() - 1<n) {//if number is negative or number is bigger then graph size
				fout << "InvalidVertexKey" << endl;
				fout << "=================" << endl << endl;
				PrintError(InvalidVertexKey);
				continue;
			}
			if (ch != 1) {//if there is no number
				fout << "VertexKeyNotExist " << endl;
				fout << "=================" << endl << endl;
				PrintError(VertexKeyNotExist);
				continue;
			}
			for (i = j; i < l; i++) {//select second number
				if (!(com[i] >= '0' && com[i] <= '9' || com[i] == ' ')) {//if number is negative or number is bigger then graph size
					ch = -1;
					break;
				}
				if (com[i] >= '0' && com[i] <= '9') {
					ch++;
					for (j = i; j <= l; j++) {
						if (!(com[j] >= '0' && com[j] <= '9')) break;
						m *= 10; m += com[j] - '0';
					}
					break;
				}
			}
			if (ch == -1 || m_graph.Size() - 1<m) {//if number is negative or number is bigger then graph size
				fout << "InvalidVertexKey" << endl;
				fout << "=================" << endl << endl;
				PrintError(InvalidVertexKey);
				continue;
			}
			if (ch != 2) {//if there is no number
				fout << "VertexKeyNotExist " << endl;
				fout << "=================" << endl << endl;
				PrintError(VertexKeyNotExist);
				continue;
			}
			R=FindShortestPathBellmanFord(n, m);
			PrintError(R);
		}
		else {//check NonDefinedCommand
			fout << "====== " << com << " ======" << endl;
			fout << "NonDefinedCommand" << endl;
			fout << "====================" << endl << endl;
			PrintError(NonDefinedCommand);
		}
	}
	
}
void Manager::PrintError(Result result)
{
	fout << "===================" << endl;
    fout << "Error code: " << result << std::endl;
	fout << "===================" << endl<<endl;
}

/// <summary>
/// make a graph
/// </summary>
///
/// <param name="filepath">
/// the filepath to read to make the graph
/// </param>
///
/// <returns>
/// Result::Success if load is successful.
/// Result::LoadFileNotExist if file is not exist.
/// </returns>
Result Manager::Load(const char* filepath)
{
	FILE* in = fopen(filepath, "r");//input graph
	int n,i,j,x;
	if (in == NULL) return LoadFileNotExist;
	fscanf(in, "%d", &n);
	for (i = 0; i < n; i++) {
		m_graph.AddVertex(i);
		for (j = 0; j < n; j++) {//make linked_list
			fscanf(in, "%d", &x);
			if (x != 0) m_graph.AddEdge(i, j, x);
		}
	}
	return Success;
    // TODO: implement
}
/// <summary>
/// print out the graph as matrix form
/// </summary>
///
/// <returns>
/// Result::Success if the printing is successful
/// Result::GraphNotExist if there is no graph
/// </returns>
Result Manager::Print()
{
	m_graph.Print(fout);//print graph
	fout << "===================" << endl << endl;
	if (m_graph.Size() == 0) return GraphNotExist;
	else return Success;
    // TODO: implement
}
/// <summary>
/// find the path from startVertexKey to endVertexKey with DFS (stack)
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>

void insert(vector<int>* v, int s, int e) {//insert sort
	int i,j;
	for (i = s + 1; i <= e; i++) {
		for (j = i - 1; j >= s; j--) {
			if ((*v)[j + 1] < (*v)[j]) {
				int tmp = (*v)[j];
				(*v)[j] = (*v)[j + 1];
				(*v)[j + 1] = tmp;
			}
			else break;
		}
	}
}
int part(vector<int>* v, int s, int e) {//partition vector
	int i, c = s;
	s++;
	while (1) {
		if (s > e) break;
		if ((*v)[s] < (*v)[c]) {
			int tmp = (*v)[s];
			(*v)[s] = (*v)[c];
			(*v)[c] = tmp;
			s++;
			c++;
		}
		else if ((*v)[s]>(*v)[c]) {
			int tmp = (*v)[s];
			(*v)[s] = (*v)[e];
			(*v)[e] = tmp;
			e--;
		}
	}
	return c;
}
void quick(vector<int>* v,int s,int e) {//quick sort
	int i;
	if (e - s + 1 <= 6) insert(v, s, e);
	else {
		int pivot = part(v, s, e);
		quick(v, s, pivot - 1);
		quick(v, pivot + 1, e);
	}
}
Result Manager::FindShortestPathFloyd() {
	std::vector<vector<int>> v = m_graph.FindShortestPathFloyd();//run floyd algorithm
	int i, j;
	if (m_graph.Size()==0) {//check graph exist
		fout << "GraphNotExist" << endl;
		fout << "================" << endl << endl;
		return GraphNotExist;
	}
	for (i = 0; i < m_graph.Size(); i++) {//print graph
		for (j = 0; j < m_graph.Size(); j++) {
			fout << v[i][j] << " ";
		}
		fout << endl;
	}
	fout << "================" << endl << endl;
	return Success;
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
	int i;
	std::vector<int> v=m_graph.FindShortestPathDijkstraUsingSet(startVertexKey, endVertexKey),vv;//run dijkstra using set
	if (v[0] == -2) {//check graph exist
		fout << "GraphNotExist" << endl;
		fout << "================" << endl << endl;
		return GraphNotExist;
	}
	fout << "shortest path: ";//print path
	for (i = 1; i < v.size(); i++) {
		fout << v[i] << " ";
		vv.push_back(v[i]);
	}
	fout << endl;
	fout << "sorted nodes: ";//print sorted path
	quick(&vv,0,vv.size()-1);
	for (i = 0; i < vv.size(); i++) {
		fout << vv[i] << " ";
	}
	fout << endl;
	fout << "path length: " << v[0] << endl;//print path length
	fout << "================" << endl << endl;
	return Success;
    // TODO: implement
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using MinHeap
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)
{
	int i;
	std::vector<int> v = m_graph.FindShortestPathDijkstraUsingMinHeap(startVertexKey, endVertexKey),vv;//run dijkstra using hip
	if(v[0]==-2){//check graph exist
		fout << "GraphNotExist" << endl;
		fout << "================" << endl << endl;
		return GraphNotExist;
	}
	fout << "shortest path: ";//print path
	for (i = 1; i < v.size(); i++) {
		fout << v[i] << " ";
		vv.push_back(v[i]);
	}
	fout << endl;
	fout << "sorted nodes: ";//print sorted path
	quick(&vv, 0, vv.size() - 1);
	for (i = 0; i < vv.size(); i++) {
		fout << vv[i] << " ";
	}
	fout << endl;
	fout << "path length: " << v[0] << endl;//print length
	fout << "================" << endl << endl;
	return Success;
    // TODO: implement
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Bellman-Ford
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::NegativeCycleDetected if exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
	int i;
	std::vector<int> v = m_graph.FindShortestPathBellmanFord(startVertexKey, endVertexKey),vv;//run bellmanford
	if (v[0] == -2) {//check graph exist
		fout << "GraphNotExist" << endl;
		fout << "================" << endl << endl;
		return GraphNotExist;
	}
	if (v[0] == -1) {//check negative edge
		fout << "NegativeCycleDetected" << endl;
		fout << "================" << endl << endl;
		return NegativeCycleDetected;
	}
	fout << "shortest path: ";//print path
	for (i = 1; i < v.size(); i++) {
		fout << v[i] << " ";
		vv.push_back(v[i]);
	}
	fout << endl;
	fout << "sorted nodes: ";//print sorted path
	quick(&vv, 0, vv.size() - 1);
	for (i = 0; i < vv.size(); i++) {
		fout << vv[i] << " ";
	}
	fout << endl;
	fout << "path length: " << v[0] << endl;//print length
	fout << "================" << endl << endl;
	return Success;
    // TODO: implement
}
