/**********************************************************************/
/* Interpolation points for a tet based on the Chen - Babuska paper.  */
/**********************************************************************/
#include <stdio.h>

#include <FCMangle.h>

typedef double DARR4[4];

/* 4-point (p = 1) */
static double pts4[][4] = 
{
  {1.0000000000, 0.0000000000, 0.0000000000, 0.0000000000},
  {0.0000000000, 1.0000000000, 0.0000000000, 0.0000000000},
  {0.0000000000, 0.0000000000, 1.0000000000, 0.0000000000},
  {0.0000000000, 0.0000000000, 0.0000000000, 1.0000000000}
};

/* 10-point (p = 2) */
static double pts10[][4] =
{
  {1.0000000000, 0.0000000000, 0.0000000000, 0.0000000000},
  {0.0000000000, 1.0000000000, 0.0000000000, 0.0000000000},
  {0.0000000000, 0.0000000000, 1.0000000000, 0.0000000000},
  {0.0000000000, 0.0000000000, 0.0000000000, 1.0000000000},
  {0.5000000000, 0.5000000000, 0.0000000000, 0.0000000000},
  {0.0000000000, 0.5000000000, 0.5000000000, 0.0000000000},
  {0.5000000000, 0.0000000000, 0.5000000000, 0.0000000000},
  {0.5000000000, 0.0000000000, 0.0000000000, 0.5000000000},
  {0.0000000000, 0.5000000000, 0.0000000000, 0.5000000000},
  {0.0000000000, 0.0000000000, 0.5000000000, 0.5000000000}
};

/* 20-point (p = 3) */
static double pts20[][4] =
{
  {1.0000000000, 0.0000000000, 0.0000000000, 0.0000000000},
  {0.0000000000, 1.0000000000, 0.0000000000, 0.0000000000},
  {0.0000000000, 0.0000000000, 1.0000000000, 0.0000000000},
  {0.0000000000, 0.0000000000, 0.0000000000, 1.0000000000},
  {0.7236067977, 0.2763932023, 0.0000000000, 0.0000000000},
  {0.2763932023, 0.7236067977, 0.0000000000, 0.0000000000},
  {0.0000000000, 0.7236067977, 0.2763932023, 0.0000000000},
  {0.0000000000, 0.2763932023, 0.7236067977, 0.0000000000},
  {0.7236067977, 0.0000000000, 0.2763932023, 0.0000000000},
  {0.2763932023, 0.0000000000, 0.7236067977, 0.0000000000},
  {0.7236067977, 0.0000000000, 0.0000000000, 0.2763932023},
  {0.2763932023, 0.0000000000, 0.0000000000, 0.7236067977},
  {0.0000000000, 0.7236067977, 0.0000000000, 0.2763932023},
  {0.0000000000, 0.2763932023, 0.0000000000, 0.7236067977},
  {0.0000000000, 0.0000000000, 0.7236067977, 0.2763932023},
  {0.0000000000, 0.0000000000, 0.2763932023, 0.7236067977},
  {0.3333333333, 0.3333333333, 0.3333333333, 0.0000000000},
  {0.3333333333, 0.3333333333, 0.0000000000, 0.3333333333},
  {0.3333333333, 0.0000000000, 0.3333333333, 0.3333333333},
  {0.0000000000, 0.3333333333, 0.3333333333, 0.3333333333}
};

/* 35-point (p = 4) */
static double pts35[][4] =
{
  {1.0000000000, 0.0000000000, 0.0000000000, 0.0000000000},
  {0.0000000000, 1.0000000000, 0.0000000000, 0.0000000000},
  {0.0000000000, 0.0000000000, 1.0000000000, 0.0000000000},
  {0.0000000000, 0.0000000000, 0.0000000000, 1.0000000000},
  {0.8273268354, 0.1726731646, 0.0000000000, 0.0000000000},
  {0.5000000000, 0.5000000000, 0.0000000000, 0.0000000000},
  {0.1726731646, 0.8273268354, 0.0000000000, 0.0000000000},
  {0.0000000000, 0.8273268354, 0.1726731646, 0.0000000000},
  {0.0000000000, 0.5000000000, 0.5000000000, 0.0000000000},
  {0.0000000000, 0.1726731646, 0.8273268354, 0.0000000000},
  {0.8273268354, 0.0000000000, 0.1726731646, 0.0000000000},
  {0.5000000000, 0.0000000000, 0.5000000000, 0.0000000000},
  {0.1726731646, 0.0000000000, 0.8273268354, 0.0000000000},
  {0.8273268354, 0.0000000000, 0.0000000000, 0.1726731646},
  {0.5000000000, 0.0000000000, 0.0000000000, 0.5000000000},
  {0.1726731646, 0.0000000000, 0.0000000000, 0.8273268354},
  {0.0000000000, 0.8273268354, 0.0000000000, 0.1726731646},
  {0.0000000000, 0.5000000000, 0.0000000000, 0.5000000000},
  {0.0000000000, 0.1726731646, 0.0000000000, 0.8273268354},
  {0.0000000000, 0.0000000000, 0.8273268354, 0.1726731646},
  {0.0000000000, 0.0000000000, 0.5000000000, 0.5000000000},
  {0.0000000000, 0.0000000000, 0.1726731646, 0.8273268354},
  {0.2165423725, 0.2165423725, 0.5669152550, 0.0000000000},
  {0.2165423725, 0.5669152550, 0.2165423725, 0.0000000000},
  {0.5669152550, 0.2165423725, 0.2165423725, 0.0000000000},
  {0.2165423725, 0.5669152550, 0.0000000000, 0.2165423725},
  {0.5669152550, 0.2165423725, 0.0000000000, 0.2165423725},
  {0.2165423725, 0.2165423725, 0.0000000000, 0.5669152550},
  {0.5669152550, 0.0000000000, 0.2165423725, 0.2165423725},
  {0.2165423725, 0.0000000000, 0.2165423725, 0.5669152550},
  {0.2165423725, 0.0000000000, 0.5669152550, 0.2165423725},
  {0.0000000000, 0.2165423725, 0.2165423725, 0.5669152550},
  {0.0000000000, 0.2165423725, 0.5669152550, 0.2165423725},
  {0.0000000000, 0.5669152550, 0.2165423725, 0.2165423725},
  {0.2500000000, 0.2500000000, 0.2500000000, 0.2500000000}
};

/* 56-point (p = 5) */
static double pts56[][4] =
{
  {1.0000000000, 0.0000000000, 0.0000000000, 0.0000000000},
  {0.0000000000, 1.0000000000, 0.0000000000, 0.0000000000},
  {0.0000000000, 0.0000000000, 1.0000000000, 0.0000000000},
  {0.0000000000, 0.0000000000, 0.0000000000, 1.0000000000},
  {0.8825276620, 0.1174723380, 0.0000000000, 0.0000000000},
  {0.6426157582, 0.3573842418, 0.0000000000, 0.0000000000},
  {0.3573842418, 0.6426157582, 0.0000000000, 0.0000000000},
  {0.1174723380, 0.8825276620, 0.0000000000, 0.0000000000},
  {0.0000000000, 0.8825276620, 0.1174723380, 0.0000000000},
  {0.0000000000, 0.6426157582, 0.3573842418, 0.0000000000},
  {0.0000000000, 0.3573842418, 0.6426157582, 0.0000000000},
  {0.0000000000, 0.1174723380, 0.8825276620, 0.0000000000},
  {0.8825276620, 0.0000000000, 0.1174723380, 0.0000000000},
  {0.6426157582, 0.0000000000, 0.3573842418, 0.0000000000},
  {0.3573842418, 0.0000000000, 0.6426157582, 0.0000000000},
  {0.1174723380, 0.0000000000, 0.8825276620, 0.0000000000},
  {0.8825276620, 0.0000000000, 0.0000000000, 0.1174723380},
  {0.6426157582, 0.0000000000, 0.0000000000, 0.3573842418},
  {0.3573842418, 0.0000000000, 0.0000000000, 0.6426157582},
  {0.1174723380, 0.0000000000, 0.0000000000, 0.8825276620},
  {0.0000000000, 0.8825276620, 0.0000000000, 0.1174723380},
  {0.0000000000, 0.6426157582, 0.0000000000, 0.3573842418},
  {0.0000000000, 0.3573842418, 0.0000000000, 0.6426157582},
  {0.0000000000, 0.1174723380, 0.0000000000, 0.8825276620},
  {0.0000000000, 0.0000000000, 0.8825276620, 0.1174723380},
  {0.0000000000, 0.0000000000, 0.6426157582, 0.3573842418},
  {0.0000000000, 0.0000000000, 0.3573842418, 0.6426157582},
  {0.0000000000, 0.0000000000, 0.1174723380, 0.8825276620},
  {0.1480194978, 0.1480194978, 0.7039610043, 0.0000000000},
  {0.1480194978, 0.7039610043, 0.1480194978, 0.0000000000},
  {0.7039610043, 0.1480194978, 0.1480194978, 0.0000000000},
  {0.4208255904, 0.4208255904, 0.1583488191, 0.0000000000},
  {0.4208255904, 0.1583488191, 0.4208255904, 0.0000000000},
  {0.1583488191, 0.4208255904, 0.4208255904, 0.0000000000},
  {0.1480194978, 0.7039610043, 0.0000000000, 0.1480194978},
  {0.7039610043, 0.1480194978, 0.0000000000, 0.1480194978},
  {0.1480194978, 0.1480194978, 0.0000000000, 0.7039610043},
  {0.4208255904, 0.1583488191, 0.0000000000, 0.4208255904},
  {0.1583488191, 0.4208255904, 0.0000000000, 0.4208255904},
  {0.4208255904, 0.4208255904, 0.0000000000, 0.1583488191},
  {0.7039610043, 0.0000000000, 0.1480194978, 0.1480194978},
  {0.1480194978, 0.0000000000, 0.1480194978, 0.7039610043},
  {0.1480194978, 0.0000000000, 0.7039610043, 0.1480194978},
  {0.1583488191, 0.0000000000, 0.4208255904, 0.4208255904},
  {0.4208255904, 0.0000000000, 0.4208255904, 0.1583488191},
  {0.4208255904, 0.0000000000, 0.1583488191, 0.4208255904},
  {0.0000000000, 0.1480194978, 0.1480194978, 0.7039610043},
  {0.0000000000, 0.1480194978, 0.7039610043, 0.1480194978},
  {0.0000000000, 0.7039610043, 0.1480194978, 0.1480194978},
  {0.0000000000, 0.4208255904, 0.4208255904, 0.1583488191},
  {0.0000000000, 0.4208255904, 0.1583488191, 0.4208255904},
  {0.0000000000, 0.1583488191, 0.4208255904, 0.4208255904},
  {0.1779987615, 0.1779987615, 0.1779987615, 0.4660037155},
  {0.1779987615, 0.1779987615, 0.4660037155, 0.1779987615},
  {0.1779987615, 0.4660037155, 0.1779987615, 0.1779987615},
  {0.4660037155, 0.1779987615, 0.1779987615, 0.1779987615}
};
  
/* 84-point (p = 6) */
static double pts84[][4] =
{
  {1.0000000000, 0.0000000000, 0.0000000000, 0.0000000000},
  {0.0000000000, 1.0000000000, 0.0000000000, 0.0000000000},
  {0.0000000000, 0.0000000000, 1.0000000000, 0.0000000000},
  {0.0000000000, 0.0000000000, 0.0000000000, 1.0000000000},
  {0.9151119481, 0.0848880519, 0.0000000000, 0.0000000000},
  {0.7344243967, 0.2655756033, 0.0000000000, 0.0000000000},
  {0.5000000000, 0.5000000000, 0.0000000000, 0.0000000000},
  {0.2655756033, 0.7344243967, 0.0000000000, 0.0000000000},
  {0.0848880519, 0.9151119481, 0.0000000000, 0.0000000000},
  {0.0000000000, 0.9151119481, 0.0848880519, 0.0000000000},
  {0.0000000000, 0.7344243967, 0.2655756033, 0.0000000000},
  {0.0000000000, 0.5000000000, 0.5000000000, 0.0000000000},
  {0.0000000000, 0.2655756033, 0.7344243967, 0.0000000000},
  {0.0000000000, 0.0848880519, 0.9151119481, 0.0000000000},
  {0.9151119481, 0.0000000000, 0.0848880519, 0.0000000000},
  {0.7344243967, 0.0000000000, 0.2655756033, 0.0000000000},
  {0.5000000000, 0.0000000000, 0.5000000000, 0.0000000000},
  {0.2655756033, 0.0000000000, 0.7344243967, 0.0000000000},
  {0.0848880519, 0.0000000000, 0.9151119481, 0.0000000000},
  {0.9151119481, 0.0000000000, 0.0000000000, 0.0848880519},
  {0.7344243967, 0.0000000000, 0.0000000000, 0.2655756033},
  {0.5000000000, 0.0000000000, 0.0000000000, 0.5000000000},
  {0.2655756033, 0.0000000000, 0.0000000000, 0.7344243967},
  {0.0848880519, 0.0000000000, 0.0000000000, 0.9151119481},
  {0.0000000000, 0.9151119481, 0.0000000000, 0.0848880519},
  {0.0000000000, 0.7344243967, 0.0000000000, 0.2655756033},
  {0.0000000000, 0.5000000000, 0.0000000000, 0.5000000000},
  {0.0000000000, 0.2655756033, 0.0000000000, 0.7344243967},
  {0.0000000000, 0.0848880519, 0.0000000000, 0.9151119481},
  {0.0000000000, 0.0000000000, 0.9151119481, 0.0848880519},
  {0.0000000000, 0.0000000000, 0.7344243967, 0.2655756033},
  {0.0000000000, 0.0000000000, 0.5000000000, 0.5000000000},
  {0.0000000000, 0.0000000000, 0.2655756033, 0.7344243967},
  {0.0000000000, 0.0000000000, 0.0848880519, 0.9151119481},
  {0.3162696586, 0.5665493829, 0.1171809585, 0.0000000000},
  {0.5665493829, 0.3162696586, 0.1171809585, 0.0000000000},
  {0.5665493792, 0.1171809548, 0.3162696660, 0.0000000000},
  {0.1171809548, 0.5665493792, 0.3162696660, 0.0000000000},
  {0.1171809641, 0.3162696752, 0.5665493608, 0.0000000000},
  {0.3162696752, 0.1171809641, 0.5665493608, 0.0000000000},
  {0.1063355939, 0.1063355939, 0.7873288122, 0.0000000000},
  {0.1063355939, 0.7873288122, 0.1063355939, 0.0000000000},
  {0.7873288122, 0.1063355939, 0.1063355939, 0.0000000000},
  {0.3333333333, 0.3333333333, 0.3333333333, 0.0000000000},
  {0.5665493829, 0.1171809585, 0.0000000000, 0.3162696586},
  {0.3162696586, 0.1171809585, 0.0000000000, 0.5665493829},
  {0.1171809548, 0.3162696660, 0.0000000000, 0.5665493792},
  {0.5665493792, 0.3162696660, 0.0000000000, 0.1171809548},
  {0.3162696752, 0.5665493608, 0.0000000000, 0.1171809641},
  {0.1171809641, 0.5665493608, 0.0000000000, 0.3162696752},
  {0.1063355939, 0.7873288122, 0.0000000000, 0.1063355939},
  {0.7873288122, 0.1063355939, 0.0000000000, 0.1063355939},
  {0.1063355939, 0.1063355939, 0.0000000000, 0.7873288122},
  {0.3333333333, 0.3333333333, 0.0000000000, 0.3333333333},
  {0.1171809585, 0.0000000000, 0.3162696586, 0.5665493829},
  {0.1171809585, 0.0000000000, 0.5665493829, 0.3162696586},
  {0.3162696660, 0.0000000000, 0.5665493792, 0.1171809548},
  {0.3162696660, 0.0000000000, 0.1171809548, 0.5665493792},
  {0.5665493608, 0.0000000000, 0.1171809641, 0.3162696752},
  {0.5665493608, 0.0000000000, 0.3162696752, 0.1171809641},
  {0.7873288122, 0.0000000000, 0.1063355939, 0.1063355939},
  {0.1063355939, 0.0000000000, 0.1063355939, 0.7873288122},
  {0.1063355939, 0.0000000000, 0.7873288122, 0.1063355939},
  {0.3333333333, 0.0000000000, 0.3333333333, 0.3333333333},
  {0.0000000000, 0.3162696586, 0.5665493829, 0.1171809585},
  {0.0000000000, 0.5665493829, 0.3162696586, 0.1171809585},
  {0.0000000000, 0.5665493792, 0.1171809548, 0.3162696660},
  {0.0000000000, 0.1171809548, 0.5665493792, 0.3162696660},
  {0.0000000000, 0.1171809641, 0.3162696752, 0.5665493608},
  {0.0000000000, 0.3162696752, 0.1171809641, 0.5665493608},
  {0.0000000000, 0.1063355939, 0.1063355939, 0.7873288122},
  {0.0000000000, 0.1063355939, 0.7873288122, 0.1063355939},
  {0.0000000000, 0.7873288122, 0.1063355939, 0.1063355939},
  {0.0000000000, 0.3333333333, 0.3333333333, 0.3333333333},
  {0.3630696293, 0.3630696293, 0.1369303707, 0.1369303707},
  {0.3630696293, 0.1369303707, 0.1369303707, 0.3630696293},
  {0.3630696293, 0.1369303707, 0.3630696293, 0.1369303707},
  {0.1369303707, 0.3630696293, 0.1369303707, 0.3630696293},
  {0.1369303707, 0.1369303707, 0.3630696293, 0.3630696293},
  {0.1369303707, 0.3630696293, 0.3630696293, 0.1369303707},
  {0.1293440398, 0.1293440398, 0.1293440398, 0.6119678806},
  {0.1293440398, 0.1293440398, 0.6119678806, 0.1293440398},
  {0.1293440398, 0.6119678806, 0.1293440398, 0.1293440398},
  {0.6119678806, 0.1293440398, 0.1293440398, 0.1293440398}
};

/* return the requested number of interpolation points */
#define getintpnts FortranCInterface_GLOBAL_(getintpnts, GETINTPNTS)

void getintpnts(double points[][3], int *npts)
{
  int   i, j;
  DARR4 *pnts;
  
  switch (*npts){
  case 4:
    pnts = pts4;
    break;
  case 10:
    pnts = pts10;
    break;
  case 20:
    pnts = pts20;
    break;
  case 35:
    pnts = pts35;
    break;
  case 56:
    pnts = pts56;
    break;
  case 84:
    pnts = pts84;
    break;
  default:
    fprintf(stderr,"\n%d interpolation points not supported...\n",*npts);
    fprintf(stderr,"\ngive {4,10,20,35,56,84}\nexiting...\n");
    exit(-1);
  }

  /* copy points to the fortran array */
  for (i=0; i < *npts; i++) {
    for (j=0; j < 3; j++) {
      points[i][j] = pnts[i][j];
    }
  }
  
  return;
}

    
      
