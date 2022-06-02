#include <iostream>

#include "ListGraph.h"
#include "SetGraph.h"
#include "MatrixGraph.h"
#include "ArcGraph.h"

int main(){
	ListGraph listGraph(5);
	listGraph.AddEdge(0,1);
	listGraph.AddEdge(0,2);
	listGraph.AddEdge(0,4);
	listGraph.AddEdge(2,1);
	listGraph.AddEdge(2,3);
	listGraph.AddEdge(2,0);
	listGraph.AddEdge(3,1);
	listGraph.AddEdge(4,3);
	std::cout << "ListGraph common filling show" << std::endl;
	listGraph.print(std::cout);

	MatrixGraph matrixGraph(5);
	matrixGraph.AddEdge(0,1);
	matrixGraph.AddEdge(0,2);
	matrixGraph.AddEdge(0,4);
	matrixGraph.AddEdge(2,1);
	matrixGraph.AddEdge(2,3);
	matrixGraph.AddEdge(2,0);
	matrixGraph.AddEdge(3,1);
	matrixGraph.AddEdge(4,3);
	std::cout << "MatrixGraph common filling show" << std::endl;
	matrixGraph.print(std::cout);
	
	SetGraph setGraph(5);
	setGraph.AddEdge(0,1);
	setGraph.AddEdge(0,2);
	setGraph.AddEdge(0,4);
	setGraph.AddEdge(2,1);
	setGraph.AddEdge(2,3);
	setGraph.AddEdge(2,0);
	setGraph.AddEdge(3,1);
	setGraph.AddEdge(4,3);
	std::cout << "SetGraph common filling show" << std::endl;
	setGraph.print(std::cout);
	
	
	ArcGraph arcGraph(5);
	arcGraph.AddEdge(0,1);
	arcGraph.AddEdge(0,2);
	arcGraph.AddEdge(0,4);
	arcGraph.AddEdge(2,1);
	arcGraph.AddEdge(2,3);
	arcGraph.AddEdge(2,0);
	arcGraph.AddEdge(3,1);
	arcGraph.AddEdge(4,3);
	std::cout << "ArcGraph common filling show" << std::endl;
	arcGraph.print(std::cout);
	

	ListGraph listGraph2(matrixGraph);
	std::cout << "ListGraph copying from MatrixGraph show" << std::endl;
	listGraph.print(std::cout);
	
	MatrixGraph matrixGraph2(setGraph);
	std::cout << "MatrixGraph copying from SetGraph show" << std::endl;
	matrixGraph2.print(std::cout);
	
	SetGraph setGraph2(arcGraph);
	std::cout << "SetGraph copying from ArcGraph show" << std::endl;
	setGraph2.print(std::cout);
	
	ArcGraph arcGraph2(listGraph);
	std::cout << "ArcGraph copying from ListGraph show" << std::endl;
	arcGraph2.print(std::cout);
}