#include "mex.h"
#include "solver.h"
#include <string.h>

vars v;    // stores result

void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] )
{
  params p;
  pwork *mywork;
  mxArray *xm;
  int i = 0; int j = 0; double *ptr;

  int numerr = 0;
  mxArray *outvar;
  mxArray *tinfos;
    /* change number of infofields according to profiling setting */    
#if PROFILING > 0 
#define NINFOFIELDS 15
#else 
#define NINFOFIELDS 14
#endif
    const char *infofields[NINFOFIELDS] = { "pcost",
                                            "dcost",
                                            "pres",
                                            "dres",
                                            "pinf",
                                            "dinf",
                                            "pinfres",
                                            "dinfres",
                                            "gap",
                                            "relgap",   
                                            "r0",
                                            "numerr",
                                            "iter",
                                            "infostring"
#if PROFILING > 0
                                           ,"timing"
#endif
                                           };

#if PROFILING == 1 
#define NTFIELDS 3
    const char *tinfo[NTFIELDS] = {"runtime", "tsolve", "tsetup"};
#endif            
    
#if PROFILING == 2
#define NTFIELDS 8
    const char *tinfo[NTFIELDS] = {"runtime", "tsolve", "tsetup", "tkktcreate", "tkktfactor", "tkktsolve", "torder", "ttranspose"};
#endif

#ifdef MEXARGMUENTCHECKS
  if( !(nrhs == 1) )
  {
       mexErrMsgTxt("scooper only takes 1 argument: scooper(params)");
  }
  if( nlhs > 2 ) mexErrMsgTxt("scooper has up to 2 output arguments only");
#endif

  xm = mxGetField(prhs[0], 0, "a11");
  if (xm == NULL) {
    mexErrMsgTxt("could not find params.a11");
  } else {
    if (!( (mxGetM(xm) == 1) && (mxGetN(xm) == 1) )) mexErrMsgTxt("a11 must be size (1, 1)\n");
    if (mxIsComplex(xm)) mxErrMsgTxt("parameter a11 must be real\n");
    if (!mxIsClass(xm, "double")) mxErrMsgTxt("parameter a11 must be full vector of doubles");
    if (mxIsSparse(xm)) mxErrMsgTxt("parameter a11 must be full vector");
    p.a11 = *mxGetPr(xm);
  }

  xm = mxGetField(prhs[0], 0, "a12");
  if (xm == NULL) {
    mexErrMsgTxt("could not find params.a12");
  } else {
    if (!( (mxGetM(xm) == 1) && (mxGetN(xm) == 1) )) mexErrMsgTxt("a12 must be size (1, 1)\n");
    if (mxIsComplex(xm)) mxErrMsgTxt("parameter a12 must be real\n");
    if (!mxIsClass(xm, "double")) mxErrMsgTxt("parameter a12 must be full vector of doubles");
    if (mxIsSparse(xm)) mxErrMsgTxt("parameter a12 must be full vector");
    p.a12 = *mxGetPr(xm);
  }

  xm = mxGetField(prhs[0], 0, "a21");
  if (xm == NULL) {
    mexErrMsgTxt("could not find params.a21");
  } else {
    if (!( (mxGetM(xm) == 1) && (mxGetN(xm) == 1) )) mexErrMsgTxt("a21 must be size (1, 1)\n");
    if (mxIsComplex(xm)) mxErrMsgTxt("parameter a21 must be real\n");
    if (!mxIsClass(xm, "double")) mxErrMsgTxt("parameter a21 must be full vector of doubles");
    if (mxIsSparse(xm)) mxErrMsgTxt("parameter a21 must be full vector");
    p.a21 = *mxGetPr(xm);
  }

  xm = mxGetField(prhs[0], 0, "a22");
  if (xm == NULL) {
    mexErrMsgTxt("could not find params.a22");
  } else {
    if (!( (mxGetM(xm) == 1) && (mxGetN(xm) == 1) )) mexErrMsgTxt("a22 must be size (1, 1)\n");
    if (mxIsComplex(xm)) mxErrMsgTxt("parameter a22 must be real\n");
    if (!mxIsClass(xm, "double")) mxErrMsgTxt("parameter a22 must be full vector of doubles");
    if (mxIsSparse(xm)) mxErrMsgTxt("parameter a22 must be full vector");
    p.a22 = *mxGetPr(xm);
  }

  xm = mxGetField(prhs[0], 0, "a31");
  if (xm == NULL) {
    mexErrMsgTxt("could not find params.a31");
  } else {
    if (!( (mxGetM(xm) == 1) && (mxGetN(xm) == 1) )) mexErrMsgTxt("a31 must be size (1, 1)\n");
    if (mxIsComplex(xm)) mxErrMsgTxt("parameter a31 must be real\n");
    if (!mxIsClass(xm, "double")) mxErrMsgTxt("parameter a31 must be full vector of doubles");
    if (mxIsSparse(xm)) mxErrMsgTxt("parameter a31 must be full vector");
    p.a31 = *mxGetPr(xm);
  }

  xm = mxGetField(prhs[0], 0, "a32");
  if (xm == NULL) {
    mexErrMsgTxt("could not find params.a32");
  } else {
    if (!( (mxGetM(xm) == 1) && (mxGetN(xm) == 1) )) mexErrMsgTxt("a32 must be size (1, 1)\n");
    if (mxIsComplex(xm)) mxErrMsgTxt("parameter a32 must be real\n");
    if (!mxIsClass(xm, "double")) mxErrMsgTxt("parameter a32 must be full vector of doubles");
    if (mxIsSparse(xm)) mxErrMsgTxt("parameter a32 must be full vector");
    p.a32 = *mxGetPr(xm);
  }

  xm = mxGetField(prhs[0], 0, "a41");
  if (xm == NULL) {
    mexErrMsgTxt("could not find params.a41");
  } else {
    if (!( (mxGetM(xm) == 1) && (mxGetN(xm) == 1) )) mexErrMsgTxt("a41 must be size (1, 1)\n");
    if (mxIsComplex(xm)) mxErrMsgTxt("parameter a41 must be real\n");
    if (!mxIsClass(xm, "double")) mxErrMsgTxt("parameter a41 must be full vector of doubles");
    if (mxIsSparse(xm)) mxErrMsgTxt("parameter a41 must be full vector");
    p.a41 = *mxGetPr(xm);
  }

  xm = mxGetField(prhs[0], 0, "a42");
  if (xm == NULL) {
    mexErrMsgTxt("could not find params.a42");
  } else {
    if (!( (mxGetM(xm) == 1) && (mxGetN(xm) == 1) )) mexErrMsgTxt("a42 must be size (1, 1)\n");
    if (mxIsComplex(xm)) mxErrMsgTxt("parameter a42 must be real\n");
    if (!mxIsClass(xm, "double")) mxErrMsgTxt("parameter a42 must be full vector of doubles");
    if (mxIsSparse(xm)) mxErrMsgTxt("parameter a42 must be full vector");
    p.a42 = *mxGetPr(xm);
  }

  xm = mxGetField(prhs[0], 0, "b1");
  if (xm == NULL) {
    mexErrMsgTxt("could not find params.b1");
  } else {
    if (!( (mxGetM(xm) == 1) && (mxGetN(xm) == 1) )) mexErrMsgTxt("b1 must be size (1, 1)\n");
    if (mxIsComplex(xm)) mxErrMsgTxt("parameter b1 must be real\n");
    if (!mxIsClass(xm, "double")) mxErrMsgTxt("parameter b1 must be full vector of doubles");
    if (mxIsSparse(xm)) mxErrMsgTxt("parameter b1 must be full vector");
    p.b1 = *mxGetPr(xm);
  }

  xm = mxGetField(prhs[0], 0, "b2");
  if (xm == NULL) {
    mexErrMsgTxt("could not find params.b2");
  } else {
    if (!( (mxGetM(xm) == 1) && (mxGetN(xm) == 1) )) mexErrMsgTxt("b2 must be size (1, 1)\n");
    if (mxIsComplex(xm)) mxErrMsgTxt("parameter b2 must be real\n");
    if (!mxIsClass(xm, "double")) mxErrMsgTxt("parameter b2 must be full vector of doubles");
    if (mxIsSparse(xm)) mxErrMsgTxt("parameter b2 must be full vector");
    p.b2 = *mxGetPr(xm);
  }

  xm = mxGetField(prhs[0], 0, "b3");
  if (xm == NULL) {
    mexErrMsgTxt("could not find params.b3");
  } else {
    if (!( (mxGetM(xm) == 1) && (mxGetN(xm) == 1) )) mexErrMsgTxt("b3 must be size (1, 1)\n");
    if (mxIsComplex(xm)) mxErrMsgTxt("parameter b3 must be real\n");
    if (!mxIsClass(xm, "double")) mxErrMsgTxt("parameter b3 must be full vector of doubles");
    if (mxIsSparse(xm)) mxErrMsgTxt("parameter b3 must be full vector");
    p.b3 = *mxGetPr(xm);
  }

  xm = mxGetField(prhs[0], 0, "b4");
  if (xm == NULL) {
    mexErrMsgTxt("could not find params.b4");
  } else {
    if (!( (mxGetM(xm) == 1) && (mxGetN(xm) == 1) )) mexErrMsgTxt("b4 must be size (1, 1)\n");
    if (mxIsComplex(xm)) mxErrMsgTxt("parameter b4 must be real\n");
    if (!mxIsClass(xm, "double")) mxErrMsgTxt("parameter b4 must be full vector of doubles");
    if (mxIsSparse(xm)) mxErrMsgTxt("parameter b4 must be full vector");
    p.b4 = *mxGetPr(xm);
  }

  xm = mxGetField(prhs[0], 0, "c11");
  if (xm == NULL) {
    mexErrMsgTxt("could not find params.c11");
  } else {
    if (!( (mxGetM(xm) == 1) && (mxGetN(xm) == 1) )) mexErrMsgTxt("c11 must be size (1, 1)\n");
    if (mxIsComplex(xm)) mxErrMsgTxt("parameter c11 must be real\n");
    if (!mxIsClass(xm, "double")) mxErrMsgTxt("parameter c11 must be full vector of doubles");
    if (mxIsSparse(xm)) mxErrMsgTxt("parameter c11 must be full vector");
    p.c11 = *mxGetPr(xm);
  }

  xm = mxGetField(prhs[0], 0, "c12");
  if (xm == NULL) {
    mexErrMsgTxt("could not find params.c12");
  } else {
    if (!( (mxGetM(xm) == 1) && (mxGetN(xm) == 1) )) mexErrMsgTxt("c12 must be size (1, 1)\n");
    if (mxIsComplex(xm)) mxErrMsgTxt("parameter c12 must be real\n");
    if (!mxIsClass(xm, "double")) mxErrMsgTxt("parameter c12 must be full vector of doubles");
    if (mxIsSparse(xm)) mxErrMsgTxt("parameter c12 must be full vector");
    p.c12 = *mxGetPr(xm);
  }

  xm = mxGetField(prhs[0], 0, "d");
  if (xm == NULL) {
    mexErrMsgTxt("could not find params.d");
  } else {
    if (!( (mxGetM(xm) == 1) && (mxGetN(xm) == 1) )) mexErrMsgTxt("d must be size (1, 1)\n");
    if (mxIsComplex(xm)) mxErrMsgTxt("parameter d must be real\n");
    if (!mxIsClass(xm, "double")) mxErrMsgTxt("parameter d must be full vector of doubles");
    if (mxIsSparse(xm)) mxErrMsgTxt("parameter d must be full vector");
    p.d = *mxGetPr(xm);
  }

  xm = mxGetField(prhs[0], 0, "e");
  if (xm == NULL) {
    mexErrMsgTxt("could not find params.e");
  } else {
    if (!( (mxGetM(xm) == 1) && (mxGetN(xm) == 1) )) mexErrMsgTxt("e must be size (1, 1)\n");
    if (mxIsComplex(xm)) mxErrMsgTxt("parameter e must be real\n");
    if (!mxIsClass(xm, "double")) mxErrMsgTxt("parameter e must be full vector of doubles");
    if (mxIsSparse(xm)) mxErrMsgTxt("parameter e must be full vector");
    p.e = *mxGetPr(xm);
  }

  mywork = setup(&p);
  if(mywork == NULL) {
    mexErrMsgTxt("Internal problem occurred in ECOS while setting up the problem.\nPlease send a bug report with data to Alexander Domahidi.\nEmail: domahidi@control.ee.ethz.ch");
  }
  int flag = 0;
  flag = solve(mywork, &v);
  const int num_var_names = 2;
  const char *var_names[] = {"x1", "x2"};
  plhs[0] = mxCreateStructMatrix(1, 1, num_var_names, var_names);
  xm = mxCreateDoubleMatrix(1, 1,mxREAL);
  mxSetField(plhs[0], 0, "x1", xm);
  *mxGetPr(xm) = v.x1;

  xm = mxCreateDoubleMatrix(1, 1,mxREAL);
  mxSetField(plhs[0], 0, "x2", xm);
  *mxGetPr(xm) = v.x2;


  if( nlhs == 2 ){
      plhs[1] = mxCreateStructMatrix(1, 1, NINFOFIELDS, infofields);
      
      /* 1. primal objective */
      outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
      *mxGetPr(outvar) = 1.0*((double)mywork->info->pcost);
      mxSetField(plhs[1], 0, "pcost", outvar);
      
      /* 2. dual objective */
      outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
      *mxGetPr(outvar) = (double)mywork->info->dcost;
      mxSetField(plhs[1], 0, "dcost", outvar);
        
      /* 3. primal residual */
      outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
      *mxGetPr(outvar) = (double)mywork->info->pres;
      mxSetField(plhs[1], 0, "pres", outvar);
        
      /* 4. dual residual */
      outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
      *mxGetPr(outvar) = (double)mywork->info->dres;
      mxSetField(plhs[1], 0, "dres", outvar);
      
      /* 5. primal infeasible? */
      outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
      *mxGetPr(outvar) = (double)mywork->info->pinf;
      mxSetField(plhs[1], 0, "pinf", outvar);
      
      /* 6. dual infeasible? */
      outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
      *mxGetPr(outvar) = (double)mywork->info->dinf;
      mxSetField(plhs[1], 0, "dinf", outvar);
      
      /* 7. primal infeasibility measure */
      outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
      *mxGetPr(outvar) = (double)mywork->info->pinfres;
      mxSetField(plhs[1], 0, "pinfres", outvar);
      
      /* 8. dual infeasibility measure */
      outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
      *mxGetPr(outvar) = (double)mywork->info->dinfres;
      mxSetField(plhs[1], 0, "dinfres", outvar);
      
      /* 9. duality gap */
      outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
      *mxGetPr(outvar) = (double)mywork->info->gap;
      mxSetField(plhs[1], 0, "gap", outvar);
      
      /* 10. relative duality gap */
      outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
      *mxGetPr(outvar) = (double)mywork->info->relgap;
      mxSetField(plhs[1], 0, "relgap", outvar);
      
      /* 11. feasibility tolerance??? */
      outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
      *mxGetPr(outvar) = (double)mywork->stgs->feastol;
      mxSetField(plhs[1], 0, "r0", outvar);
      
      /* 12. iterations */
      outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
      *mxGetPr(outvar) = (double)mywork->info->iter;
      mxSetField(plhs[1], 0, "iter", outvar);
      
      /* 13. infostring */
      switch( flag ){
        case ECOS_OPTIMAL:
              outvar = mxCreateString("Optimal solution found");
              break;
          case ECOS_MAXIT:
              outvar = mxCreateString("Maximum number of iterations reached");
              break;
          case ECOS_PINF:
              outvar = mxCreateString("Primal infeasible");
              break;
          case ECOS_DINF:
              outvar = mxCreateString("Dual infeasible");
              break;
          case ECOS_KKTZERO:
              outvar = mxCreateString("Element of D zero during KKT factorization");
              break;
          case ECOS_OUTCONE:
              outvar = mxCreateString("PROBLEM: Mulitpliers leaving the cone");
              break;
          default:
              outvar = mxCreateString("UNKNOWN PROBLEM IN SOLVER");
      }       
      mxSetField(plhs[1], 0, "infostring", outvar);
        
#if PROFILING > 0        
      /* 14. timing information */
      tinfos = mxCreateStructMatrix(1, 1, NTFIELDS, tinfo);
      
      /* 14.1 --> runtime */
      outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
      *mxGetPr(outvar) = (double)mywork->info->tsolve + (double)mywork->info->tsetup;
      mxSetField(tinfos, 0, "runtime", outvar);
        
      /* 14.2 --> setup time */
      outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
      *mxGetPr(outvar) = (double)mywork->info->tsetup;
      mxSetField(tinfos, 0, "tsetup", outvar);
        
      /* 14.3 --> solve time */
      outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
      *mxGetPr(outvar) = (double)mywork->info->tsolve;
      mxSetField(tinfos, 0, "tsolve", outvar);
#if PROFILING > 1        
        
      /* 14.4 time to create KKT matrix */
      outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
      *mxGetPr(outvar) = (double)mywork->info->tkktcreate;
      mxSetField(tinfos, 0, "tkktcreate", outvar);
      /* 14.5 time for kkt solve */
      outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
      *mxGetPr(outvar) = (double)mywork->info->tkktsolve;
      mxSetField(tinfos, 0, "tkktsolve", outvar);
      
      /* 14.6 time for kkt factor */
      outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
      *mxGetPr(outvar) = (double)mywork->info->tfactor;
      mxSetField(tinfos, 0, "tkktfactor", outvar);
        
      /* 14.7 time for ordering */
      outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
      *mxGetPr(outvar) = (double)mywork->info->torder;
      mxSetField(tinfos, 0, "torder", outvar);
      
      /* 14.8 time for transposes */
      outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
      *mxGetPr(outvar) = (double)mywork->info->ttranspose;
      mxSetField(tinfos, 0, "ttranspose", outvar);
#endif       
        
      mxSetField(plhs[1], 0, "timing", tinfos);        
#endif        
        
      /* 15. numerical error? */
      if( (flag == ECOS_NUMERICS) || (flag == ECOS_OUTCONE) || (flag == ECOS_FATAL) ){
          numerr = 1;
      }
      outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
      *mxGetPr(outvar) = (double)numerr;
      mxSetField(plhs[1], 0, "numerr", outvar);        
  }

  cleanup(mywork);
}
