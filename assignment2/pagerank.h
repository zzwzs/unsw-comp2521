#ifndef PAGERANK_H
#define PAGERANK_H

#include "graph.h"

//void pageRankW(double, double, int);
double calculatePR(Graph, GraphPage, double);
int LinkBothside(Graph, GraphPage, GraphPage);
double WeightinLink(Graph, GraphPage, GraphPage);
double WeightoutLink(Graph, GraphPage, GraphPage);
int urlInLinks(Graph, GraphPage);
int urlOutLinks(Graph, GraphPage);
void orderUrls(Graph); 
int URLIndex(Graph, GraphPage);

#endif
