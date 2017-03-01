/* (C) Oscar. Y. Takeshita 2017 */
#include <vector>
#include <algorithm>
#include <cassert>
#include <random>
typedef unsigned int uint32;

int main (int argc, char *argv[]) {
	std::random_device device;
	std::mt19937 generator(device());
	int N; // interleaver length
	if (argc == 1 ) 
		N = 1024;
	else
		if(argc == 2 )
			N = atoi(argv[1]);
	assert(N>0);

	std::vector<int> inter(N);
	/* S is the spread value */
	/* Typically S<sqrt(N/2) for convergence */
	int S = floor(sqrt((double)N/2.)), p;
	int count, point, trials;
	bool done = false;
	bool found;
	fprintf(stderr,"Trying spread %d\n",S);

	while(!done) {
		/* build pool */
		std::vector <int> pool;
		for(int i = 0; i <N; i++)
			pool.push_back(i);
		/* shuffle */
		std::shuffle(pool.begin(), pool.end(), generator);
		count  = 0;
		trials = 0;
		p      = 0;
		//fprintf(stderr, "trying\n");
		while (count<N) {
			if (p >= pool.size())
				p = 0;
			found = true;
			for(point = count-S; point<count; point++) {
				if((point >-1) && (abs(pool[p]-inter[point])<S)){
					found = false;
					p++;
					break;
				}
			}
			if(found) {
				/* fprintf(stderr, "%d %d\n" ,count, pool[p]);  */
				inter[count] = *(pool.begin()+p);
				/* delete chosen element from the pool */
				pool.erase(pool.begin()+p);
				count++;
				done = (count == N);
			}
			trials++;
			if(trials>100*N) // It hasn't converged. Restart.
				break;
			if(done)
				break;
		}
	}
	/*
	   printf("%d 2\n",N);       // interleaver length and number of constituent codes 
	   for(int i = 0; i< N; i++) // information order for the first constituent code 
	   printf("%d\n",i);
	 */
	for(auto i : inter) { printf("%d\n", i); }; // information order for the second constintuent code
}
