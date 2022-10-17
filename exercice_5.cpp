#include <iostream> // terminal input-output
#include <random> // random numbers
#include <fstream> // files input-output
#include <cmath>

void box_muller(double mu, double sigma, int N, std::vector<double> &array) {
    /* This function generates an array of N normally distributed random numbers from 
    a uniform distribution of random numbers using the box-müller transform. */

    std::random_device seed; // generate a random seed (random integer)
    std::mt19937 generator(seed()); // initialise mt19937 random number generator with the seed
    std::uniform_real_distribution<float> uniform(0, 1); // function to generate a uniform real random number between 0 and 1
    double uniform_1;
    double uniform_2;
    double pi = acos(-1);

    for (int i = 0; i < N/2; i+=1) {
        uniform_1 = uniform(generator);
        uniform_2 = uniform(generator);
        array.push_back(sigma*sqrt(-2*log(uniform_1))*cos(2*pi*uniform_2)+mu);
        array.push_back(sigma*sqrt(-2*log(uniform_1))*sin(2*pi*uniform_2)+mu);
    }
}

int sign(float x){
    /* This function is equivalent to the sing(x) math function,
    returns +1 if x is positive and -1 if x is negative. */

    if (signbit(x)) {
        return 1;
    }
    else {
        return -1;
    }
}

double metric(double x, double x_0, double y, double y_0) {
    /* This function calculates distance between two points 
    in the plane (x,y) (x_0,y_0)*/

    return sqrt(pow((x-x_0),2) + pow((y-y_0),2));
}

int main() {

    // Generation of N normally distributed ranodm numbers with mean 0 and standard deviation 1
    int N = 10e4; // number of random numbers to generete
    std::vector<double> normal; // vector for the random numbers
    box_muller(0,1,N,normal); 

    std::random_device seed; // generate a random seed (random integer)
    std::mt19937 generator(seed()); // initialise mt19937 random number generator with the seed
    std::uniform_int_distribution<> rand_int(0, N); // generate a uniformly distributed random number between 0 and N
    
    double dt = 0.1; // time step
    int t_steps = 100; // total number of time steps
    double T = t_steps*dt; // total evolution time
    int M = 1000; // number of particles
    double Gamma[] = {0.1, 1, 3, 10, 30, 100, 300, 1000}; // amplitude of the noise
    std::vector< std::vector<double> > x_out(t_steps+1, std::vector<double> (M, 0)), y_out(t_steps+1, std::vector<double> (M, 0)); // coordinates

    double MSD; // mean-square displacement
    double D; // diffusivity

    // Plot diffusivity as a function of the amplitude of the noise
    std::ofstream file;
    file.open("data_4.dat");  
    // Loop over all amplitude of the noise values
    for (int k = 0; k < sizeof(Gamma)/sizeof(*Gamma); k++) {
        // Calculate trajectory
        for (int j = 0; j < M; j++) {
            for (int t = 0; t < t_steps; t++) { 
                x_out[t+1][j] = sqrt(2*Gamma[k]*dt)*normal[rand_int(generator)]+x_out[t][j];
                y_out[t+1][j] = sqrt(2*Gamma[k]*dt)*normal[rand_int(generator)]+y_out[t][j];
            }
        }

        // calculate the mean-square displacement
        for (int j = 0; j < M; j++) {
            MSD = MSD + pow(metric(x_out[t_steps][j],0,y_out[t_steps][j],0),2);
        }
        MSD = MSD/M;
        // calculate diffusivity
        D = MSD/(4*T);
        file << Gamma[k] << ' ' << D << '\n';
    }
    file.close();
    
    system("gnuplot figure_4.gnu");

    return 0;
}


