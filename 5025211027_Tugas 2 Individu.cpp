//Danno Denis Dhaifullah 5025211027

#include <bits/stdc++.h>
#include <limits.h>
using namespace std;
#define V 5
#define GENES ABCDE
#define START 0
#define POP_SIZE 10

// Define a structure to represent an individual in the population
struct individual {
	string gnome; // Represents the order in which cities are visited
	int fitness; // The fitness of the individual
};

// Generate a random number between start and end
int rand_num(int start, int end) {
	int r = end - start;
	int rnum = start + rand() % r;
	return rnum;
}

// Check if the character ch is already present in string s
bool repeat(string s, char ch) {
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ch)
			return true;
	}
	return false;
}

string mutatedGene(string gnome) {
	while (true) {
		int r = rand_num(1, V);
		int r1 = rand_num(1, V);
		if (r1 != r) {
			char temp = gnome[r];
			gnome[r] = gnome[r1];
			gnome[r1] = temp;
			break;
		}
	}
	return gnome;
}

// Generate a random genome representing the order in which cities are visited
string create_gnome() {
	string gnome = "0";
	while (true) {
		// If all cities have been added to the genome, add the starting city to the end to complete the tour
		if (gnome.size() == V) {
			gnome += gnome[0];
			break;
		}

		// Generate a random number and add it to the genome if it hasn't already been added
		int temp = rand_num(1, V);
		if (!repeat(gnome, (char)(temp + 48)))
			gnome += (char)(temp + 48);
	}
	return gnome;
}

// Calculate the fitness of an individual based on the given map of distances between cities
int cal_fitness(string gnome) {
	int map[V][V] = { { 0, 2, INT_MAX, 12, 5 },
					{ 2, 0, 4, 8, INT_MAX },
					{ INT_MAX, 4, 0, 3, 3 },
					{ 12, 8, 3, 0, 10 },
					{ 5, INT_MAX, 3, 10, 0 } };
	int f = 0;
	for (int i = 0; i < gnome.size() - 1; i++) {
		if (map[gnome[i] - 48][gnome[i + 1] - 48] == INT_MAX)
			return INT_MAX;
		f += map[gnome[i] - 48][gnome[i + 1] - 48];
	}
	return f;
}

// A function to reduce the temperature during the annealing process
int cooldown(int temp) {
	return (90 * temp) / 100;
}

// A comparison function for sorting the population based on fitness value
bool lessthan(struct individual t1, struct individual t2) {
	return t1.fitness < t2.fitness;
}

// A function to initialize the population with random gnomes and their corresponding fitness values
void TSPUtil(int map[V][V]) {
	int gen = 1; // Generation counter
	int gen_thres = 5; // Maximum number of generations

	vector<struct individual> population; // Population of individuals
	struct individual temp;
	
	// Generate random gnomes and calculate their fitness values
	for (int i = 0; i < POP_SIZE; i++) {
		temp.gnome = create_gnome();
		temp.fitness = cal_fitness(temp.gnome);
		population.push_back(temp);
	}
	
	// Print the initial population
	cout << "\nInitial population: " << endl << "GNOME	 FITNESS VALUE\n";
	for (int i = 0; i < POP_SIZE; i++)
		cout << population[i].gnome << " " << population[i].fitness << endl;
	cout << "\n";

	bool found = false;
	int temperature = 10000; // Starting temperature for simulated annealing
	
	//Loop until temperature drops below 1000 or maximum generations reached
	while (temperature > 1000 && gen <= gen_thres) {
		// Sort the population based on fitness value
		sort(population.begin(), population.end(), lessthan); 
		cout << "\nCurrent temp: " << temperature << "\n";
		vector<struct individual> new_population;
		
		// Generate new individuals by mutating existing ones
		for (int i = 0; i < POP_SIZE; i++) {
			struct individual p1 = population[i];

			while (true) {
				string new_g = mutatedGene(p1.gnome); // Function to generate a mutated version of the gnome
				struct individual new_gnome;
				new_gnome.gnome = new_g;
				new_gnome.fitness = cal_fitness(new_gnome.gnome);
				
				// If the new gnome is better, add it to the new population
				if (new_gnome.fitness <= population[i].fitness) {
					new_population.push_back(new_gnome);
					break;
				} else {
					// Calculate the probability of accepting the new gnome based on the difference in fitness and temperature
					float prob = pow(2.7, -1 * ((float)(new_gnome.fitness - population[i].fitness) / temperature));
					
					// If the probability is greater than 0.5, accept the new gnome and add it to the new population
					if (prob > 0.5) {
						new_population.push_back(new_gnome);
						break;
					}
				}
			}
		}

		temperature = cooldown(temperature); // Reduce the temperature
		population = new_population; // Replace the old population with the new one
		cout << "Generation " << gen << " \n";
		cout << "GNOME	 FITNESS VALUE\n";

		for (int i = 0; i < POP_SIZE; i++)
			cout << population[i].gnome << " " << population[i].fitness << endl;
		gen++;
	}
}

int main() {
	int map[V][V] = { { 0, 2, INT_MAX, 12, 5 },
					{ 2, 0, 4, 8, INT_MAX },
					{ INT_MAX, 4, 0, 3, 3 },
					{ 12, 8, 3, 0, 10 },
					{ 5, INT_MAX, 3, 10, 0 } };
	TSPUtil(map);
}