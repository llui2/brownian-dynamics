#include <iostream> // terminal input-output
#include <random> // random numbers
#include <fstream> // files input-output

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

int main() {

    // Generation of N normally distributed ranodm numbers with mean 0 and standard deviation 1    
    int N = 10e4; // number of random numbers to generete
    std::vector<double> normal; // array for the random numbers
    box_muller(0,1,N,normal);

    std::random_device seed; // generate a random seed (random integer)
    std::mt19937 generator(seed()); // initialise mt19937 random number generator with the seed
    std::uniform_int_distribution<> rand_int(0, N); // generate a uniformly distributed random number between 0 and N
    std::uniform_real_distribution<float> uniform_one(-1, 1); // function to generate a uniform real random number between 0 and 1
    
    double dt = 0.1; // time step
    int t_steps = 100; // total number of time steps
    double T = t_steps*dt; // total evolution time
    int M = 1000; // number of particles
    double Gamma = 1; // amplitude of the noise
    int L = 100; // size of the box
    std::vector< std::vector<double> > x_out(t_steps+1, std::vector<double> (M, 0)), y_out(t_steps+1, std::vector<double> (M, 0)); // coord. without PBC
    std::vector< std::vector<double> > x_in(t_steps+1, std::vector<double> (M, 0)), y_in(t_steps+1, std::vector<double> (M, 0)); // coord. with PBC

    // Calculate trajectories with and without PBC
    for (int j = 0; j < M; j++) {
        // random initial position
        x_in[0][j] = uniform_one(generator)*L/2, y_in[0][j] = uniform_one(generator)*L/2;
        x_out[0][j] = uniform_one(generator)*L/2, y_out[0][j] = uniform_one(generator)*L/2;
        for (int t = 0; t < t_steps-1; t++) { 
            x_out[t+1][j] = sqrt(2*Gamma*dt)*normal[rand_int(generator)]+x_out[t][j];
            y_out[t+1][j] = sqrt(2*Gamma*dt)*normal[rand_int(generator)]+y_out[t][j];
            x_in[t+1][j] = sqrt(2*Gamma*dt)*normal[rand_int(generator)]+x_out[t][j];
            y_in[t+1][j] = sqrt(2*Gamma*dt)*normal[rand_int(generator)]+y_out[t][j];
            // PBC check
            if (x_in[t+1][j] < -L/2 ||  x_in[t+1][j] > L/2) {
                x_in[t+1][j] = x_in[t+1][j] + L*sign(x_in[t+1][j]);
            }
            if (y_in[t+1][j] < -L/2 ||  y_in[t+1][j] > L/2) {
                y_in[t+1][j] = y_in[t+1][j] + L*sign(y_in[t+1][j]);
            }
        }
    }
        
    // Plot initial and final configuration
    std::ofstream file;
    file.open("data_3.dat");  
    for (int j = 0; j < M; j++) {
        file << x_in[0][j] << ' ' << y_in[0][j] << '\n';
    }
    file << '\n';
    file << '\n';
    for (int j = 0; j < M; j++) {
        file << x_in[t_steps-1][j] << ' ' << y_in[t_steps-1][j] << '\n';
    }
    file.close();
    
    system("gnuplot figure_3.gnu");

    return 0;
}


