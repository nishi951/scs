/*! \page page_installation Installation
 * 
 * \tableofcontents
 * 
 * \section sec-interfaces Interfaces
 * 
 * \subsection installation_in_c Building the source
 *
 * 
 * First, you need to [download SuperSCS](https://github.com/kul-forbes/scs/archive/master.zip)
 * from the [github repo](https://github.com/kul-forbes/scs) of SuperSCS, or use the 
 * command:
 * 
 *     git clone https://github.com/kul-forbes/scs.git
 *     cd scs/
 * 
 * Installation runs as simple as 
 * 
 *     make
 * 
 * Once \c make finishes, the library files will be in <code>out/</code>.
 *  
 * If you want to run the tests, do 
 *
 *     make run-test
 *
 * 
 * If, additionally, you want to run the tests and perform a memory check
 * using [valgrind](http://valgrind.org), do 
 * 
 *     make run-test-mem
 * 
 * 
 * For more advanced options, type in your terminal 
 * 
 *     make help
 * 
 * \subsection sec_matlab MATLAB
 * 
 * To install <code>SuperSCS</code> in MATLAB, you need to build a MEX interface.
 * 
 * Do:
 *
 * \code{.cpp}
 *  cd matlab;
 *  make_scs;
 * \endcode
 * 
 * This should work. If not, please [report an issue](https://github.com/kul-forbes/scs/issues).
 * 
 * 
 * 
 * \subsection sec_cvx_matlab CVX MATLAB
 * 
 * Necessary steps:
 * 
 * - Download and unpack <code>CVX 3.0</code> from [here](http://cvxr.com/cvx/beta/)
 * - You need to do a tiny modification in [<code>cvx/shims/cvx_scs.m</code>](https://gist.github.com/alphaville/13d059b67166997eef9947e91ce5d714)
 *   and comment-out lines 165-175. 
 *   Find the modified file [here](https://gist.github.com/alphaville/13d059b67166997eef9947e91ce5d714).
 * - Navigate to the <code>cvx</code> directory
 * - Run <code>cvx_setup</code>
 * - To use <code>SuperSCS</code>, we call <code>cvx</code> with <code>cvx_solver scs</code>
 *   and setting the parameter <code>do_super_scs</code> to 1.
 * 
 * Here is an example of an LP problem
 * ~~~~~{.m}
 * A(1,1) = 0.3; A(4,1) = -0.5;
 * A(2,2) = 0.7; A(4,2) =  0.9; A(3,3) = 0.2;
 * A = sparse(A);
 * n = size(A,2);
 * b = [0.2; 0.1; -0.1; 0.1];
 * c = [1;-2;-3];
 * 
 * cvx_begin
 *     cvx_solver scs
 *     cvx_solver_settings('eps', 1e-8, 'do_super_scs', 1, 'rho_x', 1,...
 *          'direction', 100, 'memory', 50);
 *     variable x(n);
 *     dual variable y;
 *     minimize( x'*x + c' * x );
 *     subject to
 *          y : A * x <= b;
 * cvx_end
 *~~~~~
 * 
 * We have chosen the SuperSCS mode with \f$\rho_x=1\f$, the restarted Broyden 
 * direction and memory equal to \f$50\f$.
 * 
 * We have set the tolerance to \f$10^{-8}\f$.
 * 
 * In case you encounter any problems, please [report an issue](https://github.com/kul-forbes/scs/issues).
 * 
 * \note This a pre-alpha unstable version, so there might be issues. 
 * 
 * \note For example, <code>cvx_precision</code> is not supported (you have to use 
 * <code>cvx_solver_settings('eps',...)</code>).
 * 
 */