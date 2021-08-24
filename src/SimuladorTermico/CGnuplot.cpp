#include "CGnuplot.hpp"

using namespace std;

void CGnuplot::plot(string name, string xlabel, string ylabel, string saveName) {
#ifdef _WIN32
	FILE* pipe = _popen(GNUPLOT_NAME, "w");
#else
	FILE* pipe = popen(GNUPLOT_NAME, "w");
#endif
	fprintf(pipe, ("set xlabel '" + xlabel + "'\n").c_str());
	fprintf(pipe, ("set ylabel '" + ylabel + "'\n").c_str());
	fprintf(pipe, "unset key\n");
	fprintf(pipe, ("plot '" + name + "' with linespoints linestyle 1\n").c_str());
	fprintf(pipe, "set term pngcairo\n");
	fprintf(pipe, ("set output '" + saveName + "'\n").c_str());
	fprintf(pipe, "replot\n");
	fprintf(pipe, "set term win\n");
	fflush(pipe);
}

void CGnuplot::semilog(string name, string xlabel, string ylabel, string saveName) {
#ifdef _WIN32
	FILE* pipe = _popen(GNUPLOT_NAME, "w");
#else
	FILE* pipe = popen(GNUPLOT_NAME, "w");
#endif
	fprintf(pipe, ("set xlabel '" + xlabel + "'\n").c_str());
	fprintf(pipe, ("set ylabel '" + ylabel + "'\n").c_str());
	fprintf(pipe, ("set logscale y\n"));
	fprintf(pipe, "unset key\n");
	fprintf(pipe, ("plot '" + name + "' with linespoints linestyle 1\n").c_str());
	fprintf(pipe, "set term pngcairo\n");
	fprintf(pipe, ("set output '" + saveName + "'\n").c_str());
	fprintf(pipe, "replot\n");
	fprintf(pipe, "set term win\n");
	fflush(pipe);
}