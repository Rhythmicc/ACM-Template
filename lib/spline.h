#ifndef TK_SPLINE_H
#define TK_SPLINE_H

#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>


// unnamed namespace only because the implementation is in this
// header file and we don't want to export symbols to the obj files
namespace
{
    namespace tk
    {
// band matrix solver
        class band_matrix
        {
        public:
            std::vector< std::vector<double> > m_upper;  // upper band
            std::vector< std::vector<double> > m_lower;  // lower band
        public:
            band_matrix() {};                             // constructor
            band_matrix(int dim);       // constructor
            ~band_matrix() {};                            // destructor
            void resize(int dim);      // init with dim,n_u,n_l
            int dim() const;                             // matrix dimension
            // access operator
            double & operator () (int i, int j);            // write
            double   operator () (int i, int j) const;      // read
            // we can store an additional diogonal (in m_lower)
            double& saved_diag(int i);
            double  saved_diag(int i) const;
            void lu_decompose();
            std::vector<double> r_solve(const std::vector<double>& b) const;
            std::vector<double> l_solve(const std::vector<double>& b) const;
            std::vector<double> lu_solve(const std::vector<double>& b);

        };


// spline interpolation
        class spline{
        public:
            std::vector<double> m_x,m_y;            // x,y coordinates of points
            // interpolation parameters
            // f(x) = a*(x-x_i)^3 + b*(x-x_i)^2 + c*(x-x_i) + y_i
            std::vector<double> m_a,m_b,m_c;        // spline coefficients
            double  m_b0, m_c0;                     // for left extrapol

        public:
            // set default boundary condition to be zero curvature at both ends
            spline(){}
            void set_points(const std::vector<double>& x, const std::vector<double>& y);
            double operator() (double x) const;
        };



// ---------------------------------------------------------------------
// implementation part, which could be separated into a cpp file
// ---------------------------------------------------------------------


// band_matrix implementation
// -------------------------

        band_matrix::band_matrix(int dim){
            resize(dim);
        }
        void band_matrix::resize(int dim){
            m_upper.resize(2);
            m_lower.resize(2);
            for(size_t i=0; i<m_upper.size(); i++) m_upper[i].resize(dim);
            for(size_t i=0; i<m_lower.size(); i++) m_lower[i].resize(dim);
        }
        int band_matrix::dim() const{
            if(m_upper.size()>0) {
                return m_upper[0].size();
            } else {
                return 0;
            }
        }


// defines the new operator (), so that we can access the elements
// by A(i,j), index going from i=0,...,dim()-1
        double & band_matrix::operator () (int i, int j){
            int k=j-i;       // what band is the entry
            // k=0 -> diogonal, k<0 lower left part, k>0 upper right part
            if(k>=0)   return m_upper[k][i];
            else	    return m_lower[-k][i];
        }
        double band_matrix::operator () (int i, int j) const{
            int k=j-i;       // what band is the entry
            // k=0 -> diogonal, k<0 lower left part, k>0 upper right part
            if(k>=0)   return m_upper[k][i];
            else	    return m_lower[-k][i];
        }
// second diag (used in LU decomposition), saved in m_lower
        double band_matrix::saved_diag(int i) const{
            assert( (i>=0) && (i<dim()) );
            return m_lower[0][i];
        }
        double & band_matrix::saved_diag(int i){
            assert( (i>=0) && (i<dim()) );
            return m_lower[0][i];
        }

// LR-Decomposition of a band matrix
        void band_matrix::lu_decompose(){
            int  i_max,j_max;
            int  j_min;
            double x; int n = this->dim();

            // preconditioning
            // normalize column i so that a_ii=1
            for(int i=0; i<n; i++) {
                assert(this->operator()(i,i)!=0.0);
                m_lower[0][i]=1.0/m_upper[0][i];
                j_min=std::max(0,i-1);
                j_max=std::min(n-1,i+1);
                for(int j=j_min; j<=j_max; j++) {
                    int k = j-i;
                    if(k>=0)m_upper[k][i] *= m_lower[0][i];
                    else m_lower[-k][i] *= m_lower[0][i];
                }
                m_upper[0][i]=1.0;          // prevents rounding errors
            }
            // Gauss LR-Decomposition
            for(int k=0; k<this->dim(); k++) {
                i_max=std::min(this->dim()-1,k+1);  // num_lower not a mistake!
                for(int i=k+1; i<=i_max; i++) {
                    assert(this->operator()(k,k)!=0.0);
                    x=-this->operator()(i,k)/this->operator()(k,k);
                    this->operator()(i,k)=-x;                         // assembly part of L
                    j_max=std::min(this->dim()-1,k+1);
                    for(int j=k+1; j<=j_max; j++) {
                        // assembly part of R
                        this->operator()(i,j)=this->operator()(i,j)+x*this->operator()(k,j);
                    }
                }
            }
        }
// solves Ly=b
        std::vector<double> band_matrix::l_solve(const std::vector<double>& b) const{
            assert( this->dim()==(int)b.size() );
            int n = this->dim();
            std::vector<double> x(n);
            int j_start;
            double sum;
            for(int i=0; i<n; i++) {
                sum=0;
                j_start=std::max(0,i-1);
                for(int j=j_start; j<i; j++) sum += m_lower[i-j][i]*x[j];
                x[i]=(b[i]*this->saved_diag(i)) - sum;
            }
            return x;
        }
// solves Rx=y
        std::vector<double> band_matrix::r_solve(const std::vector<double>& b) const{
            assert( this->dim()==(int)b.size() );
            int n = this->dim();
            std::vector<double> x(n);
            int j_stop;
            double sum;
            for(int i=this->dim()-1; i>=0; i--) {
                sum=0;
                j_stop=std::min(n-1,i+1);
                for(int j=i+1; j<=j_stop; j++) sum += this->operator()(i,j)*x[j];
                x[i]=( b[i] - sum ) / this->operator()(i,i);
            }
            return x;
        }

        std::vector<double> band_matrix::lu_solve(const std::vector<double>& b){
            std::vector<double>  x,y;
            this->lu_decompose();
            y=this->l_solve(b);
            x=this->r_solve(y);
            return x;
        }

        void spline::set_points(const std::vector<double>& x, const std::vector<double>& y) {
            assert(x.size() == y.size());
            assert(x.size() > 2);
            m_x = x;
            m_y = y;
            int n = x.size();
            band_matrix A(n);
            std::vector<double> rhs(n);
            for (int i = 1; i < n - 1; i++) {
                A(i, i - 1) = 1.0 / 3.0 * (x[i] - x[i - 1]);
                A(i, i) = 2.0 / 3.0 * (x[i + 1] - x[i - 1]);
                A(i, i + 1) = 1.0 / 3.0 * (x[i + 1] - x[i]);
                rhs[i] = (y[i + 1] - y[i]) / (x[i + 1] - x[i]) - (y[i] - y[i - 1]) / (x[i] - x[i - 1]);
            }
            A(0, 0) = 2.0;
            A(0, 1) = 0.0;
            rhs[0] = 0;
            A(n - 1, n - 1) = 2.0;
            A(n - 1, n - 2) = 0.0;
            rhs[n - 1] = 0;
            m_b = A.lu_solve(rhs);
            m_a.resize(n);
            m_c.resize(n);
            for (int i = 0; i < n - 1; i++) {
                m_a[i] = 1.0 / 3.0 * (m_b[i + 1] - m_b[i]) / (x[i + 1] - x[i]);
                m_c[i] = (y[i + 1] - y[i]) / (x[i + 1] - x[i])
                         - 1.0 / 3.0 * (2.0 * m_b[i] + m_b[i + 1]) * (x[i + 1] - x[i]);
            }
            m_b0 = m_b[0];
            m_c0 = m_c[0];
            double h = x[n - 1] - x[n - 2];
            m_a[n - 1] = 0.0;
            m_c[n - 1] = 3.0 * m_a[n - 2] * h * h + 2.0 * m_b[n - 2] * h + m_c[n - 2];   // = f'_{n-2}(x_{n-1})
        }

        double spline::operator() (double x) const{
            size_t n=m_x.size();
            // find the closest point m_x[idx] < x, idx=0 even if x<m_x[0]
            std::vector<double>::const_iterator it;
            it=std::lower_bound(m_x.begin(),m_x.end(),x);
            int idx=std::max( int(it-m_x.begin())-1, 0);
            double h=x-m_x[idx];
            double interpol;
            if(x<m_x[0]) interpol=(m_b0*h + m_c0)*h + m_y[0];
            else if(x>m_x[n-1])interpol=(m_b[n-1]*h + m_c[n-1])*h + m_y[n-1];
            else interpol=((m_a[idx]*h + m_b[idx])*h + m_c[idx])*h + m_y[idx];
            return interpol;
        }

    } // namespace tk
} // namespace

#endif /* TK_SPLINE_H */