#ifndef ___nbprob__
#define ___nbprob__
#include "nbstruct.h"
#include "nbdata.h"

void *priorprobcalc(Features *dataset, struct FeatureSet *probresult, unsigned int rowcount);
void *cpcalc(Features *dataset, struct FeatureSet *priorprob, Probability *resultset, unsigned int rowcount);
void *postprobcalc(Features *dataset,struct FeatureSet *fsetdatas, Probability *probdataset, Probability_Err *resultset, unsigned int rowcount);
void *cmatrix(Probability_Err *postprobdata, struct Confusion_Matrix *resultset, unsigned int rowcount, unsigned int index);
double gaussiancalc(double mean, double variance, double xval);
void printmatrix(Confusion_Matrix_Type *cmatrixdata, int n);
void plot_graph(Confusion_Matrix_Type *cmatrixdata, int n);
#endif