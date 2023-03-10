#include "Prepare.h"
#include "Solution.h"

extern double X[1000], Y[1000];
extern double dimensions[1000][1000];
extern double C[1000];
extern int number_of_trucks;
extern int number_of_cities;
extern int capacity;
extern int N;
extern int N_random;
double antWorst;
double best_distance;
double worst_distance;
double average_distance;

void randomSolution(std::string filename, bool loaderPrint, bool distanceMatrixPrint) {
	double sumBestDistance = 0.0;
	double best_random_distance = std::numeric_limits<double>::max();
	double worst_random_distance = std::numeric_limits<double>::min();
	Loader(filename, loaderPrint);
	createDistanceMatrix(number_of_cities, distanceMatrixPrint);

	for (int i = 0; i < N_random; i++) {

		average_distance = 0;

		std::vector<std::vector<int>> truckRoutesId = random(number_of_trucks, capacity, number_of_cities);
		std::vector<double> truckDistances = calculateResultDstVect(0, truckRoutesId);
		double result = calculateResult("Random", truckDistances);
		sumBestDistance += result;

		if (result < best_random_distance) {
			best_random_distance = result;
		}
		if (result > worst_random_distance) {
			worst_random_distance = result;
		}
	}

	std::cout << "Random best: " << best_random_distance << std::endl;
	std::cout << "Random worst: " << worst_random_distance << std::endl;
	std::cout << "Random avg : " << sumBestDistance / N_random << std::endl;


}

void greedySolution(std::string filename, bool loaderPrint, bool distanceMatrixPrint) {
	Loader(filename, loaderPrint);
	createDistanceMatrix(number_of_cities, distanceMatrixPrint);
	std::vector<std::vector<int>> truckRoutesId = greedy(number_of_trucks, capacity, number_of_cities);
	std::vector<double> truckDistances = calculateResultDstVect(0, truckRoutesId);
	calculateResult("Greedy", truckDistances);
}

void antSolution(std::string filename, bool loaderPrint, bool distanceMatrixPrint) {
	double sumBestDistance = 0.0;
	double sumWorstDistance = 0.0;
	double sumAverageDistance = 0.0;
	Loader(filename, loaderPrint);
	createDistanceMatrix(number_of_cities, distanceMatrixPrint);

	for (int i = 0; i < N; i++) {
		best_distance = std::numeric_limits<double>::max();
		worst_distance = std::numeric_limits<double>::min();
		average_distance = 0;

		antColonyOptimalization(number_of_trucks, capacity, number_of_cities);
		sumBestDistance += best_distance;
		sumWorstDistance += worst_distance;
		sumAverageDistance += average_distance;
		
		std::cout << "best:\t" << best_distance << "\tworst:\t" << worst_distance << "\taverage:\t" << average_distance << std::endl;
	}

	std::cout << "Ant Colony Optimalization best avg: " << sumBestDistance / N << std::endl;
	std::cout << "Ant Colony Optimalization worst avg: " << sumWorstDistance / N << std::endl;
	std::cout << "Ant Colony Optimalization average avg : " << sumAverageDistance / N << std::endl;
}

void saSolution(std::string filename, bool loaderPrint, bool distanceMatrixPrint) {
	Loader(filename, loaderPrint);
	createDistanceMatrix(number_of_cities, distanceMatrixPrint);

	//for (int i = 0; i < 10;  i++) {
		simulated_annealing(false);
	//}
}