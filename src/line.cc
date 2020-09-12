#include <stdio.h>
#include <math.h>

void printUsage() {
  printf(
    "lineint\n"
    "Copyright (C) 2020 Greg Hedger\n"
    "Calculate intersection of two bounded lines.\n"
    "Usage:\n"
    "  lineint x1 y1 x2 y2 x3 y3 x4 y4\n");
}

bool calcIntersectBezier(double *x, double *y, double *x_int, double *y_int) {
  bool ret = true;
  double t_num = (x[0] - x[2]) * (y[2] - y[3]) - (y[0] - y[2]) * (x[2] - x[3]);
  double t_denom = (x[0] - x[1]) * (y[2] - y[3]) - (y[0] - y[1]) * (x[2] - x[3]);
  double u_num = (x[0] - x[1]) * (y[0] - y[2]) - (y[0] - y[1]) * (x[0] - x[2]);
  double u_denom = (x[0] - x[1]) * (y[2] - y[3]) - (y[0] - y[1]) * (x[2] - x[3]);

  double t, u;
  if (t_denom) {
    t = t_num / t_denom;
    *x_int = x[0] + t * (x[1] - x[0]);
  } else {
    *x_int = 0;
    ret = false;
  }
  if (u_denom) {
    u = -(u_num / u_denom);
    *y_int = y[0] + u * (y[1] - y[0]);
  } else {
    *y_int = 0;
    ret = false;
  }

  if (ret) {
    if (!(0 <= u && u <= 1.0 && 0 <= t && t <= 1.0)) {
      ret = true;
    }
  }

  return ret;
}

int main(int argt, char *argv[]) {
  if (argt < 9) {
    printUsage();
    return 1;
  }

  double x[4], y[4];
  for (auto i = 0; i < 4; i++) {
    sscanf(argv[1 + i*2], "%lf", x + i);
    sscanf(argv[1 + i*2+1], "%lf", y + i);
  }
  double x_int, y_int;

  if (calcIntersectBezier(x, y, &x_int, &y_int)) {
    printf("x: %lf\ny: %lf\n", x_int, y_int);
  } else {
    printf("Lines are parallel / do not intersect\n");
  }

  return 0;
}
