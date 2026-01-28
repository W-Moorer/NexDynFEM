#if defined(PARDISO_SOLVER_IS_AVAILABLE)
  // Intel MKL is available
  #include <mkl_cblas.h>
  #include <mkl_types.h>
  #include <mkl_lapack.h>
  #include <mkl_blas.h>
#elif defined(__APPLE__)
  #include <Accelerate/Accelerate.h>
  #ifdef __GNUC__
    #ifndef __clang__
    // The following below applies to Mac OS X, when using the gcc compiler as opposed to clang.
    // On our MacBooks with recent OS X versions, the following headers are required to find CBLAS routines when using gcc (as opposed to clang).
      #if MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_9
        #include </System/Library/Frameworks/Accelerate.framework/Frameworks/vecLib.framework/Headers/cblas.h>
        #include </System/Library/Frameworks/Accelerate.framework/Frameworks/vecLib.framework/Headers/clapack.h>
      #endif
    #endif
  #endif
#else
  // Use OpenBLAS and LAPACK as fallback
  #include <openblas/cblas.h>
  // LAPACK functions are linked via the lapack library
  // Declare external LAPACK functions
  extern "C" {
    // LU decomposition
    void dgetrf_(int* m, int* n, double* a, int* lda, int* ipiv, int* info);
    void dgetri_(int* n, double* a, int* lda, int* ipiv, double* work, int* lwork, int* info);
    void dgetrs_(char* trans, int* n, int* nrhs, double* a, int* lda, int* ipiv, double* b, int* ldb, int* info);
    void sgetrf_(int* m, int* n, float* a, int* lda, int* ipiv, int* info);
    void sgetri_(int* n, float* a, int* lda, int* ipiv, float* work, int* lwork, int* info);
    void sgetrs_(char* trans, int* n, int* nrhs, float* a, int* lda, int* ipiv, float* b, int* ldb, int* info);
    // SVD
    void dgesvd_(char* jobu, char* jobvt, int* m, int* n, double* a, int* lda, double* s, double* u, int* ldu, double* vt, int* ldvt, double* work, int* lwork, int* info);
    void sgesvd_(char* jobu, char* jobvt, int* m, int* n, float* a, int* lda, float* s, float* u, int* ldu, float* vt, int* ldvt, float* work, int* lwork, int* info);
    // Linear solve
    void dgesv_(int* n, int* nrhs, double* a, int* lda, int* ipiv, double* b, int* ldb, int* info);
    void sgesv_(int* n, int* nrhs, float* a, int* lda, int* ipiv, float* b, int* ldb, int* info);
    void dposv_(char* uplo, int* n, int* nrhs, double* a, int* lda, double* b, int* ldb, int* info);
    void dsysv_(char* uplo, int* n, int* nrhs, double* a, int* lda, int* ipiv, double* b, int* ldb, double* work, int* lwork, int* info);
    // Eigenvalues
    void dsyev_(char* jobz, char* uplo, int* n, double* a, int* lda, double* w, double* work, int* lwork, int* info);
    void ssyev_(char* jobz, char* uplo, int* n, float* a, int* lda, float* w, float* work, int* lwork, int* info);
    void dsygv_(int* itype, char* jobz, char* uplo, int* n, double* a, int* lda, double* b, int* ldb, double* w, double* work, int* lwork, int* info);
    void ssygv_(int* itype, char* jobz, char* uplo, int* n, float* a, int* lda, float* b, int* ldb, float* w, float* work, int* lwork, int* info);
    // Generalized eigenvalue problem
    void dgeev_(char* jobvl, char* jobvr, int* n, double* a, int* lda, double* wr, double* wi, double* vl, int* ldvl, double* vr, int* ldvr, double* work, int* lwork, int* info);
    void sgeev_(char* jobvl, char* jobvr, int* n, float* a, int* lda, float* wr, float* wi, float* vl, int* ldvl, float* vr, int* ldvr, float* work, int* lwork, int* info);
    // Least squares
    void dgelsy_(int* m, int* n, int* nrhs, double* a, int* lda, double* b, int* ldb, int* jpvt, double* rcond, int* rank, double* work, int* lwork, int* info);
    void sgelsy_(int* m, int* n, int* nrhs, float* a, int* lda, float* b, int* ldb, int* jpvt, float* rcond, int* rank, float* work, int* lwork, int* info);
  }
  // Define LAPACK function names without trailing underscore for consistency
  #define dgetrf dgetrf_
  #define dgetri dgetri_
  #define dgetrs dgetrs_
  #define sgetrf sgetrf_
  #define sgetri sgetri_
  #define sgetrs sgetrs_
  #define dgesvd dgesvd_
  #define sgesvd sgesvd_
  #define dgesv dgesv_
  #define sgesv sgesv_
  #define dposv dposv_
  #define dsysv dsysv_
  #define dsyev dsyev_
  #define ssyev ssyev_
  #define dsygv dsygv_
  #define ssygv ssygv_
  #define dgeev dgeev_
  #define sgeev sgeev_
  #define dgelsy dgelsy_
  #define sgelsy sgelsy_
#endif

